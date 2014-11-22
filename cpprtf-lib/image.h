#ifndef IMAGE_H
#define IMAGE_H
#include "parformat.h"

class CppRtf;
class CppRtf_StreamOutput;

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

    CppRtf_Image(CppRtf* rtf, FILE *stream, float width = -1, float height = -1);

    ~CppRtf_Image();

    //sets paragraph format for image
    void setParFormat(CppRtf_ParFormat *parFormat);

    //gets paragraph format for image
    CppRtf_ParFormat* getParFormat();

    //sets image width; if not defined (-1) image is displayed by it's height.
    void setWidth(float width);

    //gets image width
    float getWidth();

    //sets image height; if not defined (-1) image is displayed by it's width.
    void setHeight(float height);

    //gets image height
    float getHeight();

    //sets border
    void setBorder(CppRtf_Border * border);

    //gets border
    CppRtf_Border *getBorder();

    bool isMissing();

    void setIsMissing();

    //creates rtf image from file
    static CppRtf_Image *createFromFile(CppRtf *rtf, string file, float width = -1, float height = -1);

    //creates rtf image from string
    static CppRtf_Image* createFromString(CppRtf *rtf, string imageString, ImageType type, float width = -1, float height = -1);

    //renders rtf image for rtf document
    void render();


protected:
    CppRtf* m_rtf; //rtf document
    FILE* m_stream; //stream as resource
    CppRtf_ParFormat* m_parFormat;//par format
    CppRtf_Border* m_border;//rtf border
    float m_width;//resize to width
    float m_height;//resize to height
    float m_imageWidth; //original image width
    float m_imageHeight; //original image height
    string m_imageRtfType; //image rtf type
    bool m_isMissing; //flag, true if image file is missing

    //sets image original width
    void setImageWidth(float width);

    //sets image original height
    void setImageHeight(float height);

    //writes image into rtf stream
    void writeIntoRtfStream(int startFrom = 0);

    //gets image rtf type
    string getImageTypeAsRtf();


private:
    //gets rtf image width
    int getImageRtfWidth();

    //gets rtf image height
    int getImageRtfHeight();

    //adds rtf image code to show that the file is missing
    static string getMissingImage();

    //factory method,creates rtf image from stream
    static CppRtf_Image* create(CppRtf rtf, CppRtf_StreamOutput* stream, ImageType type, float width, float height);

    //creates a missing image instance
    static CppRtf_Image* createMissingImage(CppRtf rtf, float width, float height);


};

#endif // IMAGE_H


