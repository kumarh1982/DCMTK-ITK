// This is vxl/vnl/examples/vnl_lsqr_test.cxx
#include <vcl_cstdlib.h>
#include <vcl_iostream.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_sparse_matrix.h>
#include <vnl/vnl_sparse_matrix_linear_system.h>
#include <vnl/algo/vnl_lsqr.h>

int main (int , char** ) {

  vnl_sparse_matrix<double> A(10000, 1000);

  vcl_vector<int> cols(50);
  vcl_vector<double> vals(50);

  for (int row_ = 0; row_ < 10000; ++row_) {
    double sum = 0;
    for (int i = 0; i < 50; ++i) {
      cols[i] = vcl_rand() % 999;
      vals[i] = (double) vcl_rand() / (double) RAND_MAX;
      sum += vals[i];
    }
    A.set_row(row_, cols, vals);
    A.scale_row(row_, 1.0/sum);
  }

  vnl_vector<double> x(1000);
  for (int i=0; i < 1000; ++i)
    x[i] = (double) vcl_rand() / (double) RAND_MAX;

  vnl_vector<double> b(10000);
  A.mult(x,b);

  for (int i=0; i < 10000; ++i)
    b[i] += 0.01*(((double) vcl_rand() / (double) RAND_MAX) - 0.5);

  vnl_sparse_matrix_linear_system<double> linear_system(A, b);
  vnl_lsqr lsqr(linear_system);
  vnl_vector<double> result(1000);
  lsqr.minimize(result);
  lsqr.diagnose_outcome(vcl_cerr);

  vcl_cerr << "Ground truth relative residual : " << (x - result).two_norm() / x.two_norm() << vcl_endl;
  return 0;
}
