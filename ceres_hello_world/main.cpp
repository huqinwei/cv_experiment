
#include "ceres.h"


struct CostFunctor {
    template<typename T>
    bool operator()(const T* const x, T*residual)const {
        residual[0] = 10.0 - x[0];
        return true;
    }
};


//http://ceres-solver.org/nnls_tutorial.html

int main(int argc, char** argv)
{
    google::InitGoogleLogging(argv[0]);

    double initial_x = 5.0;
    double x = initial_x;




    return 0;
}