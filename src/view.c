#include <app.h>
#include <efl_extension.h>
#include "basicuiwithedc.h"
#include "view_defines.h"
#include "view.h"
#include "view/view_common.h"
#include "view/view_peer.h"

static struct view_info{
    Evas_Object *win;
    Evas_Object *conform;
    Evas_Object *scroller;
    Evas_Object *layout;
} s_info = {
    .win = NULL,
    .conform = NULL,
    .scroller = NULL,
    .layout = NULL,
};

static void _switch_view_cb(void *data, Evas_Object *obj, const char *emission, const char *source);
static bool _create_scroller(void);
static bool _create_main_view(void);
static void _delete_win_request_cb(void *data, Evas_Object *obj, void *event_info);
static void _back_button_clicked_cb(void *data, Evas_Object *obj, void *event_info);

Eina_Bool view_create(void *user_data){
    s_info.win = view_create_win(PACKAGE);
    if(!s_info.win) {
        dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a window.");
        return EINA_FALSE;
    } 

    s_info.conform = view_create_conformant(s_info.win);
    if(!s_info.conform) {
        dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a conformant.");
        return EINA_FALSE;
    }

    if(!_create_scroller()) {
        dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] Function _create_scroller() failed", __FILE__, __LINE__);
        return EINA_FALSE;
    }

    if(!_create_main_view()) {
        dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] Function _create_main_view*() failed", __FILE__, __LINE__);
        return EINA_FALSE;
    }

    if(!view_peer_mode_create(s_info.layout)) {
        dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] Function view_peer_mode_create() failed", __FILE__, __LINE__);
        return EINA_FALSE;
    }
    elm_layout_content_set(s_info.layout, PART_MAIN_PANEL, view_peer_mode_get());
    evas_object_show(s_info.win);
    return EINA_TRUE;
}

Evas_Object *view_create_win(const char *pkg_name) {
    Evas_Object *win = elm_win_util_standard_add(pkg_name, pkg_name);
    elm_win_conformant_set(win, EINA_TRUE);
    elm_win_indicator_mode_set(win, ELM_WIN_INDICATOR_SHOW);
    elm_win_indicator_opacity_set(win, ELM_WIN_INDICATOR_OPAQUE);
    elm_win_autodel_set(win, EINA_TRUE);

    evas_object_smart_callback_add(win, "delete,request", _delete_win_request_cb, NULL);
    eext_object_event_callback_add(win, EEXT_CALLBACK_BACK, _back_button_clicked_cb, NULL);

    return win;
}

Evas_Object *view_create_conformant(Evas_Object *parent) {
    Evas_Object *conform = NULL;
    if(!parent){
        dlog_print(DLOG_ERROR, LOG_TAG, "Wrong input arguments.");
        return NULL;
    }
    conform = elm_conformant_add(parent);
    if(!conform) {
        dlog_print(DLOG_ERROR, LOG_TAG, "Function elm_conformant, add() failed.");
        return NULL;
    }
    evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(parent, conform);
    elm_object_signal_emit(conform, "elm,state,indicato,overlap", "elm");
    evas_object_show(conform);
    return conform;
}

void view_destroy(void) {
    if(!s_info.win) {
        return;
    }
    evas_object_del(s_info.win);
}

static void _switch_view_cb(void *data, Evas_Object *obj, const char *emission, const char *source) {
    bool to_client_mode = (bool)data;

	Evas_Object *content = elm_layout_content_get(s_info.layout, PART_MAIN_PANEL);
	Evas_Object *switch_to = NULL;

	if (content) {
		elm_layout_content_unset(s_info.layout, PART_MAIN_PANEL);
		evas_object_hide(content);
	}

	if (to_client_mode)
		return;
		//switch_to = view_client_mode_get();
	else
		switch_to = view_peer_mode_get();


	elm_layout_content_set(s_info.layout, PART_MAIN_PANEL, switch_to);
}

static bool _create_scroller(void) {
    s_info.scroller = elm_scroller_add(s_info.conform);
	if (!s_info.scroller) {
		dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] s_info.scroller == NULL", __FILE__, __LINE__);
		return false;
	}

	elm_scroller_bounce_set(s_info.scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(s_info.scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	elm_scroller_movement_block_set(s_info.scroller, ELM_SCROLLER_MOVEMENT_BLOCK_VERTICAL);

	elm_object_content_set(s_info.conform, s_info.scroller);
	return true;
}

static bool _create_main_view(void) {
	s_info.layout = view_create_layout(s_info.conform, EDJ_MAIN_FILE_NAME, GROUP_MAIN);
	if (!s_info.layout) {
		dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] s_info.layout == NULL", __FILE__, __LINE__);
		return false;
	}

	elm_layout_signal_callback_add(s_info.layout, SIGNAL_SWITCH_PEER_MODE_VIEW, "", _switch_view_cb, (void *)false);
	elm_layout_signal_callback_add(s_info.layout, SIGNAL_SWITCH_CLIENT_MODE_VIEW, "", _switch_view_cb, (void *)true);
	evas_object_size_hint_weight_set(s_info.layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	elm_object_content_set(s_info.scroller, s_info.layout);
	return true;
}

static void _delete_win_request_cb(void *data, Evas_Object *obj, void *event_info) {
    ui_app_exit();
}

static void _back_button_clicked_cb(void *data, Evas_Object *obj, void *event_info) {
    elm_win_lower(s_info.win);
}
