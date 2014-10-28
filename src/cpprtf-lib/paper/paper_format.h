#ifndef PAPER_FORMAT_H
#define PAPER_FORMAT_H

//Class for paper format.
class CppRtf_Paper_Format
{
public:
    enum Format{
        //Constants for international paper formats: A
        FORMAT_A3,
        FORMAT_A4,
        FORMAT_A5,
        //Constants for north american paper formats.
        FORMAT_LETTER,
        FORMAT_LEGAL
    };
    struct FormatSize{
        int width;
        int height;
    };

    static int getPaperWidthByPaperFormat(Format format);

    static int getPaperHeightByPaperFormat(Format format);
private:
    //Mapping array from paper format to width and height of a paper. The values for width and height are in millimeter.
    FormatSize static paperFormats(Format format);
};

#endif // PAPER_FORMAT_H
