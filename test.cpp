#include<algorithm>
#include<iostream>
#include"Matrix.h"
#include"loss.h"
#include"connect_block.h"
#include"flatten.h"
#include"pool.h"
#include"cNN_block.h"
#include"activation.h"
using namespace std;

double sum(Matrix q) {
  double sum = 0.0;
  for (int i = 0; i < q.w; i++) {
    for (int j = 0; j < q.h; j++) {
      sum += q.Ma[i][j];
    }
  }
  return sum;
}

void print(Matrix tmp) {
  std::cout << "Matrix message" << std::endl;
  for (int i = 0; i < tmp.w; i++) {
    for (int j = 0; j < tmp.h; j++) {
        cout << tmp.Ma[i][j] << " ";
    }
    cout << endl;
  }
  cout  << endl;
}

void test_Matrix() {
   Matrix a(3, 3);
   for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
         a.Ma[i][j] = i * 3 + j;
    }
   }

   Matrix b(3, 3);
   for (int i = 0; i < 3; i++) {
     for (int j = 0; j < 3; j++) {
       b.Ma[i][j] = i * 3 + j;
     }
   }
   print(a);
   print(b);
   print(a+b);
   print(a*b);
}

void test_loss() {
  Matrix x(10, 6);
  vector<int>ve;
  for (int i = 0; i < 6; i++) {
    ve.push_back(i);

  }
  x.init(XAVIER);
  print(x);

  loss layer;
  print(layer.forward(x, ve));

  cout << ">>>backward<<<" << endl;
  print(layer.backward());

  Matrix query = x;
  Matrix ans = x;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 6; j++) {
        Matrix a1 = x, a2 = x;
        a1.Ma[i][j] += 0.000001;
        a2.Ma[i][j] -= 0.000001;
        double tmp = sum(layer.forward(a1, ve)) - sum(layer.forward(a2, ve));
        ans.Ma[i][j] = tmp / 0.000002;
    }
  }
  cout << ">>>check<<<" << endl;
  print(ans);
}

void test_connect() {
   connectBlock W(10, 4);
   Matrix X(4, 6);
   X.init(XAVIER);

   vector<int>label;
   for(int i = 0; i < 6; i++) {
     label.push_back(i);
   }

   cout << "w value" << endl;
   print(W.W);
   cout << "b value" << endl;
   print(W.b);
   cout << "x value" << endl;
   print(X);
   cout << "ans value" << endl;
   print(W.forward(X));

   loss layer;
   activation act(RELU);
   Matrix tmp = W.forward(X);
   Matrix tmp2 = act.forward(tmp);
   Matrix ans = layer.forward(tmp2, label);
   cout << "connect + loss value" << endl;
   print(ans);

   Matrix grad = W.backward(act.backward(layer.backward()));
   cout << "grad X" << endl;
   print(grad);
   cout << "grad W" << endl;
   print(W.W_gradent);
   cout << "grad b" << endl;
   print(W.b_gradent);

   Matrix X1 = X, X2 = X, ans_1 = X;
   for (int i = 0; i < X1.w; i++) {
     for (int j = 0; j < X1.h; j++) {
         X1.Ma[i][j] += 0.000001;
         X2.Ma[i][j] -= 0.000001;

         double tmp3 = (sum(layer.forward(act.forward(W.forward(X1)), label)) -
                        sum(layer.forward(act.forward(W.forward(X2)), label))) / 0.000002;
         ans_1.Ma[i][j] = tmp3;

         X1.Ma[i][j] -= 0.000001;
         X2.Ma[i][j] += 0.000001;
     }
   }
   cout << "check X grad" << endl;
   print(ans_1);


   Matrix w_ans = W.W_gradent;
   connectBlock w_tmp1 = W;
   connectBlock w_tmp2 = W;
   for (int i = 0 ; i < w_tmp1.W.w; i++) {
     for (int j = 0; j < w_tmp1.W.h; j++) {
         w_tmp1.W.Ma[i][j] += 0.000001;
         w_tmp2.W.Ma[i][j] -= 0.000001;

         double tmp2 = (sum(layer.forward(act.forward(w_tmp1.forward(X)),label)) -
                        sum(layer.forward(act.forward(w_tmp2.forward(X)),label))) / 0.000002;
         w_ans.Ma[i][j] = tmp2;

         w_tmp1.W.Ma[i][j] -= 0.000001;
         w_tmp2.W.Ma[i][j] += 0.000001;
     }
   }
   cout << "check w grad" << endl;
   print(w_ans);

   Matrix b_ans = W.b_gradent;
   for (int i = 0; i < w_tmp1.b.w; i++) {
     for (int j = 0; j < w_tmp2.b.h; j++) {
       w_tmp1.b.Ma[i][j] += 0.000001;
       w_tmp2.b.Ma[i][j] -= 0.000001;

       double tmp2 = (sum(layer.forward(act.forward(w_tmp1.forward(X)),label)) -
                      sum(layer.forward(act.forward(w_tmp2.forward(X)),label))) / 0.000002;
       b_ans.Ma[i][j] = tmp2;

       w_tmp1.b.Ma[i][j] -= 0.000001;
       w_tmp2.b.Ma[i][j] += 0.000001;
     }
   }

   cout << "check b grad" << endl;
   print(b_ans);
}

void print_cnn(vector<vector<Matrix> > x) {
  for (int i = 0; i < x.size(); i++) {
    cout << "the " << i << " data" << endl;
    for (int j = 0; j < x[i].size(); j++) {
       cout << "the " << j << "  channel" << endl;
       print(x[i][j]);
    }
  }
}

void test_flatten() {
    vector<vector<Matrix> > x;
    for (int i = 0; i < 4; i++) {
      vector<Matrix>tmp1;
      for (int i = 0; i < 3; i++) {
          Matrix tmp2(10 ,10);
          tmp2.init(XAVIER);
          tmp1.push_back(tmp2);
      }
      x.push_back(tmp1);
    }
    //print_cnn(x);

    flattenLayer flatten(x[0].size(), x[0][0].w, x[0][0].h);
    cout << "flatten !!" << endl;
    //print(flatten.forward_flatten(x));

    cout << "grad !!!" << endl;
    loss loss_layer;
    vector<int>ve;
    for(int i = 0; i < 4; i++) {
      ve.push_back(i);
    }
    loss_layer.forward(flatten.forward_flatten(x), ve);
    print_cnn(flatten.backward_flatten(loss_layer.backward()));

    vector<vector<Matrix> >x_tmp1 = x, x_tmp2 = x, ans = x;
    for (int i = 0; i < x.size(); i++) {
      for (int j = 0; j < x[i].size(); j++) {
        for (int k1 = 0; k1 < x[i][j].w; k1++) {
          for (int k2 = 0; k2 < x[i][j].h; k2++) {
             x_tmp1[i][j].Ma[k1][k2] += 0.000001;
             x_tmp2[i][j].Ma[k1][k2] -= 0.000001;

             ans[i][j].Ma[k1][k2] = (sum(loss_layer.forward(flatten.forward_flatten(x_tmp1), ve)) -
                                     sum(loss_layer.forward(flatten.forward_flatten(x_tmp2), ve))) / 0.000002;
             x_tmp1[i][j].Ma[k1][k2] -= 0.000001;
             x_tmp2[i][j].Ma[k1][k2] += 0.000001;
          }
        }
      }
    }

    cout << "check grad  !!!!!" << endl;
    print_cnn(ans);
}

void test_pool() {
  vector<vector<Matrix> > x1;
  vector<vector<Matrix> > x;
  for (int i = 0; i < 4; i++) {
    vector<Matrix>tmp1;
    for (int i = 0; i < 6; i++) {
        int q = -12;
        Matrix tmp2(5 ,5);
        for (int k1 = 0; k1 < tmp2.w; k1++) {
          for (int k2 = 0; k2 < tmp2.h; k2++) {
             tmp2.Ma[k1][k2] = (q++) * 1.0;
          }
        }
        tmp1.push_back(tmp2);
    }
    x1.push_back(tmp1);
  }

  pool Pool(3, 3, MAX);
  x = Pool.forward_cnn(x1);
  print_cnn(x1);
  print_cnn(x);

  flattenLayer flatten(x[0].size(), x[0][0].w, x[0][0].h);
  cout << "flatten !!" << endl;
  //print(flatten.forward_flatten(x));

  cout << "grad !!!" << endl;
  loss loss_layer;
  vector<int>ve;
  for(int i = 0; i < 4; i++) {
    ve.push_back(i);
  }
  loss_layer.forward(flatten.forward_flatten(x), ve);
  print_cnn(Pool.backward_cnn(flatten.backward_flatten(loss_layer.backward())));
  //print_cnn(flatten.backward_flatten(loss_layer.backward()));

  vector<vector<Matrix> >x_tmp1 = x1, x_tmp2 = x1, ans = x1;
  for (int i = 0; i < x1.size(); i++) {
    for (int j = 0; j < x1[i].size(); j++) {
      for (int k1 = 0; k1 < x1[i][j].w; k1++) {
        for (int k2 = 0; k2 < x1[i][j].h; k2++) {
           x_tmp1[i][j].Ma[k1][k2] += 0.000001;
           x_tmp2[i][j].Ma[k1][k2] -= 0.000001;

           ans[i][j].Ma[k1][k2] = (sum(loss_layer.forward(flatten.forward_flatten(Pool.forward_cnn(x_tmp1)), ve)) -
                                   sum(loss_layer.forward(flatten.forward_flatten(Pool.forward_cnn(x_tmp2)), ve))) / 0.000002;


           //ans[i][j].Ma[k1][k2] = (sum(loss_layer.forward(flatten.forward_flatten(x_tmp1), ve)) -
          //                         sum(loss_layer.forward(flatten.forward_flatten(x_tmp2), ve))) / 0.000002;

           x_tmp1[i][j].Ma[k1][k2] -= 0.000001;
           x_tmp2[i][j].Ma[k1][k2] += 0.000001;
        }
      }
    }
  }

  cout << "check grad  !!!!!" << endl;
  print_cnn(ans);
}
void test_cnn() {
  vector<vector<Matrix> > x2;
  vector<vector<Matrix> > x1;
  vector<vector<Matrix> > x3;
  vector<vector<Matrix> > x;
  for (int i = 0; i < 4; i++) {
    vector<Matrix>tmp1;
    for (int j = 0; j < 3; j++) {
        Matrix tmp2(8 ,8);
        tmp2.init(XAVIER);
        tmp1.push_back(tmp2);
    }
    x2.push_back(tmp1);
   }

   cnnBlock cnn(5, 3, 3, 3);
   x1 = cnn.forward_cnn(x2);

   //cout << "scan message " << endl;
   //print_cnn(x2);

   //cout << "kernel message" << endl;
   //print_cnn(cnn.kernel);
   //print(cnn.b);

   //cout << "print message" << endl;
   //print_cnn(x1);

   pool Pool(3, 3, MAX);

   activation act(RELU);
   x3 = act.forward_cnn(x1);
   x = Pool.forward_cnn(x3);
   //print_cnn(x1);
   print_cnn(x);

   flattenLayer flatten(x[0].size(), x[0][0].w, x[0][0].h);
   cout << "flatten !!" << endl;
   //print(flatten.forward_flatten(x));

   cout << "grad x!!!" << endl;
   loss loss_layer;
   vector<int>ve;
   for(int i = 0; i < 4; i++) {
     ve.push_back(i);
   }
   loss_layer.forward(flatten.forward_flatten(x), ve);
   cout << "debug" << endl;
   print_cnn(cnn.backward_cnn(act.backward_cnn(Pool.backward_cnn(flatten.backward_flatten(loss_layer.backward())))));
   //print_cnn(flatten.backward_flatten(loss_layer.backward()));

   vector<vector<Matrix> >x_tmp1 = x2, x_tmp2 = x2, ans = x2;
   for (int i = 0; i < x2.size(); i++) {
     for (int j = 0; j < x2[i].size(); j++) {
       for (int k1 = 0; k1 < x2[i][j].w; k1++) {
         for (int k2 = 0; k2 < x2[i][j].h; k2++) {
            x_tmp1[i][j].Ma[k1][k2] += 0.000001;
            x_tmp2[i][j].Ma[k1][k2] -= 0.000001;

            ans[i][j].Ma[k1][k2] = (sum(loss_layer.forward(flatten.forward_flatten(Pool.forward_cnn(act.forward_cnn(cnn.forward_cnn(x_tmp1)))), ve)) -
                                    sum(loss_layer.forward(flatten.forward_flatten(Pool.forward_cnn(act.forward_cnn(cnn.forward_cnn(x_tmp2)))), ve))) / 0.000002;


            //ans[i][j].Ma[k1][k2] = (sum(loss_layer.forward(flatten.forward_flatten(x_tmp1), ve)) -
           //                         sum(loss_layer.forward(flatten.forward_flatten(x_tmp2), ve))) / 0.000002;

            x_tmp1[i][j].Ma[k1][k2] -= 0.000001;
            x_tmp2[i][j].Ma[k1][k2] += 0.000001;
         }
       }
     }
   }
   cout << "check grad x !!!" << endl;
   print_cnn(ans);

   cout << "grad w!!!" << endl;
   print_cnn(cnn.grad_kernel);
   cout << "check grad  w!!!!!" << endl;
   cnnBlock cnn1 = cnn, cnn2 = cnn;
   ans = cnn.grad_kernel;
   for (int i = 0; i < cnn.grad_kernel.size(); i++) {
     for (int j = 0; j < cnn.grad_kernel[i].size(); j++) {
       for (int k1 = 0; k1 < cnn.grad_kernel[i][j].w; k1++) {
         for (int k2 = 0; k2 < cnn.grad_kernel[i][j].h; k2++) {
            cnn1.kernel[i][j].Ma[k1][k2] += 0.000001;
            cnn2.kernel[i][j].Ma[k1][k2] -= 0.000001;

            ans[i][j].Ma[k1][k2] = (sum(loss_layer.forward(flatten.forward_flatten(Pool.forward_cnn(act.forward_cnn(cnn1.forward_cnn(x2)))), ve)) -
                                    sum(loss_layer.forward(flatten.forward_flatten(Pool.forward_cnn(act.forward_cnn(cnn2.forward_cnn(x2)))), ve))) / 0.000002;


            //ans[i][j].Ma[k1][k2] = (sum(loss_layer.forward(flatten.forward_flatten(x_tmp1), ve)) -
           //                         sum(loss_layer.forward(flatten.forward_flatten(x_tmp2), ve))) / 0.000002;

            cnn1.kernel[i][j].Ma[k1][k2] -= 0.000001;
            cnn2.kernel[i][j].Ma[k1][k2] += 0.000001;
         }
       }
     }
    }
     print_cnn(ans);

     cout << "grad b!!!" << endl;
     print(cnn.grad_b);
     Matrix ans2(1, 5);
     for (int i = 0; i < cnn.grad_b.w; i++) {
       for (int j = 0; j < cnn.grad_b.h; j++) {
         cnn1.b.Ma[i][j] += 0.000001;
         cnn2.b.Ma[i][j] -= 0.000001;

         ans2.Ma[i][j] = (sum(loss_layer.forward(flatten.forward_flatten(Pool.forward_cnn(act.forward_cnn(cnn1.forward_cnn(x2)))), ve)) -
                          sum(loss_layer.forward(flatten.forward_flatten(Pool.forward_cnn(act.forward_cnn(cnn2.forward_cnn(x2)))), ve))) / 0.000002;


         //ans[i][j].Ma[k1][k2] = (sum(loss_layer.forward(flatten.forward_flatten(x_tmp1), ve)) -
        //                         sum(loss_layer.forward(flatten.forward_flatten(x_tmp2), ve))) / 0.000002;

         cnn1.b.Ma[i][j] -= 0.000001;
         cnn2.b.Ma[i][j] += 0.000001;
      }
      }
      cout << "check grad b" << endl;
      print(ans2);
}

int main() {
    cout << "hello world" << endl;
    //test_Matrix();
    //test_loss();
    //test_connect();
    //test_flatten();
    //test_pool();
    test_cnn();
    return 0;
}
