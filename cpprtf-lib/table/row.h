#ifndef ROW_H
#define ROW_H
//#include "table.h"
#include <vector>
#include "font.h"

class CppRtf_Table;
class CppRtf_Table_Cell;

//Class for creating rows of table in rtf documents.
class CppRtf_Table_Row
{
public:
    CppRtf_Table_Row(CppRtf_Table* table,int rowIndex, float height = -100);
    ~CppRtf_Table_Row();

    void setHeight(float height); //sets row height

    float getHeight(); //gets row height

    CppRtf_Table_Cell * getCellByIndex(int columnIndex); //Gets cell instance for the given column index

    void setFont(CppRtf_Font* font); //sets default font for all cells in the row

    int getRowIndex(); //gets index of row

protected:
    CppRtf_Table* m_table;
    int m_rowIndex;//row index in table
    vector<CppRtf_Table_Cell*> m_cells;
    float m_height; //row height

};

#endif // ROW_H
