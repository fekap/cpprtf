#include "border.h"
#include "cpprtf.h"

CppRtf_Border::CppRtf_Border(CppRtf *rtf, CppRtf_Border_Format *left, CppRtf_Border_Format *top, CppRtf_Border_Format *right, CppRtf_Border_Format *bottom)
{
    m_rtf = rtf;
    m_borderLeft = left? new CppRtf_Border_Format(*left) : 0;
    if (m_borderLeft!=0) {
        m_borderLeft->setColorTable(rtf->getColorTable());
    }

    m_borderTop = top? new CppRtf_Border_Format(*top) : 0;
    if (m_borderTop!=0) {
        m_borderTop->setColorTable(rtf->getColorTable());
    }

    m_borderRight = right? new CppRtf_Border_Format(*right) : 0;
    if (m_borderRight!=0) {
        m_borderRight->setColorTable(rtf->getColorTable());
    }

    m_borderBottom  = bottom? new CppRtf_Border_Format(*bottom) : 0;
    if (m_borderBottom!=0) {
        m_borderBottom->setColorTable(rtf->getColorTable());
    }
}

CppRtf_Border::CppRtf_Border(CppRtf_Border &border)
{
    m_rtf = border.m_rtf;
    m_borderBottom = border.m_borderBottom ? new CppRtf_Border_Format(*border.m_borderBottom) : 0;
    m_borderLeft = border.m_borderLeft ? new CppRtf_Border_Format(*border.m_borderLeft) : 0;
    m_borderRight = border.m_borderRight ? new CppRtf_Border_Format(*border.m_borderRight) : 0;
    m_borderTop = border.m_borderTop ? new CppRtf_Border_Format(*border.m_borderTop) : 0;
}

CppRtf_Border::~CppRtf_Border()
{
    if(m_borderBottom!=0){
        delete m_borderBottom;
    }
    if(m_borderLeft!=0){
        delete m_borderLeft;
    }
    if(m_borderRight!=0){
        delete m_borderRight;
    }
    if(m_borderTop!=0){
        delete m_borderTop;
    }
}

CppRtf_Border *CppRtf_Border::create(CppRtf *rtf, float size, string color, CppRtf_Border_Format::FormatType type, float space, bool left, bool top, bool right, bool bottom)
{
    CppRtf_Border* border = new CppRtf_Border(rtf);
    CppRtf_Border_Format* format = new CppRtf_Border_Format(size, color, type, space);
    border->setBorders(format, left, top, right, bottom);
    delete format;
    return border;
}

void CppRtf_Border::setBorders(CppRtf_Border_Format *borderFormat, bool left, bool top, bool right, bool bottom)
{
    if (left) {
        if(m_borderLeft!=0){
            delete m_borderLeft;
        }
        m_borderLeft  = new CppRtf_Border_Format(*borderFormat);
        m_borderLeft->setColorTable(m_rtf->getColorTable());
    }

    if (top) {
        if(m_borderTop!=0){
            delete m_borderTop;
        }
        m_borderTop   = new CppRtf_Border_Format(*borderFormat);
        m_borderTop->setColorTable(m_rtf->getColorTable());
    }

    if (right) {
        if(m_borderRight!=0){
            delete m_borderRight;
        }
        m_borderRight = new CppRtf_Border_Format(*borderFormat);
        m_borderRight->setColorTable(m_rtf->getColorTable());
    }

    if (bottom) {
        if(m_borderBottom!=0){
            delete m_borderBottom;
        }
        m_borderBottom = new CppRtf_Border_Format(*borderFormat);
        m_borderBottom->setColorTable(m_rtf->getColorTable());
    }
}

void CppRtf_Border::setBorderLeft(CppRtf_Border_Format *borderFormat)
{
    setBorders(borderFormat,true,false,false,false);
}

CppRtf_Border_Format *CppRtf_Border::getBorderLeft()
{
    return m_borderLeft;
}

void CppRtf_Border::setBorderRight(CppRtf_Border_Format *borderFormat)
{
    setBorders(borderFormat,false,false,true,false);
}

CppRtf_Border_Format *CppRtf_Border::getBorderRight()
{
    return m_borderRight;
}

void CppRtf_Border::setBorderTop(CppRtf_Border_Format *borderFormat)
{
    setBorders(borderFormat,false,true,false,false);
}

CppRtf_Border_Format *CppRtf_Border::getBorderTop()
{
    return m_borderTop;
}

void CppRtf_Border::setBorderBottom(CppRtf_Border_Format *borderFormat)
{
    setBorders(borderFormat,false,false,false,true);
}

CppRtf_Border_Format *CppRtf_Border::getBorderBottom()
{
    return m_borderBottom;
}

string CppRtf_Border::getContent(string type)
{
    string content = "";
    if (m_borderLeft!=0) {
        content += type + "brdrl" + m_borderLeft->getContent();
    }
    if (m_borderRight!=0) {
        content += type + "brdrr" + m_borderRight->getContent();
    }
    if (m_borderTop!=0) {
        content += type + "brdrt" + m_borderTop->getContent();
    }
    if (m_borderBottom!=0) {
        content += type + "brdrb" + m_borderBottom->getContent();
    }
    return content;
}
