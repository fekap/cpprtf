#ifndef SECTION_H
#define SECTION_H
#include "container/footer.h"
#include "container.h"
//#include "cpprtf.h"

//class CppRtf_Container;
class CppRtf;
//Class for creating sections within the rtf document.
class CppRtf_Container_Section : public CppRtf_Container
{
public:
    CppRtf_Container_Section(CppRtf* rtf);

    //sets landscape orientation for the section
    void setLandscape();

    //returns true, if landscape layout should be used
    bool isLandscape();

    //sets the paper width of pages in section.
    void setPaperWidth(float width);

    //gets the paper width of pages in section.
    float getPaperWidth();

    //sets the paper height of pages in section.
    void setPaperHeight(float height);

    //gets the paper height of pages in section.
    float setPaperHeight();

    //setters&getters for margins of pages in section.
    void setMarginLeft(float margin);
    void setMarginRight(float margin);
    void setMarginTop(float margin);
    void setMarginBottom(float margin);
    void setMargins(float marginLeft,float marginTop,float marginRight,float marginBottom);
    bool getMarginLeft();
    bool getMarginRight();
    bool getMarginTop();
    bool getMarginBottom();

    //sets&gets the gutter width. <br>  NOTICE: Does note work with OpenOffice.
    void setGutter(float gutter);
    float getGutter();

    //sets the margin definitions on left and right pages.<br> Notice: Does not work with OpenOffice.
    void setMirrorMargins();

    //returns true, if use mirror margins should be used
    bool isMirrorMargins();

    //gets width of page layout. Exception: if paper layout width is lower or equal 0
    float getLayoutWidth();

    //sets&gets border to rtf document
    void setBorder(CppRtf_Border* border);
    CppRtf_Border* getBorder();

    //sets borders to rtf document.
    void setBorders(CppRtf_Border_Format* borderFormat,bool left = true, bool top = true,bool right = true, bool bottom = true);

    //sets&gets number of columns in section.
    void setNumberOfColumns(int columnsCount);
    int getNumberOfColumns();

    //sets&gets space (width) between columns
    void setSpaceBetweenColumns(float spaceBetweenColumns);
    float getSpaceBetweenColumns();

    /* sets section columns with different widths.<br>
     * NOTE: If you use this function, you shouldn't use {setNumberOfColumns} */
    void setColumnWidths(vector<float> columnWidths);

    //gets widths for columns
    vector<float> getColumnWidths();

    /* sets that it should not do a break within the section
     * NOTE: If foot notes are used in different sections, MS Word will always break sections.*/
    void setNoBreak(bool doNotBreak = true);

    //sets line between columns.
    void setLineBetweenColumns(bool flag = true);

    //returns true, if line between columns is sets
    bool hasLineBetweenColumns();


    /* creates header for sections.
     * type Represented by class constants PHPRtfLite_Container_Header::TYPE_*  Possible values: <br>
     *   CppRtf_Container_Header::TYPE_ALL      - all pages (different odd and even headers/footers must be not set) <br>
     *   CppRtf_Container_Header::TYPE_LEFT     - left pages (different odd and even headers/footers must be set) <br>
     *   CppRtf_Container_Header::TYPE_RIGHT    - right pages (different odd and even headers/footers must be set) <br>
     *   CppRtf_Container_Header::TYPE_FIRST    - first page */
    CppRtf_Container_Header* addHeader(CppRtf_Container_Header::HeaderType type = CppRtf_Container_Header::TYPE_ALL);

    //gets defined headers for document pages.
    vector<CppRtf_Container_Header*> getHeaders();

    //creates footer for the document.
    CppRtf_Container_Footer* addFooter(CppRtf_Container_Header::HeaderType type = CppRtf_Container_Header::TYPE_ALL);

    //gets defined footers for document pages.
     vector<CppRtf_Container_Footer*> getFooters();

     //insert a page break
     void insertPageBreak();

     void setFont(CppRtf_Font* font);
     CppRtf_Font* getFont();

     //sets border surrounds header/footer
     CppRtf_Container_Section* setBorderSurroundsHeader(bool borderSurroundsHeader = true);
     CppRtf_Container_Section* setBorderSurroundsFooter(bool borderSurroundsFooter = true);


     //checks, if border surrounds header/footer
     bool borderSurroundsHeader();
     bool borderSurroundsFooter();

     //renders rtf code of section
     void render();

protected:
    CppRtf_Border* m_border; //border for section
    int m_numberOfColumns; //number of columns within the section
    vector<float> m_columnWidths; //array of column widths. only used when using more than one column within the section
    bool m_doNotBreak; //flag for not breaking within the section, if true do not break
    bool m_lineBetweenColumns; //flag, if true using lines between the section columns
    float m_spaceBetweenColumns; //defines space between the section columns
    bool m_isLandscape; //flag, if true use landscape layout for this section, isLandscape of rtf must be set to portrait
    float m_paperWidth; //paper width
    float m_paperHeight; //paper height
    float m_marginLeft; //left margin
    float m_marginRight; //right margin
    float m_marginTop; //top margin
    float m_marginBottom; //bottom margin
    float m_gutter; //gutter
    bool m_useMirrorMargins; //flag, if true margins will be the opposite for odd and even pages
    vector<CppRtf_Container_Header*> m_headers; //rtf headers
    vector<CppRtf_Container_Footer*> m_footers; //rtf footers
    CppRtf_Font* m_font;
    bool m_borderSurroundsHeader;
    bool m_borderSurroundsFooter;
};

#endif // SECTION_H  /**

