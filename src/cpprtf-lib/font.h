#ifndef FONT_H
#define FONT_H
#include "dochead/colortable.h"
#include "dochead/fonttable.h"
#include "tools/stringtools.h"

using namespace std;

//Class for fonts in rtf documents.
class CppRtf_Font
{
public:
    CppRtf_Font(int size = 10, string fontFamily = "", string color = "", string backgroundColor = "");

    // sets rtf color table
    void setColorTable(CppRtf_DocHead_ColorTable* colorTable);

    // sets rtf font table
    void setFontTable(CppRtf_DocHead_FontTable* fontTable);

    //gets font family
    string getFontFamily();

    //gets font size
    int getSize();

    //gets font color
    string getColor();

    //gets background color
    string getBackgroungColor();

    //sets text bold
    void setBold(bool bold=true);

    //returns true, if text is styled bold
    bool isBold();


    //sets text italic
    void setItalic(bool italic=true);

    //returns true, if text is styled italic
    bool isItalic();

    //sets text underline
    void setUnderline(bool underlined);

    //returns true, if text is styled underline
    bool isUnderlined();

    //sets striked text
    void setStriked(bool striked = true);

    //returns true, if text is striked
    bool isStriked();

    //sets double striked text
    void setDoubleStriked(bool striked = true);

    //returns true, if text is striked double
    bool isDoubleStriked();

    /*
         * sets animation for text
         *
         * @param integer $animation animation<br>
         *   Represented by class constants ANIMATE_*<br>
         *   Possible values:<br>
         *     ANIMATE_LAS_VEGAS_LIGHTS     => 1    - las vegas lights
         *     ANIMATE_BLINKING_BACKGROUND  => 2    - blinking brackground
         *     ANIMATE_SPARKLE_TEXT         => 3    - sparkle text
         *     ANIMATE_MARCHING_BLACK_ANTS  => 4    - marching black ants
         *     ANIMATE_MARCHING_RED_ANTS    => 5    - marching red ants
         *     ANIMATE_SHIMMER              => 6    - shimmer
         */
    void setAnimation(int animation);

    //gets rtf code of font
    string getContent();

    //closes font content
    string getClosingContent();

    //constants for types of animated text
    static const int ANIMATE_LAS_VEGAS_LIGHTS=1;
    static const int ANIMATE_BLINKING_BACKGROUND=2;
    static const int ANIMATE_SPARKLE_TEXT=3;
    static const int ANIMATE_MARCHING_BLACK_ANTS=4;
    static const int ANIMATE_MARCHING_RED_ANTS=5;
    static const int ANIMATE_SHIMMER=6;

protected:
    CppRtf_DocHead_ColorTable* m_colorTable;
    CppRtf_DocHead_FontTable* m_fontTable;
    int m_size; //font size
    string m_fontFamily; //font family
    string m_color; //font color
    string m_backgroundColor; //background color
    bool m_isBold; //true, if font is italic
    bool m_isItalic; //true, if font is bold
    bool m_isUnderlined; //true, if font is underlined
    bool m_isStriked; //true, if font is striked
    bool m_isDoubleStriked; //true, if font is double striked
    string m_animation; //text animation
};

#endif // FONT_H
