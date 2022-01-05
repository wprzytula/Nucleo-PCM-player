#ifndef DAC_PCM_H
#define DAC_PCM_H

#include <stddef.h>
#include <stdint.h>
#include "pcm_t.h"

#define PCM_len 4

pcm_t PCM_arr[PCM_len];

extern pcm_t PCM_JAZGOT;
extern pcm_t PCM_JESZCZE_GORSZY_JAZGOT;
extern pcm_t PCM_MARIO;
extern pcm_t PCM_UNDERTALE;

static void init_PCM_arr() {
    PCM_arr[0] = PCM_JAZGOT;
    PCM_arr[1] = PCM_JESZCZE_GORSZY_JAZGOT;
    PCM_arr[2] = PCM_MARIO;
    PCM_arr[3] = PCM_UNDERTALE;
}

pcm_t const* PCM = PCM_arr;

static void change_PCM(int direction) {
    static size_t idx = PCM_len - 1;
    if (direction < 0 && idx == 0)
        idx = PCM_len;
    idx = (idx + direction) % PCM_len;
    PCM = PCM_arr + idx;
}

#endif //DAC_PCM_H
