/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Declaration of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_PROCESSDATA_H
#define DSA191_A1_PROCESSDATA_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cassert>

/// Prototype declaration
void Initialization();
void Finalization();

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &);

template <typename T>
void PrintReqOutput(const char* pRequest, T* pOutput, int);


#endif //DSA191_A1_PROCESSDATA_H
