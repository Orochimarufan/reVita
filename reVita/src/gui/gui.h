#ifndef _GUI_H_
#define _GUI_H_
#include "../remap.h"
#include "img/icons-font.h"
#include "../fio/profile.h"
#include <psp2common/display.h>

#define UI_WIDTH            480
#define UI_HEIGHT           272
#define HEADER_HEIGHT		(CHA_H + 6)
#define BOTTOM_OFFSET		5
#define L_0    				5		//Left margin for menu
#define L_1    				18		
#define L_2    				36

#define HEADER_TYPE         -1

#define TTL_POPUP_SHORT		2##000##000
#define TTL_POPUP_LONG		2##000##000

enum MENU_ID{
	MENU_MAIN_ID = 0,
	MENU_MAIN_PROFILE_ID,
	MENU_MAIN_SETTINGS_ID,
	MENU_MAIN_DEVELOPER_ID,
	MENU_ANALOG_ID,
	MENU_TOUCH_ID,
	MENU_TURBO_ID,
	MENU_GYRO_ID,
	MENU_CONTROLLER_ID,
	MENU_MORE_ID,
	MENU_HOKS_ID,
	MENU_DEBUG_BUTTONS_ID,
	MENU_SETT_ID,
	MENU_POPUP_ID,
	MENU_HOTKEYS_ID,
	MENU_CREDITS_ID,
	MENU_PROFILE_ID,
	MENU_SAVEMANAGER_ID,

	MENU_PICK_BUTTON_ID,
	MENU_PICK_ANALOG_LEFT_ID,
	MENU_PICK_ANALOG_RIGHT_ID,
	MENU_PICK_TOUCH_POINT_ID,
	MENU_PICK_TOUCH_ZONE_ID,
	MENU_PICK_TOUCH_SWIPE_ID,

	MENU_REMAP_ID,
	MENU_REMAP_TRIGGER_TYPE_ID,
	MENU_REMAP_TRIGGER_TOUCH_FRONT_ID,
	MENU_REMAP_TRIGGER_TOUCH_BACK_ID,
	MENU_REMAP_TRIGGER_GYRO_ID,
	MENU_REMAP_EMU_TYPE_ID,
	MENU_REMAP_EMU_TOUCH_FRONT_ID,
	MENU_REMAP_EMU_TOUCH_BACK_ID,
	MENU_REMAP_EMU_SYSACTIONS_ID,
	MENU_REMAP_EMU_REMAPSV_ID,
	MENU_ID__NUM
};

struct Menu;
struct MenuEntry;

typedef void (*onButtonF)(uint32_t btn);
typedef void (*onInputF)(SceCtrlData *ctrl);
typedef void (*onDrawF)(uint32_t menuY);
typedef void (*onDrawFBF)();
typedef void (*onDrawHeader)();
typedef void (*onBuildF)(struct Menu* m);
typedef struct Menu{
	enum MENU_ID id;
	enum MENU_ID prev;
	enum MENU_ID next;
	enum MENU_ID parent;

	uint8_t idx;
	char* name;
	char* footer;
	bool noIndent;

	uint8_t num;
	struct MenuEntry* entries;

	onButtonF onButton;
	onInputF onInput;
	onDrawF onDraw;
	onDrawFBF onDrawFB;
	onDrawHeader onDrawHeader;
	onBuildF onBuild;
	union {
		int32_t dataInt;
		uint32_t dataUint;
		void* dataPtr;
	};
}Menu;

typedef void (*onDrawEntryF)(int x, int y, struct MenuEntry* me, bool isSelected, bool hasHeaders);
typedef struct MenuEntry{
	char* name;
	int32_t type;
	ICON_ID icn;
	onDrawEntryF onDraw;

	int32_t dataInt;
	uint32_t dataUint;
	ProfileEntry* dataPE;
	ProfileEntry* dataPEButton;
	char** dataPEStr;
} MenuEntry;

extern uint32_t gui_confirmButton;
extern uint32_t gui_cancelButton;
extern uint8_t gui_isOpen;
extern uint8_t gui_lines;
extern struct Menu* gui_menu;
extern Menu* menus[MENU_ID__NUM];

extern struct RemapRule ui_ruleEdited; //Rule currently edited
extern int ui_ruleEditedIdx;
extern int64_t tickUIOpen;
extern int64_t tickUIClose;
extern int64_t tickMenuOpen;

extern const char* STR_BTN_S[HW_BUTTONS_NUM];
extern const char* STR_YN[2];
extern const char* STR_SWITCH[2];

void gui_drawTouchPointer(uint32_t panel, TouchPoint* tp);
void gui_drawTouchPointerN(uint32_t panel, TouchPoint* tp, char* str);
void gui_generateBtnComboName(char* str, uint32_t btns, int max);
int gui_calcStartingIndex(int idx, int entriesNum, int screenEntries, int bottomOffset);
void gui_setColorHeader(uint8_t isCursor);
void gui_setColor(uint8_t isCursor, uint8_t isDefault);
void gui_setColorExt(uint8_t isCursor, uint8_t isDefault, uint8_t isDisabled);
void gui_drawStringFRight(int x, int y, const char *format, ...);
void gui_drawScroll(int8_t up, int8_t down);
void gui_drawFullScroll(int8_t up, int8_t down, float pos);
void gui_drawEditPointer(uint16_t x, uint16_t y);
void gui_updateEmulatedTouch(SceTouchPortType panel, EmulatedTouch et, SceTouchData pData);

struct MenuEntry* gui_getEntry();
void gui_registerMenu(Menu* m);
void gui_openMenu(enum MENU_ID id);void gui_openMenuSmart(enum MENU_ID id, enum MENU_ID prevId, enum MENU_ID nextId);
void gui_openMenuSmartU(enum MENU_ID id, enum MENU_ID prevId, enum MENU_ID nextId, uint32_t dataUint);
void gui_openMenuSmartI(enum MENU_ID id, enum MENU_ID prevId, enum MENU_ID nextId, int32_t dataInt);
void gui_openMenuSmartPtr(enum MENU_ID id, enum MENU_ID prevId, enum MENU_ID nextId, void* p);
void gui_openMenuPrev();
void gui_openMenuNext();
void gui_openMenuParent();
void gui_nextEntry();
void gui_prevEntry();
void gui_setIdx(int i);

void gui_input(SceCtrlData *ctrl);
void gui_draw(const SceDisplayFrameBuf *pParam);
void gui_open();
void gui_close();

void gui_popupShow(char* header, char* message, uint ttl);
void gui_popupShowSuccess(char* header, char* message, uint ttl);
void gui_popupShowWarning(char* header, char* message, uint ttl);
void gui_popupShowDanger(char* header, char* message, uint ttl);
void gui_popupHide();

void gui_init();
void gui_destroy();

#endif