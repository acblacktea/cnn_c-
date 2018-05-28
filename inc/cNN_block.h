#ifndef _CNN_BLOCK_H_
#define _CNN_BLOCK_H_

#include "nerual_block.h"

class cnnBlock: public nerualBlock{
public:
    cnnBlock(int l,int c, int w, int h) {
        len = l;
        channel = c;
        kernel_w = w;
        kernel_h = h;
        for (int i = 0; i < len; i++) {
           vector<Matrix> tmp1;
           for (int j = 0; j < c ; j++) {
             Matrix tmp2(w, h);
             tmp2.init(XAVIER);
             tmp1.push_back(tmp2);
           }
           kernel.push_back(tmp1);
        }
        b = Matrix(1, l);
        b.init(XAVIER);
    }
    vector<vector<Matrix> > forward_cnn(vector<vector<Matrix> >X);
    vector<vector<Matrix> > backward_cnn(vector<vector<Matrix> >X);
    vector<vector<Matrix> > kernel;
    vector<vector<Matrix> > grad_kernel;
    //vector<vector<Matrix> > _x;
    Matrix b;
    Matrix grad_b;

    vector<vector<Matrix> >batch_pic_x;
    int channel, len, kernel_w, kernel_h;
};

#endif
