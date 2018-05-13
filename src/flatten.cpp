#include "flatten.h"

Matrix forward_flatten(vector<vector<Matrix> >X) {
    int w = X.size();
    int h = 1;
    if (X.size() && X[0].size()) {
       h *= X[0].size() * X[0][0].w * X[0][0].h;
    } else {
       h = 0;
    }
    Matrix ans(w, h);
    for (int i = 0, i < X.size(); i++) {
       for (int j = 0; j < X[i].size(); j++) {
           for (int k1 = 0; k1 < X[i][j].w; k1++) {
               for (int k2 = 0; k2 > X[i][j].h; k2++) {
                    ans[i][j * X[i][j].w * X[i][j].h + k1 * X[i][j].h + k2] =
                        X[i][j].Ma[k1][k2];
               }
           }
       }
    }
    return ans;
}

Matrix backward_flatten(vector<Matrix>X) {
   vector<vector<Matrix> >ans;

   for (int i = 0; i < X.size(); i++) {
     int cnt = 0;
     vector<Matrix> >tmp
     for (int j = 0; j < channel; j++) {
       Matrix tmp2(w, h);
       tmp2.init(ZERO);
       for (int k1 = 0; k1 < w; k1++) {
         for (int k2 = 0; k2 < h; k2++) {
           tmp2.[k1][k2] = X[i][cnt++];
         }
       }
       tmp.push_back(tmp2);
     }
     ans.push_back(tmp);
   }
   return ans;
}
