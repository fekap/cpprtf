#ifndef CELL_H
#define CELL_H
#include "container.h"
//#include "table/nested.h"
//#include "table.h"
#include "font.h"
#include "border.h"

class CppRtf_Table;
class CppRtf_Table_Nested;
// Class for creating cells of table in rtf documents.
class CppRtf_Table_Cell:public CppRtf_Container
{
public:
    enum RotationDirections{ //constants for rotation directions
        ROTATE_NULL,
        ROTATE_RIGHT,
        ROTATE_LEFT
    };

    enum TextAligment{ //constants for text alignment
        TEXT_ALIGN_NULL,
        TEXT_ALIGN_LEFT,
        TEXT_ALIGN_RIGHT,
        TEXT_ALIGN_CENTER,
        TEXT_ALIGN_JUSTIFY
    };

    enum VerticalAligment{ //constants for vertical alignment
        VERTICAL_ALIGN_NULL,
        VERTICAL_ALIGN_TOP,
        VERTICAL_ALIGN_BOTTOM,
        VERTICAL_ALIGN_CENTER
    };
    /*
     * table: table instance
     * rowIndex: row index for cell in table
     * columnIndex: column index for cell in TABLE_H */
    CppRtf_Table_Cell(CppRtf_Table* table,int rowIndex, int columnIndex);

    ~CppRtf_Table_Cell();

    CppRtf_Table_Nested* addTable(TextAligment alignment = TEXT_ALIGN_LEFT); //adds nested table

    CppRtf_Table* getTable();//gets table instance
    
    /* sets text alignment for cell
         * The method CppRtf_Table->writeToCell() overrides it with alignment of an instance ofCppRtf_ParFormat.
         *   Possible values:<br>
         *     TEXT_ALIGN_LEFT       - left alignment<br>
         *     TEXT_ALIGN_CENTER     - center alignment<br>
         *     TEXT_ALIGN_RIGHT      - right alignment<br>
         *     TEXT_ALIGN_JUSTIFY    - justify alignment */
    
    void setTextAlignment(TextAligment alignment);
    
    //gets text alignment for cell
    TextAligment getTextAligment();
    
    /* sets font to a cell
         * The method PHPRtfLite_Table->writeToCell() overrides it with another Font.*/
    void setFont(CppRtf_Font* font);
    
    //gets font of cell
    CppRtf_Font* getFont();
    
    /* sets vertical alignment of cell (default top)
         *  Possible values:<br>
         *     VERTICAL_ALIGN_TOP        - top alignment<br>
         *     VERTICAL_ALIGN_CENTER     - center alignment<br>
         *     VERTICAL_ALIGN_BOTTOM     - bottom alignment
         */
    void setVerticalAlignment(VerticalAligment verticalAlignment);
    
    //gets vertical alignment of cell
    VerticalAligment getVerticalAlignment();
    
    //rotates text of cell
    void rotateTo(RotationDirections rotateTo);
    
    //gets rotation direction of cell
    RotationDirections getRotateTo();

    //sets background color
    void setBackgroundColor(string color);

    //gets background color
    string getBackgroundColor();

    //sets that cell is horizontal merged
    void setHorizontalMerged();

    //returns true, if cell is horizontal merged
    bool isHorizontalMerged();

    //sets that cell is vertical merged
    void setVerticalMerged();

    //returns true, if cell is horizontal merged
    bool isVerticalMerged();

    //sets vertical merge start
    void setVerticalMergeStart();

    //checks, if cell is first cell of a vertical cell range merge
    bool isVerticalMergedFirstInRange();

    //sets cell width
    void setWidth(float width);

    //gets cell width
    float getWidth();

    //sets cell border
    void setCellBorder(CppRtf_Border* border);

    //gets cell border
    CppRtf_Border* getBorder();

    //sets border to a cell
    void setBorder(CppRtf_Border* border);

    //gets row index of cell
    int getRowIndex();

    //gets column index of cell
    int getColumnIndex();

    //sets cell paddings
    void setCellPaddings(int paddingLeft, int paddingTop, int paddingRight, int paddingBottom);
    void setPaddingLeft(int padding);
    void setPaddingRight(int padding);
    void setPaddingTop(int padding);
    void setPaddingBottom(int padding);

    //renders cell definition
    void renderDefinition();

    //renders rtf code for cell
    void render();

    //gets cell alignment
    string getCellAlignment();


protected:
    CppRtf_Table* m_table;
    int m_rowIndex; //row index within the table
    int m_columnIndex; //column index within the table
    TextAligment m_alignment; //horizontal alignment
    VerticalAligment m_verticalAlignment; //vertical alignment
    CppRtf_Font* m_font; //font used for the cell
    RotationDirections m_rotateTo; //rotation direction
    string m_backgroundColor; //background color of the cell
    CppRtf_Border* m_border; //border of the cell
    bool m_horizontalMerged; //true, if cell is merged horizontally
    bool m_verticalMerged; //true, if cell is merged vertically
    bool m_verticalMergeStart; //ture, if cell merge starts with this cel
    float m_width;//width of cell
    float m_paddingLeft;//cell padding left
    float m_paddingRight;//cell padding right
    float m_paddingTop;//cell padding top
    float m_paddingBottom;//cell padding bottom

    //gets border for specific cell
    CppRtf_Border* getBorderForCell(int rowIndex, int columnIndex);
};

#endif // CELL_H


