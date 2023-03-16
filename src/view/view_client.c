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
    Evas_Object *w_popup;
    Evas_Object *submit_btn;
    Evas_Object *cancle_btn;
} s_info = {
    .layout = NULL,
    .list = NULL,
    .w_popup = NULL,
    .submit_btn = NULL,
    .cancle_btn = NULL,
};

static void _write_button_click_cb(void *data, Evas_Object *obj, const char *emission, const char *source);
static void _read_button_clicked_cb(void *data, Evas_Object *obj, const char *emission, const char *source);
static bool _create_write_popup(Evas_Object *parent);

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

static void _write_button_click_cb(void *data, Evas_Object *obj, const char *emission, const char *source) {

}
static void _read_button_clicked_cb(void *data, Evas_Object *obj, const char *emission, const char *source) {

}