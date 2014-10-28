#ifndef ENDNOTE_H
#define ENDNOTE_H
#include "footnote.h"

//class for creating endnotes in rtf documents.
class CppRtf_Endnote:CppRtf_Footnote
{
public:
    CppRtf_Endnote(CppRtf *rtf, string text, CppRtf_Font *font = 0, CppRtf_ParFormat *parFormat = 0);
protected:
    //gets type as rtf code
    string getTypeAsRtfCode();
};

#endif // ENDNOTE_H
