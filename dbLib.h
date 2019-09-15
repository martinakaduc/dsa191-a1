/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template <typename T>
bool reAllocA(T* &inPtr, int &curSize, int newSize, int ignorePos);

template <typename T>
void insertStation(T& TData, void* pParam);

struct Point2D {
  double x;
  double y;
  Point2D(): x(0), y(0) {}
  Point2D(double _x, double _y): x(_x), y(_y) {}
  Point2D& operator=(const Point2D& p) {
    this->x = p.x;
    this->y = p.y;
    return (*this);
  }
  bool operator==(const Point2D& p) {
    return (this->x == p.x && this->y == p.y);
  }
};

struct TStation {
   // The structure to store station information
   int id;
   string name;
   Point2D coords;
   int city_id;
   TStation(): id(-1), name(""), coords(Point2D(0, 0)), city_id(-1) {}
   TStation(int _id, string _name) : id(_id), name(_name), coords(Point2D(0, 0)), city_id(-1) {}
   TStation(int _id, string _name, Point2D _coords, int _city_id): id(_id), name(_name), coords(_coords), city_id(_city_id) {}
   bool updateStation(string _name, Point2D _coords);
};

struct TLine {
   // The structure to store line information
   int id;
   int city_id;
   TLine(): id(-1), city_id(-1), nStation(0), station(nullptr) {}
   TLine(int _id, int _city_id, int _nStation): id(_id), city_id(_city_id), nStation(_nStation), station(nullptr) {}
   TLine(const TLine &line): id(line.id), city_id(line.city_id), nStation(line.nStation), station(line.station) {}
   int nStation;
   int* station;
   bool appendStation(int station_id, int pos, int &result);
   bool removeStation(int station_id);
   template <typename T>
   friend bool reAllocA(T* &inPtr, int &curSize, int newSize);
};

struct TCity {
  // The structure to store city information
  int id;
  string name;
  TCity() : id(-1), name("") {}
  TCity(int _id, string _name) : id(_id), name(_name) {}
};

struct TTrack {
  // The structure to store track information
  int id;
  int nStation;
  Point2D* lineString;
  TTrack(): id(-1), nStation(0), lineString(nullptr) {}
  TTrack(int _id, int _nStation, Point2D* _lineString): id(_id), nStation(_nStation), lineString(_lineString) {}
  bool appendStationCoord(Point2D &station);
  int getStationByCoord(Point2D &station);
  bool removeStation(Point2D &station);
  template <typename T>
  friend bool reAllocA(T* &inPtr, int &curSize, int newSize);
};

class TDataset {
  // This class can be a container that help you manage your tables
public:
  L1List<TCity>* city;
  L1List<TLine>* line;
  L1List<TTrack>* track;
  L1List<TStation>* station;
  TDataset() : city(nullptr), line(nullptr), track(nullptr), station(nullptr) {}
  TDataset(L1List<TCity>* _city, L1List<TLine>* _line, L1List<TTrack>* _track, L1List<TStation>* _station) : city(_city), line(_line), track(_track), station(_station) {}
};

// Please add more or modify as needed

void LoadData(void* &);
void ReleaseData(void* &);

#endif //DSA191_A1_DBLIB_H
