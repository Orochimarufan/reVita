#include <vitasdkkern.h>
#include "../../main.h"
#include "../../common.h"
#include "../../fio/settings.h"
#include "../gui.h"
#include "menu.h"

void onButton_pickAnalog(uint32_t btn){
	enum REMAP_ACTION* actn = gui_menu->dataPtr;
	if (btn == gui_confirmButton) {
		*actn = gui_getEntry()->dataUint;
		if (gui_menu->next == MENU_REMAP_ID){
			if (ui_ruleEditedIdx >= 0) 
				profile.remaps[ui_ruleEditedIdx] = ui_ruleEdited;
			else
				profile_addRemapRule(ui_ruleEdited);
		}
		gui_openMenuNext();
	} else if (btn == gui_cancelButton) {
		gui_openMenuPrev();
	} else {
		onButton_generic(btn);
	}
}

static struct MenuEntry menu_pick_analog_left_entries[] = {
	(MenuEntry){.name = "Move left",	.icn = ICON_LS_LEFT, 	.dataUint = REMAP_ANALOG_LEFT},
	(MenuEntry){.name = "Move right",	.icn = ICON_LS_RIGHT,	.dataUint = REMAP_ANALOG_RIGHT},
	(MenuEntry){.name = "Move up", 		.icn = ICON_LS_UP,	 	.dataUint = REMAP_ANALOG_UP},
	(MenuEntry){.name = "Move down", 	.icn = ICON_LS_DOWN,	.dataUint = REMAP_ANALOG_DOWN}};
static struct Menu menu_pick_analog_left = (Menu){
	.id = MENU_PICK_ANALOG_LEFT_ID, 
	.parent = MENU_REMAP_TRIGGER_TYPE_ID,
	.name = "$L SELECT ANALOG STICK DIRECTION", 
	.footer = 	"$kSELECT                 $nBACK $:CLOSE",
	.onButton = onButton_pickAnalog,
	.num = SIZE(menu_pick_analog_left_entries), 
	.entries = menu_pick_analog_left_entries};
	
static struct MenuEntry menu_pick_analog_right_entries[] = {
	(MenuEntry){.name = "Move left", 	.icn = ICON_RS_LEFT, 	.dataUint = REMAP_ANALOG_LEFT},
	(MenuEntry){.name = "Move right",	.icn = ICON_RS_RIGHT, 	.dataUint = REMAP_ANALOG_RIGHT},
	(MenuEntry){.name = "Move up", 		.icn = ICON_RS_UP, 		.dataUint = REMAP_ANALOG_UP},
	(MenuEntry){.name = "Move down", 	.icn = ICON_RS_DOWN, 	.dataUint = REMAP_ANALOG_DOWN}};
static struct Menu menu_pick_analog_right = (Menu){
	.id = MENU_PICK_ANALOG_RIGHT_ID, 
	.parent = MENU_REMAP_TRIGGER_TYPE_ID,
	.name = "$l SELECT ANALOG STICK DIRECTION", 
	.footer = 	"$kSELECT                 $nBACK $:CLOSE",
	.onButton = onButton_pickAnalog,
	.num = SIZE(menu_pick_analog_right_entries), 
	.entries = menu_pick_analog_right_entries};

void menu_initPickAnalog(){
	gui_registerMenu(&menu_pick_analog_left);
	gui_registerMenu(&menu_pick_analog_right);
}