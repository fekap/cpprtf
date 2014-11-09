#include "utf8.h"
#include "iconv.hpp"
#include "tools/stringtools.h"

vector<int> CppRtf_Utf8::utf8ToUnicode(string str)
{
    vector<int> unicode;
    vector<int> values;

    int lookingFor = 1;
    for(string::iterator it=str.begin();it!=str.end();it++){
        unsigned char symb = *it;
        int thisValue= (int)symb;

        if (thisValue < 128) {
            unicode.push_back(thisValue);
          }
          else {
              if (values.size() == 0) {
                  lookingFor = thisValue < 224 ? 2 : 3;
              }

              values.push_back(thisValue);

              if ((int)values.size() == lookingFor) {
                  int number = lookingFor == 3
                            ? ((values[0] % 16) * 4096) + ((values[1] % 64) * 64) + (values[2] % 64)
                            : ((values[0] % 32) * 64) + (values[1] % 64);

                  unicode.push_back(number);
                  values.clear();
                  lookingFor = 1;
              }
          }
    }
    return unicode;
}

string CppRtf_Utf8::getUnicodeEntities(string text, string charset)
{
    using namespace iconvpp;
    converter conv(charset, "UTF-8//TRANSLIT");
      string out;
      conv.convert(text, out);
    vector<int> unicode = CppRtf_Utf8::utf8ToUnicode(out);
    text =  CppRtf_Utf8::unicodeToEntitiesPreservingAscii(unicode);
    return text;

}

string CppRtf_Utf8::unicodeToEntitiesPreservingAscii(vector<int> unicode)
{
    string entities = "";
    for(vector<int>::iterator it = unicode.begin(); it != unicode.end(); it++){
        int value = *it;
        if (value != 65279) {
            if(value > 127){
                entities += string("\\uc0{\\u") + cppstring::numtostr(value) + "}";
            }
            else{
                entities += (char)value;
            }
        }
    }
    return entities;
}
