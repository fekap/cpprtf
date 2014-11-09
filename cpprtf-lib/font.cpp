#include "font.h"

CppRtf_Font::CppRtf_Font(int size, string fontFamily, string color, string backgroundColor):
    m_colorTable(0),
    m_fontTable(0),
    m_isBold(false),
    m_isItalic(false),
    m_isUnderlined(false),
    m_isStriked(false),
    m_isDoubleStriked(false)
{
    m_size = size;
    m_fontFamily = fontFamily;
    m_color = color;
    m_backgroundColor = backgroundColor;
    m_animation="";
}

void CppRtf_Font::setColorTable(CppRtf_DocHead_ColorTable *colorTable)
{
    if (!m_color.empty()) {
        colorTable->add(m_color);
    }
    if (!m_backgroundColor.empty()) {
        colorTable->add(m_backgroundColor);
    }
    m_colorTable = colorTable;
}

void CppRtf_Font::setFontTable(CppRtf_DocHead_FontTable *fontTable)
{
    if (!m_fontFamily.empty()) {
        fontTable->add(m_fontFamily);
    }
    m_fontTable = fontTable;
}

string CppRtf_Font::getFontFamily()
{
    return m_fontFamily;
}

int CppRtf_Font::getSize()
{
    return m_size;
}

string CppRtf_Font::getColor()
{
    return m_color;
}

string CppRtf_Font::getBackgroungColor()
{
    return m_backgroundColor;
}

void CppRtf_Font::setBold(bool bold)
{
    m_isBold=bold;
}

bool CppRtf_Font::isBold()
{
    return m_isBold;
}

void CppRtf_Font::setItalic(bool italic)
{
    m_isItalic=italic;
}

bool CppRtf_Font::isItalic()
{
    return m_isItalic;
}

void CppRtf_Font::setUnderline(bool underlined)
{
    m_isUnderlined=underlined;
}

bool CppRtf_Font::isUnderlined()
{
    return m_isUnderlined;
}

void CppRtf_Font::setStriked(bool striked)
{
    m_isStriked = striked;

    if (striked) {
        m_isDoubleStriked = false;
    }
}

bool CppRtf_Font::isStriked()
{
    return m_isStriked;
}

void CppRtf_Font::setDoubleStriked(bool striked)
{
    m_isDoubleStriked = striked;

    if (striked) {
        m_isStriked = false;
    }
}

bool CppRtf_Font::isDoubleStriked()
{
    return m_isDoubleStriked;
}

void CppRtf_Font::setAnimation(int animation)
{
    m_animation=cppstring::numtostr(animation);
}

string CppRtf_Font::getContent()
{
    using namespace cppstring;
    string content = "";

    if (m_size > 0) {
        content += "\\fs" + numtostr(m_size * 2) + " ";
    }

    if ((!m_fontFamily.empty()) && (m_fontTable!=0)) {
        int fontIndex = m_fontTable->getFontIndex(m_fontFamily);
        if (fontIndex !=-1) {
            content += "\\f" + numtostr(fontIndex )+ " ";
        }
    }

    if ((!m_color .empty())&& (m_colorTable!=0)) {
        int colorIndex = m_colorTable->getColorIndex(m_color);
        if (colorIndex !=-1) {
            content += "\\cf" + numtostr(colorIndex) + ' ';
        }
    }

    if ((!m_backgroundColor.empty()) && (m_colorTable!=0)){
        int colorIndex = m_colorTable->getColorIndex(m_backgroundColor);
        if (colorIndex !=-1) {
            content += "\\chcbpat" + numtostr(colorIndex) + ' ';
        }
    }

    if (m_isBold) {
        content += "\\b ";
    }
    if (m_isItalic) {
        content += "\\i ";
    }
    if (m_isUnderlined) {
        content += "\\ul ";
    }
    if (!m_animation.empty()) {
        content += "\\animtext" + m_animation;
    }
    if (m_isStriked) {
        content += "\\strike " + m_animation;
    }
    else    if (m_isDoubleStriked) {
        content += "\\striked1 " + m_animation;
    }

    return content;
}

string CppRtf_Font::getClosingContent()
{
    string content = "";
            if (!m_color.empty()) {
                content += "\\cf0 ";
            }
            if (!m_backgroundColor.empty()) {
                content += "\\chcbpat0 ";
            }
            if (m_isBold) {
                content += "\\b0 ";
            }
            if (m_isItalic) {
                content += "\\i0 ";
            }
            if (m_isUnderlined) {
                content += "\\ul0 ";
            }
            return content;
}
