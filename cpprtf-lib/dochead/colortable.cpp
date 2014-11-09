#include "colortable.h"

CppRtf_DocHead_ColorTable::CppRtf_DocHead_ColorTable()
{
    m_colors.push_back("000000");
}

void CppRtf_DocHead_ColorTable::add(string color)
{
    if (!color.empty()) {
        color = getColorAsFullHexCode(color);
        if (getColorIndex(color)==-1) {
            m_colors.push_back(color);
        }
    }
}

int CppRtf_DocHead_ColorTable::getColorIndex(string color)
{
    color = getColorAsFullHexCode(color);
    vector<string>::iterator it=find (m_colors.begin(), m_colors.end(), color);
    if(it==m_colors.end())
        return -1;
    else
        return distance(m_colors.begin(),it)+1;
}

string CppRtf_DocHead_ColorTable::getContent()
{
    string content = "{\\colortbl;";
    for(vector<string>::iterator it=m_colors.begin();it!=m_colors.end();it++){
        content+=convertHexColorToRtf(*it)+";";
    }
    content += "}\r\n";
    return content;
}
string CppRtf_DocHead_ColorTable::getColorAsFullHexCode(string color)
{
    color = ltrim(color, "#");
    if (color.length() == 3) {
        color = str_repeat(color.substr(0,1), 2)
                +str_repeat(color.substr(1,1), 2)
                +str_repeat(color.substr(2,1), 2);
    }
    return strtoupper(color);
}

string CppRtf_DocHead_ColorTable::convertHexColorToRtf(string color)
{
    if (color.length() == 6) {
        string red=cppstring::numtostr(hexdec(color.substr(0,2)));
        string green=cppstring::numtostr(hexdec(color.substr(2,2)));
        string blue=cppstring::numtostr(hexdec(color.substr(4,2)));
        return "\\red"+ red + "\\green" + green + "\\blue" + blue;
    }
    string err="Color must be a hex number of length 3 or 6 digits! You gave me: #"+color;
    throw err;
}
