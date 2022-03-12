#ifndef KDEX_H
#define KDEX_H

#include <Eigen/Core>
#include <nanoflann.hpp>


namespace kdex{

    template<class RealType = double, class VectorType = Eigen::MatrixXd>
    class KDE{
        using realtype = RealType;
        using vectortype = VectorType;

        vectortype vec;
        public:
        KDE(const vectortype &vec) : vec{vec}{

        }
        
    };
}

#endif
