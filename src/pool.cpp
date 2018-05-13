#include "pool.h"

vector<vector<Matrix> > pool::forward_cnn(vector<vector<Matrix> >X) {
    vector<vector<Matrix> >ans;
    x_3d  = X;
    for (int i = 0; i < X.size(); i++) {
       vector<Matrix>tmp1;
       for (int j = 0; j < X[0].size(); j++) {
          Matrix tmp2((x[i][j].w - w)  + 1, (x[i][j].h - h) + 1);
          for (int k1 = 0; k1 + w <= tmp2.w; k1++) {
            for (int k2 = 0; k2 + h <= tmp2.h; k2++) {
                double pre = 0.0;
                for (int k3 = 0; k3 < w; k3++) {
                   for (int k4 = 0; k4 < h < k4++) {
                      if (type == MAX) {
                        pre = std::max(pre, X[i][j].ma[k1 + k3][k2 + k4]);
                      } else {
                        pre += X[i][j].ma[k1 + k3][k2 + k4] / (w * h);
                      }
                   }
                }
                tmp2[k1][k2] = pre;
            }
          }
          tmp1.push_back(tmp2);
       }
       ans.push_back(tmp1);
   }
   return ans;
}

vector<vector> > pool::forward_cnn(vector<vector<Matrix> >Next) {
  x_ans = x_3d;

  x_ans.init(ZERO);
  for(int i = 0; i < x_ans.size(); i++) {
    for (int j = 0; j < x_ans[i].size(); j++) {
      x_ans[i][j].init(ZERO);
      //枚举起点
      for (int k1 = 0; k1 + w <= x_ans[i][j].w; k1++) {
        for (int k2 = 0; k2 + h <= x_ans[i][j].h; k2++) {
           int index_x = -1;
           int index_y = -1;
           double pre = -1000000;
           for (int  k3 = 0; k3 < w; k3++) {
              for (int k4 = 0; k4 < h; k4++) {
                if (x_3d[i][j].ma[k1 + k3][k2 + k4] > pre) {
                  pre = x_3d[i][j].ma[k1 + k3][k2 + k4];
                  index_x = k3;
                  index_y = k4;
                }
              }
           }

           x_ans[i][j].ma[index_x][index_y] += Next[i][j].ma[k1][k2];
        }
      }

    }
  }

  return ans;
}
