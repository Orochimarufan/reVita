#include <vitasdkkern.h>
#include "../../main.h"
#include "../../sysactions.h"
#include "../../common.h"
#include "../../fio/settings.h"
#include "../../fio/theme.h"
#include "../gui.h"
#include "../rendererv.h"
#include "menu.h"

void onButton_main(uint32_t btn){
	if (btn == gui_confirmButton) {
		gui_openMenu(gui_menu->entries[gui_menu->idx].dataUint);
		gui_setIdx(0);
	} else if (btn == gui_cancelButton) {
		gui_close();
		remap_setup();
	} else if (btn == SCE_CTRL_SELECT) {
		settings[SETT_REMAP_ENABLED].v.b = !settings[SETT_REMAP_ENABLED].v.b;
	} else {
		onButton_generic(btn);
	}
}

void onButton_main_submenu(uint32_t btn){
	if (btn == gui_confirmButton) {
		gui_openMenu(gui_menu->entries[gui_menu->idx].dataUint);
		gui_setIdx(0);
	} else {
		onButton_generic(btn);
	}
}

void onButton_main_profile(uint32_t btn){
	switch (btn) {
		case SCE_CTRL_SELECT:
			sysactions_toggleSecondary();
			break;
		default: onButton_main_submenu(btn);
	}
}

void onDrawHeader_main(){
	rendererv_drawStringF(L_0, 3, "     reVita %s", VERSION);
	gui_drawStringFRight(0, 2, isSecondaryProfileLoaded ? "%s (sec)" : titleid, titleid);
	if (settings[SETT_REMAP_ENABLED].v.b){
		rendererv_setColor(theme[COLOR_SUCCESS]);
		rendererv_drawStringF(L_0, 3, "$~$`", VERSION);
	} else {
		rendererv_setColor(theme[COLOR_DANGER]);
		rendererv_drawStringF(L_0, 3, "$@$#", VERSION);
	}
}

void onDrawHeader_main_profile(){
	rendererv_drawString(L_0, 3, gui_menu->name);
	gui_drawStringFRight(0, 2, isSecondaryProfileLoaded ? "%s (sec)" : "%s", titleid);
}

static struct MenuEntry menu_main_profile_entries[] = {
	(MenuEntry){.name = "Remap rules", 		.dataUint = MENU_REMAP_ID, 			.icn = ICON_BTN_CROSS},
	(MenuEntry){.name = "Analog sticks", 	.dataUint = MENU_ANALOG_ID, 		.icn = ICON_LS_UP},
	(MenuEntry){.name = "Touch", 			.dataUint = MENU_TOUCH_ID, 			.icn = ICON_FT},
	(MenuEntry){.name = "Gyroscope", 		.dataUint = MENU_GYRO_ID, 			.icn = ICON_GY_ROLLLEFT},
	(MenuEntry){.name = "Controller",		.dataUint = MENU_CONTROLLER_ID, 	.icn = ICON_BTN_DS4TOUCH},
	(MenuEntry){.name = "Turbo", 			.dataUint = MENU_TURBO_ID, 			.icn = ICON_TURBO_SLOW},
	(MenuEntry){.name = "Compatibility",		.dataUint = MENU_MORE_ID, 			.icn = ICON_CONFIG},
	(MenuEntry){.name = "Manage Profiles", 	.dataUint = MENU_PROFILE_ID, 		.icn = ICON_MENU_STORAGE}};
static struct Menu menu_main_profile = (Menu){
	.id = MENU_MAIN_PROFILE_ID, 
	.parent = MENU_MAIN_ID,
	.name = "$X PROFILE",
	.footer = 	"$kSELECT $nBACK $;SECONDARY     $:CLOSE",
	.onButton = onButton_main_profile,
	.onDrawHeader = onDrawHeader_main_profile,
	.num = SIZE(menu_main_profile_entries), 
	.entries = menu_main_profile_entries};

static struct MenuEntry menu_main_settings_entries[] = {
	(MenuEntry){.name = "Global", 			.dataUint = MENU_SETT_ID, 			.icn = ICON_MENU_SETTINGS},
	(MenuEntry){.name = "Popups", 			.dataUint = MENU_POPUP_ID, 			.icn = ICON_POPUP},
	(MenuEntry){.name = "Hotkeys", 			.dataUint = MENU_HOTKEYS_ID, 		.icn = ICON_CONFIG}};
static struct Menu menu_main_settings = (Menu){
	.id = MENU_MAIN_SETTINGS_ID, 
	.parent = MENU_MAIN_ID,
	.name = "$| SETTINGS",
	.footer = 	"$kSELECT $nBACK                 $:CLOSE",
	.onButton = onButton_main_submenu,
	.num = SIZE(menu_main_settings_entries), 
	.entries = menu_main_settings_entries};

static struct MenuEntry menu_main_developer_entries[] = {
	(MenuEntry){.name = "Show hooks", 		.dataUint = MENU_HOKS_ID, 			.icn = ICON_MENU_BUG},
	(MenuEntry){.name = "Show buttons", 	.dataUint = MENU_DEBUG_BUTTONS_ID, 	.icn = ICON_MENU_BUG}};
static struct Menu menu_main_developer = (Menu){
	.id = MENU_MAIN_DEVELOPER_ID, 
	.parent = MENU_MAIN_ID,
	.name = "$b DEVELOPER",
	.footer = 	"$kSELECT $nBACK                 $:CLOSE",
	.onButton = onButton_main_submenu,
	.num = SIZE(menu_main_developer_entries), 
	.entries = menu_main_developer_entries};

static struct MenuEntry menu_main_entries[] = {
	(MenuEntry){.name = "Profile", 			.dataUint = MENU_MAIN_PROFILE_ID, 	.icn = ICON_BTN_CROSS},
	(MenuEntry){.name = "Settings", 		.dataUint = MENU_MAIN_SETTINGS_ID, 	.icn = ICON_MENU_SETTINGS},
	(MenuEntry){.name = "Save Manager", 	.dataUint = MENU_SAVEMANAGER_ID, 	.icn = ICON_MENU_STORAGE},
	(MenuEntry){.name = "Developer", 		.dataUint = MENU_MAIN_DEVELOPER_ID, .icn = ICON_MENU_BUG},
	(MenuEntry){.name = "Credits", 			.dataUint = MENU_CREDITS_ID, 		.icn = ICON_MENU_CREDITS}};
static struct Menu menu_main = (Menu){
	.id = MENU_MAIN_ID, 
	.name = "$P MAIN MENU",
	.footer = 	"$kSELECT $;TOGGLE             $n$:CLOSE",
	.onButton = onButton_main,
	.onDrawHeader = onDrawHeader_main,
	.num = SIZE(menu_main_entries), 
	.entries = menu_main_entries};

void menu_initMain(){
	gui_registerMenu(&menu_main);
	gui_registerMenu(&menu_main_profile);
	gui_registerMenu(&menu_main_settings);
	gui_registerMenu(&menu_main_developer);
}