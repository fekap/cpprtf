#include "formfield.h"
#include "cpprtf.h"
#include "writer/interface.h"

CppRtf_FormField::CppRtf_FormField(CppRtf *rtf, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
{
    m_rtf = rtf;
    m_font = font;
    m_parFormat = parFormat;
   if (font) {
       m_rtf->registerFont(font);
   }

   //null
   m_defaultValue = "";
}

void CppRtf_FormField::setDefaultValue(string value)
{
    m_defaultValue = value;
}

CppRtf_Font *CppRtf_FormField::getFont()
{
    return m_font;
}

CppRtf_ParFormat *CppRtf_FormField::getParFormat()
{
    return m_parFormat;
}

void CppRtf_FormField::render()
{
    CppRtf_Writer_Interface* stream = m_rtf->getWriter();
    stream->write(" ");
      if (m_font) {
          stream->write("{" + m_font->getContent());
      }

      string defaultValue = CppRtf_Utf8::getUnicodeEntities(m_defaultValue, m_rtf->getCharset());
      string content = "{\\field{\\*\\fldinst " + this->getType()
          + "  {\\*\\formfield" + this->getRtfCode() + "}"
          + "}{\\fldrslt " + defaultValue + "}}";

      stream->write(content);

      if (m_font) {
          stream->write(m_font->getClosingContent() + "}");
      }
      stream->write(" ");
}
