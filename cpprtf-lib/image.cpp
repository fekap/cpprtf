#include "image.h"
#include "cpprtf.h"
#include"unit.h"

CppRtf_Image::CppRtf_Image(CppRtf *rtf, FILE *stream, float width, float height)
{
    m_rtf    = rtf;
    m_stream = stream;
    m_width  = width;
    m_height = height;

    m_isMissing = false;
    m_border = 0;
    m_parFormat = 0;
}

CppRtf_Image::~CppRtf_Image()
{
    //TODO
    if(m_border != 0){
        delete m_border;
        m_border = 0;
    }
}

void CppRtf_Image::setParFormat(CppRtf_ParFormat *parFormat)
{
    m_parFormat = parFormat;
    m_parFormat->setColorTable(m_rtf->getColorTable());
}

CppRtf_ParFormat *CppRtf_Image::getParFormat()
{
    return m_parFormat;
}

void CppRtf_Image::setWidth(float width)
{
    m_width = width;
}

float CppRtf_Image::getWidth()
{
    return m_width;
}

void CppRtf_Image::setHeight(float height)
{
    m_height=height;
}

float CppRtf_Image::getHeight()
{
    return m_height;
}

void CppRtf_Image::setBorder(CppRtf_Border *border){
    m_border = new CppRtf_Border(*border);
}

CppRtf_Border* CppRtf_Image::getBorder()
{
    return m_border;
}

bool CppRtf_Image::isMissing()
{
    return m_isMissing;
}

void CppRtf_Image::setIsMissing()
{
    m_isMissing = true;
}

CppRtf_Image *CppRtf_Image::createFromString(CppRtf *rtf, string imageString, CppRtf_Image::ImageType type, float width, float height)
{
//    FILE* stream = fopen("data://text/plain;base64," . base64_encode(string), "rb");
//    CppRtf_Image image = create(rtf, stream, type, width, height);
//    if (type != TYPE_WMF) {
//        imageResource = imagecreatefromstring(string);
//        image->setImageWidth(imagesx(imageResource));
//        image->setImageHeight(imagesy(imageResource));
//    }
//    return image;
}

void CppRtf_Image::render()
{
    writeIntoRtfStream();
}

CppRtf_Image* CppRtf_Image::createFromFile(CppRtf *rtf, string file, float width, float height)
{
//    if (file_exists(file) && is_readable(file)) {
//        stream = fopen(file, "rb");
//        pathInfo = pathinfo(file);
//        type = isset(pathInfo["extension"]) ? strtolower(pathInfo["extension"]) : "jpeg";
//        CppRtf_Image* image = self::create(rtf, stream, type, width, height);

//        if (type != self::TYPE_WMF) {
//            list(width, height, imageType) = getimagesize(file);
//            imageType = image_type_to_extension(imageType, false);
//            image->setImageWidth(width);
//            image->setImageHeight(height);
//            if (type != imageType) {
//                image->setImageType(imageType);
//            }
//        }
//        return image;
//    }

//    return createMissingImage(rtf, width, height);
}

void CppRtf_Image::setImageWidth(float width)
{
    m_imageWidth = width;
}

void CppRtf_Image::setImageHeight(float height)
{
    m_imageHeight = height;
}

void CppRtf_Image::writeIntoRtfStream(int startFrom)
{
//    fseek(m_stream, startFrom,SEEK_SET);
//    string rtfImageType = this->getImageTypeAsRtf();

//    CppRtf_StreamOutput* rtfStream = m_rtf->getWriter();
//    rtfStream->write("{\\*\\shppict {\\pict");

//    if (m_border) {
//        rtfStream->write(m_border->getContent());
//    }

//    rtfStream->write(rtfImageType + "\\picscalex100\\picscaley100");
//    rtfStream->write("\\picwgoal" + this->getImageRtfWidth());
//    rtfStream->write("\\pichgoal" + this->getImageRtfHeight());
//    rtfStream->write(" ");

//    while (!feof(m_stream)) {
//        stringBuffer = fread(m_stream, 1024);
//        stringHex = bin2hex(stringBuffer);
//        rtfStream->write(stringHex);
//    }

//    fclose(m_stream);

//    rtfStream->write("}}");
}

string CppRtf_Image::getImageTypeAsRtf()
{
    return m_imageRtfType;
}

int CppRtf_Image::getImageRtfWidth()
{
    if (m_width > 0) {
        return CppRtf_Unit::getUnitInTwips(m_width);
    }

    float imageWidth = m_imageWidth > -1 ? m_imageWidth : 100;
    if (m_height > 0) {
        float imageHeight = m_imageHeight > -1 ? m_imageHeight : 100;
        float width = (imageWidth / imageHeight) * m_height;
        return CppRtf_Unit::getUnitInTwips(width);
    }

    return CppRtf_Unit::getPointsInTwips(imageWidth);
}

int CppRtf_Image::getImageRtfHeight()
{
    if (m_height > 0) {
        return CppRtf_Unit::getUnitInTwips(m_height);
    }

    float imageHeight = m_imageHeight > -1 ? m_imageHeight : 100;
    if (m_width > 0) {
        float imageWidth = m_imageWidth > -1 ? m_imageWidth : 100;
        float height = (imageHeight /imageWidth) * m_width;
        return CppRtf_Unit::getUnitInTwips(height);
    }

    return CppRtf_Unit::getPointsInTwips(imageHeight);
}

string CppRtf_Image::getMissingImage()
{
    string str = string("iVBORw0KGgoAAAANSUhEUgAAABQAAAAUCAIAAAAC64paAAAAAXNSR0IArs4c6QAAAAlwSFlzAAALEwAA")
            + "CxMBAJqcGAAAAAd0SU1FB9gMGgoaGog16G8AAAAZdEVYdENvbW1lbnQAQ3JlYXRlZCB3aXRoIEdJTVBX"
            + "gQ4XAAAAfUlEQVQ4y62TsQ3AIAwEnRcSc2T/eVIzR7p0yAn+N4K4xD49cHBctl7FzM57hWzVsBHs4Fat"
            + "1TzNz2BsC5Im95OHfF/0F/RKZnxIBtseeUYG8IcXZAyPo+wh/ORZWGH+oK1of0h9Ch4zPhmPlBQ8tCTd"
            + "KjMYm9nyXPQ31PUAECcxtbZxAkYAAAAASUVORK5CYII=";

    return str;
}

CppRtf_Image *CppRtf_Image::create(CppRtf rtf, CppRtf_StreamOutput *stream, CppRtf_Image::ImageType type, float width, float height)
{
//    switch (type) {
//    case TYPE_WMF:
//        return new CppRtf_Image_Wmf(rtf, stream, width, height);
//    default:
//        CppRtf_Image_Gd* image = new CppRtf_Image_Gd(rtf, stream, width, height);
//        image->setImageType(type);
//        return image;
//    }
}

CppRtf_Image *CppRtf_Image::createMissingImage(CppRtf rtf, float width, float height)
{
//    stream = fopen("data://text/plain;base64," + getMissingImage(), "rb");
//    CppRtf_Image_Gd* image = new CppRtf_Image_Gd(rtf, stream, width, height);
//    image->setImageType(TYPE_PNG);
//    image->setIsMissing();
//    return image;
}
