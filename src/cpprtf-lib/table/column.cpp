#include "column.h"
#include "table.h"

CppRtf_Table_Column::CppRtf_Table_Column(CppRtf_Table *table, int columnIndex, float width)
    :m_width(width),m_table(table),m_columnIndex(columnIndex)
{
}

void CppRtf_Table_Column::setWidth(float width)
{
    m_width = width;
}

float CppRtf_Table_Column::getWidth()
{
    return m_width;
}

int CppRtf_Table_Column::getColumnIndex()
{
    return m_columnIndex;
}

void CppRtf_Table_Column::setFont(CppRtf_Font *font)
{
    vector<CppRtf_Table_Row *> rows = m_table->getRows();
    for(vector<CppRtf_Table_Row *>::iterator it = rows.begin();it!=rows.end();it++){
        CppRtf_Table_Row* row = *it;
        CppRtf_Table_Cell* cell = m_table->getCell(row->getRowIndex(), m_columnIndex);
        cell->setFont(font);
    }
}
