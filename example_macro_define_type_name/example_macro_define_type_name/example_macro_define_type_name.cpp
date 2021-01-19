// example_macro_define_type_name.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

//利用宏，自定义类型，测试
#define EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, Size, SizeSuffix)   \
typedef std::vector<Type>    Vector##SizeSuffix##TypeSuffix;  \
typedef std::vector<std::vector<Type>> Matrix##SizeSuffix##TypeSuffix;

#define EIGEN_MAKE_TYPEDEFS_ALL_SIZES(Type, TypeSuffix) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 2, 2) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 3, 3) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 4, 4) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, Dynamic, X)

EIGEN_MAKE_TYPEDEFS_ALL_SIZES(int, i)
EIGEN_MAKE_TYPEDEFS_ALL_SIZES(float, f)
EIGEN_MAKE_TYPEDEFS_ALL_SIZES(double, d)

#undef EIGEN_MAKE_TYPEDEFS_ALL_SIZES
#undef EIGEN_MAKE_TYPEDEFS
#undef EIGEN_MAKE_FIXED_TYPEDEFS

int main()
{
    Vector3d a;
    a.push_back(1.4);
    Vector3i b;
    b.push_back(1);
    Matrix3i c;
    std::vector<int> d;
    c.push_back(d);
    c[0].push_back(1);

    system("pause");
    return 0;
}


