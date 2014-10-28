#include "format.h"
#include "cpprtf.h"
#include "unit.h"
#include "math.h"

CppRtf_Border_Format::CppRtf_Border_Format(float size, string color, FormatType type, float space):
    m_colorTable(0)
{
    m_size    = round(size * CppRtf::SPACE_IN_POINTS); // convert points to twips
    m_type    = type;
    m_color   = color;
    m_space   = CppRtf_Unit::getUnitInTwips(space);
}

CppRtf_Border_Format::FormatType CppRtf_Border_Format::getType()
{
    return m_type;
}

string CppRtf_Border_Format::getColor()
{
    return m_color;
}

int CppRtf_Border_Format::getSize()
{
    return m_size;
}

float CppRtf_Border_Format::getSpace()
{
    return m_space;
}

void CppRtf_Border_Format::setColorTable(CppRtf_DocHead_ColorTable *colorTable)
{
    if (!m_color.empty()) {
        colorTable->add(m_color);
    }
    m_colorTable = colorTable;
}

string CppRtf_Border_Format::getContent()
{
    using namespace cppstring;
    string content = (m_size > 0 ? getTypeAsRtfCode() : "");
    content += "\\brdrw" + numtostr(m_size)
            + "\\brsp" + numtostr(m_space);

    if ((!m_color.empty())&& (m_colorTable!=0)) {
        int colorIndex = m_colorTable->getColorIndex(m_color);
        if (colorIndex !=-1) {
            content += "\\brdrcf" + numtostr(colorIndex);
        }
    }

    return content + " ";
}

string CppRtf_Border_Format::getTypeAsRtfCode()
{
    switch (m_type) {
        case CppRtf_Border_Format::TYPE_DOT:
            return "\\brdrdot";

        case CppRtf_Border_Format::TYPE_DASH:
            return "\\brdrdash";

        case CppRtf_Border_Format::TYPE_DOTDASH:
            return "\\brdrdashd";

        default:
            return "\\brdrs";
    }
}


