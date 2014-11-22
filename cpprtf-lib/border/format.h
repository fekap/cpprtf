#ifndef BORDER_FORMAT_H
#define BORDER_FORMAT_H
#include "dochead/colortable.h"

//Class for border format.
class CppRtf_Border_Format
{
public:
    /*
         * parameters:
         * size   size of border
         * color of border (example '#ff0000' or '#f00')
         * type   represented by class constants PHPRtfLite_Border_Format::TYPE_*<br>
         *   Possible values:<br>
         *     TYPE_SINGLE:     single (default)<br>
         *     TYPE_DOT:        dot<br>
         *     TYPE_DASH:       dash<br>
         *     TYPE_DOTDASH:    dotdash<br>
         * @param   float       $space  space between borders and the paragraph
         */
    enum FormatType{
        TYPE_SINGLE,
        TYPE_DOT,
        TYPE_DASH,
        TYPE_DOTDASH
    };

    CppRtf_Border_Format(float size = 0.0, string color = "", FormatType type = TYPE_SINGLE, float space = 0.0);
    CppRtf_Border_Format(CppRtf_Border_Format& format);
    ~CppRtf_Border_Format();

    //gets border format type
    FormatType getType();

    //gets border color
    string getColor();

    //gets size in twips
    int getSize();

    //gets border space
    float getSpace();

    //sets rtf color table
    void setColorTable(CppRtf_DocHead_ColorTable* colorTable);

    //gets rtf code
    string getContent();

protected:
    int m_size;
    FormatType m_type;
    string m_color;
    CppRtf_DocHead_ColorTable* m_colorTable;//rtf color table
    int m_space;

private:
    //Gets border format type as rtf code
    string getTypeAsRtfCode();
};

#endif // BORDER_FORMAT_H
