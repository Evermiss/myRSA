#ifndef RSA_EXTEND  
#define RSA_EXTEND

#include <string>
#include <iostream>
#include <sstream>
#include "esa_extend.cpp"

using namespace std;

typedef unsigned long ul;

string strImult_c(string s, char c);
void strAdd(string &s, string s1);
string strImult(string sreslt, string sstep);
bool strCmp(string s1, string s2);
string strSub(string s1, string s2);
string strMod_t(string s, string pattern);
int strMod(string s, string pattern);
string strPower(string s, int pw);



#endif
