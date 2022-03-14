#ifndef KDEX_H
#define KDEX_H

#include <Eigen/Core>


namespace kdex{

    class GaussianKernel{
        public:
            GaussianKernel(double sigma):sigma(sigma){}
            double operator()(double x){
                return exp(-x*x/(2*sigma*sigma));
            }
    };
    

    template<class KernelType = GaussianKernel>
    class BivariateKDE{
    public:
        BivariateKDE(const Eigen::MatrixXd& data, const KernelType& kernel = KernelType()):
            data_(data),
            kernel_(kernel),
            n_(data.rows()),
            d_(data.cols()),
            grid_(Eigen::MatrixXd::Zero(n_,n_)){
                for(int i=0; i<n_; ++i){
                    for(int j=0; j<n_; ++j){
                        grid_(i,j) = kernel_(data_.row(i),data_.row(j));
                    }
                }
            }
        double operator()(const Eigen::VectorXd& x) const{
            double sum = 0.0;
            for(int i=0; i<n_; ++i){
                sum += grid_(i,i)*kernel_(x,data_.row(i));
            }
            return sum;
        }
    private:
        const Eigen::MatrixXd& data_;
        const KernelType& kernel_;
        int n_, d_;
        Eigen::MatrixXd grid_;
    };

    

    void test_KDE(){
        Eigen::MatrixXd data(10,2);
        data << 0,0,
                1,0,
                2,0,
                3,0,
                4,0,
                5,0,
                6,0,
                7,0,
                8,0,
                9,0;
        BivariateKDE<> kde(data, GaussianKernel(1.0));
        Eigen::VectorXd x(2);
        x << 0,0;
        std::cout << kde(x) << std::endl;
    }
    
}

#endif
