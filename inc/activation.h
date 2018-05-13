#ifndef _BLACKTEA_ACTIVATION_H_
#define _BLACKTEA_ACTIVATION_H_


#include "nerual_block.h"
enum activation_type{
    RELU,LINEAR
};

class activation {
public:
    activation(activation a) {
       type = a;
    }
    virtual Matrix forward(Matrix X);
    virtual Matrix backward(Matrix X);
    virtual vector<vector<Matrix> > forward_cnn(vector<vector<Matrix> >X);
    virtual vector<vector<Matrix> > backward_cnn(vector<vector<Matrix> >X);
    activation_type type;
    Matrix x_con;
    vector<vector<Matrix> > x_conv;
};

#endif
