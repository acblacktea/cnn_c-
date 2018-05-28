#include "pool.h"

vector<vector<Matrix> > pool::forward_cnn(vector<vector<Matrix> >X) {
    vector<vector<Matrix> >ans;
    x_3d  = X;
    for (int i = 0; i < X.size(); i++) {
       vector<Matrix>tmp1;
       for (int j = 0; j < X[0].size(); j++) {
          Matrix tmp2((X[i][j].w - w)  + 1, (X[i][j].h - h) + 1);
          for (int k1 = 0; k1 < tmp2.w; k1++) {
            for (int k2 = 0; k2 < tmp2.h; k2++) {
                double pre = 0.0;
                if(type == MAX) {
                  pre = -111111111.000;
                }
                //cout << pre << endl;
                for (int k3 = 0; k3 < w; k3++) {
                   for (int k4 = 0; k4 < h; k4++) {
                      if (type == MAX) {
                        pre = std::max(pre, X[i][j].Ma[k1 + k3][k2 + k4]);
                      } else {
                        pre += X[i][j].Ma[k1 + k3][k2 + k4] / (w * h);
                      }
                   }
                }
                //cout << k1 << " " << k2 << endl;
                tmp2.Ma[k1][k2] = pre;
            }
          }
          tmp1.push_back(tmp2);
       }
       ans.push_back(tmp1);
   }
   return ans;
}

vector<vector<Matrix> > pool::backward_cnn(vector<vector<Matrix> >Next) {
  vector<vector<Matrix> >x_ans = x_3d;

  //x_ans.init(ZERO);
  for(int i = 0; i < x_ans.size(); i++) {
    for (int j = 0; j < x_ans[i].size(); j++) {
      x_ans[i][j].init(ZERO);
      //枚举起点
      for (int k1 = 0; k1 + w <= x_ans[i][j].w; k1++) {
        for (int k2 = 0; k2 + h <= x_ans[i][j].h; k2++) {
           int index_x = -1;
           int index_y = -1;
           double pre = -1000000.0;
           for (int  k3 = 0; k3 < w; k3++) {
              for (int k4 = 0; k4 < h; k4++) {
                if (x_3d[i][j].Ma[k1 + k3][k2 + k4] > pre) {
                  pre = x_3d[i][j].Ma[k1 + k3][k2 + k4];
                  index_x = k1 + k3;
                  index_y = k2 + k4;
                }
              }
           }
           //cout << index_x << " " << index_y << endl;
           x_ans[i][j].Ma[index_x][index_y] += Next[i][j].Ma[k1][k2];
        }
      }

    }
  }

  return x_ans;
}
