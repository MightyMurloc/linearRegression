//
// Created by DucDung Nguyen on 05/04/2017.
//

#ifndef PF162A01_LINEARREGRESSION_H
#define PF162A01_LINEARREGRESSION_H

#include "commonLib.h"

// Function: linearRegression
// Input: DataIterator struct that contains input data
//        ProbParam struct that contains configuration for linear regression method
// Output: LinearRegressionModel struct that contains the estimated model
// Return: return true if this estimation finished successfully, return false otherwise.
bool linearRegression(DataIterator_t&, ProbParam_t&, LinearRegressionModel_t&);
bool modelEvaluationLR(DataIterator_t&, LinearRegressionModel_t&);

// Perform K-Fold training
bool kFoldTraining(DataIterator_t&, ProbParam_t&, LinearRegressionModel_t&);

#endif //PF162A01_LINEARREGRESSION_H
