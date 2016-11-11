#include "io.hpp"

using namespace sdm;
using namespace Eigen;
using namespace std;

int main(int argc, char const *argv[]) {
  std::string file_name = argv[1];
  int flag_random = atoi(argv[2]);
  Eigen::SparseMatrix<double, 1> sx1, sx2;
  Eigen::ArrayXd y1, y2;
  split_libsvm_binary(sx1, y1, sx2, y2, file_name, 0.2, flag_random);
  printf("load end\n");
  for (int i = 0; i < 0.1 * sx1.rows(); ++i) {
    cout << y1[i] << " " << sx1.row(i) << endl;
  }
  cout << sx1.rows() << ", " << sx1.cols() << " : " << sx2.rows() << ", "
       << sx2.cols() << endl;
  return 0;
}
