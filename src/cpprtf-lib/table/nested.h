#ifndef NESTED_H
#define NESTED_H
#include "table.h"

// Class for creating cells of table in rtf documents.
class CppRtf_Table_Nested : public CppRtf_Table
{
public:
    CppRtf_Table_Nested(CppRtf_Container *container, TableAligment alignment = CppRtf_Table::ALIGN_LEFT, int nestDepth = 1);

    //renders nested table
    void render()
    {
        if (m_rows.empty()|| m_columns.empty()) {
            return;
        }
        for(vector<CppRtf_Table_Row*>::iterator it = m_rows.begin();it!=m_rows.end();it++){
            renderRowCells(*it);
        }
      }
};

#endif // NESTED_H
