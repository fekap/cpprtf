#include "cpprtf.h"
#include "font.h"
#include "parformat.h"
#include "container/section.h"
#include "unit.h"
#include "writer/interface.h"

CppRtf::CppRtf()
{
    this->setPaperFormat(CppRtf_Paper_Format::FORMAT_A4);
    m_writer = new CppRtf_StreamOutput();//TODO переделать

    m_charset = "UTF-8";
//    m_paperWidth = 0;
//    m_paperHeight = 0;
    m_marginLeft = 3;
    m_marginRight = 3;
    m_marginTop = 1;
    m_marginBottom = 2;
    m_gutter = -1;
    m_useOddEvenDifferent = false;
    m_fontTable = 0;
    m_colorTable = 0;
    m_defaultFont = 0;
    m_borderSurroundsHeader = false;
    m_borderSurroundsFooter = false;
    m_defaultTabWidth = 2.29;
    m_useMirrorMargins = false;
    m_pageNumberStart = 1;
    m_titlepg = false;
    m_border = 0;
    m_isLandscape = false;
    m_isHyphenation = false;
    m_noteDocHead = 0;
//    m_writer = 0;
    m_useTemporaryFile = false;
    m_zoomLevel = -1;
    m_viewMode = VIEW_MODE_NONE;
    m_zoomMode = ZOOM_MODE_NONE;
}

CppRtf::~CppRtf()
{
    delete m_writer;
    if (m_noteDocHead!=0)
    {
        delete m_noteDocHead;
        m_noteDocHead = 0;
    }
    for (vector<CppRtf_Container_Section*>::iterator it = m_sections.begin(); it!=m_sections.end(); ++it)
    {
        delete *it;
        *it = 0;
    }
    if (m_colorTable != 0) {
        delete m_colorTable;
        m_colorTable = 0;
    }
    if (m_fontTable != 0) {
        delete m_fontTable;
        m_fontTable = 0;
    }
    for(vector<CppRtf_Container_Section*>::iterator it = m_sections.begin(); it != m_sections.end(); it++){
        delete *it;
        *it = 0;
    }
    for(vector<CppRtf_Container_Header*>::iterator it = m_headers.begin(); it != m_headers.end(); it++){
        delete *it;
        *it = 0;
    }
    for(vector<CppRtf_Container_Footer*>::iterator it = m_footers.begin(); it != m_footers.end(); it++){
        delete *it;
        *it = 0;
    }

    if(m_border != 0){
        delete m_border;
        m_border = 0;
    }

}

void CppRtf::setUseTemporaryFile(bool flag)
{
    m_useTemporaryFile = flag;
}

void CppRtf::setCharset(string charset)
{
    m_charset = charset;
}

string CppRtf::getCharset()
{
    return m_charset;
}

CppRtf_DocHead_Note *CppRtf::getNoteDocHead()
{
    if (m_noteDocHead == 0) {
        m_noteDocHead = new CppRtf_DocHead_Note();
    }
    return m_noteDocHead;
}

void CppRtf::setFootnoteNumberingType(int numberingType)
{
    getNoteDocHead()->setFootnoteNumberingType(numberingType);
}

int CppRtf::getFootnoteNumberingType()
{
    return getNoteDocHead()->getFootnoteNumberingType();
}

void CppRtf::setEndnoteNumberingType(int numberingType)
{
    getNoteDocHead()->setEndnoteNumberingType(numberingType);
}

int CppRtf::getEndnoteNumberingType()
{
    return getNoteDocHead()->getEndnoteNumberingType();
}

void CppRtf::setFootnoteStartNumber(int startNumber)
{
    getNoteDocHead()->setFootnoteStartNumber(startNumber);
}

int CppRtf::getFootnoteStartNumber()
{
    return getNoteDocHead()->getFootnoteStartNumber();
}

void CppRtf::setEndnoteStartNumber(int startNumber)
{
    getNoteDocHead()->setEndnoteStartNumber(startNumber);
}

int CppRtf::getEndnoteStartNumber()
{
    return getNoteDocHead()->getEndnoteStartNumber();
}

void CppRtf::setRestartFootnoteNumberEachPage()
{
    getNoteDocHead()->setRestartFootnoteNumberEachPage();
}

bool CppRtf::isRestartFootnoteNumberEachPage()
{
    return getNoteDocHead()->isRestartFootnoteNumberEachPage();
}

void CppRtf::setRestartEndnoteNumberEachPage()
{
    getNoteDocHead()->setRestartEndnoteNumberEachPage();
}

bool CppRtf::isRestartEndnoteNumberEachPage()
{
    return getNoteDocHead()->isRestartEndnoteNumberEachPage();
}

void CppRtf::setDefaultFontForNotes(CppRtf_Font *font)
{
    CppRtf_Footnote::setDefaultFont(font);
}

CppRtf_Font *CppRtf::getDefaultFontForNotes()
{
    return CppRtf_Footnote::getDefaultFont();
}

CppRtf_Container_Section *CppRtf::addSection(CppRtf_Container_Section *section)
{
    if(section==0)
        section=new CppRtf_Container_Section(this);
    m_sections.push_back(section);
    return section;
}

vector<CppRtf_Container_Section *> CppRtf::getSections()
{
    return m_sections;
}

void CppRtf::setDefaultTabWidth(float defaultTabWidth)
{
    m_defaultTabWidth = defaultTabWidth;
}

float CppRtf::getDefaultTabWidth()
{
    return m_defaultTabWidth;
}

void CppRtf::setPaperFormat(CppRtf_Paper_Format::Format format)
{
    int defaultUnit = CppRtf_Unit::getGlobalUnit();

    int paperWidth = CppRtf_Paper_Format::getPaperWidthByPaperFormat(format);
    m_paperWidth = CppRtf_Unit::convertTo(paperWidth, CppRtf_Unit::UNIT_MM, defaultUnit);

    int paperHeight = CppRtf_Paper_Format::getPaperHeightByPaperFormat(format);
    m_paperHeight = CppRtf_Unit::convertTo(paperHeight, CppRtf_Unit::UNIT_MM, defaultUnit);
}

void CppRtf::setPaperWidth(float width){
    m_paperWidth = width;
}

float CppRtf::getPaperWidth()
{
    return m_paperWidth;
}

void CppRtf::setPaperHeight(float height)
{
    m_paperHeight = height;
}

float CppRtf::getPaperHeight()
{
    return m_paperHeight;
}

void CppRtf::setMarginLeft(float margin)
{
    m_marginLeft = margin;
}

void CppRtf::setMarginRight(float margin)
{
    m_marginRight = margin;
}

void CppRtf::setMarginTop(float margin)
{
    m_marginTop = margin;
}

void CppRtf::setMarginBottom(float margin)
{
    m_marginBottom = margin;
}

void CppRtf::setMargins(float marginLeft, float marginTop, float marginRight, float marginBottom)
{
    setMarginLeft(marginLeft);
    setMarginTop(marginTop);
    setMarginRight(marginRight);
    setMarginBottom(marginBottom);
}

float CppRtf::getMarginLeft()
{
    return m_marginLeft;
}

float CppRtf::getMarginRight()
{
    return m_marginRight;
}

float CppRtf::getMarginTop()
{
    return m_marginTop;
}

float CppRtf::getMarginBottom()
{
    return m_marginBottom;
}

void CppRtf::setMirrorMargins()
{
    m_useMirrorMargins = true;
}

bool CppRtf::isMirrorMargins()
{
    return m_useMirrorMargins;
}

void CppRtf::setGutter(float gutter)
{
    m_gutter = gutter;
}

float CppRtf::getGutter()
{
    return m_gutter;
}

void CppRtf::setPageNumberStart(int pageNumber)
{
    m_pageNumberStart = pageNumber;
}

int CppRtf::getPageNumberStart()
{
    return m_pageNumberStart;
}

void CppRtf::setViewMode(VIEW_MODE viewMode)
{
    m_viewMode = viewMode;
}

CppRtf::VIEW_MODE CppRtf::getViewMode()
{
    return m_viewMode;
}

void CppRtf::setZoomLevel(int zoom)
{
    m_zoomLevel = zoom;
}

int CppRtf::getZoomLevel()
{
    return m_zoomLevel;
}

void CppRtf::setZoomMode(CppRtf::ZOOM_MODE zoomMode)
{
    m_zoomMode = zoomMode;
}

CppRtf::ZOOM_MODE CppRtf::getZoomMode()
{
    return m_zoomMode;
}

void CppRtf::setLandscape()
{
    m_isLandscape = true;
}

bool CppRtf::isLandscape()
{
    return m_isLandscape;
}

void CppRtf::setHyphenation()
{
    m_isHyphenation = true;
}

void CppRtf::setBorder(CppRtf_Border *border)
{
    m_border = new CppRtf_Border(*border);
}

CppRtf_Border *CppRtf::getBorder()
{
    return m_border;
}

CppRtf *CppRtf::setBorderSurroundsHeader(bool borderSurroundsHeader)
{
    m_borderSurroundsHeader = borderSurroundsHeader;
    return this;
}

CppRtf *CppRtf::setBorderSurroundsFooter(bool borderSurroundsFooter)
{
    m_borderSurroundsFooter = borderSurroundsFooter;
    return this;
}

bool CppRtf::borderSurroundsHeader()
{
    return m_borderSurroundsHeader;
}

bool CppRtf::borderSurroundsFooter()
{
    return m_borderSurroundsFooter;
}

void CppRtf::setBorders(CppRtf_Border_Format *borderFormat, bool left, bool top, bool right, bool bottom)
{
    if (m_border == 0) {
        m_border = new CppRtf_Border(this);
    }
    m_border->setBorders(borderFormat, left, top, right, bottom);
}

void CppRtf::setOddEvenDifferent(bool different)
{
    m_useOddEvenDifferent = different;
}

bool CppRtf::isOddEvenDifferent()
{
    return m_useOddEvenDifferent;
}

CppRtf_Container_Header *CppRtf::addHeader(CppRtf_Container_Header::HeaderType type, CppRtf_Container_Header *header)
{
    if (header == 0) {
         header = new CppRtf_Container_Header(this, type);
     }
     m_headers.push_back(header);

     return header;
}

CppRtf_Container_Footer *CppRtf::addFooter(CppRtf_Container_Header::HeaderType type, CppRtf_Container_Footer *footer)
{
    if (footer == 0) {
        footer = new CppRtf_Container_Footer(this, type);
    }
    m_footers.push_back(footer);

    return footer;
}

vector<CppRtf_Container_Header *> CppRtf::getHeaders()
{
    return m_headers;
}

vector<CppRtf_Container_Footer *> CppRtf::getFooters()
{
    return m_footers;
}

CppRtf_DocHead_ColorTable *CppRtf::getColorTable()
{
    if (m_colorTable == 0) {
        m_colorTable = new CppRtf_DocHead_ColorTable();
    }
    return m_colorTable;
}

CppRtf_DocHead_FontTable *CppRtf::getFontTable()
{
    if (m_fontTable == 0) {
        m_fontTable = new CppRtf_DocHead_FontTable();
    }
    return m_fontTable;
}

void CppRtf::registerFont(CppRtf_Font *font)
{
    font->setColorTable(getColorTable());
    font->setFontTable(getFontTable());
}

void CppRtf::setDefaultFont(CppRtf_Font *font)
{
    m_defaultFont = font;
    this->registerFont(font);
}

CppRtf_Font *CppRtf::getDefaultFont()
{
    return m_defaultFont;
}

void CppRtf::registerParFormat(CppRtf_ParFormat *parFormat)
{
    parFormat->setColorTable(this->getColorTable());
}

string CppRtf::getContent()
{
    this->createWriter();
    this->render();
    return m_writer->getContent();
}

void CppRtf::save(string file)
{
    this->createWriter(file);
    this->render();
}

void CppRtf::sendRtf(string filename)
{
   (void)filename;// TODO
}

void CppRtf::setSpecialLayoutForFirstPage(bool specialLayout)
{
    m_titlepg = specialLayout;
}

bool CppRtf::hasSpecialLayoutForFirstPage()
{
    return m_titlepg;
}

string CppRtf::quoteRtfCode(string text, bool convertNewlines)
{
    //TODO
    // escape backslashes and curly brackets
    vector<string> search;search.push_back("\\");search.push_back("{");search.push_back("}");
    vector<string> replace;replace.push_back("\\\\");replace.push_back("\\{");replace.push_back("\\}");
       text = str_replace(search, replace, text);
       if (convertNewlines) {
           text = convertNewlinesToRtfCode(text);
       }

       return text;
}

string CppRtf::convertNewlinesToRtfCode(string text)
{
    // convert breaks into rtf break
    vector<string> search;search.push_back("\r\n");search.push_back("\n");search.push_back("\r");
    string replace = "\\line ";
    text = str_replace(search, replace, text);
    return text;
}

void CppRtf::setWriter(CppRtf_StreamOutput *writer)
{
    m_writer = writer;
}

CppRtf_StreamOutput *CppRtf::getWriter()
{
    return m_writer;
}

void CppRtf::createWriter(string file)
{//TODO
    if (file.length()>0 || m_useTemporaryFile) {

//                if (file.length()== 0) {
//                    file = sys_get_temp_dir() . '/' . md5(microtime(true)) . '.rtf';
//                }
        m_writer->setFilename(file);
     }
    else {

//        if (!($this->_writer instanceof PHPRtfLite_Writer_String)) {
//            $this->_writer = new PHPRtfLite_Writer_String();
//        }
    }
}

string CppRtf::getInfoPart()
{
    string part = "{\\info\r\n";
    //TODO
//            foreach (m_properties as $key => $value) {
//                $value = PHPRtfLite_Utf8::getUnicodeEntities($value, $this->_charset);
//                $part .= '{\\' . $key . ' ' . $value . '}'."\r\n";
//            }
    part += "}\r\n";
    return part;
}

void CppRtf::render()
{
    //TODO
    using namespace cppstring;
    m_writer->open(CppRtf_StreamOutput::WriteOnly);
    int defaultFontSize = 20;
    int defaultFontIndex = 0;
       if (m_defaultFont) {
           defaultFontIndex = this->getFontTable()->getFontIndex(m_defaultFont->getFontFamily());
           defaultFontSize = m_defaultFont->getSize() * 2;
       }

       m_writer->write("{\\rtf\\ansi\\deff" + numtostr(defaultFontIndex) + "\\fs" + numtostr(defaultFontSize) + "\r\n");

       m_writer->write(this->getFontTable()->getContent());

       m_writer->write(this->getColorTable()->getContent());

       m_writer->write(this->getInfoPart());

       float paperWidth = m_paperWidth;
       float paperHeight = m_paperHeight;

       // page properties
       if (m_isLandscape) {
           m_writer->write("\\landscape ");
           if (paperWidth < paperHeight) {
               float tmp = paperHeight;
               paperHeight = paperWidth;
               paperWidth = tmp;
           }
       }
       int twipsW = CppRtf_Unit::getUnitInTwips(paperWidth),twipsH = CppRtf_Unit::getUnitInTwips(paperHeight);
       m_writer->write("\\paperw" + numtostr(twipsW)  + " ");
       m_writer->write("\\paperh" + numtostr(twipsH)  + " ");

       // hyphenation
       if (m_isHyphenation) {
           m_writer->write("\\hyphauto1");
       }
       m_writer->write("\\deftab" + numtostr(CppRtf_Unit::getUnitInTwips(m_defaultTabWidth)) + " ");
       m_writer->write("\\margl" + numtostr(CppRtf_Unit::getUnitInTwips(m_marginLeft)) + " ");
       m_writer->write("\\margr" + numtostr(CppRtf_Unit::getUnitInTwips(m_marginRight)) + " ");
       m_writer->write("\\margt" +numtostr(CppRtf_Unit::getUnitInTwips(m_marginTop)) + " ");
       m_writer->write("\\margb" +numtostr(CppRtf_Unit::getUnitInTwips(m_marginBottom)) + " ");

       if (m_gutter>-1) {
           m_writer->write("\\gutter" +numtostr(CppRtf_Unit::getUnitInTwips(m_gutter)) + " ");
       }

       if (true == m_useMirrorMargins) {
           m_writer->write("\\margmirror ");
       }

       if (m_viewMode != VIEW_MODE_NONE) {
           m_writer->write("\\viewkind" + numtostr(m_viewMode) + " ");
       }

       if (m_zoomMode != ZOOM_MODE_NONE) {
           m_writer->write("\\viewzk" + numtostr(m_zoomMode) + " ");
       }

       if (m_zoomLevel > -1) {
           m_writer->write("\\viewscale" + numtostr(m_zoomLevel) + " ");
       }

       // page numbering start
       m_writer->write("\\pgnstart" + numtostr(m_pageNumberStart));

       // headers and footers properties
       if (m_useOddEvenDifferent) {
           m_writer->write("\\facingp ");
       }
       if (m_titlepg) {
           m_writer->write("\\titlepg ");
       }

       // document header definition for footnotes and endnotes
       m_writer->write(this->getNoteDocHead()->getContent());

       // default font
       if (m_defaultFont) {
           m_writer->write(m_defaultFont->getContent());
       }

       // headers and footers if there are no sections
       if (m_sections.size() == 0) {
           for(vector<CppRtf_Container_Header*>::iterator it = m_headers.begin();it!= m_headers.end();it++){
               CppRtf_Container_Header* header = *it;
               if(header)
                   header->render();
           }
           for(vector<CppRtf_Container_Footer*>::iterator it = m_footers.begin();it!= m_footers.end();it++){
               CppRtf_Container_Footer* footer = *it;
               if(footer)
                   footer->render();
           }
       }

       // sections

       for(vector<CppRtf_Container_Section*>::iterator it = m_sections.begin();it!= m_sections.end();it++){
           if(it!=m_sections.begin()){
                m_writer->write("\\sect\\sectd ");
           }
           CppRtf_Container_Section* section = *it;
           section->render();
       }

       m_writer->write("}");
       m_writer->close();
}

const string CppRtf::VERSION = "dev";
const int CppRtf::SPACE_IN_POINTS = 20;   // used for twips conversion
const int CppRtf::SPACE_IN_LINES = 240;  // used for twips conversion

