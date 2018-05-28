#ifndef _BLACKTEA_FLATTEN_LAYER_H_
#define _BLACKTEA_FLATTEN_LAYER_H_

#include "nerual_block.h"

class flattenLayer : public nerualBlock {
public:
    flattenLayer(int a, int b, int c) : channel(a), w(b), h(c) {}
    Matrix forward_flatten(vector<vector<Matrix> >X);
    vector<vector<Matrix> > backward_flatten(Matrix X);
    int channel, w, h;
};


#endif
