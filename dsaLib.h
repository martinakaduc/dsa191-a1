/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T& a) : data(a), pNext(NULL) {}
	  L1Item(T& a, L1Item<T>* _pNext) : data(a), pNext(_pNext) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List() {
      this->clean();
    }

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);// give the reference to the element i-th in the list
    T&      operator[](int i);// give the reference to the element i-th in the list

    bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
    int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

    int     push_back(T& a);// insert to the end of the list
    int     insertHead(T& a);// insert to the beginning of the list

    int     removeHead();// remove the beginning element of the list
    int     removeLast();// remove the last element of the list

    void    reverse();

    void    traverse(void (*op)(T&)) {
        // TODO: Your code goes here
        for (L1Item<T>* p = this->_pHead; p != nullptr; p = p->pNext) {
          op(p->data);
        }
    }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        // TODO: Your code goes here
        for (L1Item<T>* p = this->_pHead; p != nullptr; p = p->pNext) {
          op(p->data, pParam);
        }
    }
};

template <class T>
void L1List<T>::clean() {
  L1Item<T>* temp;
  while (this->_pHead != nullptr) {
    temp = this->_pHead;
    this->_pHead = this->_pHead->pNext;
    delete temp;
  }
  this->_size = 0;
}

template <class T>
T& L1List<T>::at(int i) {
  //if (i < 0 || i >= this->_size) return nullptr;
  L1Item<T>* outData = this->_pHead;
  //for (int k = 0; k < i; k++) {
    //outData = outData->pNext;
  //}
  while (i) {
	  outData = outData->pNext;
	  i--;
  }
  return outData->data;
}

template <class T>
T& L1List<T>::operator[](int i) {
	//if (i < 0 || i >= this->_size) return nullptr;
	L1Item<T>* outData = this->_pHead;
	//for (int k = 0; k < i; k++) {
	  //outData = outData->pNext;
	//}
	while (i) {
		outData = outData->pNext;
		i--;
	}
	return outData->data;
}

template <class T>
bool L1List<T>::find(T& a, int& idx){
  L1Item<T>* pLoc = this->_pHead;
  for (idx = 0; idx < this->_size; idx++) {
    if (pLoc->data.name == a.name) {
      return true;
    }
    pLoc = pLoc->pNext;
  }
  idx = -1;
  return false;
}

template <class T>
int L1List<T>::insert(int i, T& a){
  if (i < 0 || i > this->_size) return -1; // Allow insert into last

  //L1Item<T>* pNew = new L1Item<T>();
  //if (pNew == nullptr) return -1;

  //pNew->data = a;

  if (this->_pHead == nullptr || i == 0) {
    //pNew->pNext = this->_pHead;
    //this->_pHead = pNew;
	  this->_pHead = new L1Item<T>(a, this->_pHead);
  } else {
    L1Item<T>* pPre = this->_pHead;
    int index = 0;
    for (int k = 0; k < i - 1; k++) {
      pPre = pPre->pNext;
    }
	pPre->pNext = new L1Item<T>(a, pPre->pNext);
    //pNew->pNext = pPre->pNext;
    //pPre->pNext = pNew;
  }

  this->_size++;
  return 0;
}

template <class T>
int L1List<T>::remove(int i){
  if (i < 0 || i >= this->_size || this->_size == 0) return -1;

  L1Item<T>* pLoc = this->_pHead;
  if (i == 0) {
    this->_pHead = pLoc->pNext;
  } else {
    L1Item<T>* pPre = this->_pHead;
    int index = 0;
    for (int k = 0; k < i - 1; k++) {
      pPre = pPre->pNext;
    }
    pLoc = pPre->pNext;
    pPre->pNext = pLoc->pNext;
  }

  delete pLoc;
  this->_size--;
  return 0;
}

template <class T>
void L1List<T>::reverse(){
  L1Item<T>* pPre = nullptr;
  L1Item<T>* pLoc = this->_pHead;
  L1Item<T>* pNex = nullptr;

  while (pLoc != nullptr) {
    pNex = pLoc->pNext;
    pLoc->pNext = pPre;
    pPre = pLoc;
    pLoc = pNex;
  }
  this->_pHead = pPre;
}

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T &a) {
    // TODO: Your code goes here
    return this->insert(this->_size, a);
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a) {
    // TODO: Your code goes here
    return this->insert(0, a);
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
    // TODO: Your code goes here
    return this->remove(0);
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
    // TODO: Your code goes here
    return this->remove(this->_size-1);
}

#endif //DSA191_A1_DSALIB_H
