#include "supervised_data.hpp"
#include "io.hpp"

using namespace sdm;
using namespace Eigen;
using namespace std;

using scm_iit = Eigen::SparseMatrix<double, 0, std::ptrdiff_t>::InnerIterator;
using srm_iit = Eigen::SparseMatrix<double, 1, std::ptrdiff_t>::InnerIterator;

int main(int argc, char const *argv[]) {
  std::string file_name = argv[1];
  sdm::supervised_data<double, 1> sd(file_name);
  sdm::info("non removed zero sd rows: %d\n", sd.x_.rows());

  sdm::supervised_data<double, 1> rsd(file_name, true);
  sdm::info("non removed zero rsd rows: %d\n", rsd.x_.rows());
  return 0;
}
