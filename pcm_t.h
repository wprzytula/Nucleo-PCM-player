#ifndef DAC_PCM_T_H
#define DAC_PCM_T_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    size_t sample_rate;
    size_t bytes_per_sample;
    size_t data_len;
    uint8_t const* data;
} pcm_t;

#endif //DAC_PCM_T_H
