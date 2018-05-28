#include "Matrix.h"
#include <time.h>


Matrix Matrix::operator+(Matrix &tmp)const {
    vector<vector<double> >Ma;
    if(w != tmp.w || h != tmp.h) {
        std::cerr << "Matrix add wrong size!" << std::endl;
    }
    Matrix ans(w, h);
    //cout << w << " " << h << endl;
    ans.init(ZERO);
    //cout << "start add" << endl;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
          //cout << i << " " << j << endl;
          //cout << ans.Ma[i][j] << endl;
          //cout << this->Ma[i][j] << endl;
          //cout << tmp.Ma[i][j] << endl;
          ans.Ma[i][j] = this->Ma[i][j] + tmp.Ma[i][j];
        }
    }
    //cout << "end" << endl;
    return ans;
}

Matrix Matrix::operator*(Matrix &tmp)const {
    if (h != tmp.w) {
        std::cerr << "Matrix multiple wrong size" << std::endl;
    }
    Matrix ans(w, tmp.h);
    ans.init(ZERO);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < tmp.h; j++) {
           for (int k = 0; k < h; k++)
            ans.Ma[i][j] += Ma[i][k] * tmp.Ma[k][j];
        }
    }
    return ans;
}

Matrix Matrix::operator^(int n)const {
    Matrix tmp = *this;
    Matrix ans(w, h);
    ans.init(ONE);
    while(n) {
        if (n & 1) {
          ans = ans * tmp;
          tmp = tmp * tmp;
          n >>= 1;
        }
    }
    return ans;
}

void Matrix::init(init_type type) {
    if (type == ZERO) {
      for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            Ma[i][j] = 0;
        }
      }
    }
    else if (type == ONE) {
      for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (i == j) Ma[i][j] = 1;
            else Ma[i][j] = 0;
        }
      }
    }
    else if (type == XAVIER) {
       for (int i = 0; i < w; i++) {
         for (int j = 0; j < h; j++) {
            Ma[i][j] = (rand() % 1000 - 500.0) / 500.0;
         }
       }
    }
}
