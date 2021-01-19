#define _CRT_SECURE_NO_WARNINGS


#include <vector>
#include <iostream>
#include <windows.h>

using namespace std;


double stringToDouble(string num)
{
    bool minus = false;      //标记是否是负数
    string real = num;       //real表示num的绝对值
    if (num.at(0) == '-')
    {
        minus = true;
        real = num.substr(1, num.size() - 1);
    }

    char c;
    int i = 0;
    double result = 0.0, dec = 10.0;
    bool isDec = false;       //标记是否有小数
    unsigned long size = real.size();
    while (i < size)
    {
        c = real.at(i);
        if (c == '.')
        {//包含小数
            isDec = true;
            i++;
            continue;
        }
        if (!isDec)
        {
            result = result * 10 + c - '0';
        }
        else
        {//识别小数点之后都进入这个分支
            result = result + (c - '0') / dec;
            dec *= 10;
        }
        i++;
    }

    if (minus == true) {
        result = -result;
    }

    return result;
}


vector<string> split(const string& str, const string& delim) {
    vector<string> res;
    if ("" == str) return res;
    //先将要切割的字符串从string类型转换为char*类型  
    char * strs = new char[str.length() + 1]; //不要忘了  
    strcpy(strs, str.c_str());

    char * d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p) {
        string s = p; //分割得到的字符串转换为string类型  
        res.push_back(s); //存入结果数组  
        p = strtok(NULL, d);
    }

    return res;
}
LPCWSTR stringToLPCWSTR(std::string orig)
{
    size_t origsize = orig.length() + 1;
    const size_t newsize = 100;
    size_t convertedChars = 0;
    wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
    mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

    return wcstring;
}



struct int_int
{
    int *a = NULL;
    int b = 999;
};

//能改成员指针的指向内容，但是不能改成员指针的指向
//不能改成员内容
void func1(const int_int* const p)
{
    int_int ii;
    int bb = 1000;
    std::cout << "*p is " << *p->a << std::endl;
    std::cout << "*p is " << *p->a << std::endl;
#if 0 
    //p = &ii;//“p” : 不能给常量赋值
    //p->a = &bb;//由于正在通过常量对象访问“a”，因此无法对其进行修改
    //*p->b = 200;//由于正在通过常量对象访问“b”，因此无法对其进行修改
#endif
    *(p->a) = 200;//z指针指向的内容肯定可以修改
    std::cout << "*p is " << *p->a << std::endl;
}

//const  不能改变p的指向
void func2(int_int* const p)
{
    int_int ii;
    std::cout << "*p is " << *p->a << std::endl;
#if 0
    //p = &ii;//“p” : 不能给常量赋值
#endif
    *p->a = 200;
    std::cout << "*p is " << *p->a << std::endl;
}
//const int_int*不能改变int_int的内容
void func3(const int_int*  p)
{
    int_int ii;
    int bb = 1000;
#if 0
    p->a = &bb;//由于正在通过常量对象访问“a”，因此无法对其进行修改
    *p->b = 100;//C3490	由于正在通过常量对象访问“b”，因此无法对其进行修改	string_operation	D : \git_dir\CV_experiment\string_operation\main.cpp	118
#endif
    std::cout << "*p is " << *p->a << std::endl;
    p = &ii;//“p” : 能给常量赋值
    std::cout << "*p is " << *p->a << std::endl;


    std::cout << "*p is " << *p->a << std::endl;
}
#if 0
int main()
{
    int i = 10;
    int_int ii;
    ii.a = &i;
    int_int *pa = &ii;
    func2(pa);

    system("pause");
    return 0;

}
#endif

#include <string.h>
/*****************************************************************************
**  函数名称: Trim
**  功能描述: 给定一个C-String的变量(非字面值常量)，去除首尾两端Blank的字符
**  当前版本:
**  作    者: JohnnyHu
**  修    改：
**  输入参数: char *src   --->  带有'\0'的C-String
**  输出参数: char *src       --->  格式化后(去除首尾两端Blank的字符)
**  返回结果：无
**  使用条件：非字母值常量的C-String变量
****************************************************************************/
void Trim(char *src)
{
    char *begin = src;
    char *end = src;

    while (*end++) {
        ;  // Statement is null  
    }

    if (begin == end)  return;

    while (*begin == ' ' || *begin == '\t')
        ++begin;
    while ((*end) == '\0' || *end == ' ' || *end == '\t')
        --end;

    if (begin > end) {
        *src = '\0';   return;
    }
    //printf("begin=%1.1s; end=%1.1s\n", begin, end);
    while (begin != end) {
        *src++ = *begin++;
    }

    *src++ = *end;
    *src = '\0';

    return;
}
/*****************************************************************************
**  函数名称: Trim2 (依赖库函数)
**  功能描述: 给定一个C-String的变量(非字面值常量)，去除首尾两端Blank的字符
**  当前版本:
**  作    者: JohnnyHu
**  修    改：
**  输入参数: char *src   --->  带有'\0'的C-String
**  输出参数: char *src       --->  格式化后(去除首尾两端Blank的字符)
**  返回结果：src
**  使用条件：非字母值常量的C-String变量
****************************************************************************/
char* Trim2(char *src)
{
    char *ori_src = src;

    char *begin = src;
    char *end = src + strlen(src);

    if (begin == end)  return ori_src;

    while (isblank(*begin))
        ++begin;

    while (isblank(*end) || !(*end))
        --end;

    if (begin > end) {
        *src = '\0';   return  ori_src;
    }


    //printf("begin=%1.1s; end=%1.1s\n", begin, end);
    while (begin != end) {
        *src++ = *begin++;
    }

    *src++ = *end;
    *src = '\0';

    return ori_src;
}

#include<atlstr.h>

struct vec_obj {
    vec_obj() { std::cout << "constructor" << std::endl; }
    vec_obj(std::string name_input) 
    {
        name = name_input;
        std::cout << "constructor:"<< name_input.c_str() << std::endl;
    }
    vec_obj(vec_obj*e) { std::cout << "copy constructor:" << e->name.c_str() << std::endl; }
    vec_obj(const vec_obj&e) { std::cout << "real copy constructor:" << e.name.c_str() << std::endl; }
    std::string name;
};
void copy_constructor_called(vec_obj vo)
{
    cout << "g_func" << endl;
}
void vector_resize_constructor() {
    vec_obj e1;
    vec_obj e2 = vec_obj("e2");
    vector<vec_obj> objs;
    objs.resize(4);
    std::cout << objs[2].name.c_str() << std::endl;
    e1.name = "e1";
    objs[2] = e1;//无法触发拷贝构造函数
    std::cout << objs[2].name.c_str() << std::endl;
    objs[3] = e2;//无法触发拷贝构造函数
//     std::cout << objs[3].name.c_str() << std::endl;
//     e1 = e2;//无法触发拷贝构造函数
//     copy_constructor_called(e2);//只有调用函数才触发
//     std::cout << "push and emplace" << std::endl;
//     vec_obj e3 = vec_obj("e3");
//     vec_obj e4 = vec_obj("e4");
//     vec_obj e5 = vec_obj("e5");
//     vec_obj e6 = vec_obj("e6");
//     objs.push_back(e3);
//     objs.emplace_back(e4);
//     objs.push_back(e5);
//     objs.emplace_back(e6);
    
}


//string的npos判断问题，扩展到-1相关的判断与类型转换。
void string_npos_and_type_cast()
{
    std::string str = "hello world";
    if (str.find("hello") != std::string::npos)
    {
        std::cout << "hello founded!" << std::endl;
    }

    unsigned int ui = -1;
    unsigned long ul = -1;
    unsigned long long ull = -1;

    unsigned long long cast_res = static_cast<unsigned long long>(ul);
    cast_res = static_cast<unsigned long long>(ui);

    if (-1 == std::string::npos)
    {
        std::cout << "-1 == std::string::npos!" << std::endl;
        std::cout << "std::string::npos:   " << std::string::npos << std::endl;
    }
    if (-1 == ui&&-1 == ul&-1 == ull)//不同类型间接相等
    {
        std::cout << "unsigned int still equals to -1!" << std::endl;
        if (ul == ui)//long与int在此编译器本来就是同长度
        {
            std::cout << "unsigned int still equals to unsigned long!" << std::endl;
        }
        if (ul == ull)//不同类型不相等，相等的原因是强转，而此时没有“正确”的强转生效
        {
            std::cout << "unsigned long still equals to unsigned long long!" << std::endl;
        }
        if (ul == static_cast<unsigned long>(ull))//可降
        {
            std::cout << "cast success!" << std::endl;
        }
        if (static_cast<unsigned long long>(ul) == ull)//不能“升”
        {
            std::cout << "cast success!" << std::endl;
        }


        if (ul == (unsigned long)ull)//可降
        {
            std::cout << "success!" << std::endl;
        }
        if ((unsigned long long)ul == ull)//不能“升”
        {
            std::cout << "success!" << std::endl;
        }

        //共同降维
        if ((unsigned short)ul == (unsigned short)ull)//可降
        {
            std::cout << "success!" << std::endl;
            unsigned short us = (unsigned short)ul;
            std::cout << "us is:" << us << std::endl;
            unsigned short us2 = static_cast<unsigned long>(ul);
            std::cout << "us2 is:" << us2 << std::endl;
        }

    }

}


int main()
{
    string_npos_and_type_cast();
    vector_resize_constructor();
//     std::string str = "./Data/Tile_+006_+007/Tile_+006_+007.osgb";
//     std::string str = "./Data/Tile_+006_+007/Tile_+006_+007.osgb";

//     std::string strElemValue = "./Data/Tile_+006_+007/Tile_+006_+007.osgb";
//     strElemValue = Trim2(strElemValue)

    //DEString strTitle = DEFile::GetTitle(strElemValue);


    int  n = ceil(5.5);
    n = floor(5.5);

    CString s1("abc");
    CString s2("ABC");
    CString s3("abd");
    CString s4("abddddddd");
    CString s5("abedddddd");

    int res;
    res = s1.CompareNoCase(s2);
    res = s1.CompareNoCase(s3);
    res = s1.CompareNoCase(s4);
    res = s1.CompareNoCase(s5);

    /////////////////////////////////////////////
    /////////////////////////////////////////////
    /////////////////////////////////////////////
    char sentence[] = "Tile_+006_+007";
    char* str_ptr = std::strtok(sentence,"_");

    while (str_ptr != NULL) {
        cout << str_ptr << '\n';
        str_ptr = strtok(NULL, "_");
    }


    /*
    std::regex ws_re("_");
    std::vector<std::string> strArry(std::sregex_token_iterator(dir_list[dir_index].begin(), dir_list[dir_index].end(), ws_re, -1), std::sregex_token_iterator());
    for (auto&& s : strArry)
    {
        std::cout << s << "\n";
    }
    */

//     std::vector<std::string> str_vec;
//     str.split(str_vec, "_");


    system("pause");
    return 0;

}