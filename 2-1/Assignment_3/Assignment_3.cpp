#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "oopstd.h"
using namespace std;

int main()
{
    //memset
    /*
    char str[20] = "hello world!";
    char str2[20] = "hello world!";
    
    cout << "str : " << str << endl;

    oopstd::memset(str, '-', 3);
    cout << "using oopstd memset : " << str << endl;

    memset(str2, '-', 3);
    cout << "using std memset : " << str << endl;
    */

    //memcpy
    /*
    char str[20] = "hello world!";
    char str2[20]{};
    char str3[20]{};

    cout << "str : " << str << endl;

    oopstd::memcpy(str2, str, 5);
    cout << "using oopstd memcpy : " << str2 << endl;
    memcpy(str3, str, 8);
    cout << "using std memcpy : " << str3 << endl;
    */

    //strcmp
    /*
    char str[20] = "hello world!";
    char str2[20] = "hello world!";
    char str3[20] = "Hello world!";

    cout << "str : " << str << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str3 : " << str3 << endl;
    int a, b;
    a=oopstd::strcmp(str, str2);
    b=oopstd::strcmp(str, str3);

    cout << "str & str2 : " << a<<endl;
    cout << "str & str3 : " << b << endl;
    */

    //strncmp
    /*
    char str[5] = "R2D2";
    char str2[5] = "R2D6";
    char str3[5] = "R5D8";
    cout << "Looking R2 : " << endl;
    cout << "str : " << str << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str3 : " << str3 << endl;
    int a, b;
    a = oopstd::strncmp(str, str2,2);
    b = oopstd::strncmp(str, str3,5);
    
    cout << "Found : " << endl;
    if (a == 0)
        cout << str2 << endl;
    if (b == 0)
        cout << str3 << endl;
    */

    //strcpy
    /*
    char str[20] = "hello world!";
    char str2[20]{};
    char str3[20]{};

    cout << "str : " << str << endl;

    oopstd::strcpy(str2, str);
    strcpy(str3, str);

    cout << "using oopstd strcpy : " << str2 << endl;
    cout << "using std strcpy : " << str3 << endl;
    */

    //strncpy
    /*
    char str[20] = "hello world!";
    char str2[20]{};
    char str3[20]{};

    cout << "str : " << str << endl;

    oopstd::strncpy(str2, str,3);
    strncpy(str3, str,7);

    cout << "oopstd 3자리 복사, std 7자리 복사" << endl;
    cout << "using oopstd strcpy : " << str2 << endl;
    cout << "using std strcpy : " << str3 << endl;
    */

    //strlen
    /*
    char str[20] = "hello world!";
    char str2[20] = "I wanna sleep....";

    cout << "str : " << str << endl;
    cout << "str2 : " << str2 << endl;

    cout << "using oopstd strlen : " << oopstd::strlen(str) << endl;
    cout << "using std strlen : " << oopstd::strlen(str2) << endl;
    */


    //atoi, atof
    /*
    char to_int[5] = "3.26";
    char to_float[8] = "-1";


    cout << to_int << "     " << to_float << endl;
    int q;
    q = oopstd::atoi(to_int);
    float w;
    w = oopstd::atof(to_float);
    cout << "char to int using oopstd atoi : " << q << endl;
    cout << "char to float using oopstd atof : " << w << endl;
    printf("char to float using oopstd atof : %f", w);
    */
}