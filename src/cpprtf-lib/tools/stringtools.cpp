#include "stringtools.h"

string phpstring::ltrim(string str,string charlist)
{
    unsigned int length=str.length();
    if(length>0){
        for(string::iterator it=charlist.begin();it!=charlist.end();it++){
            if(str[0]==*it)
                str.erase(0,1);
        }
        if(str.length()<length)
            return ltrim(str,charlist);
    }
    return str;
}


string phpstring::str_repeat(string input, unsigned int multiplier)
{
    if(multiplier==0)return "";
    string result="";
    for(unsigned int i=0;i<multiplier;i++){
        result+=input;
    }
    return result;
}

string phpstring::strtoupper(string str)
{
    string result;
    for(string::iterator it=str.begin();it!=str.end();it++)
        result.push_back(toupper( *it ));
    return result;
}

int phpstring::hexdec(string hex_string)
{
    int res;
    stringstream ss;
    ss<<hex<<hex_string;
    ss>>res;
    return res;
}


string cppstring::numtostr(int number)
{
    stringstream ss;
    ss<<number;
    return ss.str();
}


string cppstring::numtostr(float number)
{
    stringstream ss;
    ss<<number;
    return ss.str();
}


string cppstring::numtostr(double number)
{
    stringstream ss;
    ss<<number;
    return ss.str();
}


string phpstring::preg_replace(string pattern, string replacement, string subject)
{
    using namespace boost;
//    regex xRegEx(pattern, regex::perl|regex::icase); // for |smi
    regex xRegEx(pattern, regex::perl|regex::icase|regex::mod_s|regex::mod_x); // for |smi
    return regex_replace(subject, xRegEx, replacement) ;
}


string phpstring::preg_replace(vector<string> pattern, vector<string> replacement, string subject)
{
    string result=subject;
    for(int i=0;i<(int)(pattern.size()-replacement.size());i++)
        replacement.push_back("");
    for(int i=0;i<(int)pattern.size();i++){
        result=preg_replace(pattern[i],replacement[i],result);
    }
    return result;
}


string phpstring::str_replace(string search, string replace, string subject)
{
    int pos = subject.find(search);
    while (pos>-1)
    {
        subject.replace(pos, search.length(), replace);
        pos+=replace.length();
        pos = subject.find(search, pos);
    }
//    for(int pos = subject.find(search);pos<subject.length();pos = subject.find(search)){
//        subject.replace(pos, search.length(), replace);
//        pos++;
//    }

    return subject;
}


string phpstring::str_replace(vector<string> search, string replace, string subject)
{
    for(vector<string>::iterator it = search.begin();it!= search.end();it++){
        string s = *it;
        subject = str_replace(s,replace,subject);
    }
    return subject;
}


string phpstring::str_replace(vector<string> search, vector<string> replace, string subject)
{
    for(int i=0;i<(int)(search.size()-replace.size());i++)
        replace.push_back("");
    for(int i=0;i<(int)search.size();i++){
        subject=str_replace(search[i],replace[i],subject);
    }
    return subject;
}


string phpstring::strrev(string str)
{
    string out = "";
    for(string::iterator it = str.end();it!=str.begin();it--){
        char sym = *it;
        if(sym!='\0')
            out += *it;
    }
    out += *(str.begin()) ;
    return out;
}


string phpstring::chr(int asciiCode)
{
    string out = "";
    char symb = asciiCode;
    out += symb;
    return out;
}


string phpstring::strtolower(string str)
{
    string result;
    for(string::iterator it=str.begin();it!=str.end();it++)
        result.push_back(tolower( *it ));
    return result;
}
