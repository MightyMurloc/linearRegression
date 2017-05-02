/*
 * =========================================================================================
 * Name        : main.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : This source belongs to Assignment 1 framework - Programming Fundamentals - Spring 2017
 *               This file implements functions used for database management
 * =========================================================================================
 */

#include <iostream>
#include <iomanip>

#include "commonLib.h"
#include "linearRegression.h"

using namespace std;


int main(int narg, char** argv) {
    ProbParam_t             param;
    DataIterator_t          data;
    LinearRegressionModel_t model;

    cout << fixed << setprecision(5);// preset for floating point numbers
    if (narg < 3) {
        cout << "usage: pf162a01 <inputData> <inputConfig>\n";
        return -1;
    }
    if (!loadData(argv[1], data)) {
        cout << "Error in loading data. Exiting...\n";
        return -2;
    }
    if (!loadParams(argv[2], param)) {
        cout << "Error in configuration. Exiting...\n";
        return -3;
    }

    if (!kFoldTraining(data, param, model)) {
        cout << "Error in estimation process. Exiting...\n";
        return -10;
    }
    return 0;
}