
#include <kdex.h>
#include <iostream>

using std::cout;

using namespace kdex;

int main(){

    
    Eigen::MatrixXd mat{{1,2},{3,4},{5,6}};
    KDE<> estimator{mat};
    cout << mat << "\n";

    return 0;
}
