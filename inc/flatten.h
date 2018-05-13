#ifndef _BLACKTEA_NERUAL_BLOCK_H_
#define _BLACKTEA_NERUAL_BLOCK_H_

#include "nerual_block.h"

class flattenLayer : public nerualBlock {
    flattenLayer(int a, int b, int c) : channel(a), w(b), h(c) {}
    Matrix forward_flatten(vector<vector<Matrix> >X);
    Matrix backward_flatten(vector<vector<Matrix> >X);
    int channel, w, h;
};


#endif
