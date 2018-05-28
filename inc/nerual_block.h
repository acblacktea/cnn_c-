#ifndef _BLACKTEA_NERUAL_BLOCK_H_
#define _BLACKTEA_NERUAL_BLOCK_H_

#include "Matrix.h"
#include <string>
class nerualBlock {
public:
    Matrix forward(Matrix X);
    Matrix backward(Matrix X);
    vector<vector<Matrix> > forward_cnn(vector<vector<Matrix> >X);
    vector<vector<Matrix> > backward_cnn(vector<vector<Matrix> >X);
    Matrix forward_flatten(vector<vector<Matrix> > X);
    vector<vector<Matrix> > backward_flatten(Matrix X);
};
#endif
