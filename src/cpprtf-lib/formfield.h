#ifndef FORMFIELD_H
#define FORMFIELD_H
#include "font.h"
#include "parformat.h"

//class CppRtf;
//abstract class for form fields in rtf documents.
class CppRtf_FormField
{
public:
    CppRtf_FormField(CppRtf* rtf, CppRtf_Font *font = 0, CppRtf_ParFormat *parFormat = 0);

    //sets default value
    void setDefaultValue(string value);

    CppRtf_Font* getFont();

    CppRtf_ParFormat* getParFormat();

    //renders form field
    void render();

protected:
    CppRtf* m_rtf;
    CppRtf_Font* m_font;
    CppRtf_ParFormat* m_parFormat;
    string m_defaultValue;

    //abstract method to get the form field's specific rtf code
    virtual string getRtfCode(){return "TODO";}//TODO

    //abstract method to get the form field's type
    virtual string getType(){return "TODO";}//TODO
};

#endif // FORMFIELD_H
