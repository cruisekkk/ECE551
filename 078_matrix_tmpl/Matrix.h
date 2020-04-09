#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

using std::vector;
//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  vector<T> ** rows;
 public:
  //default constructor
 Matrix() : numRows(0), numColumns(0), rows(NULL) {}

  //constructor
 Matrix(int r, int c) : numRows(r), numColumns(c), rows(new vector<T> *[r])
    {
      for (int i = 0; i < r; i++){
	rows[i] = new vector<T>(c);
      }
    }
  
 //copy constructor
 Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns),
    rows(new vector<T> *[numRows]) {
    for (int i = 0; i < numRows; i++) {
      rows[i] = new vector<T>(rhs[i]);
    }
  }
  
  //destructor
  ~Matrix(){
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }

  //assignment operator
  Matrix & operator=(const Matrix &rhs) {
    if (this != &rhs) {
      //temp
      vector<T> ** temprow = new vector<T> *[rhs.numRows];
      for (int i = 0; i < rhs.numRows; i++) {
      temprow[i] = new vector<T>(rhs[i]);
      }
      //delete
      for (int i = 0; i < numRows; i++) {
	delete rows[i];
      }
      delete[] rows;
      //assign
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = temprow;
    }
    return *this;
  }
  int getRows() const {
    return numRows;
  }
  int getColumns() const {
    return numColumns;
  }
  const vector<T> & operator[](int index) const{
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }
  
  vector<T> & operator[](int index){
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }
  bool operator==(const Matrix & rhs) const{
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
      return false;
    }
    for (int i = 0; i < numRows; i++) {
      if ((*this)[i] != rhs[i]) {
	return false;
      }
    }
    return true;
  }

  //+operator
  Matrix operator+(const Matrix & rhs) const{
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix ans(numRows, numColumns);
    ans.numColumns = numColumns;
    ans.numRows = numRows;
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
	ans[i][j] = (*this)[i][j] + rhs[i][j];
      }
    }
    return ans;
  }
  template <typename U>
    friend std::ostream & operator<<(std::ostream & s, const Matrix<U> & rhs);
};

template <typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }
  s << rhs[rhs.getRows() - 1] << " ]";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs){
  if (rhs.size() == 0) {
    s << "{  }";
    return s;
  }
  s << "{";
  for (size_t i = 0; i < rhs.size() -1; i++) {
    s << rhs[i] << ",";
  }
  s << rhs[rhs.size() -1] << "}";
  return s;
}






#endif
