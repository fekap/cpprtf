#include "footer.h"

CppRtf_Container_Footer::CppRtf_Container_Footer(CppRtf *rtf, CppRtf_Container_Header::HeaderType type):CppRtf_Container_Header(rtf,type)
{
    m_rtfType = "footer";
}
