#ifndef FOOTER_H
#define FOOTER_H
#include "container/header.h"

class CppRtf_Container_Footer : public CppRtf_Container_Header
{
public:
    CppRtf_Container_Footer(CppRtf *rtf,CppRtf_Container_Header::HeaderType type);
};

#endif // FOOTER_H
