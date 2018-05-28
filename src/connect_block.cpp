#include "connect_block.h"

Matrix connectBlock::forward(Matrix x) {
    if (W.h != x.w) {
      std::cerr << "connectBlock forward wrong!!" << std::cerr;
    }
    x_conn = x;
    Matrix ans = W * x;
    //cout << "debug " << endl;
    //cout << ans.w << "  " << ans.h << endl;
    for (int i = 0; i < ans.w; i++) {
        for (int j = 0; j < ans.h; j++) {
            ans.Ma[i][j] += b.Ma[0][i];
        }
    }
    return ans;
}

Matrix connectBlock::backward(Matrix Next) {
  int batch = Next.h;
  if (batch == 0) {
     std::cerr << "no data connent backward !!" << std::endl;
  }
  Matrix ans(x_conn.w, x_conn.h);
  ans.init(ZERO);

  //求上一层x导数
  for (int i = 0; i < x_conn.h; i++) {
    for (int j = 0; j < x_conn.w; j++) {
      for (int k = 0; k < W.w; k++) {
        ans.Ma[j][i] += Next.Ma[k][i] * W.Ma[k][j];
      }
    }
  }

  //求w, b导数
  for (int i = 0; i < batch; i++) {
      for (int j = 0; j < W.w; j++) {
        for (int k = 0; k < W.h; k++) {
           W_gradent.Ma[j][k] += x_conn.Ma[k][i] * Next.Ma[j][i];
        }
      }
  }

  for (int i = 0; i < batch; i++) {
    for (int j = 0; j < b.w; j++) {
      for (int k = 0; k < b.h; k++) {
        b_gradent.Ma[j][k] += Next.Ma[k][i];
      }
    }
  }

  //梯度下降
  /*
  for (int i = 0; i < W.w; i++) {
    for (int j = 0; j < W.h; j++) {
      W.Ma[i][j] -= W_gradent.Ma[i][j] * 0.001;
    }
  }

  for (int i = 0; i < b.w; i++) {
    for (int j = 0; j < b.h; j++) {
      b.Ma[i][j] -= b_gradent.Ma[i][j] * 0.001;
    }
  }
  */

  return ans;
}
