#ifndef _BLACKTEA_CONNECT_BLOCK_H_
#define _BLACKTEA_CONNECT_BLOCK_H_

#include "nerual_block.h"

class conectBlock : public nerualBlock{
public:
    connectBlock(int n,int m) {
      W = Matrix(n,m);
      W.init(ZERO);
      b = Matirx(1,m);
      b.init(ZERO);
      W_gradent = Matrix(n, m);
      W_gradent.init(ZERO);
      b_gradent = Matrix(1, m);
      b_gradent.init(ZERO);
    }
private:
    Matrix forward(Matrix X);
    Matrix backward(Matrix X);
    Matrix W;
    Matrix b
    Matrix W_gradent;
    Matrix b_gradent;
    Matrix x_conn;
    int layer, size;
};

#endif
