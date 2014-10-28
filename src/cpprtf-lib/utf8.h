#ifndef UTF8_H
#define UTF8_H
#include <vector>
#include <string>

using namespace std;

//UTF8 class with static functions that converts utf8 characters into rtf utf8 entities.
class CppRtf_Utf8
{
public:

    //gets unicode for each character
    //see http://www.randomchaos.com/documents/?source=php_and_unicode
    static vector<int> utf8ToUnicode(string str);

    static string getUnicodeEntities(string text, string charset){(void)text;(void)charset;return text;} //TODO
};

#endif // UTF8_H
