#ifndef BASE_H
#define BASE_H
#include <typeinfo>
#include "tools/stringtools.h"
#include "image.h"
#include "parformat.h"
#include "font.h"
#include "tools/addon.h"
#include "baseelement.h"

class CppRtf_Element;
class CppRtf;
class CppRtf_Table;
using namespace std;

//Base class for rtf containers.
class CppRtf_Container_Base
{

public:

    CppRtf_Container_Base(CppRtf* rtf);

    //gets rtf object
    CppRtf* getRtf();

    //counts container elements
    int countElements();

    //gets container elements
    vector<BaseElement *> getElements();

    //adds element with rtf code directly (no converting will be made by CppRtf)
    CppRtf_Element* writeRtfCode(string code, CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0);

    /////only headers

    //adds element with plain rtf code directly  (no converting will be made by PHPRtfLite - even no opening and closing curly brackets)
    CppRtf_Element* writePlainRtfCode(string code);

    //adds empty paragraph to container.
    CppRtf_Element* addEmptyParagraph(CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0);

    /* rites text to container.
         * text: Text. Also you can use html style tags. Possible tags:<br>
         *   strong, b- bold; <br>
         *   em - ; <br>
         *   i - italic; <br>
         *   u - underline; <br>
         *   br - line break; <br>
         *   chdate - current date; <br>
         *   chdpl - current date in long format; <br>
         *   chdpa - current date in abbreviated format; <br>
         *   chtime - current time; <br>
         *   chpgn, pagenum - page number ; <br>
         *   tab - tab
         *   sectnum - section number; <br>
         *   line - line break; <br>
         *   page - page break; <br>
         *   sect - section break; <br>
         * font:               font of text
         * parFormat:          paragraph format, if null, text is written in the same paragraph.
         * convertTagsToRtf:   if false, then html style tags are not replaced with rtf code */
    CppRtf_Element* writeText(string text, CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0, bool convertTagsToRtf = true);

    /* writes hyperlink to container.
         * hyperlink          hyperlink url (etc. "http://www.phprtf.com")
         * text               hyperlink text, if empty, hyperlink is written in previous paragraph format.
         * convertTagsToRtf   if false, then html style tags are not replaced with rtf code */
    CppRtf_Element* writeHyperLink(string hyperlink,string text, CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0, bool convertTagsToRtf = true);

    // adds table to element container. alignment: Alingment of table. Represented by class constants CppRtf_Table::ALIGN_*<br>
    CppRtf_Table* addTable(int alignment = 0);

    /* adds image to element container.
         *
         * fileName   name of image file.
         * parFormat  paragraph format, ff null image will appear in the same paragraph.
         * width      if null image is displayed by it's height.
         * height     if null image is displayed by it's width.
         *   If boths parameters are null, image is displayed as it is.
         *
         * imageString   image source code
         * type class constants of PHPRtfLite_Image: TYPE_JPEG, TYPE_PNG, TYPE_WMF */
    CppRtf_Image* addImage(string fileName, CppRtf_ParFormat* parFormat = 0, float width = -1, float height = -1);
    CppRtf_Image* addImageFromString(string imageString, string type, CppRtf_ParFormat* parFormat = 0, float width = -1, float height = -1);

    //renders rtf code for that container
    void render();

    template<class type>
    bool instanceOf(){
        if(typeid(type).name()==__name)
            return true;
        return false;
    }


protected:

    //adds element
    template<class type>
    void addElement(type newClass){
        BaseElement *e=new BaseElement();
        e->set(newClass);
        m_elements.push_back(e);
    }

    CppRtf* m_rtf;
    vector<BaseElement*> m_elements; //pointers array
    string m_pard;

    const char* __name;// for instanceOf
private:

    //checks, if a \par has to be added
    bool needToAddParagraphEnd(int key);

    //gets font if container is a cell
    CppRtf_Font* getCellFont(BaseElement *elem);
    CppRtf_Font* getCellFont(CppRtf_Container_Base* elem);
};

#endif // BASE_H
