#include "table.h"
#include "writer/interface.h"

CppRtf_Table::CppRtf_Table(CppRtf_Container_Base *container, TableAligment alignment, int nestDepth)
    :m_container(container),m_aligment(alignment),m_nestDepth(nestDepth),
      m_preventPageBreak(false),m_firstRowIsHeader(false),m_repeatFirstRowHeader(false),m_leftPosition(0),m_preventEmptyParagraph(false)
{
}

CppRtf_Table::~CppRtf_Table()
{
    for(vector<CppRtf_Table_Column*>::iterator it = m_columns.begin(); it != m_columns.end(); it++){
        delete *it;
        *it = 0;
    }
    for(vector<CppRtf_Table_Row*>::iterator it = m_rows.begin(); it != m_rows.end(); it++){
        delete *it;
        *it = 0;
    }
}

int CppRtf_Table::getNestDepth()
{
    return m_nestDepth;
}

bool CppRtf_Table::isNestedTable()
{
    return m_nestDepth > 1;
}

CppRtf_Container_Base *CppRtf_Table::getContainer()
{
    return m_container;
}

CppRtf *CppRtf_Table::getRtf()
{
    return m_container->getRtf();
}

void CppRtf_Table::setPreventPageBreak()
{
    m_preventPageBreak = true;
}

bool CppRtf_Table::isPreventPageBreak()
{
    return m_preventPageBreak;
}

void CppRtf_Table::setLeftPosition(float leftPosition)
{
    m_leftPosition = leftPosition;
}

float CppRtf_Table::getLeftPosition()
{
    return m_leftPosition;
}

void CppRtf_Table::setFirstRowAsHeader()
{
    m_firstRowIsHeader = true;
}

bool CppRtf_Table::isFirstRowHeader()
{
    return m_firstRowIsHeader;
}

CppRtf_Table::TableAligment CppRtf_Table::getAligment()
{
    return m_aligment;
}

void CppRtf_Table::preventEmptyParagraph(bool value)
{
    m_preventEmptyParagraph = value;
}

bool CppRtf_Table::getPreventEmptyParagraph()
{
    return m_preventEmptyParagraph;
}

CppRtf_Table_Row *CppRtf_Table::addRow(float height)
{
    CppRtf_Table_Row* row = new CppRtf_Table_Row(this, this->getRowsCount() + 1, height);
    m_rows.push_back(row);
    return row;
}

void CppRtf_Table::addRows(int rowCnt, float height)
{
    for (int i = 0; i < rowCnt; i++) {
        this->addRow(height);
    }
}

void CppRtf_Table::addRowList(vector<float> heights)
{
    for(vector<float>::iterator it = heights.begin();it!=heights.end();it++){
        addRow(*it);
    }
}

int CppRtf_Table::getRowsCount()
{
    return m_rows.size();
}

vector<CppRtf_Table_Row *> CppRtf_Table::getRows()
{
    return m_rows;
}

CppRtf_Table_Row *CppRtf_Table::getRow(int rowIndex)
{
    if(getRowsCount()>=rowIndex&&rowIndex>0){
        return m_rows[rowIndex-1];
    }
    throw "Invalid row index for table: " + cppstring::numtostr(rowIndex);
}

CppRtf_Table_Column *CppRtf_Table::addColumn(float width)
{
    CppRtf_Table_Column* column = new CppRtf_Table_Column(this, this->getColumnsCount() + 1, width);
    m_columns.push_back(column);
    return column;
}

int CppRtf_Table::getColumnsCount()
{
    return m_columns.size();
}

vector<CppRtf_Table_Column *> CppRtf_Table::getColumns()
{
    return m_columns;
}

CppRtf_Table_Column *CppRtf_Table::getColumn(int columnIndex)
{
    if(getColumnsCount()>=columnIndex&&columnIndex>0){
        return m_columns[columnIndex-1];
    }
    throw "Invalid column index for table: " + cppstring::numtostr(columnIndex);
}

void CppRtf_Table::addColumnsList(vector<float> widths)
{
    for(vector<float>::iterator it = widths.begin();it!=widths.end();it++){
        addColumn(*it);
    }
}

bool CppRtf_Table::checkIfCellExists(int rowIndex, int columnIndex)
{
    if(rowIndex>0&&columnIndex>0)
        return (getRowsCount()>=rowIndex)&&(getColumnsCount()>=columnIndex);
    return false;
}

CppRtf_Table_Cell *CppRtf_Table::getCell(int rowIndex, int columnIndex)
{
    if (checkIfCellExists(rowIndex,columnIndex)) {
        return this->getRow(rowIndex)->getCellByIndex(columnIndex);
    }
    string err ="Wrong index for cell! You gave me: (row:" + cppstring::numtostr(rowIndex) + ", column:" + cppstring::numtostr(columnIndex) + ")";
    throw err;
}

CppRtf_Element *CppRtf_Table::writeToCell(int rowIndex, int columnIndex, string text, CppRtf_Font *font, CppRtf_ParFormat *parFormat, bool convertTagsToRtf)
{
    CppRtf_Table_Cell* cell = this->getCell(rowIndex, columnIndex);
    if (font == 0) {
        font = cell->getFont();
    }
    return cell->writeText(text, font, parFormat, convertTagsToRtf);
}

CppRtf_Image *CppRtf_Table::addImageToCell(int rowIndex, int columnIndex, string file, CppRtf_ParFormat *parFormat, float width, float height)
{
    CppRtf_Table_Cell* cell = getCell(rowIndex, columnIndex);
    return cell->addImage(file, parFormat, width, height);
}

CppRtf_Image *CppRtf_Table::addImageFromStringToCell(int rowIndex, int columnIndex, string imageString, CppRtf_Image::ImageType type, CppRtf_ParFormat *parFormat, float width, float height)
{
    CppRtf_Table_Cell* cell = getCell(rowIndex, columnIndex);
    return cell->addImageFromString(imageString, type, parFormat, width, height);
}

vector<int> CppRtf_Table::getValidCellRange(int startRow, int startColumn, int endRow, int endColumn)
{
    int temp;
    if (endRow <0) {
        endRow = startRow;
    }
    else if (startRow > endRow) {
        temp = startRow;
        startRow = endRow;
        endRow = temp;
    }

    if (endColumn <0) {
        endColumn = startColumn;
    }
    else if (startColumn > endColumn) {
        temp = startColumn;
        startColumn = endColumn;
        endColumn = temp;
    }
    vector<int> res;
    res.push_back(startRow);
    res.push_back(startColumn);
    res.push_back(endRow);
    res.push_back(endColumn);
    return res;
}

vector<CppRtf_Table_Cell *> CppRtf_Table::getCellsByCellRange(int startRow, int startColumn, int endRow, int endColumn)
{
    vector<CppRtf_Table_Cell *> cells ;
    for (int rowIndex = startRow; rowIndex <= endRow; rowIndex++) {
        for (int columnIndex = startColumn; columnIndex <= endColumn; columnIndex++) {
            cells.push_back(getCell(rowIndex,columnIndex));
        }
    }
    return cells;
}

void CppRtf_Table::setVerticalAlignmentForCellRange(CppRtf_Table_Cell::VerticalAligment verticalAlignment, int startRow, int startColumn, int endRow, int endColumn)
{
    vector<int> list = CppRtf_Table::getValidCellRange(startRow, startColumn, endRow, endColumn);
    startRow = list[0];
    startColumn = list[1];
    endRow = list[2];
    endColumn = list[3];

    if (this->checkIfCellExists(startRow, startColumn) && this->checkIfCellExists(endRow, endColumn))
    {
        vector<CppRtf_Table_Cell *>  cells = this->getCellsByCellRange(startRow, startColumn, endRow, endColumn);
        for(vector<CppRtf_Table_Cell *>::iterator it=cells.begin();it!=cells.end();it++){
            CppRtf_Table_Cell *cell = *it;
            cell->setVerticalAlignment(verticalAlignment);
        }
    }
}

void CppRtf_Table::setTextAlignmentForCellRange(CppRtf_Table_Cell::TextAligment alignment, int startRow, int startColumn, int endRow, int endColumn)
{
    vector<int> list = CppRtf_Table::getValidCellRange(startRow, startColumn, endRow, endColumn);
    startRow = list[0];
    startColumn = list[1];
    endRow = list[2];
    endColumn = list[3];

    if (this->checkIfCellExists(startRow, startColumn) && this->checkIfCellExists(endRow, endColumn))
    {
        vector<CppRtf_Table_Cell *>  cells = this->getCellsByCellRange(startRow, startColumn, endRow, endColumn);
        for(vector<CppRtf_Table_Cell *>::iterator it=cells.begin();it!=cells.end();it++){
            CppRtf_Table_Cell *cell = *it;
            cell->setTextAlignment(alignment);
        }
    }
}

void CppRtf_Table::setFontForCellRange(CppRtf_Font *font, int startRow, int startColumn, int endRow, int endColumn)
{
    vector<int> list = CppRtf_Table::getValidCellRange(startRow, startColumn, endRow, endColumn);
    startRow = list[0];
    startColumn = list[1];
    endRow = list[2];
    endColumn = list[3];

    if (this->checkIfCellExists(startRow, startColumn) && this->checkIfCellExists(endRow, endColumn))
    {
        vector<CppRtf_Table_Cell *>  cells = this->getCellsByCellRange(startRow, startColumn, endRow, endColumn);
        for(vector<CppRtf_Table_Cell *>::iterator it=cells.begin();it!=cells.end();it++){
            CppRtf_Table_Cell *cell = *it;
            cell->setFont(font);
        }
    }
}

void CppRtf_Table::rotateCellRange(CppRtf_Table_Cell::RotationDirections rotateTo, int startRow, int startColumn, int endRow, int endColumn)
{
    vector<int> list = CppRtf_Table::getValidCellRange(startRow, startColumn, endRow, endColumn);
    startRow = list[0];
    startColumn = list[1];
    endRow = list[2];
    endColumn = list[3];

    if (this->checkIfCellExists(startRow, startColumn) && this->checkIfCellExists(endRow, endColumn))
    {
        vector<CppRtf_Table_Cell *>  cells = this->getCellsByCellRange(startRow, startColumn, endRow, endColumn);
        for(vector<CppRtf_Table_Cell *>::iterator it=cells.begin();it!=cells.end();it++){
            CppRtf_Table_Cell *cell = *it;
            cell->rotateTo(rotateTo);
        }
    }
}

void CppRtf_Table::setBackgroundForCellRange(string backgroundColor, int startRow, int startColumn, int endRow, int endColumn)
{
    vector<int> list = CppRtf_Table::getValidCellRange(startRow, startColumn, endRow, endColumn);
    startRow = list[0];
    startColumn = list[1];
    endRow = list[2];
    endColumn = list[3];

    if (this->checkIfCellExists(startRow, startColumn) && this->checkIfCellExists(endRow, endColumn))
    {
        vector<CppRtf_Table_Cell *>  cells = this->getCellsByCellRange(startRow, startColumn, endRow, endColumn);
        for(vector<CppRtf_Table_Cell *>::iterator it=cells.begin();it!=cells.end();it++){
            CppRtf_Table_Cell *cell = *it;
            cell->setBackgroundColor(backgroundColor);
        }
    }
}

void CppRtf_Table::setBorderForCellRange(CppRtf_Border *border, int startRow, int startColumn, int endRow, int endColumn)
{
    vector<int> list = CppRtf_Table::getValidCellRange(startRow, startColumn, endRow, endColumn);
    startRow = list[0];
    startColumn = list[1];
    endRow = list[2];
    endColumn = list[3];

    if (this->checkIfCellExists(startRow, startColumn) && this->checkIfCellExists(endRow, endColumn))
    {
        vector<CppRtf_Table_Cell *>  cells = this->getCellsByCellRange(startRow, startColumn, endRow, endColumn);
        for(vector<CppRtf_Table_Cell *>::iterator it=cells.begin();it!=cells.end();it++){
            CppRtf_Table_Cell *cell = *it;
            cell->setBorder(border);
        }
    }
}

void CppRtf_Table::mergeCellRange(int startRow, int startColumn, int endRow, int endColumn)
{
    vector<int> list = CppRtf_Table::getValidCellRange(startRow, startColumn, endRow, endColumn);
    startRow = list[0];
    startColumn = list[1];
    endRow = list[2];
    endColumn = list[3];

    if (startRow == endRow && startColumn == endColumn) {
        return;
    }

    if (!this->checkIfCellExists(endRow, endColumn)) {
        return;
    }

    for (int j = startRow; j <= endRow; j++) {
        int start = startColumn;
        CppRtf_Table_Cell* cell = this->getCell(j,start);

        while (cell->isHorizontalMerged()) {
            start--;
            cell = this->getCell(j, start);
        }

        int end = endColumn;

        cell = this->getCell(j, end);
        while (cell->isHorizontalMerged()) {
            end++;
            cell = this->getCell(j, end + 1);
        }

        float width = 0;

        for (int i = start; i <= end; i++) {
            cell = this->getCell(j, i);
            if (j == startRow) {
                cell->setVerticalMergeStart();
            }
            else {
                cell->setVerticalMerged();
            }

            width += cell->getWidth();
            if (i != start) {
                cell->setHorizontalMerged();
            }
        }

        this->getCell(j, start)->setWidth(width);
    }
}

void CppRtf_Table::render()
{
    if (m_rows.empty() || m_columns.empty()) {
        return;
    }
    CppRtf_Writer_Interface* stream = getRtf()->getWriter();
    stream->write("\\pard");
    for(vector<CppRtf_Table_Row*>::iterator it= m_rows.begin();it!=m_rows.end();it++){
        this->renderRowDefinition(*it);
        stream->write("\r\n");
        this->renderRowCells(*it);
        stream->write("\r\n\\row\r\n");
    }
    stream->write("\\pard\\itap0\r\n");
}

void CppRtf_Table::renderRowDefinition(CppRtf_Table_Row *row)
{
    int rowIndex = row->getRowIndex();
    CppRtf_Writer_Interface* stream = getRtf()->getWriter();
    stream->write("\\trowd");

    if(m_aligment == CppRtf_Table::ALIGN_CENTER){
        stream->write("\\trqc");
    }
    if(m_aligment == CppRtf_Table::ALIGN_RIGHT){
        stream->write("\\trqr");
    }
    else
        stream->write("\\trql");

    float rowHeight = row->getHeight();
    if (rowHeight>-100) //TODO:better
    {
        int twips =  CppRtf_Unit::getUnitInTwips(rowHeight);
        stream->write("\\trrh" + cppstring::numtostr(twips));
    }

    if (this->isPreventPageBreak()) {
        stream->write("\\trkeep ");
    }

    if (this->isFirstRowHeader() && rowIndex == 1) {
        stream->write("\trhdr ");
    }

    if (this->getLeftPosition() >0) {
        int twips = CppRtf_Unit::getUnitInTwips(this->getLeftPosition());
        stream->write("\\trleft" + cppstring::numtostr(twips) + " ");
    }
    int width = 0;
    for(int columnIndex = 1; columnIndex<=getColumnsCount(); columnIndex++){
        CppRtf_Table_Cell* cell = getCell(rowIndex,columnIndex);
        // render cell definition
        if (!cell->isHorizontalMerged()) {
            cell->renderDefinition();

            // cell width
            width += CppRtf_Unit::getUnitInTwips(cell->getWidth());
            stream->write("\\cellx" + cppstring::numtostr(width));
            if(width == 5103||width == 6804){
                int bla = 5;
            }
        }
    }
}

void CppRtf_Table::renderRowCells(CppRtf_Table_Row *row)
{
    int rowIndex = row->getRowIndex();
    for(int columnIndex = 0; columnIndex<getColumnsCount(); columnIndex++){
        CppRtf_Table_Cell* cell = getCell(rowIndex,columnIndex+1);
        if (!cell->isHorizontalMerged()) {
            cell->render();
        }
    }
}
