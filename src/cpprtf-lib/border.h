#ifndef BORDER_H
#define BORDER_H
#include "border/format.h"
//#include "cpprtf.h"


class CppRtf;

//Class for creating borders within rtf documents.
class CppRtf_Border
{
public:
    CppRtf_Border(CppRtf* rtf, CppRtf_Border_Format* left  = 0, CppRtf_Border_Format* top   = 0, CppRtf_Border_Format* right = 0, CppRtf_Border_Format* bottom = 0);
    CppRtf_Border(CppRtf_Border* border);

    /*
         * creates border by defining border format
         * size:   size of border
         * color:  color of border (example '#ff0000' or '#f00')
         * type:   represented by class constants PHPRtfLite_Border_Format::TYPE_*<br>
         *   Possible values:<br>
         *     PHPRtfLite_Border_Format::TYPE_SINGLE  'single'<br>
         *     PHPRtfLite_Border_Format::TYPE_DOT     'dot'<br>
         *     PHPRtfLite_Border_Format::TYPE_DASH    'dash'<br>
         *     PHPRtfLite_Border_Format::TYPE_DOTDASH 'dotdash'
         * space:  space between borders and the paragraph
         * left:   left border
         * top:    top border
         * right:  right border
         * bottom: bottom border
         *
         */
    static CppRtf_Border* create(CppRtf* rtf, float size = 0, string color = "", CppRtf_Border_Format::FormatType type = CppRtf_Border_Format::TYPE_SINGLE, float space = 0.0,
                                 bool left = true, bool top = true, bool right = true, bool bottom = true);

    //sets border format of element
    void setBorders(CppRtf_Border_Format* borderFormat, bool left = true, bool top = true, bool right = true, bool bottom = true);

    //sets border format for left border
    void setBorderLeft(CppRtf_Border_Format* borderFormat);

    //gets border format of left border
    CppRtf_Border_Format* getBorderLeft();

    //sets border format for right border
    void setBorderRight(CppRtf_Border_Format* borderFormat);

    //gets border format of right border
    CppRtf_Border_Format* getBorderRight();

    //sets border format for top border
    void setBorderTop(CppRtf_Border_Format* borderFormat);

    //gets border format of top border
    CppRtf_Border_Format* getBorderTop();

    //sets border format for bottom border
    void setBorderBottom(CppRtf_Border_Format* borderFormat);

    //gets border format of bottom border
    CppRtf_Border_Format* getBorderBottom();

    //gets rtf code of object
    //type: rtf code part
    string getContent(string type = "\\");

protected:
    CppRtf* m_rtf;
    CppRtf_Border_Format* m_borderLeft;
    CppRtf_Border_Format* m_borderRight;
    CppRtf_Border_Format* m_borderTop;
    CppRtf_Border_Format* m_borderBottom;
};

#endif // BORDER_H
