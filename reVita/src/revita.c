#include <vitasdkkern.h>
#include <psp2/motion.h>
#include <stdbool.h>
#include <string.h>
#include "fio/profile.h"
#include "revita.h"
#include "log.h"

#define TTL   500##000
static SceUID mutex_sce_ms_uid = -1;

//Arguments for sceMotionGetState
SceInt64 tick = 0;
SceMotionState sms;
int result; 
bool reset = false;

/*export*/ void reVita_getProfile(Profile* p){
    ksceKernelMemcpyKernelToUser(&p[0], &profile, sizeof(profile));
}

/*export*/ int reVita_setSceMotionState(SceMotionState *pData, int r){
    ksceKernelLockMutex(mutex_sce_ms_uid, 1, NULL);

    ksceKernelMemcpyUserToKernel(&sms, pData, sizeof(SceMotionState)); 
    result = r;
    tick = ksceKernelGetSystemTimeWide();
    int ret = reset;
    if (reset)
        reset = false;

    ksceKernelUnlockMutex(mutex_sce_ms_uid, 1);

    return ret;

}

int revita_sceMotionGetState(SceMotionState *pData){
    int ret = -1;
    ksceKernelLockMutex(mutex_sce_ms_uid, 1, NULL);

    if (tick + TTL > ksceKernelGetSystemTimeWide()){
        memcpy(pData, &sms, sizeof(SceMotionState));
        ret = result;
    }
    
    ksceKernelUnlockMutex(mutex_sce_ms_uid, 1);
    return ret;
}

void revita_sceMotionReset(){
    ksceKernelLockMutex(mutex_sce_ms_uid, 1, NULL);
    reset = true;
    ksceKernelUnlockMutex(mutex_sce_ms_uid, 1);
}

void revita_init(){
    mutex_sce_ms_uid = ksceKernelCreateMutex("reVita_mutex_userspace", 0, 0, NULL);
}
void revita_destroy(){
    if (mutex_sce_ms_uid >= 0)
        ksceKernelDeleteMutex(mutex_sce_ms_uid);
}