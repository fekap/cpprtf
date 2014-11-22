#include "element.h"
#include "writer/interface.h"
#include <boost/regex.hpp>

CppRtf_Element::CppRtf_Element(CppRtf *rtf, string text, CppRtf_Font *font, CppRtf_ParFormat *parFormat):
    m_isRtfCode(false),
    m_convertTagsToRtf(false)
{
    m_rtf         = rtf;
    m_text        = text;
    m_font        = font? new CppRtf_Font(*font) : 0;
    m_parFormat   = parFormat ? new CppRtf_ParFormat(*parFormat) : 0;

    if (m_font!=0) {
        rtf->registerFont(m_font);
    }
    if (m_parFormat!=0) {
        rtf->registerParFormat(m_parFormat);
    }
}

CppRtf_Element::CppRtf_Element(CppRtf_Element &element)
{
    m_rtf         = element.m_rtf;
    m_text        = element.m_text;
    m_isRtfCode   = element.m_isRtfCode;
    m_convertTagsToRtf = element.m_convertTagsToRtf;
    m_font        = element.m_font? new CppRtf_Font(*element.m_font) : 0;
    m_parFormat   = element.m_parFormat ? new CppRtf_ParFormat(*element.m_parFormat) : 0;
}



CppRtf_Element::~CppRtf_Element()
{
    if(m_font!=0){
        delete m_font;
        m_font = 0;
    }
    if(m_parFormat!=0){
        delete m_parFormat;
        m_parFormat = 0;
    }
}

bool CppRtf_Element::isEmptyParagraph()
{
    return (m_parFormat!=0 )&& (m_text == "\\\\par") && m_isRtfCode;
}

void CppRtf_Element::setConvertTagsToRtf()
{
    m_convertTagsToRtf=true;
}

void CppRtf_Element::setIsRtfCode()
{
    m_isRtfCode=true;
}

bool CppRtf_Element::isRtfCode()
{
    return m_isRtfCode;
}

CppRtf_Font *CppRtf_Element::getFont()
{
    return m_font;
}

CppRtf_ParFormat *CppRtf_Element::getParFormat()
{
    return m_parFormat;
}

string CppRtf_Element::convertTagsToRtf(string text, string charset)
{
    //TODO: preg_replace - доделать и проверить |smi
    vector<string> search;
    // bold
    search.push_back("<STRONG\\s*>(.*?)</STRONG\\s*>");
    search.push_back("<B*>(.*?)</B*>");
    // italic
     search.push_back("<EM\\s*>(.*?)</EM\\s*>");
     search.push_back("<I\\s*>(.*?)</I\\s*>");
     // underline
      search.push_back("<U\\s*>(.*?)</U\\s*>");
      // break
     search.push_back("<BR\\s*(/)?\\s*>");
     search.push_back("<LINE\\s*(/)?\\s*>");
     // horizontal rule
    search.push_back("<HR\\s*(/)?\\s*>");
    search.push_back("<CHDATE\\s*(/)?\\s*>");

    search.push_back("<CHDPL\\s*(/)?\\s*>");
    search.push_back("<CHDPA\\s*(/)?\\s*>");
    search.push_back("<CHTIME\\s*(/)?\\s*>");
    search.push_back("<CHPGN\\s*(/)?\\s*>");
    // tab
    search.push_back("<TAB\\s*(/)?\\s*>");
    // bullet
    search.push_back("<BULLET\\s*(/)?\\s*>");
    search.push_back("<PAGENUM\\s*(/)?\\s*>");
    search.push_back("<PAGETOTAL\\s*(/)?\\s*>");
    search.push_back("<SECTNUM\\s*(/)?\\s*>");
    search.push_back("<SUP\\s*>(.*?)</SUP\\s*>");
    search.push_back("<SUB\\s*>(.*?)</SUB\\s*>");

     /////////////
     vector<string> replace;
     // bold
     replace.push_back("\\\\b \\1\\\\b0 ");
     replace.push_back("\\\\b \\1\\\\b0 ");
     // italic
     replace.push_back("\\\\i \\1\\\\i0 ");
     replace.push_back("\\\\i \\1\\\\i0 ");
     // underline
     replace.push_back("\\\\ul \\1\\\\ul0 ");
     // break
     replace.push_back("\\\\line ");
     replace.push_back("\\\\line ");
      // horizontal rule
     replace.push_back("{\\\\pard \\\\brdrb \\\\brdrs \\\\brdrw10 \\\\brsp20 \\\\par}");
     replace.push_back("\\\\chdate ");
     replace.push_back("\\\\chdpl ");
     replace.push_back("\\\\chdpa ");
     replace.push_back("\\\\chtime ");
     replace.push_back("\\\\chpgn ");
     //tab
     replace.push_back("\\\\tab ");
     // bullet
     replace.push_back("\\\\bullet ");
     replace.push_back("\\\\chpgn ");
     replace.push_back("{\\\\field {\\\\*\\\\fldinst {NUMPAGES }}}");  //???TODO
     replace.push_back("\\\\sectnum ");
     replace.push_back("{\\\\super \\1\\\\super0}");
     replace.push_back("{\\\\sub \\1\\\\sub0}");

     text = preg_replace(search, replace, text);
//     $text = html_entity_decode($text, ENT_COMPAT, $charset);//TODO
     return text;
}

void CppRtf_Element::render()
{
    CppRtf_Writer_Interface * stream = m_rtf->getWriter();
    string text = m_text;
    if (!m_isRtfCode) {
        string charset = m_rtf->getCharset();
        text = CppRtf::quoteRtfCode(text);
        if (m_convertTagsToRtf) {
            text = CppRtf_Element::convertTagsToRtf(text, charset);
        }
        text = CppRtf_Utf8::getUnicodeEntities(text, charset);
    }

    stream->write(this->getOpeningToken());

    if (m_font) {
        stream->write(m_font->getContent());
    }
    if (!this->isEmptyParagraph() || m_isRtfCode) {
        stream->write(text);
    }

    stream->write(this->getClosingToken() + "\r\n");
}

string CppRtf_Element::getOpeningToken()
{
    return "{";
}

string CppRtf_Element::getClosingToken()
{
    return "}";
}
