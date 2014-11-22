#include "section.h"
#include "unit.h"
#include "cpprtf.h"
#include "writer/interface.h"

CppRtf_Container_Section::CppRtf_Container_Section(CppRtf *rtf):CppRtf_Container(rtf)
{
    m_border = 0;
    m_numberOfColumns = 1;
    m_doNotBreak = false;
    m_lineBetweenColumns = false;
    m_isLandscape = false;
    m_font = 0;
    m_borderSurroundsHeader = false;
    m_borderSurroundsFooter = false;
    m_useMirrorMargins = false;

    //null
    m_paperWidth = -1;
    m_paperHeight= -1;
    m_marginLeft = -1;
    m_marginRight = -1;
    m_marginTop= -1;
    m_marginBottom = -1;
    m_spaceBetweenColumns = -1;
    m_gutter = -1;
}

CppRtf_Container_Section::~CppRtf_Container_Section()
{
    if(m_border != 0){
        delete m_border;
        m_border = 0;
    }
    if(m_font != 0){
        delete m_font;
        m_font = 0;
    }
    for(vector<CppRtf_Container_Header*>::iterator it = m_headers.begin(); it != m_headers.end(); it++){
        delete *it;
        *it = 0;
    }
    for(vector<CppRtf_Container_Footer*>::iterator it = m_footers.begin(); it != m_footers.end(); it++){
        delete *it;
        *it = 0;
    }
}

void CppRtf_Container_Section::setLandscape()
{
    m_isLandscape = true;
}

bool CppRtf_Container_Section::isLandscape()
{
    return m_isLandscape;
}

void CppRtf_Container_Section::setPaperWidth(float width)
{
    m_paperWidth = width;
}

float CppRtf_Container_Section::getPaperWidth()
{
    return m_paperWidth;
}

void CppRtf_Container_Section::setPaperHeight(float height)
{
    m_paperHeight = height;
}

float CppRtf_Container_Section::setPaperHeight()
{
    return m_paperHeight;
}

void CppRtf_Container_Section::setMarginLeft(float margin)
{
    m_marginLeft = margin;
}

void CppRtf_Container_Section::setMarginRight(float margin)
{
    m_marginRight = margin;
}

void CppRtf_Container_Section::setMarginTop(float margin)
{
    m_marginTop = margin;
}

void CppRtf_Container_Section::setMarginBottom(float margin)
{
    m_marginBottom = margin;
}

void CppRtf_Container_Section::setMargins(float marginLeft, float marginTop, float marginRight, float marginBottom)
{
    setMarginLeft(marginLeft);
    setMarginTop(marginTop);
    setMarginRight(marginRight);
    setMarginBottom(marginBottom);
}

bool CppRtf_Container_Section::getMarginLeft()
{
    return m_marginLeft;
}

bool CppRtf_Container_Section::getMarginRight()
{
    return m_marginRight;
}

bool CppRtf_Container_Section::getMarginTop()
{
    return m_marginTop;
}

bool CppRtf_Container_Section::getMarginBottom()
{
    return m_marginBottom;
}

void CppRtf_Container_Section::setGutter(float gutter)
{
    m_gutter = gutter;
}

float CppRtf_Container_Section::getGutter()
{
    return m_gutter;
}

void CppRtf_Container_Section::setMirrorMargins()
{
    m_useMirrorMargins = true;
}

bool CppRtf_Container_Section::isMirrorMargins()
{
    return m_useMirrorMargins;
}

float CppRtf_Container_Section::getLayoutWidth()
{
    float paperWidth     = m_paperWidth >-1   ? m_paperWidth    : m_rtf->getPaperWidth();
    float marginLeft     = m_marginLeft >-1   ? m_marginLeft    : m_rtf->getMarginLeft();
    float marginRight    = m_marginRight >-1   ? m_marginRight   : m_rtf->getMarginRight();
    float layoutWidth    = paperWidth - marginLeft - marginRight;

    if (layoutWidth <= 0) {
        string err = "The paper layout width is lower or equal zero!";
        throw err;
    }

    return layoutWidth;
}

void CppRtf_Container_Section::setBorder(CppRtf_Border *border)
{
    m_border = new CppRtf_Border(*border);
}

CppRtf_Border *CppRtf_Container_Section::getBorder()
{
    return m_border;
}

void CppRtf_Container_Section::setBorders(CppRtf_Border_Format *borderFormat, bool left, bool top, bool right, bool bottom)
{
    if (m_border == 0) {
        m_border = new CppRtf_Border(m_rtf);
    }
    m_border->setBorders(borderFormat, left, top, right, bottom);
}

void CppRtf_Container_Section::setNumberOfColumns(int columnsCount)
{
    m_numberOfColumns = columnsCount;
}

int CppRtf_Container_Section::getNumberOfColumns()
{
    return m_numberOfColumns;
}

void CppRtf_Container_Section::setSpaceBetweenColumns(float spaceBetweenColumns)
{
    m_spaceBetweenColumns = spaceBetweenColumns;
}

float CppRtf_Container_Section::getSpaceBetweenColumns()
{
    return m_spaceBetweenColumns;
}

void CppRtf_Container_Section::setColumnWidths(vector<float> columnWidths)
{
    m_numberOfColumns = columnWidths.size();
    float layoutWidth = getLayoutWidth();
    int usedWidth=0;
    for(int i = 0;i<m_numberOfColumns;i++)
        usedWidth += columnWidths[i];

    if (usedWidth <= layoutWidth) {
        m_columnWidths = columnWidths;
    }
    else {
        string err= "The section column widths are exceeding the defined layout width!";
        throw err;
    }
}

vector<float> CppRtf_Container_Section::getColumnWidths()
{
    return m_columnWidths;
}

void CppRtf_Container_Section::setNoBreak(bool doNotBreak)
{
    m_doNotBreak = doNotBreak;
}

void CppRtf_Container_Section::setLineBetweenColumns(bool flag)
{
    m_lineBetweenColumns = flag;
}

bool CppRtf_Container_Section::hasLineBetweenColumns()
{
    return m_lineBetweenColumns;
}

CppRtf_Container_Header *CppRtf_Container_Section::addHeader(CppRtf_Container_Header::HeaderType type)
{
    CppRtf_Container_Header* header = new CppRtf_Container_Header(m_rtf,type);
    m_headers.push_back(header);
    return header;
}

vector<CppRtf_Container_Header *> CppRtf_Container_Section::getHeaders()
{
    return m_headers;
}

CppRtf_Container_Footer* CppRtf_Container_Section::addFooter(CppRtf_Container_Header::HeaderType type)
{
    CppRtf_Container_Footer* footer = new CppRtf_Container_Footer(m_rtf,type);
    m_footers[type] = footer;
    return footer;
}

vector<CppRtf_Container_Footer *> CppRtf_Container_Section::getFooters()
{
    return m_footers;
}

void CppRtf_Container_Section::insertPageBreak()
{
    this->writeRtfCode("\\page");
}

void CppRtf_Container_Section::setFont(CppRtf_Font *font)
{
    m_font = new CppRtf_Font(*font);
    m_rtf->registerFont(m_font);
}

CppRtf_Font *CppRtf_Container_Section::getFont()
{
    return m_font;
}

CppRtf_Container_Section *CppRtf_Container_Section::setBorderSurroundsHeader(bool borderSurroundsHeader)
{
    m_borderSurroundsHeader = borderSurroundsHeader;
    return this;
}

CppRtf_Container_Section *CppRtf_Container_Section::setBorderSurroundsFooter(bool borderSurroundsFooter)
{
    m_borderSurroundsFooter = borderSurroundsFooter;
    return this;
}

bool CppRtf_Container_Section::borderSurroundsHeader()
{
    return m_borderSurroundsHeader;
}

bool CppRtf_Container_Section::borderSurroundsFooter()
{
    return m_borderSurroundsFooter;
}

void CppRtf_Container_Section::render()
{
    using namespace cppstring;
    CppRtf_Writer_Interface *writer = m_rtf->getWriter();

    //headers
    bool emptyHeaders = true;
    for(vector<CppRtf_Container_Header*>::iterator it = m_headers.begin();it!=m_headers.end();it++){
        CppRtf_Container_Header *h = *it;
        if(h)
            emptyHeaders = false;
    }

    vector<CppRtf_Container_Header*> headers = !emptyHeaders ? m_headers : m_rtf->getHeaders();
    if (!headers.empty()) {
        for(vector<CppRtf_Container_Header*>::iterator it = headers.begin();it!=headers.end();it++){
            CppRtf_Container_Header *header = *it;
            if(header)
                header->render();
        }
    }

    //footers

    bool emptyFooters = true;
    for(vector<CppRtf_Container_Footer*>::iterator it = m_footers.begin();it!=m_footers.end();it++){
        CppRtf_Container_Footer *f = *it;
        if(f)
            emptyFooters = false;
    }

    vector<CppRtf_Container_Footer*> footers = !emptyFooters ? m_footers : m_rtf->getFooters();
    if (!footers.empty()) {
        for(vector<CppRtf_Container_Footer*>::iterator it = footers.begin();it!=footers.end();it++){
            CppRtf_Container_Footer *footer = *it;
            if(footer)
                footer->render();
        }
    }

    //borders
    if (m_border) {
        if (m_borderSurroundsHeader) {
            writer->write("\\pgbrdrhead");
        }
        if (m_borderSurroundsFooter) {
            writer->write("\\pgbrdrfoot");
        }
        writer->write(m_border->getContent("\\pg"));
    }
    else {
        CppRtf_Border* border = m_rtf->getBorder();
        if (border) {
            if (m_rtf->borderSurroundsHeader()) {
                writer->write("\\pgbrdrhead");
            }
            if (m_rtf->borderSurroundsFooter()) {
                writer->write("\\pgbrdrfoot");
            }
            writer->write(border->getContent("\\pg"));
        }
    }

    //do not break within the section
    if (m_doNotBreak) {
        writer->write("\\sbknone ");
    }

    //set column index, when using more than one column for this section
    if (m_numberOfColumns > 1) {
        writer->write("\\cols" + numtostr(m_numberOfColumns) + " ");
    }

    if (m_columnWidths.empty()) {
        if (m_spaceBetweenColumns>-1) {
            int twips = CppRtf_Unit::getUnitInTwips(m_spaceBetweenColumns);
              writer->write("\\colsx" + numtostr(twips) + " ");
        }
    }
    else {
        int width = 0;
        for(vector<float>::iterator it = m_columnWidths.begin();it!=m_columnWidths.end();it++){
            width += CppRtf_Unit::getUnitInTwips(*it);
        }
        float printableWidth = m_rtf->getPaperWidth() - m_rtf->getMarginLeft() - m_rtf->getMarginRight();
        int space = round((CppRtf_Unit::getUnitInTwips(printableWidth) - width) / (m_columnWidths.size()- 1));

        int count = m_columnWidths.size();
        for(int key = 0;key<count;key++){
            float value = m_columnWidths[key];
            int twips = CppRtf_Unit::getUnitInTwips(value);
            writer->write("\\colno" + numtostr(key+1) + "\\colw" + numtostr(twips));
            if (value>-1) {
                writer->write("\\colsr" + numtostr(space));
            }
        }
        writer->write(" ");
    }

    if (m_lineBetweenColumns) {
        writer->write("\\linebetcol ");
    }

    /*---Page part---*/
    if (m_isLandscape) {
        writer->write("\\lndscpsxn ");
    }

    if (m_paperWidth>-1) {
        writer->write("\\pgwsxn" + numtostr(CppRtf_Unit::getUnitInTwips(m_paperWidth) )+ " ");
    }

    if (m_paperHeight>-1) {
        writer->write("\\pghsxn" + numtostr(CppRtf_Unit::getUnitInTwips(m_paperHeight) )+ " ");
    }

    if (m_marginLeft>-1) {
        writer->write("\\marglsxn" + numtostr(CppRtf_Unit::getUnitInTwips(m_marginLeft)) + " ");
    }

    if (m_marginRight>-1) {
        writer->write("\\margrsxn" + numtostr(CppRtf_Unit::getUnitInTwips(m_marginRight)) + " ");
    }

    if (m_marginTop>-1) {
        writer->write("\\margtsxn" + numtostr(CppRtf_Unit::getUnitInTwips(m_marginTop)) + " ");
    }

    if (m_marginBottom>-1) {
        writer->write("\\margbsxn" + numtostr(CppRtf_Unit::getUnitInTwips(m_marginBottom)) + " ");
    }

    if (m_gutter>-1) {
        writer->write("\\guttersxn" + numtostr(CppRtf_Unit::getUnitInTwips(m_gutter)) + " ");
    }

    if (m_useMirrorMargins) {
        writer->write("\\margmirsxn ");
    }

    if (m_font) {
        writer->write(m_font->getContent());
    }

    writer->write("\r\n");
    CppRtf_Container::render();
    writer->write("\r\n");
}
