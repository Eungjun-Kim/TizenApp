#include <app.h>
#include <efl_extension.h>
#include <basicuiwithedc.h>
#include "view/view_peer.h"
#include "view/view_client.h"
#include "view/view_common.h"
#include "view/view_list.h"
#include "view.h"
#include "view_defines.h"

static struct view_info {
    Evas_Object *layout;
    Evas_Object *list;
    Evas_Object *item;
    Elm_Genlist_Item_Class *itc_item;
    bool is_peer_check;
} s_info = {
    .layout = NULL,
    .list = NULL,
    .item = NULL,
    .itc_item = NULL,
    .is_peer_check = false,
};

static bool _create_list(void);
static bool _finalize_list(void);
static bool _create_check(Evas_Object *parent);
static bool _set_peer_mode(bool state);
static Evas_Object *item_content_get_cb(void *data, Evas_Object *obj, const char *part);
static void _peer_mode_checked(void *data, Evas_Object *obj, const char *emission, const char *source);
static void _list_item_selected_cb(void *data, Evas_Object *obj, void *event_info);

bool view_peer_mode_create(Evas_Object *parent) {
    s_info.layout = view_create_layout(parent, EDJ_PEER_MODE_FILE_NAME, GROUP_PEER_MODE);
    if(!s_info.layout) {
        dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] s_info.layout == NULL", __FILE__, __LINE__);
        return false;
    }

    elm_layout_signal_callback_add(s_info.layout, SIGNAL_PEER_MODE_OFF, "", _peer_mode_checked, (void*)true);
    elm_layout_signal_callback_add(s_info.layout, SIGNAL_PEER_MODE_ON, "", _peer_mode_checked, (void*)false);

    evas_object_size_hint_weight_set(s_info.layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    return true;
}

void view_peer_mode_finalize(void) {

}

Evas_Object *view_peer_mode_get(void){
    return s_info.layout;
}

static bool _create_list(void) {
    
    return true;
}

static bool _finalize_list(void) {
    return true;
}

static bool _set_peer_mode(bool state){
    s_info.is_peer_check = state;
    if(state){

    }
    else{
        _finalize_list();
    }
    return true;
}

static void _peer_mode_checked(void *data, Evas_Object *obj, const char *emission, const char *source){
    _set_peer_mode((bool)data);
    dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] %s %d", __FILE__, __LINE__, emission, s_info.is_peer_check);
}
