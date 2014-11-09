#ifndef FOOTNOTE_H
#define FOOTNOTE_H
#include <string>
#include "cpprtf.h"
#include "font.h"
#include "parformat.h"

class CppRtf;
class CppRtf_Font;
class CppRtf_ParFormat;

using namespace std;

// class for creating footnotes in rtf documents.
class CppRtf_Footnote
{
public:
    CppRtf_Footnote(
            CppRtf *rtf,
            string text,
            CppRtf_Font *font = 0,
            CppRtf_ParFormat *parFormat = 0);

    /*
     * constants for numbering type
     *  0 => Arabic numbering (1, 2, 3, ...)
     *  1 => Alphabetic lowercase (a, b, c, ...)
     *  2 => Alphabetic uppercase (A, B, C, ...)
     *  3 => Roman lowercase (i, ii, iii, ...)
     *  4 => Roman uppercase (I, II, III, ...)
     *  5 => Chicago Manual of Style (*, [dagger], [daggerdbl], §)
     *  6 => Footnote Korean numbering 1 (*chosung).
     *  7 => Footnote Korean numbering 2 (*ganada).
     *  8 => Footnote Circle numbering (*circlenum).
     *  9 => Footnote kanji numbering without the digit character (*dbnum1).
     *  10 => Footnote kanji numbering with the digit character (*dbnum2).
     *  11 => Footnote kanji numbering 3 (*dbnum3).
     *  12 => Footnote kanji numbering 4 (*dbnum4).
     *  13 => Footnote double-byte numbering (*dbchar).
     *  14 => Footnote Chinese numbering 1 (*gb1).
     *  15 => Footnote Chinese numbering 2 (*gb2).
     *  16 => Footnote Chinese numbering 3 (*gb3).
     *  17 => Footnote Chinese numbering 4 (*gb4).
     *  18 => Footnote numbering—Chinese Zodiac numbering 1 (* zodiac1).
     *  19 => Footnote numbering—Chinese Zodiac numbering 2 (* zodiac2).
     *  20 => Footnote numbering—Chinese Zodiac numbering 3 (* zodiac3).
     */
     static const int NUMTYPE_ARABIC_NUMBERS=0;
     static const int NUMTYPE_ALPHABETH_LC=1;
     static const int NUMTYPE_ALPHABETH_UC=2;
     static const int NUMTYPE_ROMAN_LC=3;
     static const int NUMTYPE_ROMAN_UC=4;
     static const int NUMTYPE_CHICAGO=5;
     static const int NUMTYPE_KOREAN_1=6;
     static const int NUMTYPE_KOREAN_2=7;
     static const int NUMTYPE_CIRCLE=8;
     static const int NUMTYPE_KANJI_1=9;
     static const int NUMTYPE_KANJI_2=10;
     static const int NUMTYPE_KANJI_3=11;
     static const int NUMTYPE_KANJI_4=12;
     static const int NUMTYPE_DOUBLE_BYTE=13;
     static const int NUMTYPE_CHINESE_1=14;
     static const int NUMTYPE_CHINESE_2=15;
     static const int NUMTYPE_CHINESE_3=16;
     static const int NUMTYPE_CHINESE_4=17;
     static const int NUMTYPE_CHINESE_ZODIAC_1=18;
     static const int NUMTYPE_CHINESE_ZODIAC_2=19;
     static const int NUMTYPE_CHINESE_ZODIAC_3=20;

     static const string TYPE_SUPER;
     static const string TYPE_SUB;
     static const string TYPE_NORMAL;

     //sets default font for notes
     static void setDefaultFont(CppRtf_Font* defaultFont);

     //gets default font
     static CppRtf_Font* getDefaultFont();

     //sets font
     void setFont(CppRtf_Font* font);

     //gets font
     CppRtf_Font* getFont();

     //sets paragraph format
     void setParFormat(CppRtf_ParFormat* parFormat);

     //gets paragraph format
     CppRtf_ParFormat* getParFormat();

     void setTypeSettingType(string type);

     //gets type as rtf code
     virtual string getTypeAsRtfCode();

     //renders footnote/endnote
     virtual void render();

protected:

     //footnote/endnote text
     string m_text;

     //font
     CppRtf_Font *m_font;

     //paragraph format
     CppRtf_ParFormat *m_parFormat;

     //rtf document
     CppRtf *m_rtf;

     //type setting type (superscript/subscript/normal)
     string m_typeSettingType;

     //default font
     static CppRtf_Font *defaultFont;
};

#endif // FOOTNOTE_H
