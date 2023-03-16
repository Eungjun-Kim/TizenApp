#include <app.h>
#include <efl_extension.h>
#include "basicuiwithedc.h"
#include "view/view_client.h"
#include "view/view_peer.h"
#include "view/view_common.h"
#include "view_defines.h"

static struct view_info {
    Evas_Object *layout;
    Evas_Object *list;
    //Evas_Object *w_popup;
    //Evas_Object *submit_btn;
    //Evas_Object *cancle_btn;
} s_info = {
    .layout = NULL,
    .list = NULL,
    //.w_popup = NULL,
    //.submit_btn = NULL,
    //.cancle_btn = NULL,
};

static struct popup_info {
    Evas_Object *popup;
    Evas_Object *submit_btn;
    Evas_Object *cancle_btn;
} p_info = {
    .popup = NULL,
    .submit_btn = NULL,
    .cancle_btn = NULL,
};

Evas_Object *button;

static void _write_button_click_cb(void *data, Evas_Object *obj, const char *emission, const char *source);
static void _read_button_clicked_cb(void *data, Evas_Object *obj, const char *emission, const char *source);
static bool _create_write_popup(Evas_Object *parent);
static void popup_block_clicked_cb(void *data, Evas_Object *obj, void *event_info);


bool view_client_mode_create(Evas_Object *parent) {
    s_info.layout = view_create_layout(parent, EDJ_CLIENT_MODE_FILE_NAME, GROUP_CLIENT_MODE);
    if(!s_info.layout) {
        dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] s_info.layout == NULL", __FILE__, __LINE__);
        return false;
    }
    elm_layout_signal_callback_add(s_info.layout, SIGNAL_CLIENT_WRITE, "", _write_button_click_cb, NULL);
    elm_layout_signal_callback_add(s_info.layout, SIGNAL_CLIENT_READ, "", _read_button_clicked_cb, NULL);
    return true;
}

void view_client_mode_finalize(void) {

}

Evas_Object *view_client_mode_get(void) {
    return s_info.layout;
}

static bool _create_write_popup(Evas_Object *parent) {
    p_info.popup = elm_popup_add(parent);
    if(!p_info.popup) {
        dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] p_info.popup == NULL", __FILE__, __LINE__);
        return false;
    }
    elm_popup_align_set(p_info.popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
    evas_object_size_hint_weight_set(p_info.popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    
    elm_object_part_text_set(p_info.popup, "title,text", "Title");
    elm_object_text_set(p_info.popup, "This Popup has title area, content area and action area set, action area has two buttons OK and Cancel.");

    /*s_info.submit_btn = elm_button_add(s_info.w_popup);
    elm_object_style_set(s_info.submit_btn, "popup");
    elm_object_text_set(s_info.submit_btn, "OK");
    elm_object_part_content_set(s_info.w_popup, PART_WRITE_POPUP_SUBMIT_BUTTON, s_info.submit_btn);

    s_info.submit_btn = elm_button_add(s_info.w_popup);
    elm_object_style_set(s_info.submit_btn, "popup");
    elm_object_text_set(s_info.submit_btn, "Cancel");
    elm_object_part_content_set(s_info.w_popup, "CANCLE", s_info.submit_btn);*/

    p_info.submit_btn = elm_button_add(p_info.popup);
    elm_object_style_set(p_info.submit_btn, "popup");
    elm_object_text_set(p_info.submit_btn, "OK");
    elm_object_part_content_set(p_info.popup, "button1", p_info.submit_btn);

    p_info.cancle_btn = elm_button_add(p_info.popup);
    elm_object_style_set(p_info.cancle_btn, "popup");
    elm_object_text_set(p_info.cancle_btn, "CANCLE");
    elm_object_part_content_set(p_info.popup, "button2", p_info.cancle_btn);
/*
    button = elm_button_add(s_info.w_popup);
    elm_object_style_set(button, "popup");
    elm_object_text_set(button, "Cancel");
    elm_object_part_content_set(s_info.w_popup, "button2", button);
*/
    eext_object_event_callback_add(p_info.popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
    evas_object_smart_callback_add(p_info.popup, "block,clicked", popup_block_clicked_cb, NULL);

    evas_object_show(p_info.popup);
    return true;
}

static void _write_button_click_cb(void *data, Evas_Object *obj, const char *emission, const char *source) {
    if(!_create_write_popup(s_info.layout)) {
        dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] _create_write_popup() failed", __FILE__, __LINE__);
        return;
    }
}
static void _read_button_clicked_cb(void *data, Evas_Object *obj, const char *emission, const char *source) {

}


static void popup_block_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_popup_dismiss(obj);
}
