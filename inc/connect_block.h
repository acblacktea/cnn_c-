#ifndef _BLACKTEA_CONNECT_BLOCK_H_
#define _BLACKTEA_CONNECT_BLOCK_H_

#include "nerual_block.h"

class connectBlock : public nerualBlock{
public:
    connectBlock(int n,int m) {
      W = Matrix(n,m);
      W.init(XAVIER);
      b = Matrix(1,n);
      b.init(XAVIER);
      W_gradent = Matrix(n, m);
      W_gradent.init(ZERO);
      b_gradent = Matrix(1, n);
      b_gradent.init(ZERO);
    }
    Matrix forward(Matrix X);
    Matrix backward(Matrix X);
    Matrix W;
    Matrix b;
    Matrix W_gradent;
    Matrix b_gradent;
    Matrix x_conn;
    int layer, size;
};

#endif
