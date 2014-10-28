#ifndef COLORTABLE_H
#define COLORTABLE_H
#include <vector>
#include "tools/stringtools.h"

using namespace phpstring;

//defines color table for the rtf document head
class CppRtf_DocHead_ColorTable
{
public:
    CppRtf_DocHead_ColorTable();

    //adds color to rtf document
    void add(string color);

    // gets rtf code of color or return -1
    int getColorIndex(string color);

    //gets rtf color table
    string getContent();

protected:
    //defined colors for this color table
    vector<string> m_colors;

private:
    //gets color in hex code
    static string getColorAsFullHexCode(string color);

    //formats color code.
    static string convertHexColorToRtf(string color);
};

#endif // COLORTABLE_H
