#ifndef _BLACKTEA_POOL_H_
#define _BLACKTEA_POOL_H_

#include "nerual_block.h"

enum pool_type{
  MAX,
  POOL
};
class pool : public nerualBlock {
public:
    pool(int a, int b, pool_type d):w(a), h(b), type(d){}
    vector<vector<Matrix> >forward_cnn(vector<vector<Matrix> >X);
    vector<vector<Matrix> >backward_cnn(vector<vector<Matrix> > X);
    int w, h;
    vector<vector<Matrix> >x_3d;
    pool_type type;
};


#endif
