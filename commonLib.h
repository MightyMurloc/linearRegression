//
// Created by DucDung Nguyen on 05/04/2017.
//

#ifndef PF162A01_COMMONLIB_H
#define PF162A01_COMMONLIB_H

#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define DATA_BLOCK_SIZE      64

typedef struct Point2D {
    float   x, y;
} Point2D_t;

typedef struct LinearRegressionModel {
    float				Ermsd;
    float				a, b;
    float				errHistogram[10];
} LinearRegressionModel_t;

typedef struct ProbParam {
    int                 nIterations;
    int                 nFolds;
    float               learningRate;
    Point2D_t           startPoint;
    bool                eval;
} ProbParam_t;

typedef struct DataIterator {
    vector<Point2D_t>   data;
    int                 batchSize;
    int                 curBlock;
} DataIterator_t;

bool loadData(char*, DataIterator_t&);
bool loadParams(char*, ProbParam_t&);

#endif //PF162A01_COMMONLIB_H
