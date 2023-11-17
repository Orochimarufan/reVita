#ifndef _THEME_H_
#define _THEME_H_

#include <stdint.h>
#include <stdbool.h>

enum THEME_ID{
	THEME_DARK,
	THEME_LIGHT,
    THEME__NUM
};
enum THEME_COLOR_ID{
	COLOR_DEFAULT,
	COLOR_HEADER,
	COLOR_ACTIVE,
	COLOR_DANGER,
	COLOR_SUCCESS,
	COLOR_CURSOR_DEFAULT,
	COLOR_CURSOR_HEADER,
	COLOR_CURSOR_ACTIVE,
	COLOR_CURSOR_DANGER,
	COLOR_BG_HEADER,
	COLOR_BG_BODY,
	COLOR_TOUCH_FRONT,
	COLOR_TOUCH_BOTTOM,
	COLOR_TOUCH_SHADOW,
    THEME_COLOR__NUM
};
extern uint32_t theme[THEME_COLOR__NUM];

enum THEME_ID theme_findIdByKey(char* n);
extern char* THEME_STR[THEME__NUM];

void theme_reset();

bool theme_save(int themeId);
bool theme_load(int themeId);

void theme_init();
void theme_destroy();

#endif