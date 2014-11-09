#include "fonttable.h"
#include "tools/stringtools.h"

CppRtf_DocHead_FontTable::CppRtf_DocHead_FontTable()
{
    m_fontFamilies.push_back("Times New Roman");
}

void CppRtf_DocHead_FontTable::add(string fontFamily)
{
    if(!fontFamily.empty()){
        if(getFontIndex(fontFamily)==-1){
            m_fontFamilies.push_back(fontFamily);
        }
    }
}
int CppRtf_DocHead_FontTable::getFontIndex(string fontFamily)
{
    vector<string>::iterator it=find (m_fontFamilies.begin(), m_fontFamilies.end(), fontFamily);
    if(it==m_fontFamilies.end())
        return -1;
    else{
        return distance(m_fontFamilies.begin(),it);
    }
}

string CppRtf_DocHead_FontTable::getContent()
{
    string content = "{\\fonttbl";
    for(unsigned int index=0;index<m_fontFamilies.size();index++){
        content+="{\\f"+cppstring::numtostr((int)index)+" "+m_fontFamilies[index]+";}";
    }
    content += "}\r\n";

    return content;
}
