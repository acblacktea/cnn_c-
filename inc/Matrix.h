#ifndef _BLACKTEA_MATRIX_H_
#define _BLACKTEA_MATRIX_H_

#include<algorithm>
#include<cstdio>
#include<iostream>
#include<vector>

enum init_type{
    ZERO,XAVIER,ONE
};

class Matrix {
public:
    Matrix() {}
    Matrix(int n, int m) {
      for (int i = 0; i < n; i++) {
        vector<double>tmp(m);
        Ma.push_back(tmp);
      }
      w = n;
      h = m;
    }
    ~Matrix() {

    }
    vector<vector<double> >Ma;
    int w, h;
    Matrix operator+(Matrix &tmp)const;
    Matrix operator*(Matrix &tmp)const;
    Matrix operator^(Matrix &tmp, int n)const;
    void init(init_type type);
};
#endif
