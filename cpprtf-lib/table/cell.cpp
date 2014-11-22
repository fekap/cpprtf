#include "cell.h"
#include "table/nested.h"
#include "writer/interface.h"

CppRtf_Table_Cell::CppRtf_Table_Cell(CppRtf_Table *table, int rowIndex, int columnIndex)
    :CppRtf_Container(this->getRtf()),m_table(0),m_font(0),m_border(0),
      m_horizontalMerged(false),m_verticalMerged(false),m_verticalMergeStart(false)
{
    m_rtf = 0;
    m_table = table;
    m_rowIndex = rowIndex;
    m_columnIndex = columnIndex;
    m_rtf         = table->getRtf();
    m_pard = "";

    m_width = -1; //null
    m_paddingLeft = -1;//null
    m_paddingRight = -1;//null
    m_paddingTop = -1;//null
    m_paddingBottom = -1; //null
    m_verticalAlignment = VERTICAL_ALIGN_NULL;
    m_rotateTo = ROTATE_NULL;
    m_alignment = TEXT_ALIGN_NULL;

    __name = typeid(this).name();
}

CppRtf_Table_Cell::~CppRtf_Table_Cell()
{
    if(m_font!=0){
        delete m_font;
        m_font = 0;
    }
    if(m_border!=0){
        delete m_border;
        m_border = 0;
    }
}

CppRtf_Table_Nested *CppRtf_Table_Cell::addTable(CppRtf_Table_Cell::TextAligment alignment)
{
    int nestDepth = m_table->getNestDepth() + 1;
    CppRtf_Table_Nested* table = new CppRtf_Table_Nested(this,(CppRtf_Table::TableAligment)alignment,nestDepth);
    addElement(table);
    return table;
}

CppRtf_Table *CppRtf_Table_Cell::getTable()
{
    return m_table;
}

void CppRtf_Table_Cell::setTextAlignment(CppRtf_Table_Cell::TextAligment alignment)
{
    m_alignment = alignment;
}

CppRtf_Table_Cell::TextAligment CppRtf_Table_Cell::getTextAligment()
{
    return m_alignment;
}

void CppRtf_Table_Cell::setFont(CppRtf_Font *font)
{
    m_rtf->registerFont(font);
    if(m_font)
        delete m_font;
    m_font = new CppRtf_Font(*font);
}

CppRtf_Font *CppRtf_Table_Cell::getFont()
{
    return m_font;
}

void CppRtf_Table_Cell::setVerticalAlignment(CppRtf_Table_Cell::VerticalAligment verticalAlignment)
{
    m_verticalAlignment = verticalAlignment;
}

CppRtf_Table_Cell::VerticalAligment CppRtf_Table_Cell::getVerticalAlignment()
{
    return m_verticalAlignment;   
}

void CppRtf_Table_Cell::rotateTo(CppRtf_Table_Cell::RotationDirections rotateTo)
{
    m_rotateTo = rotateTo;
}

CppRtf_Table_Cell::RotationDirections CppRtf_Table_Cell::getRotateTo()
{
    return m_rotateTo;
}

void CppRtf_Table_Cell::setBackgroundColor(string color)
{
    m_backgroundColor = color;
    m_rtf->getColorTable()->add(color);
}

string CppRtf_Table_Cell::getBackgroundColor()
{
    return m_backgroundColor;
}

void CppRtf_Table_Cell::setHorizontalMerged()
{
    m_horizontalMerged = true;
}

bool CppRtf_Table_Cell::isHorizontalMerged()
{
    return m_horizontalMerged;
}

void CppRtf_Table_Cell::setVerticalMerged()
{
    m_verticalMerged = true;
}

bool CppRtf_Table_Cell::isVerticalMerged()
{
    return m_verticalMerged;
}

void CppRtf_Table_Cell::setVerticalMergeStart()
{
    m_verticalMergeStart = true;
    m_verticalMerged = true;
}

bool CppRtf_Table_Cell::isVerticalMergedFirstInRange()
{
    return m_verticalMergeStart;
}

void CppRtf_Table_Cell::setWidth(float width)
{
    m_width = width;
}

float CppRtf_Table_Cell::getWidth()
{
    if (m_width<0) {
        return m_table->getColumn(m_columnIndex)->getWidth();
    }
    return m_width;
}

void CppRtf_Table_Cell::setCellBorder(CppRtf_Border *border)
{
    m_border = new CppRtf_Border(*border);
}

CppRtf_Border *CppRtf_Table_Cell::getBorder()
{
    return m_border;
}

CppRtf_Border *CppRtf_Table_Cell::getBorderForCell(int rowIndex, int columnIndex)
{
    CppRtf_Table_Cell* cell = m_table->getCell(rowIndex, columnIndex);
    CppRtf_Border * border = cell->getBorder();
    if (border == 0) {
        border = new CppRtf_Border(m_rtf);
        cell->setCellBorder(border);
        delete border;
    }
    return cell->getBorder();;
}

void CppRtf_Table_Cell::setBorder(CppRtf_Border *border)
{
    CppRtf_Border_Format* borderFormatTop = border->getBorderTop();
    CppRtf_Border_Format* borderFormatBottom = border->getBorderBottom();
    CppRtf_Border_Format* borderFormatLeft   = border->getBorderLeft();
    CppRtf_Border_Format* borderFormatRight  = border->getBorderRight();

    if (m_border == 0) {
        m_border = new CppRtf_Border(m_rtf);
    }
    if (borderFormatLeft) {
        m_border->setBorderLeft(borderFormatLeft);
    }
    if (borderFormatRight) {
        m_border->setBorderRight(borderFormatRight);
    }
    if (borderFormatTop) {
        m_border->setBorderTop(borderFormatTop);
    }
    if (borderFormatBottom) {
        m_border->setBorderBottom(borderFormatBottom);
    }

    if (borderFormatTop && m_table->checkIfCellExists(m_rowIndex - 1, m_columnIndex)) {
        this->getBorderForCell(m_rowIndex - 1, m_columnIndex)->setBorderBottom(borderFormatTop);
    }

    if (borderFormatBottom && m_table->checkIfCellExists(m_rowIndex + 1, m_columnIndex)) {
        this->getBorderForCell(m_rowIndex + 1, m_columnIndex)->setBorderTop(borderFormatBottom);
    }

    if (borderFormatLeft && m_table->checkIfCellExists(m_rowIndex, m_columnIndex - 1)) {
        this->getBorderForCell(m_rowIndex, m_columnIndex - 1)->setBorderRight(borderFormatLeft);
    }

    if (borderFormatRight && m_table->checkIfCellExists(m_rowIndex, m_columnIndex + 1)) {
        this->getBorderForCell(m_rowIndex, m_columnIndex + 1)->setBorderLeft(borderFormatRight);
    }
}

int CppRtf_Table_Cell::getRowIndex()
{
    return m_rowIndex;
}

int CppRtf_Table_Cell::getColumnIndex()
{
    return m_columnIndex;
}

void CppRtf_Table_Cell::setCellPaddings(int paddingLeft, int paddingTop, int paddingRight, int paddingBottom)
{
    setPaddingLeft(paddingLeft);
    setPaddingTop(paddingTop);
    setPaddingRight(paddingRight);
    setPaddingBottom(paddingBottom);
}

void CppRtf_Table_Cell::setPaddingLeft(int padding)
{
    m_paddingLeft = padding;
}

void CppRtf_Table_Cell::setPaddingRight(int padding)
{
    m_paddingRight= padding;
}

void CppRtf_Table_Cell::setPaddingTop(int padding)
{
    m_paddingTop = padding;
}

void CppRtf_Table_Cell::setPaddingBottom(int padding)
{
    m_paddingBottom = padding;
}

void CppRtf_Table_Cell::renderDefinition()
{
    CppRtf_Writer_Interface * stream = m_rtf->getWriter();
    if (this->isVerticalMerged()) {
        if (this->isVerticalMergedFirstInRange()) {
            stream->write("\\clvmgf");
        }
        else {
            stream->write("\\clvmrg");
        }
    }

    string backgroundColor = this->getBackgroundColor();
    if (!backgroundColor.empty()) {
        CppRtf_DocHead_ColorTable* colorTable = m_rtf->getColorTable();
        stream->write("\\clcbpat" + cppstring::numtostr(colorTable->getColorIndex(backgroundColor)) + " ");
    }

    switch (this->getVerticalAlignment()) {
        case CppRtf_Table_Cell::VERTICAL_ALIGN_TOP:
            stream->write("\\clvertalt");
            break;

        case CppRtf_Table_Cell::VERTICAL_ALIGN_CENTER:
            stream->write("\\clvertalc");
            break;

        case CppRtf_Table_Cell::VERTICAL_ALIGN_BOTTOM:
            stream->write("\\clvertalb");
            break;
    }

    switch (this->getRotateTo()) {
        case CppRtf_Table_Cell::ROTATE_RIGHT:
            stream->write("\\cltxtbrl");
            break;

        case CppRtf_Table_Cell::ROTATE_LEFT:
            stream->write("\\cltxbtlr");
            break;
    }

    // NOTE: microsoft and all other rtf readers I know confound left with top cell padding
    if (m_paddingLeft>-1) {
        int twips = CppRtf_Unit::getUnitInTwips(m_paddingLeft);
        stream->write("\\clpadft3\\clpadt" + cppstring::numtostr(twips) + " ");
    }
    if (m_paddingTop>-1) {
        int twips = CppRtf_Unit::getUnitInTwips(m_paddingTop);
        stream->write("\\clpadfl3\\clpadl" +  cppstring::numtostr(twips) + " ");
    }
    if (m_paddingBottom>-1) {
        int twips = CppRtf_Unit::getUnitInTwips(m_paddingBottom);
        stream->write("\\clpadfb3\\clpadb" +  cppstring::numtostr(twips) + " ");
    }
    if (m_paddingRight>-1) {
        int twips = CppRtf_Unit::getUnitInTwips(m_paddingRight);
        stream->write("\\clpadfr3\\clpadr" +  cppstring::numtostr(twips) + " ");
    }

    CppRtf_Border* border = this->getBorder();
    if (border) {
        stream->write(border->getContent("\\cl"));
    }
}

void CppRtf_Table_Cell::render()
{
    CppRtf_Writer_Interface* stream = m_rtf->getWriter();
            stream->write("\r\n");

            // renders container elements
            CppRtf_Container::render();

            vector<BaseElement*> containerElements = this->getElements();
            int numOfContainerElements = containerElements.size();

            if (m_table->isNestedTable()) {
                // if last container element is not a nested table, close cell
                bool flag = false;
                if (numOfContainerElements == 0){
                    flag = true;
                }
                else{
                    BaseElement *el = containerElements[numOfContainerElements - 1];
                    if(!el->instanceOf<CppRtf_Table_Nested*>())
                        flag = true;
                }

                if (flag)
                {
                    stream->write("\\{\nestcell{\\nonesttables\\par}\\pard}\r\n");

                    // if last cell of row, close row
                    if (this->getColumnIndex() == m_table->getColumnsCount()) {
                        stream->write("{\\\\*\\\\nesttableprops ");
                        CppRtf_Table_Row* row = m_table->getRow(m_rowIndex);
                        m_table->renderRowDefinition(row);
                        stream->write("\\nestrow}");
                    }
                }
            }
            else {
                bool flag = false;
                if (numOfContainerElements >0){
                    BaseElement *el = containerElements[numOfContainerElements - 1];
                    if(el->instanceOf<CppRtf_Table_Nested*>()){
                        flag = true;
                    }
                }

                if (flag)
                {
                    stream->write("\\intbl\\itap1\\~");
                }
                // closing tag for cell definition
                stream->write("\\cell");
            }
            stream->write("\r\n");
}

string CppRtf_Table_Cell::getCellAlignment()
{
    switch (m_alignment) {
        case CppRtf_Table_Cell::TEXT_ALIGN_CENTER:
            return "\\qc";

        case CppRtf_Table_Cell::TEXT_ALIGN_RIGHT:
            return "\\qr";

        case CppRtf_Table_Cell::TEXT_ALIGN_JUSTIFY:
            return "\\qj";

        default:
            return "\\ql";
    }
}
