include"matrix.h"

Matrix Matrix::operator+(Matrix &tmp) {
    vector<vector<double> >Ma;
    int w, h;
    Matrix operator+(Matrix tmp) {
        if(w != tmp.w || h != tmp.h) {
            std::cerr << "Matrix add wrong size!" << std::endl;
            return NULL;
        }
        Matix ans(w, h);
        ans.init(ZERO);
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
               ans.Ma[i][j] = Mat[i][j] + tmp.Ma[i][j];
            }
        }
        return ans;
    }
}

Matrix Matrix::operator*(Matrix &tmp) {
    if (h != tmp.w) {
        std::cerr << "Matrix multiple wrong size" << std::endl;
        return NULL;
    }
    Matrix ans(w, h);
    ans.init(ZERO);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < tmp.h; j++) {
           for (int k = 0; k < h; k++)
            ans.Ma[i][j] += Ma[i][k] * tmp.Ma[k][j];
        }
    }
    return ans;
}

Matrix Matrix::operator^(Matrix tmp, int n) {
    Matrix ans(w, h);
    ans.init(ONE);
    while(n) {
        if (n & 1) {
          ans *= tmp;
          tmp *= tmp;
          n >>= 1;
        }
    }
    return ans;
}

void Matix::init(init_type type) {
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

    }
}

