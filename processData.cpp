/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"
#include "dsaLib.h"
#include "dbLib.h"

using namespace std;
/* TODO: You can implement methods, functions that support your data structures here.
 * */
struct ArrayOut {
  int* data;
  int size;
  ArrayOut(): data(nullptr), size(0) {}
  ArrayOut(int* _data, int _size): data(_data), size(_size) {}
  void push_back(int a) {
    int* newData = new int[this->size+1];
    for (int i = 0; i < this->size; i++) {
      newData[i] = this->data[i];
    }
    newData[this->size] = a;
    this->size++;
    delete [] data;
    data = newData;

  }
};

struct IdxCoord {
  Point2D coord;
  int idx;
};

 template <typename T>
 void countLine(T& TData, void* pParam) {
   int* paras = (int*) pParam;
   if (TData.city_id == paras[0]) {
     paras[1]++;
   }
 }

 template <typename T>
 void listMatch(T& TData, void* pParam) {
   ArrayOut* paras = (ArrayOut*) pParam;
   if (TData.city_id == paras->data[0]) {
     // cout << "Matched\n";
     paras->push_back(TData.id);
   }
 }

 template <typename T>
 void findIdxById(T& TData, void* pParam) {
   int* paras = (int*) pParam;
   if (TData.id == paras[0]) {
     paras[1] = paras[2];
   }
   paras[2]++;
 }

 template <typename T>
 void findMaxId(T& TData, void* pParam) {
   int* paras = (int*) pParam;
   if (TData.id > *paras) {
     *paras = TData.id;
   }
 }

 template <typename T>
 void removeStationById(T& TData, void* pParam) {
   int* paras = (int*) pParam;
   TData.removeStation(*paras);
 }

 template <typename T>
 void removeStationByCoords(T& TData, void* pParam) {
   Point2D* paras = (Point2D*) pParam;
   TData.removeStation(*paras);
 }

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number
    TDataset* pDataset = (TDataset*) pData;

    if (pRequest[0] == 'C' && pRequest[1] == 'L' && strlen(pRequest) == 2) {
      N = 1;
      int* pOutputt = new int();
      *pOutputt = pDataset->line->getSize();
      pOutput = (void*) pOutputt;

    } else if (pRequest[0] == 'C' && pRequest[1] == 'L' && pRequest[2] == ' ' && strlen(pRequest) > 3) {
      int city_idx = -1;
      string name = pRequest;
      name = name.substr(name.find(' ')+1);
      TCity findCity = TCity(-1, name);
      pDataset->city->find(findCity, city_idx);

      if (city_idx == -1) {
        N = 1;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }

      int* paras = new int[2];
      paras[0] = pDataset->city->at(city_idx).id;
      paras[1] = 0;
      pDataset->line->traverse(countLine, (void*) paras);

      N = 1;
      int* pOutputt = new int();
      *pOutputt = paras[1];
      pOutput = (void*) pOutputt;

    } else if (pRequest[0] == 'L' && pRequest[1] == 'S' && pRequest[2] == 'C' && pRequest[3] == ' ' && strlen(pRequest) > 4) {
      int city_idx = -1;
      string name = pRequest;
      name = name.substr(name.find(' ')+1);
      TCity findCity = TCity(-1, name);
      pDataset->city->find(findCity, city_idx);

      if (city_idx == -1) {
        N = 0;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }

      ArrayOut* paras = new ArrayOut();
      paras->push_back(pDataset->city->at(city_idx).id);
      pDataset->station->traverse(listMatch, (void*) paras);

      N = paras->size - 1;
      int* pOutputt = new int[N];
      for (int i = 0; i < N; i++) {
        pOutputt[i] = paras->data[i+1];
      }
      pOutput = (void*) pOutputt;

      // LSC Shanghai
    } else if (pRequest[0] == 'L' && pRequest[1] == 'L' && pRequest[2] == 'C' && pRequest[3] == ' ' && strlen(pRequest) > 4) {
      int city_idx = -1;
      string name = pRequest;
      name = name.substr(name.find(' ')+1);
      TCity findCity = TCity(-1, name);
      pDataset->city->find(findCity, city_idx);

      if (city_idx == -1) {
        N = 0;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }

      ArrayOut* paras = new ArrayOut();
      paras->push_back(pDataset->city->at(city_idx).id);
      pDataset->line->traverse(listMatch, (void*) paras);

      N = paras->size - 1;
      int* pOutputt = new int[N];
      for (int i = 0; i < N; i++) {
        pOutputt[i] = paras->data[i+1];
      }
      pOutput = (void*) pOutputt;

      // LLC Shanghai
    } else if (pRequest[0] == 'L' && pRequest[1] == 'S' && pRequest[2] == 'L' && pRequest[3] == ' ' && strlen(pRequest) > 4) {
      string request = pRequest;
      int line_id = stoi(request.substr(request.find(' ')+1));

      int* paras = new int[3];
      paras[0] = line_id;
      paras[1] = -1;
      paras[2] = 0;
      pDataset->line->traverse(findIdxById, (void*) paras);

      if (paras[1] == -1) {
        N = 0;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }

      TLine line = pDataset->line->at(paras[1]);

      N = line.nStation;
      int* pOutputt = new int[N];
      for (int i = 0; i < N; i++) {
        pOutputt[i] = line.station[i];
      }
      pOutput = (void*) pOutputt;

      // LSL 494
    } else if (pRequest[0] == 'F' && pRequest[1] == 'C' && pRequest[2] == ' ' && strlen(pRequest) > 3) {
      int city_idx = -1;
      string name = pRequest;
      name = name.substr(name.find(' ')+1);
      TCity findCity = TCity(-1, name);
      pDataset->city->find(findCity, city_idx);

      if (city_idx == -1) {
        N = 1;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }

      N = 1;
      int* pOutputt = new int();
      *pOutputt = pDataset->city->at(city_idx).id;
      pOutput = (void*) pOutputt;

    } else if (pRequest[0] == 'F' && pRequest[1] == 'S' && pRequest[2] == ' ' && strlen(pRequest) > 3) {
      int station_idx = -1;
      string name = pRequest;
      name = name.substr(name.find(' ')+1);
      TStation findStation = TStation(-1, name);
      pDataset->station->find(findStation, station_idx);

      if (station_idx == -1) {
        N = 1;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }

      N = 1;
      int* pOutputt = new int();
      *pOutputt = pDataset->station->at(station_idx).id;
      pOutput = (void*) pOutputt;

    } else if (pRequest[0] == 'S' && pRequest[1] == 'L' && pRequest[2] == 'P' && pRequest[3] == ' ' && strlen(pRequest) > 4) {
      string request = pRequest;
      request = request.substr(request.find(' ')+1);
      int station_id = stoi(request.substr(0, request.find(' ')));
      int track_id = stoi(request.substr(request.find(' ')+1));

      int* paras = new int[3];

      paras[0] = station_id;
      paras[1] = -1;
      paras[2] = 0;
      pDataset->station->traverse(findIdxById, (void*) paras);

      if (paras[1] == -1) {
        N = 1;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }
      int station_idx = paras[1];

      paras[0] = track_id;
      paras[1] = -1;
      paras[2] = 0;
      pDataset->track->traverse(findIdxById, (void*) paras);

      if (paras[1] == -1) {
        N = 1;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }
      int track_idx = paras[1];

      int station_pos = pDataset->track->at(track_idx).getStationByCoord(pDataset->station->at(station_idx).coords);

      N = 1;
      int* pOutputt = new int();
      *pOutputt = station_pos;
      pOutput = (void*) pOutputt;

      // SLP 13219 7992
    } else if (pRequest[0] == 'I' && pRequest[1] == 'S' && pRequest[2] == ' ' && strlen(pRequest) > 3) {
      string csv_description = pRequest;
      csv_description = csv_description.substr(csv_description.find(' ')+1);

      int* id_max = new int();
      *id_max = -1;
      pDataset->station->traverse(findMaxId, (void*) id_max);

      TStation aStation;
      aStation.id = ++(*id_max);

      stringstream csvStream(csv_description);
      string eachCol;
      int colOrder = 0;
      while (getline(csvStream, eachCol, ',')) {
        if (colOrder == 0) {
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
        } else if (colOrder == 1) {
          Point2D coords;
          int spiltPoint = eachCol.find(' ');
          coords.x = stof(eachCol.substr(6, spiltPoint - 6));
          coords.y = stof(eachCol.substr(spiltPoint+1, eachCol.length() - spiltPoint - 2));
          aStation.coords = coords;
        } else {
          continue;
        }
        colOrder++;
      }

      pDataset->station->push_back(aStation);

      N = 1;
      pOutput = (void*) id_max;

    } else if (pRequest[0] == 'R' && pRequest[1] == 'S' && pRequest[2] == ' ' && strlen(pRequest) > 3) {
      string request = pRequest;
      request = request.substr(request.find(' ')+1);
      int station_id = stoi(request);

      int* paras = new int[3];
      paras[0] = station_id;
      paras[1] = -1;
      paras[2] = 0;
      pDataset->station->traverse(findIdxById, (void*) paras);

      if (paras[1] == -1) {
        N = 1;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }

      delete [] paras;
      paras = new int();
      *paras = station_id;
      pDataset->line->traverse(removeStationById, (void*) paras);

      Point2D* coords = new Point2D();
      *coords = pDataset->station->at(paras[1]).coords;
      pDataset->track->traverse(removeStationByCoords, (void*) coords);

      pDataset->station->remove(paras[1]);

      N = 1;
      int* pOutputt = new int();
      *pOutputt = 0;
      pOutput = (void*) pOutputt;

    } else if (pRequest[0] == 'U' && pRequest[1] == 'S' && pRequest[2] == ' ' && strlen(pRequest) > 3) {
      string request = pRequest;
      request = request.substr(request.find(' ')+1);
      int station_id = stoi(request.substr(0, request.find(' ')));
      string csv_description = request.substr(request.find(' ')+1);

      int* paras = new int[3];
      paras[0] = station_id;
      paras[1] = -1; // Station index
      paras[2] = 0;
      pDataset->station->traverse(findIdxById, (void*) paras);

      if (paras[1] == -1) {
        N = 1;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }

      string name;
      Point2D coords;

      stringstream csvStream(csv_description);
      string eachCol;
      int colOrder = 0;
      while (getline(csvStream, eachCol, ',')) {
        if (colOrder == 0) {
          if (eachCol == """") {
            colOrder++;
            continue;
          }
          if (eachCol[0] == '"') {
            if (eachCol[eachCol.length() - 1] == '"') {
              name = eachCol.substr(1, eachCol.length()-2);
            } else {
              name = eachCol.substr(1) + ',';
              continue;
            }
          } else if (eachCol[eachCol.length() - 1] == '"') {
            name = name + eachCol.substr(0, eachCol.length()-1);
          } else if (name != ""){
            name = name + eachCol + ',';
            continue;
          } else {
            name = eachCol;
          }
        } else if (colOrder == 1) {
          int spiltPoint = eachCol.find(' ');
          coords.x = stof(eachCol.substr(6, spiltPoint-6));
          coords.y = stof(eachCol.substr(spiltPoint+1, eachCol.length()-spiltPoint-2));
        } else {
          continue;
        }
        colOrder++;
      }

      bool result = pDataset->station->at(paras[1]).updateStation(name, coords);

      N = 1;
      int* pOutputt = new int();
      *pOutputt = result - 1;
      pOutput = (void*) pOutputt;

      // FS Glonnières - Centre Sud
      // US 13219 "Duc ,Dep Trai",POINT(0.2167901 47.9721115),,2007,999999
      // FS Duc Dep Trai
    } else if (pRequest[0] == 'I' && pRequest[1] == 'S' && pRequest[2] == 'L' && pRequest[3] == ' ' && strlen(pRequest) > 4) {
      string request = pRequest;
      request = request.substr(request.find(' ')+1);
      int station_id = stoi(request.substr(0, request.find(' ')));
      request = request.substr(request.find(' ')+1);
      int line_id = stoi(request.substr(0, request.find(' ')));
      int pos = stoi(request.substr(request.find(' ') + 1));

      int* paras = new int[3];

      paras[0] = station_id;
      paras[1] = -1;
      paras[2] = 0;
      pDataset->station->traverse(findIdxById, (void*) paras);

      if (paras[1] == -1) {
        N = 1;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }

      delete[] paras;

      paras = new int[4];
      paras[0] = line_id;
      paras[1] = station_id;
      paras[2] = pos;
      paras[3] = -1; // result
      pDataset->line->traverse(insertStation, (void*) paras);

      N = 1;
      int* pOutputt = new int();
      *pOutputt = paras[3];
      pOutput = (void*) pOutputt;

      // LSL 494
      // ISL 6100 494 0
      // LSL 494
    } else if (pRequest[0] == 'R' && pRequest[1] == 'S' && pRequest[2] == 'L' && pRequest[3] == ' ' && strlen(pRequest) > 4) {
      string request = pRequest;
      request = request.substr(request.find(' ')+1);
      int station_id = stoi(request.substr(0, request.find(' ')));
      int line_id = stoi(request.substr(request.find(' ') + 1));

      int* paras = new int[3];
      paras[0] = line_id;
      paras[1] = -1;
      paras[2] = 0;
      pDataset->line->traverse(findIdxById, (void*) paras);

      if (paras[1] == -1) {
        N = 1;
        int* pOutputt = new int();
        *pOutputt = -1;
        pOutput = (void*) pOutputt;
        return;
      }

      bool result = pDataset->line->at(paras[1]).removeStation(station_id);

      N = 1;
      int* pOutputt = new int();
      *pOutputt = result - 1;
      pOutput = (void*) pOutputt;

      // LSL 494
      // RSL 6100 494
      // LSL 494
    } else {
      return;
    }

}
