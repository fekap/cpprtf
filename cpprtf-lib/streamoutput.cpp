#include "streamoutput.h"

CppRtf_StreamOutput::CppRtf_StreamOutput()
    :m_filename("")
{
}

void CppRtf_StreamOutput::setFilename(string filename)
{
    m_filename = filename;
}

string CppRtf_StreamOutput::getFilename()
{
    return m_filename;
}

void CppRtf_StreamOutput::open(OpenMode mode)
{
    if (m_handle.is_open()) {
        return;
    }
    if(mode == ReadOnly){
        m_handle.open(m_filename.c_str(),ios_base::in);
    }

    if(mode == WriteOnly){
        m_handle.open(m_filename.c_str(),ios_base::out|ios_base::binary);
    }
    if (!m_handle.is_open()) {
        string err = "Could not open rtf output stream (url: " +m_filename+ ")!";
        throw err;
    }
    //    flock($this->_handle, LOCK_EX); //TODO - разобраться
}

void CppRtf_StreamOutput::close()
{
    if (m_handle.is_open()) {
        m_handle.close();
    }
}

void CppRtf_StreamOutput::write(string data)
{
    if (!m_handle.is_open()) {
        string err = "Can not write on an undefined handle! Forgot to call open()?";
        throw err;
    }
    m_handle<<data;
}

string CppRtf_StreamOutput::getContent()
{
    open(ReadOnly);
    if(m_handle.is_open()){
        string out;
        string line;
        while( getline( m_handle, line ) ) {
            out += line;
        }
        return out;
    }
    return "";
}
