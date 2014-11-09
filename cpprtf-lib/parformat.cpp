#include "parformat.h"
#include "math.h"
#include "unit.h"
#include "element.h"
#include "cpprtf.h"

CppRtf_ParFormat::CppRtf_ParFormat(TextAlign alignment):
    m_indentFirstLine(0),
    m_indentLeft(0),
    m_indentRight(0),
    m_spaceBefore(0),
    m_spaceAfter(0),
    m_spaceBetweenLines(0),
    m_shading(0),
    m_border(0)
{
    m_alignment = alignment;
}

void CppRtf_ParFormat::setTextAlignment(TextAlign alignment)
{
    m_alignment = alignment;
}

CppRtf_ParFormat::TextAlign CppRtf_ParFormat::getTextAlignment()
{
    return m_alignment;
}

void CppRtf_ParFormat::setIndentFirstLine(float indentFirst)
{
    m_indentFirstLine=indentFirst;
}

float CppRtf_ParFormat::getIndentFirstLine()
{
    return m_indentFirstLine;
}

void CppRtf_ParFormat::setIndentLeft(float indentLeft)
{
    m_indentLeft=indentLeft;
}

float CppRtf_ParFormat::getIndentLeft()
{
    return m_indentLeft;
}

void CppRtf_ParFormat::setIndentRight(float indentRight)
{
    m_indentRight=indentRight;
}

float CppRtf_ParFormat::getIndentRight()
{
    return m_indentRight;
}

void CppRtf_ParFormat::setSpaceBefore(float spaceBefore)
{
    m_spaceBefore = round(spaceBefore * CppRtf::SPACE_IN_POINTS);
}

float CppRtf_ParFormat::getSpaceBefore()
{
    return m_spaceBefore;
}

void CppRtf_ParFormat::setSpaceAfter(float spaceAfter)
{
    m_spaceAfter = round(spaceAfter * CppRtf::SPACE_IN_POINTS);
}

float CppRtf_ParFormat::getSpaceAfter()
{
    return m_spaceAfter;
}

void CppRtf_ParFormat::setSpaceBetweenLines(float spaceBetweenLines)
{
    m_spaceBetweenLines = round(spaceBetweenLines * CppRtf::SPACE_IN_LINES);
}

float CppRtf_ParFormat::getSpaceBetweenLines()
{
    return m_spaceBetweenLines;
}

void CppRtf_ParFormat::setShading(int shading)
{
    m_shading = shading * 100;
}

int CppRtf_ParFormat::getShading()
{
    return m_shading;
}

void CppRtf_ParFormat::setColorTable(CppRtf_DocHead_ColorTable *colorTable)
{
    if (!m_backgroundColor.empty()) {
        m_colorTable->add(m_backgroundColor);
    }
    m_colorTable = colorTable;
}

void CppRtf_ParFormat::setBackgroundColor(string backgroundColor)
{
    m_backgroundColor = backgroundColor;
    if ((!m_backgroundColor.empty()) && (m_colorTable!=0)) {
        m_colorTable->add(m_backgroundColor);
    }
}

string CppRtf_ParFormat::getBackgroundColor()
{
    return m_backgroundColor;
}

void CppRtf_ParFormat::setBorder(CppRtf_Border *border)
{
    m_border = border;
}

CppRtf_Border *CppRtf_ParFormat::getBorder()
{
    return m_border;
}

string CppRtf_ParFormat::getContent()
{
    using namespace cppstring;
    string content = "";

            switch (m_alignment) {
                case CppRtf_ParFormat::TEXT_ALIGN_RIGHT:
                    content += "\\qr ";
                    break;

                case CppRtf_ParFormat::TEXT_ALIGN_CENTER:
                    content += "\\qc ";
                    break;

                case CppRtf_ParFormat::TEXT_ALIGN_JUSTIFY:
                    content += "\\qj ";
                    break;

                default:
                    content += "\\ql ";
                    break;
            }

            if (m_indentFirstLine != 0) {
                content += "\\fi" + numtostr(CppRtf_Unit::getUnitInTwips(m_indentFirstLine)) + " ";
            }

            if (m_indentLeft > 0) {
                content += "\\li" + numtostr(CppRtf_Unit::getUnitInTwips(m_indentLeft)) +  " ";
            }

            if (m_indentRight > 0) {
                content += "\\ri" + numtostr(CppRtf_Unit::getUnitInTwips(m_indentRight)) +  " ";
            }

            if (m_spaceBefore > 0) {
                content += "\\sb" + numtostr(m_spaceBefore) +  " ";
            }

            if (m_spaceAfter > 0) {
                content += "\\sa" + numtostr(m_spaceAfter) +  " ";
            }

            if (m_spaceBetweenLines > 0) {
                content += "\\sl" + numtostr(m_spaceBetweenLines) +  " ";
            }

            if (m_border!=0) {
                content += m_border->getContent("\\");
            }

            if (m_shading > 0) {
                content += "\\shading" + numtostr(m_shading) +  " ";
            }

            if (!m_backgroundColor.empty() && m_colorTable!=0) {
                int colorIndex = m_colorTable->getColorIndex(m_backgroundColor);
                if (colorIndex !=-1) {
                    content += "cbpat" + numtostr(colorIndex) +  " ";
                }
            }

            return content;
}

