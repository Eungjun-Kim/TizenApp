#ifndef _VIEW_DEFINES_H_
#define _VIEW_DEFINES_H_

#define STATE_DEFAULT "default"
#define STATE_PRESSED "pressed"
#define STATE_INACTIVE "inactive"

#define EDJ_MAIN_FILE_NAME "edje/main.edj"
#define EDJ_PEER_MODE_FILE_NAME "edje/peer_mode.edj"
#define EDJ_CLIENT_MODE_FILE_NAME "edje/client_mode.edj"
#define EDJ_WRITE_POPUP_FILE_NAME "edje/write_popup.edj"
#define EDJ_SEARCH_POPUP_FILE_NAME "edje/search_popup.edj"

#define GROUP_MAIN "main"
#define GROUP_PEER_MODE "peer"
#define GROUP_CLIENT_MODE "client"
#define GROUP_WRITE_POPUP "write,popup"
#define GROUP_SEARCH_POPUP "search,popup"

#define PART_MAIN_PANEL "part,main,panel"
#define PART_MAIN_BACKGROUND "part,main,background"
#define PART_MAIN_PREF_CHECKBOX_PANEL "part,main,pref,checkbox,panel"
#define PART_MAIN_PREF_LIST_PANEL_BACKGROUND "part,main,pref,list,panel,background"
#define PART_PEER_MODE_BACKGROUND "part,peer,background"
#define PART_CLIENT_MODE_BACKGROUND "part,client,background"

#define MAIN_BACKGROUND_MARGIN_H 0.02
#define MAIN_BACKGROUND_MARGIN_V 0.01
#define MAIN_PREF_TOOLBAR_BUTTONS_PANEL_TOP 0.0391
#define MAIN_PREF_TOOLBAR_BUTTONS_PANEL_HEIGHT 0.15
#define MAIN_PREF_CHECKBOX_PANEL_TOP (MAIN_PREF_TOOLBAR_BUTTONS_PANEL_TOP+MAIN_PREF_TOOLBAR_BUTTONS_PANEL_HEIGHT)
#define MAIN_PREF_CHECKBOX_PANEL_HEIGHT (MAIN_PREF_CHECKBOX_PANEL_TOP+0.4)
#define MAIN_PREF_LIST_PANEL_TOP (MAIN_PREF_CHECKBOX_PANEL_HEIGHT)

#define SIGNAL_SWITCH_PEER_MODE_VIEW "signal,mode,view,peer"
#define SIGNAL_SWITCH_CLIENT_MODE_VIEW "signal,mode,view,client"
#define SIGNAL_PEER_MODE_ON "signal,peer,on"
#define SIGNAL_PEER_MODE_OFF "signal,client,off"
#define SIGNAL_CLIENT_WRITE "signal,client,write"
#define SIGNAL_CLIENT_READ "signal,client,read"

#define IMAGE_ARROW_DOWN "../res/images/button3.png"
#define IMAGE_ARROW_UP "../res/images/button4.png"

#endif