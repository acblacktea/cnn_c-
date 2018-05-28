#include "activation.h"

static double trans(double va, activation_type type) {
   if (type == RELU) {
      return std::max(0.0, va);
   } else if (type == LINEAR) {
      return va;
   }
   return va;
}

Matrix activation::forward(Matrix x) {
    Matrix ans(x.w, x.h);
    for (int i = 0; i < x.w; i++) {
        for (int j = 0; j < x.h; j++) {
            ans.Ma[i][j] = trans(x.Ma[i][j], type);
        }
    }
    x_con = x;
    return ans;
}

vector<vector<Matrix> > activation::forward_cnn(vector<vector<Matrix> > X) {
    vector<vector<Matrix> >ans;
    for(int i = 0; i < X.size(); i++) {
        vector<Matrix> tmp1;
        for (int j = 0; j < X[i].size(); j++) {
            Matrix tmp2(X[i][j].w, X[i][j].h);
            for (int k1 = 0; k1 < X[i][j].w; k1++) {
                for (int k2 = 0; k2 < X[i][j].h; k2++) {
                    tmp2.Ma[k1][k2] = trans(X[i][j].Ma[k1][k2], type);
                }
            }
            tmp1.push_back(tmp2);
        }
        ans.push_back(tmp1);
    }
    x_conv = X;
    return ans;
}

double back_trans(double va, double next, activation_type type) {
   if (type == RELU) {
     if (va > 0.0) {
       return next;
     } else {
       return 0.0;
     }
   } else if (type == LINEAR) {
     return next;
   }

   return -1;
}

Matrix activation::backward(Matrix next) {
    Matrix ans(x_con.w, x_con.h);

    for (int i = 0; i < x_con.w; i++) {
      for (int j = 0; j < x_con.h; j++) {
          ans.Ma[i][j] = back_trans(x_con.Ma[i][j], next.Ma[i][j], type);
      }
    }

    return ans;
}

vector<vector<Matrix> > activation::backward_cnn(vector<vector<Matrix> > next) {
    vector<vector<Matrix> > ans;

    for (int i = 0; i < x_conv.size(); i++) {
      vector<Matrix>tmp;
      for (int j = 0; j < x_conv[i].size(); j++) {
        Matrix tmp2(x_conv[i][j].w, x_conv[i][j].h);

        for (int k1 = 0; k1 < x_conv[i][j].w; k1++) {
          for (int k2 = 0; k2 < x_conv[i][j].h; k2++) {
            tmp2.Ma[k1][k2] = back_trans(x_conv[i][j].Ma[k1][k2], next[i][j].Ma[k1][k2], type);
          }
        }

        tmp.push_back(tmp2);
      }
      ans.push_back(tmp);
    }
    return ans;
}
