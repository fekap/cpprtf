#include "string.h"

CppRtf_Writer_String::CppRtf_Writer_String()
{
    m_closed = true;
    m_content = "";
}

void CppRtf_Writer_String::open()
{
    m_closed = false;
    m_content = "";
}

void CppRtf_Writer_String::close()
{
    m_closed = true;
}

void CppRtf_Writer_String::write(string data)
{
    if (m_closed) {
        this->open();
    }
    m_content += data;
}

string CppRtf_Writer_String::getContent()
{
    this->close();
    return m_content;
}


