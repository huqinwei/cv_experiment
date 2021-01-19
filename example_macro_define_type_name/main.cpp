// example_macro_define_type_name.cpp : 定义控制台应用程序的入口点。
//

#include <vector>
#include <iostream>

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






#if 0
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

#endif

#if 0

#define F abc  
#define B def  
#define FB(arg) #arg  
#define FB1(arg) FB(arg)  

int main()
{
    std::cout << FB(F B) << std::endl;
    std::cout << FB1(F B) << std::endl;

    system("pause");
    return 0;
}
#endif

#if 1

#include <stdio.h>  
#define paster( n ) printf_s( "token" #n " = %d", token##n )  
int token9 = 9;

int main()
{
    //paster(8);//其实paster内部是把token和n用##连接起来了，所以找不到token8
    paster(9);
    system("pause");
    return 0;
}

#endif
