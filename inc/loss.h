#ifndef _BLACKTEA_LOSS_H_
#define _BLACKTEA_LOSS_H_

#include "nerual_block.h"
class loss: public nerualBlock{
public:
    Matrix X;
    Matrix X_backward;
    Matrix print;
    Matrix forward(Matrix x, vector<int> y);
    Matrix backward();
};
#endif
