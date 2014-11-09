#ifndef IMAGE_H
#define IMAGE_H
#include "parformat.h"

class CppRtf;
//Class for displaying images in rtf documents.
class CppRtf_Image
{
public:
    //class constants for image type
    enum ImageType{
        TYPE_JPEG ,
        TYPE_PNG,
        TYPE_WMF
    };

    CppRtf_Image();

    //sets paragraph format for image
    void setParFormat(CppRtf_ParFormat *parFormat){(void)parFormat; }
    CppRtf_ParFormat* getParFormat(){return (CppRtf_ParFormat*)0;}

    static CppRtf_Image* createFromFile(CppRtf* rtf, string file, float width = -1, float height = -1){
        (void)rtf;(void)file;(void)width;(void)height;
        return (CppRtf_Image*)0;
    }
    static CppRtf_Image* createFromString(CppRtf* rtf, string imageString, string type, float width = -1, float height = -1){
        (void)rtf;(void)imageString;(void)width;(void)height;(void)type;
        return (CppRtf_Image*)0;
    }
    void render(){}


protected:
    CppRtf* m_rtf; //rtf document
};

#endif // IMAGE_H
