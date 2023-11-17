#ifndef _EXPORT_H_
#define _EXPORT_H_

#include <psp2/motion.h>

int revita_sceMotionGetState(SceMotionState *pData);
void revita_sceMotionReset();

void revita_init();
void revita_destroy();

#endif