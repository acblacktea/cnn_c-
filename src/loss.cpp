#include "loss.h"
#include <cmath>
Matrix loss::forward(Matrix x, vector<int> y) {
    X = x;
    Matrix ans(1, x.h);
    ans.init(ZERO);
    vector<double>sum(x.h);
    for (int i = 0; i < sum.size(); i++) {
      sum[i] = 0.0;
    }

    for (int i = 0; i < x.w; i++) {
      for (int j = 0; j < x.h; j++) {
        sum[j] += exp(x.Ma[i][j]);
      }
    }

    for (int i = 0; i < x.h; i++) {
       ans.Ma[0][i] = exp(x.Ma[y[i]][i]) / sum[i];
    }
    print = ans;

    X_backward = X;
    for (int i = 0; i < x.w; i++) {
      for (int j = 0; j < x.h; j++) {
        if (i != y[j]) {
          X_backward.Ma[i][j] = -1.0 * exp(x.Ma[i][j]) * exp(x.Ma[y[j]][j]) / (sum[j] * sum[j]);
        } else {
          X_backward.Ma[i][j] = ans.Ma[0][j] * (1.0 - ans.Ma[0][j]);
        }
      }
    }
    return ans;
}

Matrix loss::backward() {
  return X_backward;
}
