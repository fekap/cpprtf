#include "border.h"
#include "cpprtf.h"

CppRtf_Border::CppRtf_Border(CppRtf *rtf, CppRtf_Border_Format *left, CppRtf_Border_Format *top, CppRtf_Border_Format *right, CppRtf_Border_Format *bottom)
{

    m_rtf = rtf;
    if (left!=0) {
        left->setColorTable(rtf->getColorTable());
    }
    m_borderLeft = left;

    if (top!=0) {
        top->setColorTable(rtf->getColorTable());
    }
    m_borderTop = top;

    if (right!=0) {
        right->setColorTable(rtf->getColorTable());
    }
    m_borderRight = right;

    if (bottom!=0) {
        bottom->setColorTable(rtf->getColorTable());
    }
    m_borderBottom    = bottom;
}

CppRtf_Border::CppRtf_Border(CppRtf_Border *border)
{
    m_rtf = border->m_rtf;
    m_borderBottom = border->m_borderBottom;
    m_borderLeft = border->m_borderLeft;
    m_borderRight = border->m_borderRight;
    m_borderTop = border->m_borderTop;
}

CppRtf_Border *CppRtf_Border::create(CppRtf *rtf, float size, string color, CppRtf_Border_Format::FormatType type, float space, bool left, bool top, bool right, bool bottom)
{
    CppRtf_Border* border = new CppRtf_Border(rtf);
    border->setBorders(new CppRtf_Border_Format(size, color, type, space), left, top, right, bottom);
    return border;
}

void CppRtf_Border::setBorders(CppRtf_Border_Format *borderFormat, bool left, bool top, bool right, bool bottom)
{
    borderFormat->setColorTable(m_rtf->getColorTable());

    if (left) {
        m_borderLeft  = borderFormat;
    }

    if (top) {
        m_borderTop   = borderFormat;
    }

    if (right) {
        m_borderRight = borderFormat;
    }

    if (bottom) {
        m_borderBottom = borderFormat;
    }
}

void CppRtf_Border::setBorderLeft(CppRtf_Border_Format *borderFormat)
{
    setBorders(borderFormat,true,false,false,false);
    m_borderLeft = borderFormat;
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
