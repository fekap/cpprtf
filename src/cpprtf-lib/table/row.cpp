#include "row.h"
#include "table.h"

CppRtf_Table_Row::CppRtf_Table_Row(CppRtf_Table *table, int rowIndex, float height)
    :m_table(table),m_rowIndex(rowIndex),m_height(height)
{
}

void CppRtf_Table_Row::setHeight(float height)
{
    m_height = height;
}

float CppRtf_Table_Row::getHeight()
{
    return m_height;
}

CppRtf_Table_Cell *CppRtf_Table_Row::getCellByIndex(int columnIndex)
{
    CppRtf_Table_Cell* cell;
    if((unsigned int)columnIndex>m_cells.size()){
        cell = new CppRtf_Table_Cell(m_table,m_rowIndex,columnIndex);
        m_cells.push_back(cell); //TODO
    }
    else{
        cell = m_cells[columnIndex - 1];
    }
    return cell;
}

void CppRtf_Table_Row::setFont(CppRtf_Font *font)
{
    vector<CppRtf_Table_Column *> columns = m_table->getColumns();
    for(vector<CppRtf_Table_Column *>::iterator it = columns.begin(); it!= columns.end(); it++){
        CppRtf_Table_Column* column = *it;
        CppRtf_Table_Cell* cell = m_table->getCell(m_rowIndex, column->getColumnIndex());
        cell->setFont(font);
    }
}

int CppRtf_Table_Row::getRowIndex()
{
    return m_rowIndex;
}
