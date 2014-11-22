#include <CppRtf>
#include "container/section.h"
#include "parformat.h"

int main()
{
    CppRtf rtf;
    CppRtf_Container_Section *sect = rtf.addSection();
    CppRtf_Font font(12);
    CppRtf_ParFormat parFormat(CppRtf_ParFormat::TEXT_ALIGN_CENTER);
    sect->writeText("<i>Hello <b>world</b></i>.",&font,&parFormat);
    rtf.save("hello_world.rtf");

    return 0;
}
