#ifndef DROPDOWN_H
#define DROPDOWN_H
#include "formfield.h"

//class for dropdown form fields in rtf documents.
class CppRtf_FormField_Dropdown : public CppRtf_FormField
{
public:
    CppRtf_FormField_Dropdown(CppRtf* rtf, CppRtf_Font *font = 0, CppRtf_ParFormat *parFormat = 0);

    //adds dropdown item
    void addItem(string text);

    //sets dropdown items
    void setItems(vector<string> items);

    //gets rtf code for dropdown form field
    string getRtfCode();

protected:
    vector<string> m_items; //dropdown items

    //gets form field type
    string getType();
};

#endif // DROPDOWN_H
