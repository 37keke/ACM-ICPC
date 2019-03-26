#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main()
{
    string str="how are you";
    transform(str.begin(),str.end(),str.begin(),::toupper);  这是全部大写转化 ， 小写转化用 tolower
    cout << str << endl;
    return 0;
}
