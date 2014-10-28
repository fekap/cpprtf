#include <CppRtf>
#include "container/section.h"
#include "parformat.h"

int main()
{
    CppRtf *rtf= new CppRtf();
    CppRtf_Container_Section *sect = rtf->addSection();
    sect->writeText("<i>Hello <b>world</b></i>.",new CppRtf_Font(12),new CppRtf_ParFormat(CppRtf_ParFormat::TEXT_ALIGN_CENTER));
    rtf->save("hello_world.rtf");
    return 0;
}
