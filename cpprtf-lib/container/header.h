#ifndef HEADER_H
#define HEADER_H
#include "container/base.h"

//Class for creating headers within the rtf document or section.
class CppRtf_Container_Header : public CppRtf_Container_Base
{
public:
    //constants defining header types
    enum HeaderType{
        TYPE_ALL,
        TYPE_LEFT,
        TYPE_RIGHT,
        TYPE_FIRST
    };

    CppRtf_Container_Header(CppRtf* rtf,HeaderType type);

    //Set vertical header position from the top of the page
    void setPosition(float height);

    //gets rtf type
    string getRtfType();

    //Gets type as rtf codeGets type as rtf code. Exception, if type is not allowed, because of the rtf document specific settings.
    string getTypeAsRtfCode();

    //streams rtf code for header/footer
    void render();

protected:
    HeaderType m_type;
    float m_offsetHeight;
    string m_rtfType;
};

#endif // HEADER_H
