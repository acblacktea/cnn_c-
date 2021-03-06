#include "cNN_block.h"

vector<vector<Matrix> > cnnBlock::forward_cnn(vector<vector<Matrix> >X) {

    batch_pic_x = X;
    if (X.size() != 0) {
      if (X[0].size() != channel) {
        std::cerr << "cnn_block forward err!" << std::endl;
      }
    }
    vector<vector<Matrix> >ans;
    for (int i = 0; i < X.size(); i++) {
      vector<Matrix> tmp1;
      for (int j = 0; j < len; j++) {
        Matrix tmp2(X[i][0].w - kernel_w  + 1, X[i][0].h - kernel_h + 1);
        tmp2.init(ZERO);
        for (int k1 = 0; k1 < tmp2.w; k1++) {
          for (int k2 = 0; k2 < tmp2.h; k2++) {

               double pre = 0.0;
               for (int k3 = 0; k3 < channel; k3++) {
                 for (int k4 = 0; k4 < kernel_w; k4++) {
                   for (int k5 = 0; k5 < kernel_h; k5++) {
                      pre += X[i][k3].Ma[k1 + k4][k2 + k5]
                          * kernel[j][k3].Ma[k4][k5];
                   }
                 }
               }
               tmp2.Ma[k1][k2] = pre;
               tmp2.Ma[k1][k2] += b.Ma[0][j];
          }
        }
        tmp1.push_back(tmp2);
      }
      ans.push_back(tmp1);
    }
   return ans;
}

vector<vector<Matrix> >cnnBlock::backward_cnn(vector<vector<Matrix> >next) {

  vector<vector<Matrix> >ans = batch_pic_x;
  grad_kernel = kernel;
  grad_b = b;
  grad_b.init(ZERO);
  //init 0
  for (int i = 0; i < ans.size(); i++) {
    for (int j = 0; j < ans[i].size(); j++) {
      ans[i][j].init(ZERO);
    }
  }

  for (int i = 0; i < kernel.size(); i++) {
    for (int j = 0; j < kernel[i].size(); j++) {
        grad_kernel[i][j].init(ZERO);
    }
  }

  for (int i = 0; i < batch_pic_x.size(); i++) {
          for(int  k1 = 0; k1 + kernel_w < batch_pic_x[i][0].w + 1; k1++) {
              for (int k2 = 0; k2 + kernel_h < batch_pic_x[i][0].h + 1; k2++) {
                  for(int k5 = 0; k5 < len; k5++) {
                    for (int j = 0; j < batch_pic_x[i].size(); j++) {
                      for (int k3 = 0; k3 < kernel_w; k3++) {
                          for (int k4 = 0; k4 < kernel_h; k4++) {
                              ans[i][j].Ma[k1 + k3][k2 + k4]
                                  += next[i][k5].Ma[k1][k2] * kernel[k5][j].Ma[k3][k4];
                              grad_kernel[k5][j].Ma[k3][k4] +=
                                  batch_pic_x[i][j].Ma[k1 + k3][k2 + k4] * next[i][k5].Ma[k1][k2];
                          }
                      }
                 }
                grad_b.Ma[0][k5] += next[i][k5].Ma[k1][k2];
            }
        }
      }
    }
    return ans;
}
