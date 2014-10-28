#ifndef FONTTABLE_H
#define FONTTABLE_H
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//defines font table for the rtf document head
class CppRtf_DocHead_FontTable
{
public:
    CppRtf_DocHead_FontTable();

    //adds font family to the font table
    void add(string fontFamily);

    //gets font index from font table or return -1
    int getFontIndex(string fontFamily);

    //gets rtf font table
    string getContent();
protected:
    vector<string> m_fontFamilies;
};

#endif // FONTTABLE_H


