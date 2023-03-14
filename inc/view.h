#ifndef _VIEW_H_
#define _VIEW_H_

#include <Evas.h>
#include <Elementary.h>

Eina_Bool view_create(void *user_data);
Evas_Object *view_create_win(const char *pkg_name);
Evas_Object *view_create_conformant(Evas_Object *parent);
void view_destory(void);

#endif
