#include <app.h>
#include <efl_extension.h>
#include "basicuiwithedc.h"
#include "view/view_common.h"
#include "view_defines.h"

void view_common_get_app_resource(const char *edj_file_in, char *edj_path_out)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(edj_path_out, PATH_MAX, "%s%s", res_path, edj_file_in);
		free(res_path);
	}
}

Evas_Object *view_create_layout(Evas_Object *parent, const char *edj_file_name, const char *edj_group)
{
	char edj_path[4096] = {0, };
	Evas_Object *layout = NULL;

	if (!parent || !edj_file_name || !edj_group) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Wrong input arguments.");
		return NULL;
	}

	view_common_get_app_resource(edj_file_name, edj_path);

	layout = elm_layout_add(parent);
	if (!layout) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Function elm_layout_add() failed.");
		return NULL;
	}

	if (!elm_layout_file_set(layout, edj_path, edj_group)) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Function elm_layout_file_set() failed.");
		evas_object_del(layout);
		return NULL;
	}

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	return layout;
}
