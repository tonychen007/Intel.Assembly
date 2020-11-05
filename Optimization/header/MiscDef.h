#pragma once

#include <stddef.h>

typedef struct llnode
{
    double ValA[4];
    double ValB[4];
    double ValC[4];
    double ValD[4];
    __int8 FreeSpace[376];

    llnode* Link;

#ifndef _WIN64
    __int8 Pad[4];
#endif

} LlNode;

// for main cc
extern void BasicOptimizationTest();
extern void NonTemporalTest();
extern void PrefetchTest();

// defined in asm
extern "C" void CalcResultMovaps(float* c, const float* a, const float* b, int n);
extern "C" void CalcResultMovntps(float* c, const float* a, const float* b, int n);
extern "C" void LlTraverseAVXNoPrefetch(LlNode * p);
extern "C" void LlTraverseAVXPrefetch(LlNode * p);