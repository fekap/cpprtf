#ifndef COLUMN_H
#define COLUMN_H
//#include "table.h"
#include "font.h"

// Class for creating columns of table in rtf documents.
class CppRtf_Table;
class CppRtf_Table_Column
{
public:
    CppRtf_Table_Column(CppRtf_Table* table,int columnIndex, float width);

    void setWidth(float width); //sets column width

    float getWidth(); //gets column width

    int getColumnIndex(); //gets column index

    void setFont(CppRtf_Font* font); //sets default font for all cells in the row

    //////////////
protected:
    float m_width; //column width
    CppRtf_Table* m_table; //table
    int m_columnIndex; //column index

};

#endif // COLUMN_H
