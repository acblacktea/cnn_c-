#ifndef _BLACKTEA_ACTIVATION_H_
#define _BLACKTEA_ACTIVATION_H_


#include "nerual_block.h"
enum activation_type{
    RELU,LINEAR
};

class activation {
public:
    activation(activation_type a) {
       type = a;
    }
    Matrix forward(Matrix X);
    Matrix backward(Matrix X);
    vector<vector<Matrix> > forward_cnn(vector<vector<Matrix> >X);
    vector<vector<Matrix> > backward_cnn(vector<vector<Matrix> >X);
    activation_type type;
    Matrix x_con;
    vector<vector<Matrix> > x_conv;
};

#endif
