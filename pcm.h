#ifndef DAC_PCM_H
#define DAC_PCM_H

#include <stddef.h>
#include <stdint.h>
#include "pcm_t.h"

uint8_t const PCM2_data[] = {
        0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x80,0x80,0x80,0x81,0x80,0x80,0x80,0x7f,0x7f,0x80,0x7e,0x7d,0x7d,0x7b,0x7c,0x7d,0x7b,0x7b,0x7c,0x7d,0x7d,0x7d,0x7d,0x7e,0x7f,0x7f
        ,0x7e,0x7f,0x7f,0x7e,0x7e,0x7d,0x7d,0x7e,0x7e,0x7e,0x7f,0x80,0x81,0x82,0x84,0x86,0x87,0x88,0x89,0x8a,0x89,0x89,0x88,0x87,0x85,0x83,0x80,0x7d,0x7a,0x79,0x76,0x73
        ,0x70,0x6d,0x69,0x65,0x61,0x5c,0x5a,0x56,0x54,0x57,0x5e,0x72,0x82,0x86,0x94,0xa3,0xad,0xb4,0xac,0xa1,0x9d,0x93,0x84,0x73,0x69,0x67,0x69,0x6d,0x75,0x88,0x9b,0xa6
        ,0xae,0xb4,0xb5,0xb1,0xa5,0x96,0x8b,0x80,0x74,0x6d,0x6b,0x6f,0x77,0x7c,0x82,0x8a,0x90,0x8c,0x86,0x7c,0x6e,0x5b,0x42,0x2c,0x24,0x20,0x35,0x5e,0x62,0x77,0xa7,0xbb
        ,0xd2,0xd8,0xbc,0xb9,0xb1,0x8c,0x67,0x4d,0x45,0x44,0x4a,0x55,0x63,0x87,0xa8,0xb1,0xb8,0xbe,0xba,0xb2,0x9d,0x7a,0x68,0x63,0x55,0x4f,0x56,0x66,0x7d,0x8c,0x97,0xae
        ,0xbd,0xbb,0xb4,0xa9,0x9c,0x95,0x82,0x6f,0x6a,0x67,0x63,0x66,0x6a,0x6a,0x6c,0x68,0x5b,0x51,0x40,0x28,0x22,0x3f,0x64,0x5c,0x6a,0x94,0xb0,0xcf,0xcc,0xae,0xb5,0xb0
        ,0x88,0x66,0x4d,0x48,0x4f,0x55,0x58,0x68,0x90,0xaa,0xab,0xaf,0xb3,0xb5,0xb2,0x97,0x7d,0x7d,0x7a,0x6c,0x67,0x6e,0x81,0x92,0x8d,0x92,0xa7,0xab,0xa7,0xa1,0x94,0x91
        ,0x8b,0x70,0x63,0x64,0x5a,0x52,0x48,0x3b,0x3b,0x38,0x30,0x3d,0x76,0x8f,0x80,0x9c,0xb5,0xc2,0xce,0xa9,0x90,0xa0,0x8b,0x6b,0x5b,0x54,0x65,0x76,0x81,0x89,0x9e,0xbb
        ,0xb7,0xa0,0x97,0x89,0x7b,0x6f,0x5b,0x5e,0x72,0x79,0x85,0x95,0x9f,0xab,0xa5,0x93,0x95,0x92,0x86,0x82,0x7f,0x83,0x90,0x91,0x8d,0x91,0x8e,0x84,0x7c,0x6a,0x59,0x4b
        ,0x32,0x1a,0x08,0x00,0x21,0x7a,0x96,0x87,0xb5,0xd9,0xec,0xe8,0x9e,0x80,0x95,0x6a,0x3e,0x2c,0x35,0x65,0x84,0x8f,0xa0,0xc0,0xde,0xc9,0x9c,0x82,0x69,0x55,0x3c,0x2a
        ,0x40,0x6c,0x83,0x97,0xad,0xbf,0xca,0xb2,0x8f,0x88,0x81,0x6f,0x69,0x68,0x79,0x95,0x98,0x9a,0xa4,0xa1,0x95,0x8b,0x79,0x6b,0x60,0x47,0x31,0x27,0x18,0x15,0x24,0x4f
        ,0xa4,0xb1,0xa1,0xd3,0xe6,0xe0,0xc9,0x82,0x70,0x75,0x43,0x2f,0x3a,0x51,0x87,0xa6,0xb3,0xca,0xdb,0xdb,0xb6,0x82,0x67,0x4c,0x3a,0x2e,0x33,0x5b,0x86,0xa2,0xb4,0xc1
        ,0xc7,0xc3,0xa0,0x7e,0x79,0x76,0x6e,0x74,0x7c,0x90,0xa9,0xa6,0xa1,0xa1,0x95,0x89,0x7d,0x67,0x5f,0x5d,0x53,0x49,0x42,0x3b,0x35,0x25,0x1f,0x43,0x98,0xb5,0x9a,0xbc
        ,0xdf,0xe0,0xce,0x81,0x59,0x6c,0x4f,0x37,0x3d,0x4e,0x87,0xb4,0xb7,0xbe,0xc5,0xc5,0xa7,0x69,0x44,0x36,0x35,0x3b,0x35,0x56,0x96,0xb6,0xbe,0xb9,0xb6,0xb8,0x97,0x64
        ,0x5f,0x6c,0x77,0x86,0x8d,0x9d,0xbb,0xbc,0xa9,0xa0,0x8c,0x7f,0x73,0x5b,0x54,0x61,0x5f,0x59,0x50,0x46,0x41,0x37,0x21,0x20,0x3a,0x8f,0xd0,0xa5,0xaf,0xe1,0xdf,0xcd
        ,0x8d,0x44,0x5b,0x5c,0x40,0x4c,0x56,0x81,0xc4,0xcd,0xbe,0xb8,0xb0,0xa4,0x6f,0x41,0x33,0x33,0x46,0x53,0x63,0x91,0xbd,0xcc,0xc3,0xb5,0xaa,0x9b,0x7b,0x67,0x73,0x81
        ,0x8c,0x9b,0xa1,0xa9,0xb3,0xa9,0x9c,0x8c,0x7e,0x79,0x74,0x6a,0x6d,0x6e,0x64,0x5c,0x4d,0x48,0x48,0x3f,0x31,0x32,0x43,0x7a,0xc0,0xb4,0x9f,0xca,0xd0,0xbc,0x9d,0x58
        ,0x51,0x68,0x51,0x4f,0x5b,0x69,0x9b,0xbb,0xb4,0xad,0xa2,0x9b,0x88,0x5b,0x44,0x3c,0x42,0x57,0x64,0x79,0x9f,0xb9,0xc0,0xbc,0xae,0xa3,0x92,0x7a,0x70,0x73,0x76,0x7f
        ,0x84,0x86,0x94,0x9f,0x9d,0x95,0x88,0x84,0x87,0x7d,0x6f,0x67,0x60,0x59,0x52,0x4c,0x49,0x47,0x42,0x3e,0x40,0x4c,0x7d,0xab,0xa2,0xa5,0xbf,0xbe,0xb9,0xa0,0x70,0x62
        ,0x5d,0x50,0x54,0x55,0x61,0x87,0xa7,0xb7,0xb5,0xaa,0xaa,0x9c,0x83,0x6f,0x52,0x49,0x58,0x62,0x70,0x87,0x9b,0xb1,0xc2,0xc0,0xb3,0x9e,0x92,0x8c,0x7d,0x6f,0x6e,0x73
        ,0x81,0x90,0x97,0xa2,0xa5,0xa1,0x9e,0x91,0x83,0x78,0x6e,0x66,0x5c,0x53,0x4d,0x4a,0x51,0x57,0x52,0x50,0x54,0x5d,0x78,0xa1,0xa2,0x93,0x9b,0x9c,0xa0,0x9e,0x82,0x6f
        ,0x6f,0x6b,0x72,0x73,0x68,0x6d,0x7c,0x8c,0x97,0x92,0x8b,0x8f,0x90,0x8f,0x87,0x75,0x70,0x76,0x78,0x79,0x7b,0x7b,0x85,0x92,0x95,0x95,0x93,0x95,0x9b,0x96,0x8e,0x8a
        ,0x86,0x88,0x87,0x7e,0x7e,0x80,0x81,0x86,0x89,0x87,0x83,0x7b,0x71,0x6d,0x69,0x66,0x64,0x64,0x65,0x66,0x64,0x61,0x5c,0x57,0x5b,0x6c,0x7a,0x79,0x7e,0x89,0x92,0xa0
        ,0xa0,0x92,0x88,0x7f,0x79,0x79,0x6f,0x66,0x68,0x70,0x81,0x8e,0x93,0x98,0x9a,0x99,0x97,0x8e,0x84,0x7e,0x79,0x79,0x7c,0x7f,0x83,0x8a,0x91,0x95,0x95,0x96,0x97,0x97
        ,0x94,0x8e,0x87,0x85,0x84,0x81,0x7f,0x82,0x87,0x89,0x89,0x8a,0x8c,0x8e,0x8c,0x86,0x80,0x7b,0x76,0x70,0x65,0x5b,0x59,0x5b,0x5c,0x5c,0x60,0x68,0x6d,0x71,0x7c,0x83
        ,0x80,0x82,0x83,0x85,0x89,0x88,0x84,0x84,0x84,0x84,0x85,0x83,0x82,0x84,0x86,0x88,0x84,0x81,0x81,0x7e,0x7f,0x83,0x80,0x80,0x83,0x83,0x86,0x89,0x89,0x89,0x8b,0x89
        ,0x85,0x83,0x82,0x82,0x83,0x83,0x82,0x82,0x85,0x88,0x8b,0x8b,0x89,0x88,0x89,0x89,0x88,0x83,0x7c,0x76,0x74,0x71,0x6c,0x68,0x67,0x69,0x6b,0x6c,0x69,0x67,0x68,0x68
        ,0x67,0x65,0x62,0x66,0x71,0x77,0x78,0x7e,0x86,0x8e,0x94,0x93,0x8e,0x8d,0x8a,0x86,0x83,0x80,0x80,0x84,0x86,0x87,0x8b,0x8b,0x8c,0x8c,0x8a,0x8a,0x8a,0x89,0x8b,0x8a
        ,0x89,0x89,0x8a,0x89,0x86,0x85,0x84,0x83,0x82,0x83,0x85,0x88,0x8c,0x8e,0x91,0x93,0x91,0x8f,0x8b,0x86,0x83,0x81,0x7e,0x7c,0x7b,0x7b,0x7b,0x78,0x75,0x73,0x72,0x70
        ,0x6e,0x6c,0x6d,0x6e,0x6e,0x6d,0x6b,0x6a,0x6a,0x6a,0x68,0x69,0x70,0x73,0x75,0x7c,0x82,0x89,0x90,0x91,0x90,0x90,0x8e,0x8c,0x89,0x83,0x80,0x82,0x84,0x83,0x83,0x85
        ,0x87,0x88,0x87,0x85,0x83,0x82,0x7f,0x7e,0x7e,0x7f,0x81,0x82,0x83,0x86,0x88,0x88,0x87,0x87,0x85,0x85,0x85,0x85,0x85,0x86,0x86,0x86,0x85,0x84,0x82,0x80,0x7d,0x79
        ,0x78,0x77,0x74,0x73,0x73,0x71,0x71,0x71,0x71,0x71,0x70,0x6d,0x6c,0x6b,0x68,0x69,0x6a,0x6c,0x6e,0x74,0x7c,0x82,0x84,0x87,0x8c,0x8f,0x92,0x92,0x8f,0x8d,0x8e,0x8d
        ,0x8b,0x86,0x84,0x85,0x86,0x86,0x85,0x84,0x87,0x88,0x88,0x88,0x87,0x87,0x88,0x85,0x83,0x82,0x83,0x84,0x85,0x85,0x86,0x88,0x89,0x8a,0x89,0x87,0x87,0x87,0x86,0x85
        ,0x85,0x84,0x84,0x84,0x83,0x81,0x80,0x7d,0x79,0x77,0x75,0x74,0x73,0x72,0x71,0x72,0x73,0x73,0x73,0x72,0x6f,0x6b,0x69,0x66,0x65,0x64,0x64,0x68,0x72,0x7d,0x7f,0x82
        ,0x8b,0x90,0x93,0x94,0x8e,0x88,0x88,0x86,0x84,0x82,0x7f,0x81,0x85,0x88,0x89,0x88,0x88,0x8a,0x88,0x83,0x80,0x7b,0x7a,0x7b,0x78,0x77,0x7a,0x7e,0x81,0x85,0x88,0x87
        ,0x89,0x8b,0x8a,0x87,0x86,0x84,0x83,0x82,0x80,0x80,0x82,0x82,0x82,0x83,0x84,0x83,0x81,0x7d,0x7b,0x79,0x76,0x74,0x72,0x72,0x74,0x75,0x76,0x77,0x77,0x76,0x74,0x71
        ,0x6e,0x6b,0x69,0x68,0x6a,0x74,0x81,0x84,0x86,0x90,0x97,0x9a,0x9c,0x94,0x8d,0x8f,0x8b,0x85,0x82,0x7f,0x81,0x87,0x89,0x8b,0x8a,0x8c,0x8f,0x8b,0x87,0x83,0x7c,0x7b
        ,0x7d,0x78,0x77,0x7c,0x7d,0x81,0x87,0x87,0x86,0x8a,0x8c,0x8a,0x88,0x87,0x85,0x85,0x84,0x82,0x81,0x82,0x82,0x82,0x82,0x81,0x81,0x7f,0x7c,0x78,0x76,0x74,0x72,0x71
        ,0x70,0x71,0x73,0x75,0x76,0x77,0x76,0x74,0x71,0x6c,0x68,0x64,0x62,0x63,0x67,0x74,0x7e,0x7e,0x87,0x91,0x93,0x97,0x94,0x89,0x89,0x88,0x81,0x80,0x7e,0x7e,0x85,0x8a
        ,0x8c,0x8c,0x8c,0x8e,0x8c,0x85,0x81,0x7a,0x75,0x77,0x76,0x76,0x7a,0x7d,0x82,0x8a,0x8c,0x8a,0x8c,0x8d,0x8c,0x8b,0x87,0x85,0x86,0x86,0x85,0x85,0x86,0x87,0x89,0x87
        ,0x86,0x86,0x83,0x80,0x7e,0x7b,0x78,0x76,0x75,0x75,0x76,0x77,0x78,0x78,0x79,0x79,0x77,0x74,0x70,0x6b,0x68,0x65,0x63,0x64,0x67,0x6d,0x7a,0x82,0x84,0x8c,0x92,0x95
        ,0x98,0x92,0x8a,0x8b,0x88,0x83,0x82,0x7f,0x80,0x86,0x88,0x8a,0x8b,0x8b,0x8c,0x89,0x85,0x81,0x7a,0x78,0x79,0x78,0x77,0x7b,0x7d,0x83,0x89,0x89,0x89,0x8d,0x8e,0x8d
        ,0x8c,0x88,0x87,0x87,0x84,0x83,0x83,0x82,0x84,0x84,0x82,0x81,0x81,0x7f,0x7c,0x79,0x76,0x74,0x73,0x71,0x72,0x73,0x72,0x74,0x76,0x76,0x76,0x76,0x75,0x73,0x71,0x6e
        ,0x6d,0x6d,0x6d,0x6d,0x6e,0x71,0x77,0x7b,0x7d,0x80,0x83,0x87,0x8a,0x8a,0x8a,0x8a,0x8a,0x8a,0x88,0x86,0x86,0x87,0x87,0x88,0x87,0x86,0x88,0x88,0x87,0x86,0x83,0x82
        ,0x83,0x82,0x81,0x81,0x82,0x83,0x85,0x86,0x87,0x88,0x8a,0x8b,0x8b,0x8b,0x8b,0x8a,0x8a,0x89,0x88,0x87,0x86,0x85,0x83,0x82,0x81,0x7f,0x7e,0x7c,0x7a,0x79,0x78,0x78
        ,0x78,0x77,0x76,0x77,0x77,0x77,0x76,0x75,0x75,0x75,0x74,0x72,0x71,0x71,0x70,0x6f,0x6e,0x6f,0x72,0x74,0x76,0x79,0x7e,0x83,0x87,0x8a,0x8c,0x8d,0x8e,0x8e,0x8c,0x8b
        ,0x89,0x87,0x86,0x86,0x85,0x84,0x84,0x85,0x84,0x84,0x83,0x82,0x82,0x82,0x80,0x7f,0x7e,0x7f,0x7f,0x7f,0x7f,0x80,0x82,0x84,0x85,0x85,0x86,0x87,0x88,0x87,0x86,0x85
        ,0x85,0x84,0x83,0x81,0x80,0x80,0x7f,0x7e,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x78,0x77,0x77,0x75,0x74,0x73,0x71,0x70,0x70,0x70,0x72,0x74
        ,0x77,0x7a,0x80,0x84,0x88,0x8b,0x8d,0x8e,0x90,0x8f,0x8d,0x8c,0x8a,0x89,0x89,0x88,0x87,0x87,0x88,0x88,0x87,0x86,0x85,0x84,0x83,0x81,0x7f,0x7d,0x7d,0x7d,0x7e,0x7f
        ,0x7f,0x81,0x83,0x85,0x86,0x86,0x86,0x87,0x87,0x86,0x85,0x85,0x85,0x85,0x84,0x83,0x83,0x82,0x81,0x80,0x7e,0x7c,0x7b,0x7a,0x79,0x77,0x77,0x77,0x77,0x77,0x78,0x78
        ,0x79,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x72,0x74,0x77,0x7a,0x7d,0x80,0x84,0x87,0x89,0x8a,0x8b,0x8b,0x8a,0x89,0x88,0x87,0x86,0x86,0x86,0x86,0x86,0x85
        ,0x85,0x84,0x83,0x82,0x80,0x7f,0x7d,0x7c,0x7c,0x7c,0x7c,0x7d,0x7e,0x7f,0x81,0x81,0x82,0x84,0x84,0x84,0x84,0x85,0x85,0x85,0x85,0x84,0x84,0x84,0x83,0x83,0x81,0x80
        ,0x7f,0x7e,0x7d,0x7b,0x7a,0x7a,0x79,0x79,0x79,0x79,0x7a,0x7a,0x7b,0x7b,0x7b,0x7b,0x7b,0x7a,0x7a,0x79,0x78,0x78,0x78,0x77,0x78,0x79,0x7a,0x7c,0x7e,0x80,0x82,0x84
        ,0x86,0x87,0x88,0x88,0x89,0x89,0x88,0x87,0x87,0x87,0x86,0x86,0x85,0x84,0x84,0x83,0x82,0x81,0x80,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7f,0x7f,0x80,0x80,0x80,0x81,0x82
        ,0x83,0x83,0x83,0x84,0x84,0x84,0x83,0x83,0x82,0x81,0x81,0x7f,0x7e,0x7e,0x7d,0x7c,0x7c,0x7b,0x7b,0x7b,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a
        ,0x7a,0x7a,0x79,0x79,0x78,0x79,0x79,0x79,0x7a,0x7b,0x7d,0x7e,0x80,0x81,0x82,0x84,0x86,0x86,0x87,0x88,0x88,0x88,0x88,0x87,0x86,0x86,0x85,0x84,0x83,0x82,0x82,0x81
        ,0x81,0x80,0x80,0x80,0x7f,0x7f,0x7f,0x80,0x80,0x80,0x80,0x81,0x82,0x82,0x82,0x83,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x83,0x82,0x82,0x80,0x7f,0x7e,0x7d,0x7c,0x7b
        ,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7a,0x7b,0x7b,0x7b,0x7c,0x7d,0x7d,0x7e,0x7f,0x7f,0x80,0x81,0x82,0x83,0x84
        ,0x84,0x85,0x86,0x86,0x86,0x87,0x87,0x87,0x86,0x86,0x86,0x85,0x85,0x84,0x83,0x83,0x82,0x82,0x81,0x81,0x81,0x80,0x80,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e
        ,0x7e,0x7e,0x7e,0x7e,0x7d,0x7d,0x7d,0x7d,0x7c,0x7c,0x7c,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7c
        ,0x7c,0x7d,0x7d,0x7e,0x7f,0x80,0x80,0x81,0x82,0x82,0x83,0x83,0x84,0x85,0x85,0x85,0x86,0x86,0x86,0x86,0x86,0x87,0x87,0x86,0x86,0x86,0x86,0x85,0x85,0x84,0x83,0x82
        ,0x82,0x81,0x81,0x80,0x80,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7c,0x7c,0x7c
        ,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7d,0x7d,0x7d,0x7e,0x7e,0x7f,0x7f,0x80,0x80,0x81,0x81,0x81,0x82,0x82,0x82,0x83,0x83,0x83,0x83,0x84,0x84,0x84,0x84
        ,0x84,0x84,0x84,0x83,0x83,0x83,0x83,0x83,0x82,0x82,0x82,0x81,0x81,0x80,0x80,0x80,0x7f,0x7f,0x7e,0x7e,0x7e,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d
        ,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x80,0x80,0x80,0x81,0x81,0x81,0x82,0x82,0x82
        ,0x82,0x82,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x82,0x82,0x82,0x81};

pcm_t const PCM2 = {
        .bytes_per_sample = 1,
        .sample_rate = 44100,
        .data_len = sizeof(PCM2_data),
        .data = PCM2_data
};

uint8_t const PCM1_data[] = {
        0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7d,0x7e,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f
        ,0x80,0x80,0x80,0x81,0x81,0x81,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x81,0x81,0x81,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x83,0x83,0x83,0x84,0x84,0x84,0x85,0x85,0x85
        ,0x85,0x85,0x85,0x85,0x84,0x84,0x84,0x83,0x83,0x83,0x83,0x83,0x82,0x82,0x82,0x82,0x82,0x82,0x81,0x81,0x81,0x81,0x80,0x80,0x80,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e
        ,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7d,0x7d,0x7d,0x7d,0x7d,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e
        ,0x7e,0x7e,0x7e,0x7e,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e
        ,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x80,0x80,0x80,0x80,0x81,0x81,0x81,0x81,0x82,0x81,0x81,0x81,0x81,0x81,0x80,0x81,0x81,0x81,0x81,0x81,0x82,0x82,0x82,0x82,0x83,0x83
        ,0x84,0x84,0x85,0x85,0x85,0x85,0x84,0x84,0x84,0x84,0x83,0x83,0x82,0x82,0x82,0x82,0x82,0x82,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81
        ,0x81,0x81,0x81,0x81,0x81,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e
        ,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x80,0x80,0x80,0x80,0x80,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7d
        ,0x7d,0x7d,0x7d,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x80,0x80,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x80,0x80,0x80,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f
        ,0x7f,0x80,0x80,0x80,0x80,0x81,0x81,0x82,0x82,0x82,0x83,0x83,0x83,0x83,0x83,0x84,0x84,0x84,0x85,0x85,0x86,0x86,0x86,0x86,0x85,0x85,0x84,0x84,0x83,0x83,0x82,0x82
        ,0x82,0x81,0x81,0x81,0x81,0x80,0x80,0x80,0x80,0x7f,0x7f,0x7e,0x7d,0x7d,0x7d,0x7c,0x7c,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b
        ,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7d,0x7d,0x7d,0x7e,0x7f,0x80,0x81,0x83,0x84,0x85,0x86,0x88,0x89,0x8a,0x8b,0x8c
        ,0x8c,0x8d,0x8c,0x8c,0x8b,0x8a,0x89,0x88,0x86,0x85,0x83,0x82,0x81,0x80,0x7f,0x7e,0x7d,0x7b,0x7a,0x79,0x77,0x75,0x73,0x72,0x70,0x6e,0x6c,0x6a,0x68,0x66,0x65,0x63
        ,0x61,0x5f,0x5e,0x5d,0x5e,0x60,0x67,0x6f,0x78,0x82,0x8c,0x95,0x9b,0xa0,0xa2,0xa3,0xa3,0xa1,0x9d,0x9a,0x99,0x97,0x97,0x98,0x9a,0x9b,0x9c,0x9c,0x9c,0x9b,0x99,0x97
        ,0x95,0x92,0x8e,0x8b,0x87,0x83,0x80,0x7e,0x7c,0x7b,0x7c,0x7c,0x7e,0x7e,0x7f,0x7f,0x7e,0x7d,0x7a,0x78,0x75,0x71,0x6d,0x67,0x62,0x5c,0x56,0x4f,0x49,0x42,0x3c,0x39
        ,0x3a,0x44,0x51,0x5f,0x6f,0x80,0x8e,0x98,0xa0,0xa5,0xa7,0xa7,0xa4,0x9f,0x9b,0x97,0x93,0x92,0x8f,0x8d,0x8a,0x88,0x86,0x84,0x85,0x87,0x8b,0x8e,0x92,0x94,0x96,0x97
        ,0x97,0x97,0x95,0x93,0x91,0x8e,0x8c,0x89,0x87,0x86,0x85,0x85,0x86,0x86,0x86,0x86,0x85,0x82,0x7f,0x7b,0x76,0x70,0x6a,0x64,0x5d,0x56,0x50,0x4a,0x44,0x40,0x3c,0x38
        ,0x36,0x36,0x3a,0x47,0x56,0x67,0x78,0x88,0x99,0xa4,0xae,0xb3,0xb3,0xb1,0xac,0xa5,0x9e,0x97,0x91,0x8d,0x8a,0x87,0x86,0x84,0x84,0x85,0x88,0x8c,0x91,0x97,0x9b,0x9f
        ,0xa2,0xa2,0xa1,0x9f,0x9d,0x98,0x95,0x91,0x8e,0x8c,0x8b,0x8a,0x8a,0x8b,0x8b,0x8d,0x8e,0x8d,0x8c,0x8a,0x86,0x82,0x7c,0x76,0x6f,0x68,0x60,0x59,0x53,0x4b,0x44,0x3e
        ,0x38,0x34,0x30,0x2d,0x2c,0x30,0x3d,0x4f,0x62,0x76,0x89,0x9d,0xaa,0xb2,0xb5,0xb1,0xaa,0xa0,0x96,0x8d,0x86,0x80,0x7e,0x7e,0x7f,0x81,0x85,0x88,0x8e,0x95,0x9a,0xa0
        ,0xa5,0xaa,0xaa,0xa9,0xa5,0xa0,0x9a,0x95,0x91,0x8e,0x8c,0x8b,0x8d,0x90,0x92,0x95,0x97,0x99,0x9a,0x97,0x93,0x8c,0x84,0x7b,0x74,0x6c,0x65,0x60,0x5a,0x55,0x51,0x4b
        ,0x45,0x3f,0x38,0x32,0x2c,0x26,0x23,0x25,0x33,0x47,0x5e,0x78,0x8f,0xa5,0xb4,0xbb,0xbd,0xb4,0xa8,0x9b,0x8f,0x84,0x80,0x7c,0x7d,0x83,0x87,0x8e,0x95,0x9a,0x9f,0xa5
        ,0xa8,0xab,0xab,0xa8,0xa5,0x9f,0x98,0x92,0x8d,0x8b,0x8b,0x8e,0x91,0x96,0x9b,0x9f,0xa4,0xa6,0xa6,0xa4,0x9e,0x96,0x8c,0x82,0x77,0x6f,0x69,0x66,0x66,0x65,0x64,0x61
        ,0x5c,0x55,0x49,0x3e,0x32,0x28,0x1f,0x17,0x14,0x16,0x21,0x37,0x54,0x71,0x90,0xa7,0xbb,0xc3,0xc0,0xb7,0xa4,0x92,0x81,0x75,0x6f,0x72,0x78,0x82,0x90,0x9b,0xa5,0xad
        ,0xaf,0xae,0xad,0xa7,0xa2,0x9d,0x95,0x91,0x8c,0x87,0x88,0x8c,0x92,0x9c,0xa3,0xa8,0xac,0xaa,0xa6,0xa1,0x99,0x91,0x8c,0x86,0x81,0x7d,0x77,0x75,0x74,0x75,0x77,0x79
        ,0x78,0x74,0x6b,0x5d,0x4c,0x38,0x27,0x1a,0x0f,0x09,0x08,0x0b,0x14,0x27,0x47,0x6a,0x8f,0xac,0xc0,0xcc,0xc3,0xb2,0x99,0x7b,0x68,0x5e,0x5f,0x6d,0x82,0x96,0xaa,0xbb
        ,0xc2,0xc7,0xc3,0xb8,0xae,0xa1,0x96,0x91,0x8c,0x8a,0x8f,0x94,0x99,0xa4,0xac,0xb1,0xb5,0xb1,0xab,0xa3,0x9a,0x92,0x8e,0x8a,0x88,0x88,0x84,0x84,0x83,0x81,0x83,0x83
        ,0x82,0x80,0x79,0x6c,0x5e,0x4a,0x37,0x27,0x19,0x12,0x11,0x11,0x15,0x1a,0x20,0x2d,0x46,0x68,0x87,0xa8,0xb3,0xb9,0xaf,0x93,0x7e,0x65,0x5a,0x61,0x70,0x84,0x9d,0xab
        ,0xb2,0xb9,0xb5,0xb2,0xb2,0xa9,0xa1,0x9a,0x8d,0x8a,0x88,0x89,0x95,0xa3,0xaf,0xba,0xbe,0xb9,0xb5,0xa9,0x9d,0x99,0x92,0x93,0x95,0x93,0x93,0x90,0x8b,0x89,0x88,0x85
        ,0x85,0x81,0x7c,0x77,0x6d,0x62,0x54,0x42,0x34,0x2a,0x1f,0x1c,0x19,0x19,0x1d,0x1c,0x1f,0x27,0x38,0x5c,0x7d,0x9d,0xb1,0xad,0xa8,0x8f,0x79,0x6c,0x62,0x6c,0x7c,0x8d
        ,0x9d,0xa8,0xaa,0xad,0xb1,0xb2,0xb7,0xb5,0xa8,0x9c,0x89,0x7a,0x7f,0x88,0x9f,0xbc,0xc8,0xd0,0xc8,0xb3,0xa3,0x96,0x90,0x98,0x9f,0xa2,0xa5,0x9c,0x92,0x8d,0x86,0x8a
        ,0x8f,0x8e,0x8f,0x86,0x7a,0x72,0x66,0x5f,0x59,0x50,0x46,0x39,0x29,0x1e,0x15,0x14,0x17,0x19,0x1b,0x21,0x29,0x45,0x68,0x86,0xa8,0xab,0xa6,0x99,0x78,0x6c,0x62,0x63
        ,0x7a,0x8c,0x9a,0xaa,0xa9,0xa9,0xb1,0xb1,0xb7,0xba,0xac,0x9a,0x87,0x6e,0x6f,0x7e,0x97,0xc1,0xd5,0xdb,0xd0,0xb2,0x9b,0x90,0x8d,0x9a,0xa7,0xaa,0xa8,0x9a,0x89,0x85
        ,0x84,0x8e,0x9d,0x9d,0x99,0x8a,0x75,0x6a,0x63,0x61,0x62,0x5c,0x4e,0x3f,0x2b,0x1c,0x15,0x14,0x1b,0x1d,0x1a,0x15,0x14,0x23,0x4b,0x76,0x9f,0xb5,0xa8,0x98,0x77,0x5e
        ,0x5f,0x65,0x7d,0x98,0xa1,0xa7,0xa6,0x9f,0xa9,0xb5,0xc0,0xc6,0xb9,0x9b,0x80,0x68,0x61,0x7c,0x9e,0xc6,0xe1,0xde,0xcb,0xae,0x96,0x93,0x9b,0xa8,0xb3,0xad,0x9f,0x91
        ,0x85,0x89,0x96,0xa1,0xa9,0xa4,0x95,0x86,0x77,0x71,0x71,0x6f,0x6a,0x5d,0x4a,0x3b,0x2f,0x2a,0x27,0x27,0x24,0x1e,0x15,0x0e,0x0f,0x19,0x39,0x67,0x8d,0xa7,0xa7,0x8e
        ,0x80,0x69,0x66,0x76,0x7c,0x8e,0x93,0x8f,0x95,0x9b,0xa6,0xbd,0xc5,0xc0,0xb1,0x92,0x75,0x6c,0x6e,0x81,0xa6,0xba,0xce,0xd0,0xbd,0xb3,0xa2,0x9d,0xa3,0xa3,0xa4,0xa1
        ,0x98,0x95,0x97,0x99,0xa1,0xa2,0x9d,0x98,0x8e,0x88,0x85,0x7f,0x7b,0x72,0x65,0x5b,0x50,0x4b,0x46,0x41,0x38,0x29,0x19,0x0e,0x09,0x06,0x0a,0x10,0x26,0x5b,0x84,0xa8
        ,0xb6,0x93,0x87,0x68,0x57,0x6d,0x6e,0x82,0x90,0x89,0x91,0x9f,0xa9,0xc2,0xcc,0xbf,0xab,0x8d,0x6d,0x6a,0x75,0x86,0xb1,0xbd,0xc7,0xc8,0xb3,0xaf,0xa7,0xa2,0xa7,0xa4
        ,0x9c,0x9a,0x95,0x95,0xa0,0xa1,0xa4,0xa2,0x96,0x93,0x91,0x8e,0x92,0x89,0x7e,0x74,0x64,0x61,0x5e,0x5a,0x54,0x48,0x38,0x27,0x1a,0x13,0x15,0x14,0x12,0x13,0x16,0x45
        ,0x7f,0xa2,0xc6,0xa3,0x81,0x73,0x51,0x6c,0x7f,0x80,0x8f,0x85,0x7f,0x9a,0xaf,0xc7,0xd7,0xc2,0x9c,0x81,0x6b,0x69,0x8a,0x92,0xa3,0xae,0xa7,0xb9,0xc2,0xc0,0xba,0xaa
        ,0x94,0x91,0x91,0x97,0xa7,0xa5,0xa0,0x9b,0x93,0x96,0x9e,0x9c,0x9b,0x92,0x85,0x81,0x7c,0x7a,0x77,0x6c,0x60,0x59,0x51,0x4c,0x46,0x39,0x2c,0x1c,0x13,0x10,0x12,0x0d
        ,0x0a,0x13,0x39,0x7e,0xa5,0xbd,0xa6,0x76,0x6e,0x5e,0x6c,0x84,0x7a,0x75,0x79,0x7e,0xa7,0xcd,0xd5,0xcc,0xaa,0x83,0x76,0x82,0x86,0x9a,0x96,0x87,0x95,0xaa,0xca,0xdd
        ,0xce,0xa0,0x88,0x80,0x90,0xb0,0xb0,0xa2,0x92,0x84,0x90,0xad,0xb1,0xad,0x95,0x78,0x7d,0x8c,0x9b,0xa0,0x8a,0x6a,0x5e,0x5b,0x66,0x6e,0x5d,0x43,0x2d,0x23,0x29,0x33
        ,0x2d,0x21,0x0f,0x00,0x0c,0x26,0x5e,0x9e,0xa7,0xa9,0x8e,0x6d,0x83,0x7d,0x78,0x78,0x5f,0x67,0x8f,0xaf,0xcd,0xd3,0xb2,0x9b,0x98,0x96,0x9b,0x9d,0x7d,0x77,0x81,0x96
        ,0xcb,0xd9,0xc7,0xa9,0x8d,0x88,0xa5,0xb5,0xaa,0x99,0x7d,0x7f,0x9d,0xaf,0xb2,0xa2,0x82,0x7f,0x8e,0x9d,0xa7,0x98,0x84,0x76,0x76,0x77,0x78,0x6d,0x59,0x52,0x4b,0x48
        ,0x47,0x3f,0x32,0x2f,0x2a,0x27,0x27,0x1c,0x16,0x1d,0x2e,0x54,0x91,0x9c,0x9e,0x96,0x76,0x87,0x8a,0x77,0x76,0x6e,0x76,0xa1,0xb9,0xbe,0xba,0xab,0xa6,0xaf,0xb0,0x95
        ,0x85,0x77,0x7c,0xa4,0xbc,0xba,0xb0,0x9c,0x99,0xb0,0xad,0x9b,0x8d,0x7b,0x83,0xa2,0xab,0xa5,0x9c,0x87,0x8b,0x9b,0x9b,0x9c,0x95,0x88,0x88,0x89,0x7f,0x7d,0x79,0x6f
        ,0x6f,0x65,0x55,0x4d,0x48,0x43,0x47,0x43,0x3e,0x42,0x40,0x3c,0x33,0x21,0x1c,0x21,0x31,0x53,0x7a,0x9b,0x9b,0x9f,0x9a,0x96,0x9f,0x89,0x76,0x74,0x78,0x92,0xaf,0xb5
        ,0xbe,0xc2,0xc3,0xbf,0xac,0x94,0x7c,0x7a,0x7f,0x92,0x9f,0xa4,0xab,0xac,0xad,0xa3,0x95,0x86,0x85,0x8c,0x8f,0x8c,0x8a,0x8e,0x99,0xa1,0x9c,0x92,0x86,0x84,0x85,0x81
        ,0x7c,0x77,0x7b,0x7c,0x7a,0x6c,0x5f,0x54,0x4e,0x4b,0x47,0x44,0x43,0x45,0x46,0x47,0x45,0x43,0x3d,0x33,0x2d,0x2c,0x33,0x45,0x5d,0x74,0x8f,0xa1,0xa7,0xaa,0x9c,0x8d
        ,0x88,0x86,0x8c,0x98,0xa0,0xad,0xbb,0xc1,0xc2,0xba,0xad,0x9e,0x90,0x87,0x80,0x89,0x98,0x9f,0xa8,0xa3,0xa0,0xa4,0xa0,0x97,0x8d,0x85,0x85,0x91,0x95,0x99,0x9a,0x95
        ,0x92,0x8d,0x88,0x89,0x89,0x83,0x7f,0x79,0x79,0x7c,0x7c,0x76,0x6f,0x67,0x5f,0x58,0x53,0x50,0x4e,0x4e,0x4d,0x4d,0x50,0x4f,0x45,0x39,0x2e,0x2d,0x34,0x3d,0x4a,0x5b
        ,0x70,0x91,0xa5,0xa7,0xae,0xa7,0xa4,0xa3,0x93,0x8d,0x92,0x96,0xa2,0xab,0xaa,0xaf,0xb1,0xad,0xa8,0x9d,0x92,0x8a,0x83,0x82,0x7f,0x85,0x8d,0x92,0x95,0x94,0x93,0x97
        ,0x98,0x91,0x8b,0x83,0x86,0x8e,0x91,0x8d,0x89,0x84,0x83,0x83,0x80,0x7d,0x7a,0x7c,0x7b,0x79,0x75,0x70,0x6c,0x65,0x5d,0x56,0x53,0x53,0x55,0x56,0x57,0x59,0x5b,0x5a
        ,0x57,0x56,0x51,0x4d,0x4e,0x52,0x5c,0x65,0x6e,0x74,0x7d,0x86,0x8d,0x93,0x95,0x99,0x9f,0xa5,0xa8,0xaa,0xa9,0xa7,0xa7,0xa5,0xa1,0x9d,0x96,0x93,0x90,0x8e,0x8e,0x8f
        ,0x91,0x92,0x91,0x8e,0x8d,0x8a,0x89,0x86,0x85,0x87,0x8c,0x91,0x94,0x94,0x94,0x93,0x93,0x91,0x8e,0x8b,0x87,0x84,0x82,0x81,0x81,0x82,0x82,0x7e,0x78,0x71,0x6b,0x67
        ,0x63,0x62,0x60,0x5f,0x5f,0x5f,0x5f,0x5e,0x5d,0x5b,0x5a,0x59,0x59,0x59,0x5a,0x5a,0x5b,0x5d,0x60,0x64,0x6b,0x72,0x7a,0x81,0x87,0x8f,0x96,0x9c,0x9f,0xa1,0xa2,0xa3
        ,0xa3,0xa3,0xa2,0xa0,0x9e,0x9c,0x99,0x95,0x90,0x8c,0x88,0x82,0x7e,0x7c,0x7c,0x7c,0x7e,0x80,0x83,0x87,0x89,0x8a,0x89,0x87,0x86,0x85,0x83,0x85,0x86,0x86,0x88,0x88
        ,0x89,0x89,0x87,0x82,0x7d,0x79,0x77,0x75,0x74,0x72,0x71,0x70,0x70,0x6e,0x6a,0x67,0x64,0x62,0x61,0x60,0x5f,0x5f,0x60,0x62,0x64,0x65,0x65,0x66,0x68,0x6c,0x72,0x79
        ,0x7e,0x85,0x8b,0x91,0x97,0x9c,0xa0,0xa2,0xa3,0xa3,0xa4,0xa3,0xa1,0x9f,0x9d,0x9a,0x96,0x92,0x8e,0x8b,0x8a,0x88,0x86,0x85,0x85,0x87,0x88,0x89,0x89,0x87,0x86,0x86
        ,0x87,0x88,0x88,0x88,0x89,0x8b,0x8b,0x8b,0x89,0x87,0x84,0x82,0x80,0x7f,0x7f,0x7d,0x7c,0x7a,0x79,0x78,0x75,0x72,0x6d,0x6a,0x69,0x68,0x68,0x67,0x65,0x64,0x62,0x61
        ,0x60,0x5f,0x5f,0x5f,0x60,0x63,0x66,0x6a,0x6d,0x70,0x72,0x74,0x78,0x7b,0x7f,0x83,0x87,0x8c,0x90,0x95,0x98,0x9b,0x9c,0x9b,0x99,0x97,0x94,0x92,0x90,0x8e,0x8d,0x8d
        ,0x8c,0x8c,0x8b,0x8b,0x8b,0x8b,0x8b,0x8b,0x8b,0x8b,0x8c,0x8c,0x8b,0x8b,0x8a,0x89,0x88,0x86,0x86,0x85,0x85,0x84,0x83,0x82,0x81,0x7f,0x7e,0x7c,0x7b,0x7a,0x79,0x78
        ,0x77,0x75,0x74,0x73,0x71,0x6f,0x6d,0x6b,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x6b,0x6b,0x6b,0x6c,0x6d,0x6e,0x70,0x72,0x75,0x79,0x7c,0x80,0x83,0x86,0x88,0x8b,0x8f,0x93
        ,0x95,0x97,0x99,0x9a,0x9b,0x9b,0x9b,0x9b,0x9a,0x99,0x97,0x97,0x96,0x95,0x95,0x93,0x92,0x91,0x8e,0x8c,0x8b,0x88,0x85,0x83,0x80,0x7e,0x7e,0x7d,0x7c,0x7b,0x7a,0x79
        ,0x7a,0x79,0x79,0x78,0x77,0x77,0x76,0x76,0x76,0x75,0x74,0x74,0x73,0x73,0x73,0x72,0x71,0x6f,0x6d,0x6c,0x6b,0x6b,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x6b
        ,0x6c,0x6e,0x70,0x71,0x74,0x77,0x7a,0x7e,0x83,0x86,0x8a,0x8e,0x91,0x95,0x98,0x9c,0x9f,0xa1,0xa2,0xa1,0xa2,0xa2,0xa1,0xa1,0x9f,0x9d,0x9a,0x97,0x94,0x91,0x8e,0x8a
        ,0x87,0x85,0x83,0x81,0x80,0x7f,0x7e,0x7d,0x7c,0x7c,0x7c,0x7b,0x7b,0x7b,0x7a,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7a,0x79,0x78,0x77,0x76,0x76,0x75,0x73,0x72
        ,0x71,0x70,0x6f,0x6e,0x6d,0x6d,0x6c,0x6c,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x73,0x75,0x78,0x7b,0x7e,0x81,0x85,0x89,0x8d,0x91,0x94,0x96,0x98,0x99,0x9a,0x9a,0x9a,0x9a
        ,0x99,0x99,0x97,0x95,0x93,0x91,0x8f,0x8c,0x8a,0x87,0x85,0x82,0x80,0x7f,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x76,0x76,0x76,0x77,0x77,0x78,0x78,0x78,0x78,0x78
        ,0x78,0x78,0x77,0x77,0x76,0x76,0x75,0x75,0x73,0x72,0x71,0x70,0x6f,0x6f,0x6e,0x6e,0x6e,0x6f,0x70,0x71,0x73,0x75,0x76,0x78,0x7a,0x7c,0x7f,0x81,0x83,0x86,0x88,0x8a
        ,0x8c,0x8e,0x8f,0x91,0x92,0x93,0x94,0x95,0x96,0x96,0x96,0x96,0x95,0x94,0x93,0x92,0x91,0x90,0x8e,0x8d,0x8c,0x8a,0x89,0x88,0x86,0x85,0x83,0x82,0x81,0x80,0x7f,0x7f
        ,0x7e,0x7e,0x7d,0x7d,0x7d,0x7c,0x7c,0x7b,0x7b,0x7a,0x79,0x78,0x78,0x77,0x77,0x76,0x76,0x75,0x74,0x73,0x73,0x72,0x71,0x71,0x71,0x71,0x71,0x72,0x72,0x73,0x73,0x74
        ,0x75,0x76,0x77,0x78,0x79,0x7b,0x7c,0x7d,0x7e,0x7f,0x80,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x89,0x8a,0x8a,0x8a,0x8a,0x8a,0x8a,0x8a,0x89,0x89,0x88,0x87,0x86
        ,0x85,0x85,0x84,0x83,0x82,0x82,0x81,0x81,0x80,0x7f,0x7f,0x7e,0x7e,0x7d,0x7d,0x7d,0x7d,0x7c,0x7c,0x7c,0x7b,0x7b,0x7b,0x7b,0x7a,0x7a,0x7a,0x7a,0x7a,0x79,0x79,0x79
        ,0x79,0x79,0x78,0x78,0x79,0x79,0x79,0x7a,0x7b,0x7b,0x7c,0x7d,0x7e,0x7f,0x80,0x81,0x82,0x83,0x84,0x84,0x85,0x86,0x87,0x87,0x88,0x89,0x89,0x89,0x8a,0x8a,0x8a,0x8a
        ,0x8a,0x8a,0x8a,0x89,0x89,0x89,0x89,0x88,0x88,0x88,0x87,0x87,0x86,0x85,0x85,0x84,0x84,0x83,0x82,0x82,0x81,0x80,0x80,0x7f,0x7e,0x7e,0x7d,0x7d,0x7c,0x7b,0x7b,0x7a
        ,0x7a,0x79,0x79,0x79,0x78,0x78,0x77,0x77,0x77,0x76,0x76,0x76,0x76,0x76,0x76,0x76,0x76,0x76,0x76,0x77,0x77,0x78,0x78,0x79,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,0x7f
        ,0x80,0x81,0x81,0x82,0x82,0x83,0x83,0x83,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x85,0x85,0x85,0x85,0x85,0x84
        ,0x84,0x84,0x84,0x84,0x83,0x83,0x82,0x82,0x81,0x81,0x81,0x80,0x80,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f
        ,0x7f,0x7f,0x80,0x80,0x80,0x80,0x80,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x81
        ,0x81,0x81,0x81,0x81,0x80,0x80,0x80,0x80,0x7f,0x7f,0x7e,0x7e,0x7e,0x7d,0x7d,0x7d,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7a,0x7a,0x7a,0x7a
        ,0x7a,0x7a,0x7a,0x7a,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7b,0x7c,0x7c,0x7c,0x7c,0x7d,0x7d,0x7d,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x80,0x80,0x80,0x81,0x81,0x81,0x82,0x82
        ,0x83,0x83,0x83,0x84,0x84,0x84,0x85,0x85,0x85,0x85,0x85,0x85,0x85,0x85,0x85,0x85,0x85,0x85,0x84,0x84,0x84,0x84,0x83,0x83,0x83,0x83,0x82,0x82,0x82,0x82,0x82,0x81
        ,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80};

pcm_t const PCM1 = {
        .bytes_per_sample = 1,
        .sample_rate = 44100,
        .data_len = sizeof(PCM2_data),
        .data = PCM2_data
};

#define PCM_len 3

pcm_t PCM_arr[PCM_len];

extern pcm_t PCM_MARIO_8000;

void init_PCM_arr() {
    PCM_arr[0] = PCM1;
    PCM_arr[1] = PCM2;
    PCM_arr[2] = PCM_MARIO_8000;
}

pcm_t const* PCM = &PCM1; // TODO: change into PCM_arr when fixed

void change_PCM(int direction) {
    static size_t idx = PCM_len - 1;
    idx = (idx + direction < 0 ? -1 : 1) % PCM_len;
    PCM = PCM_arr + idx;
}

#endif //DAC_PCM_H
