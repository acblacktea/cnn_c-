#ifndef _BLACKTEA_NERUAL_BLOCK_H_
#define _BLACKTEA_NERUAL_BLOCK_H_

#include "Matrix.h"
#include <string>
class nerualBlock {
public;
    virtual Matrix forward(Matrix X) {
      return NULL;
    };
    virtual Matrix backward(Matrix X) {
      return NULL;
    };
    virtual vector<vector<Matrix> > forward_cnn(vector<vector<Matrix> >X) {
      return NULL;
    };
    virtual vector<vector<Matrix> > backward_cnn(vector<vector<Matrix> >X) {
      return NULL;
    };
    virtual Matrix forward_flatten(vector<vector<Matrix> > X) {
      return NULL;
    }
    virtual Matrix backward_flatten(vector<vector<Matrix> > X) {
      return NULL;
    }
};

#endif
