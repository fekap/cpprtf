#include "footnote.h"

CppRtf_Footnote::CppRtf_Footnote(CppRtf *rtf, string text, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
    :m_text(text),
      m_rtf(rtf),
      m_typeSettingType(CppRtf_Footnote::TYPE_SUPER)
{
    if ((font==0) && (CppRtf_Footnote::defaultFont!=0)) {
        font = CppRtf_Footnote::defaultFont;
    }

    if (font!=0) {
        m_rtf->registerFont(font);
    }

    if (parFormat!=0) {
        m_rtf->registerParFormat(parFormat);
    }

    m_font        = font;
    m_parFormat   = parFormat;
}

void CppRtf_Footnote::setDefaultFont(CppRtf_Font *defaultFont)
{
    CppRtf_Footnote::defaultFont=defaultFont;
}

CppRtf_Font *CppRtf_Footnote::getDefaultFont()
{
    return CppRtf_Footnote::defaultFont;
}

void CppRtf_Footnote::setFont(CppRtf_Font *font)
{
    m_rtf->registerFont(font);
    m_font=font;
}

CppRtf_Font *CppRtf_Footnote::getFont()
{
    return m_font;
}

void CppRtf_Footnote::setParFormat(CppRtf_ParFormat *parFormat)
{
    m_rtf->registerParFormat(parFormat);
    m_parFormat=parFormat;
}

CppRtf_ParFormat *CppRtf_Footnote::getParFormat()
{
    return m_parFormat;
}

void CppRtf_Footnote::setTypeSettingType(string type)
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

    string typeSetting = m_typeSettingType != TYPE_NORMAL
        ? "\\\\" + m_typeSettingType
        : "";

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

const string CppRtf_Footnote::TYPE_SUPER="super";
const string CppRtf_Footnote::TYPE_SUB="sub";
const string CppRtf_Footnote::TYPE_NORMAL="normal";

CppRtf_Font *CppRtf_Footnote::defaultFont=0;
