#ifndef CHECKBOX_H
#define CHECKBOX_H
#include "formfield.h"

//class for check box form fields in rtf documents.
class CppRtf_FormField_Checkbox : public CppRtf_FormField
{
public:
    CppRtf_FormField_Checkbox(CppRtf* rtf, CppRtf_Font *font = 0, CppRtf_ParFormat *parFormat = 0);

    //sets checkbox to be set
    void setChecked();

    //sets default value
    void setDefaultValue(bool value);

    //sets size of checkbox
    void setSize(int size);

    //gets checkbox rtf code
    string getRtfCode();

private:
    bool m_checked; //flag, if checkbox is checked
    int m_size; //size of checkbox

protected:
    //gets form field type
    string getType();

};

#endif // CHECKBOX_H
