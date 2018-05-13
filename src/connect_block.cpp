#include "nerual_block.cpp"

Matrix connectBlock::forward(Matrix x) {
    if (W.h != x.w) {
      std::cerr << "connectBlock forward wrong!!" << std::cerr;
      return NULL;
    }
    x_conn = x;
    Matrix ans = W * x;
    for (int i = 0; i < ans.w; i++) {
        for (int j = 0; j < ans.h; j++) {
            ans.ma[i][j] += b.ma[0][j];
        }
    }
    return W * x;
}

Matrix connectBlock::backward(Matrix Next) {
  int batch = Next.w;
  if (batch == 0) {
     std::cerr << "no data connent backward !!" << std::endl;
     return NULL;
  }
  Matrix ans(batch, n);
  ans.init(ZERO);

  //求上一层x导数
  for (int i = 0; i < W.w; i++) {
    for (int j = 0; j < W.h; j++) {
      for (int k = 0; k < Next.h; k++) {
        ans.ma[i][j] += Next.ma[i][k] * W.ma[j][k];
      }
    }
  }

  //求w, b导数
  for (int i = 0; i < batch; i++) {
      for (int j = 0; j < W.w; j++) {
        for (int k = 0; k < W.h; k++) {
           W_gradent.ma[j][k] += x_conn.ma[i][j] * Next[i][k]/ batch;
        }
      }
  }

  for (int i = 0; i < batch; i++) {
    for (int j = 0; j < b.w; j++) {
      for (int k = 0; k < b.h; k++) {
        b_gradent.ma[j][k] += x_conn.ma[i][j] / batch;
      }
    }
  }

  //梯度下降
  for (int i = 0; i < W.w; i++) {
    for (int j = 0; j < W.h; j++) {
      W.ma[i][j] -= W_gradent.ma[i][j] * 0.001;
    }
  }

  for (int i = 0; i < b.w; i++) {
    for (int j = 0; j < b.h; j++) {
      b.ma[i][j] -= b_gradent.ma[i][j] * 0.001;
    }
  }

  return ans;
}
