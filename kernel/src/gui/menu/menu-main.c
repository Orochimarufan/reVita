#include <vitasdkkern.h>
#include "../../main.h"
#include "../../fio/settings.h"
#include "../gui.h"

void onButton_main(uint32_t btn){
	switch (btn) {
		case SCE_CTRL_CROSS:
			gui_openMenu(gui_menu->entries[gui_menu->idx].dataUint);
			gui_setIdx(0);
			break;
		case SCE_CTRL_CIRCLE:
			gui_close();
			settings_save();
			if (settings[0].v.b)
				profile_save(titleid);
			remap_setup();
			break;
		case SCE_CTRL_SELECT:
			settings[SETT_REMAP_ENABLED].v.b = !settings[SETT_REMAP_ENABLED].v.b;
			break;
		default: onButton_generic(btn);
	}
}

#define MENU_MAIN_NUM 10
static struct MenuEntry menu_main_entries[MENU_MAIN_NUM] = {
	(MenuEntry){.name = "Remap rules", 		.dataUint = MENU_REMAP_ID, 		.icn = ICON_BTN_CROSS},
	(MenuEntry){.name = "Analog sticks", 	.dataUint = MENU_ANALOG_ID, 	.icn = ICON_LS_UP},
	(MenuEntry){.name = "Touch", 			.dataUint = MENU_TOUCH_ID, 		.icn = ICON_FT},
	(MenuEntry){.name = "Gyroscope", 		.dataUint = MENU_GYRO_ID, 		.icn = ICON_GY_ROLLLEFT},
	(MenuEntry){.name = "External gamepads",.dataUint = MENU_CONTROLLER_ID, .icn = ICON_BTN_DS4TOUCH},
	(MenuEntry){.name = "Show hooks", 		.dataUint = MENU_HOKS_ID, 		.icn = ICON_MENU_BUG},
	// (MenuEntry){.name = "$b Show buttons", 	.dataUint = MENU_DEBUG_BUTTONS_ID, .icn = ICON_MENU_BUG},
	(MenuEntry){.name = "Settings", 		.dataUint = MENU_SETT_ID, 		.icn = ICON_MENU_SETTINGS},
	(MenuEntry){.name = "Hotkeys", 			.dataUint = MENU_HOTKEYS_ID, 	.icn = ICON_CONFIG},
	(MenuEntry){.name = "Profiles", 		.dataUint = MENU_PROFILE_ID, 	.icn = ICON_MENU_STORAGE},
	(MenuEntry){.name = "Credits", 			.dataUint = MENU_CREDITS_ID, 	.icn = ICON_MENU_CREDITS}};
static struct Menu menu_main = (Menu){
	.id = MENU_MAIN_ID, 
	.num = MENU_MAIN_NUM, 
	.name = "$P MAIN MENU",
	.footer = "$;TOGGLE REMAPS                by Mer1e",
	.onButton = onButton_main,
	.entries = menu_main_entries};

void menu_initMain(){
	gui_registerMenu(&menu_main);
}