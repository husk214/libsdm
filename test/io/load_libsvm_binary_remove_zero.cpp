#include "io.hpp"

using namespace sdm;
using namespace Eigen;
using namespace std;

using scm_iit = Eigen::SparseMatrix<double, 0, std::ptrdiff_t>::InnerIterator;
using srm_iit = Eigen::SparseMatrix<double, 1, std::ptrdiff_t>::InnerIterator;

int main(int argc, char const *argv[]) {
  std::string file_name = argv[1];
  Eigen::SparseMatrix<double, 1, std::ptrdiff_t> sx;
  Eigen::ArrayXd y;
  load_libsvm_binary(sx, y, file_name, false);
  double xi_l2norm = 0.0;
  int rows = sx.rows(), each_nnz = 0;
  sdm::info("non removed x, rows = %d\n",rows);
  for (int i = 0; i < rows; ++i) {
    xi_l2norm = 0.0;
    each_nnz = 0;
    for (srm_iit it(sx, i); it; ++it) {
      xi_l2norm += it.value() * it.value();
      ++each_nnz;
    }
    xi_l2norm = std::sqrt(xi_l2norm);
    if (std::abs(xi_l2norm) < 1e-3)
      sdm::info("||x_%d|| = %.5e, nnz = %d\n", i, xi_l2norm, each_nnz);
  }

  Eigen::SparseMatrix<double, 1, std::ptrdiff_t> rsx;
  Eigen::ArrayXd ry;
  load_libsvm_binary(rsx, ry, file_name, true);
  rows = rsx.rows();
  sdm::info("removed x, rows = %d\n", rows);
  for (int i = 0; i < rows; ++i) {
    xi_l2norm = 0.0;
    each_nnz = 0;
    for (srm_iit it(rsx, i); it; ++it) {
      xi_l2norm += it.value() * it.value();
      ++each_nnz;
    }
    xi_l2norm = std::sqrt(xi_l2norm);
    if (std::abs(xi_l2norm) < 1e-3)
      sdm::info("||x_%d|| = %.5e, nnz = %d\n", i, xi_l2norm, each_nnz);
  }
  return 0;
}
