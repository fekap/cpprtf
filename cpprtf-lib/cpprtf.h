#ifndef CPPRTF_H
#define CPPRTF_H
#include "dochead/colortable.h"
#include "dochead/note.h"
#include "utf8.h"
#include "container/footer.h"
#include "paper/paper_format.h"
//#include "global.h"
#include "streamoutput.h"

using namespace std;

class CppRtf_Font;
class CppRtf_ParFormat;
class CppRtf_Container_Section;
class CppRtf_Writer_Interface;

class CppRtf
{
public:
    //defining view modes
    enum VIEW_MODE{
        VIEW_MODE_NONE, // 0 - None
        VIEW_MODE_PAGE_LAYOUT, // 1 - Page Layout
        VIEW_MODE_OUTLINE, // 2 - Outline view
        VIEW_MODE_MASTER, // 3 - Master Document view
        VIEW_MODE_NORMAL, // 4 - Normal view
        VIEW_MODE_NLINE_LAYOUT // 5 - Online Layout view
    };
    //defining zoom modes
    enum ZOOM_MODE{
        ZOOM_MODE_NONE, // 0 - None
        ZOOM_MODE_FULL_PAGE, // 1 - Full Page
        ZOOM_MODE_BEST_FIT // 2 - Best Fit
    };

    static const string VERSION ;
    static const int SPACE_IN_POINTS;  // used for twips conversion
    static const int SPACE_IN_LINES;  // used for twips conversion

    CppRtf();

    /* set that a temporary file should be used for creating the output
         * NOTE: is slowing down the rendering because of the io operations, but uses less memory*/
    void setUseTemporaryFile(bool flag = true);

    //sets charset for rtf text inputs
    void setCharset(string charset);

    //gets charset for rtf text inputs
    string getCharset();

    /* sets document information properties
         *
         * @param string $name Property of document. Possible properties: <br>
         *   'title' => title of the document (value string)<br>
         *   'subject' => subject of the document (value string)<br>
         *   'author' => author of the document (value string)<br>
         *   'manager' => manager of the document (value string)<br>
         *   'company' => company of author (value string)<br>
         *   'operator' => operator of document. Operator is a person who last made changes to the document. (value string) <br>
         *   'category' => category of document (value string)<br>
         *   'keywords' => keywords of document (value string)<br>
         *   'doccomm' => comments of document (value string)<br>
         *   'creatim' => creation time (value int) <br>
         *   'revtim' => last revision time (value int) <br>
         *   'buptim' => last backup time (value int) <br>
         *   'printim' => last print time (value int) <br>
         * @param mixed $value Value*/
    template<class type>
    void setProperty(string name, type value){(void)name;(void)value;} //TODO

    //gets rtf property
    string getProperty(string name){(void)name;return "";} //TODO

    //gets document head definition for notes
    CppRtf_DocHead_Note* getNoteDocHead();

    //sets footnote numbering type
    void setFootnoteNumberingType(int numberingType);

    //gets footnote numbering type
    int getFootnoteNumberingType();

    //sets endnote numbering type
    void setEndnoteNumberingType(int numberingType);

    //gets endnote numbering type
    int getEndnoteNumberingType();

    //sets footnote start number
    void setFootnoteStartNumber(int startNumber);

    //gets footnote start number
    int getFootnoteStartNumber();

    //sets endnote start number
    void setEndnoteStartNumber(int startNumber);

    //gets endnote start number
    int getEndnoteStartNumber();

    //sets restart footnote number on each page
    void setRestartFootnoteNumberEachPage();

    //checks, if footnote numbering shall be started on each page
    bool isRestartFootnoteNumberEachPage();

    //sets restart endnoote number on each page
    void setRestartEndnoteNumberEachPage();

    //checks, if endnoote numbering shall be started on each page
    bool isRestartEndnoteNumberEachPage();

    //sets default font for notes
    void setDefaultFontForNotes(CppRtf_Font* font);

    //gsets default font for notes
    CppRtf_Font* getDefaultFontForNotes();

    //adds section to rtf document
    CppRtf_Container_Section* addSection(CppRtf_Container_Section *section=0);

    //gets sections
    vector<CppRtf_Container_Section*>  getSections();

    //sets default tab width of the document
    void setDefaultTabWidth(float defaultTabWidth);

    //sets default tab width of the document
    float getDefaultTabWidth();

    //sets the paper format.
    void setPaperFormat(CppRtf_Paper_Format::Format format);

    //sets the paper width of document
    void setPaperWidth(float width);

    //gets the paper width of document
    float getPaperWidth();

    //sets the paper height of document
    void setPaperHeight(float height);

    //gets the paper height of document
    float getPaperHeight();

    //setters&getters for margins of document pages.
    void setMarginLeft(float margin);
    void setMarginRight(float margin);
    void setMarginTop(float margin);
    void setMarginBottom(float margin);
    void setMargins(float marginLeft,float marginTop,float marginRight,float marginBottom);
    float getMarginLeft();
    float getMarginRight();
    float getMarginTop();
    float getMarginBottom();

    //sets the margin definitions on left and right pages. <br> NOTICE: Does not work with OpenOffice.
    void setMirrorMargins();

    //returns true, if use mirror margins should be used
    bool isMirrorMargins();

    // sets the gutter width. <br> NOTICE: Does not work with OpenOffice.
    void setGutter(float gutter);

    //gets the gutter width
    float getGutter();

    //sets the beginning page number (if not defined, Word uses 1)
    void setPageNumberStart(int pageNumber);

    //gets the beginning page number
    int getPageNumberStart();

    // sets&gets the view mode of the document
    void setViewMode(VIEW_MODE viewMode);
    VIEW_MODE getViewMode();

    //sets the zoom level (in percents) of the document. By default word uses 100%.  NOTICE: if zoom mode is defined, zoom level is not used.
    void setZoomLevel(int zoom);

    //gets the zoom level (in percents) of the document
    int getZoomLevel();

    //sets the zoom mode of the document
    void setZoomMode(ZOOM_MODE zoomMode);

    //gets the zoom mode of the document
    ZOOM_MODE getZoomMode();

    //sets landscape orientation for the document
    void setLandscape();

    //returns true, if landscape layout should be used
    bool isLandscape();

    //sets using hyphenation
    void setHyphenation();

    //Sets border to rtf document. Sections may override this border.
    void setBorder(CppRtf_Border* border);

    //gets border of document
    CppRtf_Border* getBorder();

    //sets border surrounds header/footer
    CppRtf *setBorderSurroundsHeader(bool borderSurroundsHeader = true);
    CppRtf *setBorderSurroundsFooter(bool borderSurroundsFooter = true);

    //checks, if border surrounds header/footer
    bool borderSurroundsHeader();
    bool borderSurroundsFooter();

    //Sets borders to rtf document. Sections may override this border.
    void setBorders(CppRtf_Border_Format* borderFormat,bool left = true, bool top = true, bool right = true, bool bottom = true);

    //sets&gets if odd and even headers/footers are different
    void setOddEvenDifferent(bool different = true);
    bool isOddEvenDifferent();

    /* creates header/footer for the document
    * type: Possible values: <br>
    *   CppRtf_Container_Header::TYPE_ALL - all pages (different odd and even headers/footers must be not set) <br>
    *   CppRtf_Container_Header::TYPE_LEFT - left pages (different odd and even headers/footers must be set) <br>
    *   CppRtf_Container_Header::TYPE_RIGHT - right pages (different odd and even headers/footers must be set <br>
    *   CppRtf_Container_Header::TYPE_FIRST -    first page
    * @param   PHPRtfLite_Container_Header $header
    *
    * @return  PHPRtfLite_Container_Header
    */
   CppRtf_Container_Header* addHeader(CppRtf_Container_Header::HeaderType type = CppRtf_Container_Header::TYPE_ALL, CppRtf_Container_Header* header = 0);
   CppRtf_Container_Footer* addFooter(CppRtf_Container_Header::HeaderType type = CppRtf_Container_Footer::TYPE_ALL, CppRtf_Container_Footer* footer = 0);

   //gets defined headers/footers for document pages
   vector<CppRtf_Container_Header*> getHeaders();
   vector<CppRtf_Container_Footer*> getFooters();

   //gets color table
   CppRtf_DocHead_ColorTable* getColorTable();

   //gets font table
   CppRtf_DocHead_FontTable* getFontTable();

   //registers the font in color table and font table
   void registerFont(CppRtf_Font* font);

   //sets&gets default font
   void  setDefaultFont(CppRtf_Font* font);
   CppRtf_Font* getDefaultFont();

   //registers the par format in color table
   void registerParFormat(CppRtf_ParFormat* parFormat);

   //gets rtf document code
   string getContent();

   //saves rtf document to file
   void save(string file);

   //sends rtf content as file attachment
   void sendRtf(string filename = "simple");

   //sets that first page has a special layout
   void setSpecialLayoutForFirstPage(bool specialLayout = true);

   //returns true, if first page has special layout
   bool hasSpecialLayoutForFirstPage();

   //quotes rtf code
   static string quoteRtfCode(string text, bool convertNewlines = true);

   //convert new lines to rtf line breaks
   static string convertNewlinesToRtfCode(string text);

   //sets&gets writer
   void setWriter(CppRtf_StreamOutput *writer);
   CppRtf_StreamOutput *getWriter();

private:
    string m_charset; //charset of text inputs for rtf document, default is UTF-8
    float m_paperWidth; //paper width
    float m_paperHeight; //paper height
    float m_marginLeft; //left margin
    float m_marginRight; //right height
    float m_marginTop; //top margin
    float m_marginBottom; //bottom margin
    bool m_useOddEvenDifferent; //flag, if true, even and odd pages are using different layouts
    float m_defaultTabWidth; //default tab width
    VIEW_MODE m_viewMode; //view mode
    int m_zoomLevel; //zoom level
    ZOOM_MODE m_zoomMode; //zoom mode
    float m_gutter;// gutter
    bool m_useMirrorMargins; //flag, if true margins will be the opposite for odd and even pages
    int m_pageNumberStart;//start with page number
    bool m_titlepg; //flag, if true first page has special layout
    CppRtf_Border* m_border; //rtf border
    bool m_isLandscape; //flag, if true use landscape layout
    bool m_isHyphenation; //using hyphenation
    CppRtf_DocHead_Note* m_noteDocHead;//document head definition for notes
    CppRtf_StreamOutput* m_writer; //output stream
    bool m_useTemporaryFile; //flag, if true CppRtf writes the output into a temporary file, which is slowing down a bit because of the io operations but uses less memory

    //creates writer
    void createWriter(string file = "");

protected:
    vector<CppRtf_Container_Section*> m_sections; //rtf sections
    vector<CppRtf_Container_Header*> m_headers; //rtf headers
    vector<CppRtf_Container_Footer*> m_footers; //rtf footers
    CppRtf_DocHead_FontTable* m_fontTable;
    CppRtf_DocHead_ColorTable* m_colorTable;
    CppRtf_Font* m_defaultFont; //default font
//    protected $_properties      = array();//rtf properties //TODO
    bool m_borderSurroundsHeader;
    bool m_borderSurroundsFooter;

    //gets rtf info part
    string getInfoPart();

    //prepares rtf contents
    void render();

};

#endif // CPPRTF_H

