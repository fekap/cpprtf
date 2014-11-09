#ifndef TEXT_H
#define TEXT_H
#include "formfield.h"

//class for text form fields in rtf documents.
class CppRtf_FormField_Text : public CppRtf_FormField
{
public:
    CppRtf_FormField_Text(CppRtf* rtf, CppRtf_Font *font = 0, CppRtf_ParFormat *parFormat = 0);

    //gets rtf code for form field text
    string getRtfCode();

protected:
    //gets form field type
    string getType();
};

#endif // TEXT_H
