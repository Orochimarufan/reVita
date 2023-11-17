#ifndef DSMotionLibrary_H
#define DSMotionLibrary_H

#include <psp2/motion.h>

int dsMotionStartSampling();
int dsMotionGetState(SceMotionState *ms);
int dsMotionGetSensorState(SceMotionSensorState *sensorState, int numRecords);

#endif
