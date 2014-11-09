#include "header.h"
#include "cpprtf.h"
#include "unit.h"
#include "writer/interface.h"

CppRtf_Container_Header::CppRtf_Container_Header(CppRtf *rtf, HeaderType type)
    :CppRtf_Container_Base(rtf),m_rtfType("header")
{
    m_type = type;
    if (m_type == CppRtf_Container_Header::TYPE_FIRST) {
      rtf->setSpecialLayoutForFirstPage(true);
    }
    m_offsetHeight = -1;
}

void CppRtf_Container_Header::setPosition(float height)
{
    m_offsetHeight= height;
}

string CppRtf_Container_Header::getRtfType()
{
    return m_rtfType;
}

string CppRtf_Container_Header::getTypeAsRtfCode()
{
    string rtfType = this->getRtfType();
    string err = "";
    switch (m_type) {
        case TYPE_ALL:
            if (!m_rtf->isOddEvenDifferent()) {
                return rtfType;
            }
            err = "Header type TYPE_ALL is not allowed, when using odd even different!";
            throw err;

        case TYPE_LEFT:
            if (m_rtf->isOddEvenDifferent()) {
                return rtfType + "l";
            }
            err = "Header type TYPE_LEFT is not allowed, when using not odd even different!";
            throw err;

        case TYPE_RIGHT:
            if (m_rtf->isOddEvenDifferent()) {
                return rtfType  + "r";
            }
            err = "Header type TYPE_RIGHT is not allowed, when using not odd even different!";
            throw err;

        case TYPE_FIRST:
            if (m_rtf->hasSpecialLayoutForFirstPage()) {
                return rtfType + "f";
            }
            err = "Header type TYPE_FIRST is not allowed, when using not special layout for first page!";
            throw err;

        default:
            err = "Header type is not defined!";
            throw err;
    }
}

void CppRtf_Container_Header::render()
{
    CppRtf_Writer_Interface* stream = m_rtf->getWriter();

   if (m_offsetHeight>-1) {
       stream->write("\\\\" + this->getRtfType() + 'y' + cppstring::numtostr(CppRtf_Unit::getUnitInTwips(m_offsetHeight)));
   }
//   stream->write("{\\\\" + this->getTypeAsRtfCode() + " ");//TODO: разобраться
   stream->write("{\\" + this->getTypeAsRtfCode() + " ");
   CppRtf_Container_Base::render();

   int count = countElements();
   if(count>0){
       BaseElement *last = this->getElements().at(count-1);
       if(last->instanceOf<CppRtf_Element*>()){
           stream->write("\\par");
       }
   }
   stream->write("}\r\n");
}
