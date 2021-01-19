#define _CRT_SECURE_NO_WARNINGS


#include <vector>
#include <iostream>
#include <windows.h>

using namespace std;


double stringToDouble(string num)
{
    bool minus = false;      //����Ƿ��Ǹ���
    string real = num;       //real��ʾnum�ľ���ֵ
    if (num.at(0) == '-')
    {
        minus = true;
        real = num.substr(1, num.size() - 1);
    }

    char c;
    int i = 0;
    double result = 0.0, dec = 10.0;
    bool isDec = false;       //����Ƿ���С��
    unsigned long size = real.size();
    while (i < size)
    {
        c = real.at(i);
        if (c == '.')
        {//����С��
            isDec = true;
            i++;
            continue;
        }
        if (!isDec)
        {
            result = result * 10 + c - '0';
        }
        else
        {//ʶ��С����֮�󶼽��������֧
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
    //�Ƚ�Ҫ�и���ַ�����string����ת��Ϊchar*����  
    char * strs = new char[str.length() + 1]; //��Ҫ����  
    strcpy(strs, str.c_str());

    char * d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p) {
        string s = p; //�ָ�õ����ַ���ת��Ϊstring����  
        res.push_back(s); //����������  
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

//�ܸĳ�Աָ���ָ�����ݣ����ǲ��ܸĳ�Աָ���ָ��
//���ܸĳ�Ա����
void func1(const int_int* const p)
{
    int_int ii;
    int bb = 1000;
    std::cout << "*p is " << *p->a << std::endl;
    std::cout << "*p is " << *p->a << std::endl;
#if 0 
    //p = &ii;//��p�� : ���ܸ�������ֵ
    //p->a = &bb;//��������ͨ������������ʡ�a��������޷���������޸�
    //*p->b = 200;//��������ͨ������������ʡ�b��������޷���������޸�
#endif
    *(p->a) = 200;//zָ��ָ������ݿ϶������޸�
    std::cout << "*p is " << *p->a << std::endl;
}

//const  ���ܸı�p��ָ��
void func2(int_int* const p)
{
    int_int ii;
    std::cout << "*p is " << *p->a << std::endl;
#if 0
    //p = &ii;//��p�� : ���ܸ�������ֵ
#endif
    *p->a = 200;
    std::cout << "*p is " << *p->a << std::endl;
}
//const int_int*���ܸı�int_int������
void func3(const int_int*  p)
{
    int_int ii;
    int bb = 1000;
#if 0
    p->a = &bb;//��������ͨ������������ʡ�a��������޷���������޸�
    *p->b = 100;//C3490	��������ͨ������������ʡ�b��������޷���������޸�	string_operation	D : \git_dir\CV_experiment\string_operation\main.cpp	118
#endif
    std::cout << "*p is " << *p->a << std::endl;
    p = &ii;//��p�� : �ܸ�������ֵ
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
**  ��������: Trim
**  ��������: ����һ��C-String�ı���(������ֵ����)��ȥ����β����Blank���ַ�
**  ��ǰ�汾:
**  ��    ��: JohnnyHu
**  ��    �ģ�
**  �������: char *src   --->  ����'\0'��C-String
**  �������: char *src       --->  ��ʽ����(ȥ����β����Blank���ַ�)
**  ���ؽ������
**  ʹ������������ĸֵ������C-String����
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
**  ��������: Trim2 (�����⺯��)
**  ��������: ����һ��C-String�ı���(������ֵ����)��ȥ����β����Blank���ַ�
**  ��ǰ�汾:
**  ��    ��: JohnnyHu
**  ��    �ģ�
**  �������: char *src   --->  ����'\0'��C-String
**  �������: char *src       --->  ��ʽ����(ȥ����β����Blank���ַ�)
**  ���ؽ����src
**  ʹ������������ĸֵ������C-String����
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
    objs[2] = e1;//�޷������������캯��
    std::cout << objs[2].name.c_str() << std::endl;
    objs[3] = e2;//�޷������������캯��
//     std::cout << objs[3].name.c_str() << std::endl;
//     e1 = e2;//�޷������������캯��
//     copy_constructor_called(e2);//ֻ�е��ú����Ŵ���
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


//string��npos�ж����⣬��չ��-1��ص��ж�������ת����
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
    if (-1 == ui&&-1 == ul&-1 == ull)//��ͬ���ͼ�����
    {
        std::cout << "unsigned int still equals to -1!" << std::endl;
        if (ul == ui)//long��int�ڴ˱�������������ͬ����
        {
            std::cout << "unsigned int still equals to unsigned long!" << std::endl;
        }
        if (ul == ull)//��ͬ���Ͳ���ȣ���ȵ�ԭ����ǿת������ʱû�С���ȷ����ǿת��Ч
        {
            std::cout << "unsigned long still equals to unsigned long long!" << std::endl;
        }
        if (ul == static_cast<unsigned long>(ull))//�ɽ�
        {
            std::cout << "cast success!" << std::endl;
        }
        if (static_cast<unsigned long long>(ul) == ull)//���ܡ�����
        {
            std::cout << "cast success!" << std::endl;
        }


        if (ul == (unsigned long)ull)//�ɽ�
        {
            std::cout << "success!" << std::endl;
        }
        if ((unsigned long long)ul == ull)//���ܡ�����
        {
            std::cout << "success!" << std::endl;
        }

        //��ͬ��ά
        if ((unsigned short)ul == (unsigned short)ull)//�ɽ�
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