#include "footnote.h"

CppRtf_Footnote::CppRtf_Footnote(CppRtf *rtf, string text, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
    :m_text(text),
      m_rtf(rtf),
      m_typeSettingType(CppRtf_Footnote::TYPE_SUPER)
{
    m_font = font ? new CppRtf_Font(*font) : 0;
    m_parFormat = parFormat ? new CppRtf_ParFormat(*parFormat) : 0;

    if ((m_font==0) && (CppRtf_Footnote::defaultFont!=0)) {
        m_font = CppRtf_Footnote::defaultFont ? new CppRtf_Font(*CppRtf_Footnote::defaultFont) : 0;
    }

    if (m_font!=0) {
        m_rtf->registerFont(m_font);
    }

    if (m_parFormat!=0) {
        m_rtf->registerParFormat(m_parFormat);
    }
}

CppRtf_Footnote::CppRtf_Footnote(CppRtf_Footnote &footnote)
{
    m_rtf = footnote.m_rtf;
    m_font = footnote.m_font? new CppRtf_Font(*footnote.m_font) : 0;
    m_parFormat = footnote.m_parFormat? new CppRtf_ParFormat(*footnote.m_parFormat) : 0;
}

CppRtf_Footnote::~CppRtf_Footnote()
{
    if (m_font)
        delete m_font;
    if (m_parFormat)
        delete m_parFormat;
}

void CppRtf_Footnote::setDefaultFont(CppRtf_Font *defaultFont)
{
    if (CppRtf_Footnote::defaultFont)
        delete CppRtf_Footnote::defaultFont;
    CppRtf_Footnote::defaultFont=defaultFont ? new CppRtf_Font(*defaultFont) : 0;
}

CppRtf_Font *CppRtf_Footnote::getDefaultFont()
{
    return CppRtf_Footnote::defaultFont;
}

void CppRtf_Footnote::setFont(CppRtf_Font *font)
{
    font ? m_font= new CppRtf_Font(*font): 0;
    m_rtf->registerFont(m_font);
}

CppRtf_Font *CppRtf_Footnote::getFont()
{
    return m_font;
}

void CppRtf_Footnote::setParFormat(CppRtf_ParFormat *parFormat)
{
    parFormat ? m_parFormat= new CppRtf_ParFormat(*parFormat): 0;
    m_rtf->registerParFormat(m_parFormat);
}

CppRtf_ParFormat *CppRtf_Footnote::getParFormat()
{
    return m_parFormat;
}

void CppRtf_Footnote::setTypeSettingType(SettingType type)
{
    m_typeSettingType=type;
}

string CppRtf_Footnote::getTypeAsRtfCode()
{
    return "\\footnote";
}

void CppRtf_Footnote::render()
{
    CppRtf_StreamOutput* stream = m_rtf->getWriter();

    string typeSetting = "";
    if(m_typeSettingType == TYPE_SUPER){
        typeSetting = "\\super";
    }
    if(m_typeSettingType == TYPE_SUB){
        typeSetting = "\\sub";
    }

    stream->write(
        "{" + typeSetting + "\\chftn}"
        + "{" + this->getTypeAsRtfCode()
        + "\\pard\\plain\\lin283\\fi-283 "
    );

    if (m_parFormat) {
        stream->write(m_parFormat->getContent());
    }
    if (m_font) {
        stream->write(m_font->getContent());
    }
    string charset = m_rtf->getCharset();
    string textEncoded = CppRtf::quoteRtfCode(m_text);
    stream->write(
        "{\\up6\\chftn}\r\n"
        + CppRtf_Utf8::getUnicodeEntities(textEncoded, charset)
        + "} "
    );
}

CppRtf_Font *CppRtf_Footnote::defaultFont=0;
