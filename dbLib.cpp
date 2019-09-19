/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

template <typename T>
bool reAllocA(T* &inPtr, int &curSize, int newSize, int ignorePos) {
  if (newSize == 0) return false;
  if (ignorePos >= newSize) return false;

  T* outPtr = new T[newSize];
  if (outPtr == nullptr) return false;

  if (curSize > newSize) {
    curSize = newSize;
  }
  for (int i = 0; i < curSize; i++) {
    outPtr[i+(i >= ignorePos)] = inPtr[i];
  }
  delete [] inPtr;
  inPtr = outPtr;
  curSize = newSize;
  return true;
}

bool TStation::updateStation(string _name, Point2D _coords) {
  this->name = _name;
  this->coords = _coords;
  return true;
}

bool TLine::appendStation(int station_id, int pos, int &result) {
  if (pos == -1) pos = this->nStation;
  else {
    for (int i = 0; i < this->nStation; i++) {
      if (this->station[i] == station_id) return false;
    }
  }
  bool allocSuccess = reAllocA<int>(this->station, this->nStation, this->nStation + 1, pos);
  if (!allocSuccess) return false;
  this->station[pos] = station_id;
  result = 0;
  return true;
}

bool TLine::removeStation(int station_id) {
  int i = 0;
  while (i < this->nStation) {
    if (this->station[i] == station_id) {
      this->nStation--;
      for (int k = i; k < this->nStation; k++) {
        this->station[k] = this->station[k+1];
      }
      return true;
    }
    i++;
  }
  return false;
}

bool TTrack::appendStationCoord(Point2D &station) {
  bool allocSuccess = reAllocA(this->lineString, this->nStation, this->nStation + 1, this->nStation);
  if (!allocSuccess) return false;
  this->lineString[this->nStation - 1] = station;
  return true;
}

int TTrack::getStationByCoord(Point2D &station) {
  for (int i = 0; i < this->nStation; i++) {
    if (this->lineString[i] == station) {
      return i;
    }
  }
  return -1;
}

bool TTrack::removeStation(Point2D &station) {
  int i = 0;
  while (i < this->nStation) {
    if (this->lineString[i] == station) {
      // cout << "Removing...";
      this->nStation--;
      for (int k = i; k < this->nStation; k++) {
        this->lineString[k] = this->lineString[k+1];
      }
      return true;
    }
    i++;
  }
  return false;
}

template <typename T>
void insertStation(T& TData, void* pParam) {
  int* paras = (int*) pParam;
  if (paras[3] == 0) return; // Successfully inserted
  if (TData.id == paras[0]) {
    TData.appendStation(paras[1], paras[2], paras[3]);
  }
}

 void LoadData(void* &pData) {
   ifstream readFile;
   string lineString;
   int colOrder;
   int city_id;

   // ========================================================
   // =                       READ CITIES                    =
   // ========================================================
   readFile.open("cities.csv");
   L1List<TCity>* citiData = new L1List<TCity>();
   colOrder = -1;

   while(getline(readFile, lineString)) {
     if (colOrder == -1) {
       colOrder = 0;
       continue;
     }

     TCity aCity = TCity();

     if (lineString.length() == 0) continue;
     stringstream lineStream(lineString);
     string eachCol;
     colOrder = 0;

     while (getline(lineStream, eachCol, ',')) {
       if (colOrder == 0) {
         aCity.id = stoi(eachCol);
       } else if (colOrder == 1) {
         if (eachCol == """") {
           colOrder++;
           continue;
         }
         if (eachCol[0] == '"') {
           if (eachCol[eachCol.length() - 1] == '"') {
             aCity.name = eachCol.substr(1, eachCol.length()-2);
           } else {
             aCity.name = eachCol.substr(1) + ',';
             continue;
           }
         } else if (eachCol[eachCol.length() - 1] == '"') {
           aCity.name = aCity.name + eachCol.substr(0, eachCol.length()-1);
         } else if (aCity.name != ""){
           aCity.name = aCity.name + eachCol + ',';
           continue;
         } else {
           aCity.name = eachCol;
         }
       } else {
         break;
       }
       colOrder++;
     }

     citiData->push_back(aCity);
   }

   readFile.close();

   // citiData->insert(citiData->getSize(), (*citiData)[0]);
   // citiData->insertHead((*citiData)[citiData->getSize()-1]);
   // citiData->removeLast();
   // citiData->remove(citiData->getSize()-1);
   // citiData->reverse();
   // int idx = -1;
   // citiData->find(citiData->at(10), idx);
   // for (int i = 0; i < citiData->getSize(); i++) {
   //   TCity tempCity = citiData->at(i);
   //   cout << tempCity.id << '\t' << tempCity.name << '\n';
   // }


   // ========================================================
   // =                       READ LINES                     =
   // ========================================================
   readFile.open("lines.csv");
   L1List<TLine>* lineData = new L1List<TLine>();
   colOrder = -1;
   city_id = -1;

   while(getline(readFile, lineString)) {
     if (colOrder == -1) {
       colOrder = 0;
       continue;
     }

     TLine aLine = TLine();

     if (lineString.length() == 0) continue;
     stringstream lineStream(lineString);
     string eachCol;
     colOrder = 0;

     while (getline(lineStream, eachCol, ',')) {
       if (colOrder == 0) {
         aLine.id = stoi(eachCol);
       } else if (colOrder == 1) {
         aLine.city_id = stoi(eachCol);
       } else {
         break;
       }
       colOrder++;
     }

     lineData->push_back(aLine);
   }

   readFile.close();

   // for (int i = 0; i < lineData->getSize(); i++) {
   //   TLine tempLine = lineData->at(i);
   //   cout << tempLine.id << '\t' << tempLine.city_id << '\n';
   // }
   // for (int i = 0; i < citiData->getSize(); i++) {
   //   cout << citiData->at(i).nLine << '\n';
   // }


   // ========================================================
   // =                    READ STATIONS                     =
   // ========================================================
   readFile.open("stations.csv");
   L1List<TStation>* stationData = new L1List<TStation>();
   colOrder = -1;
   city_id = -1;
   Point2D coords;
   int spiltPoint = 0;

   while(getline(readFile, lineString)) {
     if (colOrder == -1) {
       colOrder = 0;
       continue;
     }

     TStation aStation = TStation();

     if (lineString.length() == 0) continue;
     stringstream lineStream(lineString);
     string eachCol;
     colOrder = 0;

     while (getline(lineStream, eachCol, ',')) {
       if (colOrder == 0) {
         aStation.id = stoi(eachCol);
       } else if (colOrder == 1) {
         if (eachCol == """") {
           colOrder++;
           continue;
         }
         if (eachCol[0] == '"') {
           if (eachCol[eachCol.length() - 1] == '"') {
             aStation.name = eachCol.substr(1, eachCol.length()-2);
           } else {
             aStation.name = eachCol.substr(1) + ',';
             continue;
           }
         } else if (eachCol[eachCol.length() - 1] == '"') {
           aStation.name = aStation.name + eachCol.substr(0, eachCol.length()-1);
         } else if (aStation.name != ""){
           aStation.name = aStation.name + eachCol + ',';
           continue;
         } else {
           aStation.name = eachCol;
         }
       } else if (colOrder == 2) {

         spiltPoint = eachCol.find(' ');
         coords.x = stof(eachCol.substr(6, spiltPoint-6));
         coords.y = stof(eachCol.substr(spiltPoint+1, eachCol.length()-spiltPoint-2));
         aStation.coords = coords;
       } else if (colOrder == 6) {
         aStation.city_id = stoi(eachCol);
       }
       colOrder++;
     }

     stationData->push_back(aStation);
   }

   readFile.close();
   // for (int i = 0; i < stationData->getSize(); i++) {
   //   TStation tempStation = stationData->at(i);
   //   if (tempStation.city_id == -1)
   //     cout << tempStation.id << '\t' << tempStation.city_id << '\n';
   // }


   // ========================================================
   // =                 READ STATION_LINES                   =
   // ========================================================
   readFile.open("station_lines.csv");
   colOrder = -1;
   int line_id = -1;
   int station_id = -1;

   while(getline(readFile, lineString)) {
     if (colOrder == -1) {
       colOrder = 0;
       continue;
     }

     if (lineString.length() == 0) continue;
     stringstream lineStream(lineString);
     string eachCol;
     colOrder = 0;

     while (getline(lineStream, eachCol, ',')) {
       if (colOrder == 1) {
         station_id = stoi(eachCol);
       } else if (colOrder == 2) {
         line_id = stoi(eachCol);
       } else if (colOrder > 2) {
         break;
       }
       colOrder++;
     }

     int *insertParas = new int[2];

     insertParas[0] = line_id;
     insertParas[1] = station_id;
     insertParas[2] = -1;
     insertParas[3] = -1;
     lineData->traverse(insertStation, (void*) insertParas);

   }

   readFile.close();


   // ========================================================
   // =                     READ TRACKS                      =
   // ========================================================
   readFile.open("tracks.csv");
   L1List<TTrack>* trackData = new L1List<TTrack>();
   colOrder = -1;
   int track_id = -1;

   while(getline(readFile, lineString)) {
     if (colOrder == -1) {
       colOrder = 0;
       continue;
     }

     TTrack aTrack = TTrack();

     if (lineString.length() == 0) continue;
     stringstream lineStream(lineString);
     string eachCol;
     colOrder = 0;

     while (getline(lineStream, eachCol, ',')) {
       if (colOrder == 0) {
         aTrack.id = stoi(eachCol);
       } else if (colOrder == 1) {
         if (eachCol == "LINESTRING Z EMPTY") break;

         if (eachCol[0] == '"') {
           eachCol = eachCol.substr(12);
         } else if (eachCol[eachCol.length() - 1] == '"') {
           eachCol = eachCol.substr(0, eachCol.length() - 2);

           spiltPoint = eachCol.find(' ');
           coords.x = stof(eachCol.substr(0, spiltPoint));
           coords.y = stof(eachCol.substr(spiltPoint + 1));

           aTrack.appendStationCoord(coords);

           break;
         }
         spiltPoint = eachCol.find(' ');
         coords.x = stof(eachCol.substr(0, spiltPoint));
         coords.y = stof(eachCol.substr(spiltPoint + 1));

         aTrack.appendStationCoord(coords);
         continue;

       } else if (colOrder > 1) {
         break;
       }
       colOrder++;
     }

     trackData->push_back(aTrack);
   }

   readFile.close();

   TDataset* pDataset = new TDataset(citiData, lineData, trackData, stationData);
   pData = (void*) pDataset;
 }

 void ReleaseData(void* &pData) {
   TDataset* pDataset = (TDataset*) pData;
   delete pDataset->city;
   pDataset->city = nullptr;
   delete pDataset->line;
   pDataset->line = nullptr;
   delete pDataset->track;
   pDataset->track = nullptr;
   delete pDataset->station;
   pDataset->station = nullptr;
   delete pDataset;
   pDataset = nullptr;
 }
