#include "paper_format.h"


int CppRtf_Paper_Format::getPaperWidthByPaperFormat(Format format)
{
    FormatSize size = paperFormats(format);
    return size.width;
}

int CppRtf_Paper_Format::getPaperHeightByPaperFormat(Format format)
{
    FormatSize size = paperFormats(format);
    return size.height;
}

CppRtf_Paper_Format::FormatSize CppRtf_Paper_Format::paperFormats(Format format)
{
    FormatSize size;
    switch (format) {
    case FORMAT_A3:
        size.width = 297;
        size.height = 420;
        return size;
    case FORMAT_A4:
        size.width = 210;
        size.height = 297;
        return size;
    case FORMAT_A5:
        size.width = 148;
        size.height = 210;
        return size;
    case FORMAT_LETTER:
        size.width = 216;
        size.height = 279;
        return size;
    case FORMAT_LEGAL:
        size.width = 216;
        size.height = 356;
        return size;
    default:
        throw "Paper format is not supported.";
    }
}
