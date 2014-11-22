#ifndef PARFORMAT_H
#define PARFORMAT_H
#include "tools/stringtools.h"
#include "dochead/colortable.h"
#include "border.h"

// paragraph formatting class for rtf documents.
class CppRtf_ParFormat
{
public:
    /*
         *alignment:  represented by class constants TEXT_ALIGN_*<br>
         *   Possible values:<br>
         *     TEXT_ALIGN_LEFT_INT      => 'left'    - left alignment<br>
         *     TEXT_ALIGN_RIGHT_INT     => 'right'   - right alignment<br>
         *     TEXT_ALIGN_CENTER_INT    => 'center'  - center alignment<br>
         *     TEXT_ALIGN_JUSTIFY_INT   => 'justify' - justify alignment
         */
    enum TextAlign{
        TEXT_ALIGN_LEFT,
        TEXT_ALIGN_CENTER,
        TEXT_ALIGN_RIGHT,
        TEXT_ALIGN_JUSTIFY
    };
    CppRtf_ParFormat(TextAlign alignment = CppRtf_ParFormat::TEXT_ALIGN_LEFT);

    ~CppRtf_ParFormat();

    //sets text alignment
    void setTextAlignment(TextAlign alignment);

    //gets text alignment
    TextAlign getTextAlignment();

    //sets first line indention in centimeter (default 0)
    void setIndentFirstLine(float indentFirst);

    //gets first line indention in centimeter
    float getIndentFirstLine();

    //sets left indent in centimeter (default 0)
    void setIndentLeft(float indentLeft);

    //gets left indent in centimeter
    float getIndentLeft();

    //sets right indent in centimeter (default 0)
    void setIndentRight(float indentRight);

    //gets right indent in centimeter
    float getIndentRight();

    //sets the space before paragraph
    void setSpaceBefore(float spaceBefore);

    //gets the space before paragraph
    float getSpaceBefore();

    //sets the space after paragraph
    void setSpaceAfter(float spaceAfter);

    //gets the space after paragraph
    float getSpaceAfter();

    //sets line space
    void setSpaceBetweenLines(float spaceBetweenLines);

    //gets line space
    float getSpaceBetweenLines();

    /*
         * sets shading
         * shading: shading in percents (from 0 till 100)
         */
    void setShading(int shading);

    //gets shading
    int getShading();

    //sets rtf color table
    void setColorTable(CppRtf_DocHead_ColorTable* colorTable);

    //sets background color
    void setBackgroundColor(string backgroundColor);

    //gets background color
    string getBackgroundColor();

    //sets border of paragraph
    void setBorder(CppRtf_Border *border);

    //gets border of paragraph
    CppRtf_Border* getBorder();

    //gets rtf code of paragraph
    string getContent();


protected:
    CppRtf_DocHead_ColorTable* m_colorTable;//rtf color tables
    TextAlign m_alignment;//text alignment
    float m_indentFirstLine ;//indention of first line
    float m_indentLeft;//left indention of paragraph
    float m_indentRight;//right indention of paragraph
    float m_spaceBefore;//space before paragraph
    float m_spaceAfter;//space after paragraph
    float m_spaceBetweenLines;//space between each line of paragraph

    int m_shading ;//shading of paragraph
    string m_backgroundColor;//background color of paragraph
    CppRtf_Border* m_border;//border instance
};

#endif // PARFORMAT_H
