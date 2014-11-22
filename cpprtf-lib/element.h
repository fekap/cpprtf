#ifndef ELEMENT_H
#define ELEMENT_H
#include "font.h"
#include "parformat.h"
#include "cpprtf.h"

using namespace std;

//class for creating elements used in containers like sections, footers and headers.
class CppRtf_Element
{
public:
    CppRtf_Element(CppRtf* rtf,
                   string text,
                   CppRtf_Font* font = 0,
                   CppRtf_ParFormat* parFormat = 0);

    CppRtf_Element(CppRtf_Element &element);

    ~CppRtf_Element();

    //checks, if element is an empty paragraph
    bool isEmptyParagraph();

    //sets flag, that text tags shall be converted into rtf code
    void setConvertTagsToRtf();

    //sets rtf code
    void setIsRtfCode();

    //returns true, if text is rtf code
    bool isRtfCode();

    //gets font
    CppRtf_Font* getFont();

    //gets par format
    CppRtf_ParFormat* getParFormat();

    //converts text tags into rtf code - fail
    static string convertTagsToRtf(string text, string charset);

    // renders the element
    void render();

protected:
    CppRtf* m_rtf;
    string m_text;
    bool m_isRtfCode;
    bool m_convertTagsToRtf;
    CppRtf_Font* m_font;
    CppRtf_ParFormat* m_parFormat;

    //get opening token
    string getOpeningToken();

    //get closing token
    string getClosingToken();
};

#endif // ELEMENT_H
