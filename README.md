# PF162-Assignment 01

## 1. Problem statement
Our world are filled with various problems that scientist cannot 
solve or model exactly. For example, we want to determine a fish 
base on the relationship between size, shape, color. What we have 
are a tons of samples collected from the observation. And what 
we are trying to do is modeling this observation in form of some 
math models. It is an uneasy task. The curse of dimensionality 
leave us a lot of headache. In some cases, it is possible to model
using a simple math model such as linear model. The technique 
estimate the linear model from observed data is quite simple.
Given a linear model

	y = a * x + b                                           (1)
we want to estimate parameters `a` and `b` so that the data points 
can fit on this line with the smallest error.

In this assignment, students are asked to implement this algorithm. 
The purpose of this assignment is
not delivering Machine Learning techniques to students, but to 
ask students demonstrate their programming skill, how they 
organize and implement a particular algorithm. Basically,
student should understand how to implement a given algorithm.
	
## 2. Optimization
### 2.1. Error measurement
Given a set of data points `P = {p_i | p_i = (x_i, y_i)}`, where 
`y_i` is the observation obtained from input `x_i`. Let `y~_i` be
predicted value from input `x_i` as

    y~_i = a * x_i + b
    
The prediction error is `e_i = y~_i - y_i`. Our object is minimizing 
this error given all the sample data. This is done by minimizing 
the following energy function:  
	
    E(a,b) = 0.5 sum((y~_i - y_i)^2)                         (2)
	       = 0.5 sum((y~_i - a * x_i - b)^2) 

### 2.2. Gradient
In order to solve this optimization problem, we employ the 
Gradient Descent (GD) algorithm to find local extreme of the 
energy function. Note that this local extreme is not necessary 
to be the global minima even though we need to reach that point. 

### 2.3. Gradient Descent
Given a point `P_i` at step `i-th`, the next point will be 
calculated as follows

    P_{i+1} = P_i - alpha * g_i

where `P_i = (a_i, b_i)` is the parameter vector that we want to
estimate, `g_i` is the normalized gradient, and `alpha` is the 
learning rate.

With the energy function given above, one can calculate the gradient 
with respect to `a` and `b`. The initial point can be a random point.
The gradient is given as:
    
    dE_i / da = sum(-x_i * (y~_i - a * x_i - b))
    dE_i / db = sum(-(y~_i - a * x_i - b))

The gradient `[d_E_i/da, dE_i/db]` then be normalized to `g_i`.

## 3. Requirements

Student have to write a program that perform the following jobs:
- Load parameters and data from a file
- Estimate the model with given parameters
- Estimate and evaluate the model using k-Fold method
	
### 3.1. Input data
The input will be read from the command line. This file 
contents some information for estimation process: 
- `num_iterations`: number of iterations in the algorithm
- `learning_rate`: learning rate of the GD algorithm
- `start_a` and `start_b`: initial point for estimation
- `num_folds`: parameter of k-fold algorithm
- `eval`: set to `0` will force the program print out 
estimation information including `a`, `b`, and `e` (error).

The file containing parameters of the algorithm has the
following format:

	------------------------------------------------------------
	Training and Validation Parameters 
	------------------------------------------------------------
	num_iterations:                      50
	learning_rate:                      0.1
	start_a:                              0
	start_b:                              0
	num_folds:                            3
	eval:                                 1

The data file has the following form:

	------------------------------------------------------------
	Data samples 
	------------------------------------------------------------
	76.87       153.78
	83.76       167.48
	
### 3.2. Evaluating the estimation
The data points will be divided into `k` segments. All we know is
is a set data and we need to evaluate the quality of our estimation.
Using the whole data set for estimation will not help us evaluate 
the estimation. Thus, by dividing data set into `k` segments, we 
can perform the estimation on `k-1` segments and use the remaining 
segment for evaluation.

The output of this estimation/evaluation is given as follows:

	---------------------------------------------------------------------------------
	Output of the validation 
	---------------------------------------------------------------------------------
	  2.000   0.010   5.070   0.010   0.015   0.100   0.200   0.350   0.200   0.015   0.010
	  2.000   0.010   5.070   0.010   0.015   0.100   0.200   0.350   0.200   0.015   0.010
	  2.000   0.010   5.070   0.010   0.015   0.100   0.200   0.350   0.200   0.015   0.010
Numbers are aligned on the right side, the width is 7, and precision is 3 (fixed format).
Each output is separated by a space ' '.

The first two numbers are the estimated value of `a` and `b`. The next number is 
the estimate error of the model. The last 10 numbers are the histogram of error on
the test dataset. The histogram is calculated in the following way:
- Divide the range [`mean - 3 * sigma`, `mean + 3 * sigma`] into ten intervals.
- Count error `e_i` in each interval and output the frequency of each interval (note 
that the sum of frequencies must be 1).

## 4. Implementation
**Students are given the following files:**
 - `main.cpp`: the source code with main() function
 - `commonLib.h`: header file containing prototypes
 - `commonLib.cpp`: source file implementing common functions declared in `commonLib.h`
 - `linearRegression.h`: header file containing prototypes for this problem
 - `linearRegression.cpp`: source file implementing functions used for this problem

__Student are given the following functions:__
 - `loadData`: read data from file
 - `loadParams`: read parameters from file 
 
In __`linearRegression.h`__, students are given basic prototypes
of functions that will be called in the program. They should not 
be modified. However, students can write additional functions 
that they want in their program (implemented in 
`linearRegression.cpp`).

In short, students can modify, customize, add functions in 
`linearRegression.h` and `linearRegression.cpp`.
They have to implement functions in `commonLib.cpp` 
but add no new function.

**Students cannot use any extra library for their code 
without permission from the lecturer**

**Update:** To make it easier for implementing the program, students can 
customize all data structures declared in `commonLib.h`. 

## 5. Build
Students can excute the build command by typing `make` from 
the command line on Linux. If everything is ok, the output file
`pf162a01` will present. It can be executed by the following 
command:
> `./pf162a01 inputData.txt inputConfig.txt`

For students who are using VisualStudio (VS) for developing on 
Windows, the source code can be added manually to a VS project. 
If they have cmake installed thenthey can also generate the 
project easily from the given source too.