#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H
#include <string>
#include <iostream>
#include <sstream>
#include <boost/regex.hpp>
#include <vector>

using namespace std;

/* функции php-аналоги для работы со строками (полный функционал не гарантируется)*/
namespace phpstring {

string ltrim(string str,string charlist=" ");

string str_repeat( string input , unsigned int multiplier );

string strtoupper(string str);

string strtolower(string str);

int hexdec(string hex_string);

string preg_replace( string pattern , string replacement , string subject);

string preg_replace(vector<string> pattern , vector<string> replacement , string subject);

string str_replace(string search , string replace , string subject);

string str_replace(vector<string> search, string replace , string subject);

string str_replace(vector<string> search, vector<string> replace , string subject);

string strrev(string str);

string chr(int asciiCode);

}

namespace cppstring {

string numtostr(int number);
string numtostr(float number);
string numtostr(double number);

}
#endif // STRINGTOOLS_H
