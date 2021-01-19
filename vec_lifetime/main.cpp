#include <vector>
#include <iostream>

using namespace std;


vector<int>*  new_vec()
{
    vector<int>* pvec = new vector<int>;
    pvec->push_back(10);
    pvec->emplace_back(11);
    pvec->emplace_back(12);
    int result = pvec->back();
    cout << result << endl;
    return pvec;
}
void vec_test()
{
    vector<int>* pvec = new_vec();
    int result = pvec->back();
    cout << result << endl;


    vector<int>* pvec2;
    if (1)
    {
        vector<int> vec_test;
        vec_test.emplace_back(19);
        vec_test.emplace_back(22);
        vec_test.emplace_back(33);
        int result = vec_test.back();
        cout << result << endl;
        pvec2 = &vec_test;
        result = pvec2->back();
        cout << result << endl;
    }
    result = pvec2->back();//会崩，因为vec生命周期到了
    cout << result << endl;
}


int main()
{
    vec_test();



}