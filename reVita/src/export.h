#ifndef _REMAPSV_H_
#define _REMAPSV_H_

#include "fio/profile.h"
#include <psp2/motion.h>

/*export*/ extern void reVita_getProfile(Profile* p);
/*export*/ extern int reVita_setSceMotionState(SceMotionState *pData, int r);

#endif