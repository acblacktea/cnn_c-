#include "flatten.h"

Matrix flattenLayer::forward_flatten(vector<vector<Matrix> >X) {
    int w = X.size();
    int h = 1;
    if (X.size() && X[0].size()) {
       h *= X[0].size() * X[0][0].w * X[0][0].h;
    } else {
       h = 0;
    }
    Matrix ans(h, w);
    for (int i = 0; i < X.size(); i++) {
       for (int j = 0; j < X[i].size(); j++) {
           for (int k1 = 0; k1 < X[i][j].w; k1++) {
               for (int k2 = 0; k2 < X[i][j].h; k2++) {
                    //cout << j * X[i][j].w * X[i][j].h + k1 * X[i][j].h + k2 << "  " <<
                    //  i << "  " << X[i][j].Ma[k1][k2] << endl;
                    ans.Ma[j * X[i][j].w * X[i][j].h + k1 * X[i][j].h + k2][i] =
                        X[i][j].Ma[k1][k2];
               }
           }
       }
    }
    return ans;
}

vector<vector<Matrix> > flattenLayer::backward_flatten(Matrix X) {
   vector<vector<Matrix> >ans;

   for (int i = 0; i < X.h; i++) {
     int cnt = 0;
     vector<Matrix>tmp;
     for (int j = 0; j < channel; j++) {
       Matrix tmp2(w, h);
       tmp2.init(ZERO);
       for (int k1 = 0; k1 < w; k1++) {
         for (int k2 = 0; k2 < h; k2++) {
           tmp2.Ma[k1][k2] = X.Ma[cnt++][i];
         }
       }
       tmp.push_back(tmp2);
     }
     ans.push_back(tmp);
   }
   return ans;
}
