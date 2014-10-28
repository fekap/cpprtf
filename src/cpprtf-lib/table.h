#ifndef TABLE_H
#define TABLE_H
#include "container.h"
#include "table/row.h"
#include "table/column.h"
#include "table/cell.h"
#include "parformat.h"
#include "image.h"
#include "cpprtf.h"
#include "unit.h"

//class CppRtf_Table_Row;
class CppRtf_Table
{
public:

    //constants table alignment
    enum TableAligment{
        ALIGN_LEFT,
        ALIGN_CENTER,
        ALIGN_RIGHT
    };

    CppRtf_Table(CppRtf_Container_Base *container, TableAligment alignment = ALIGN_LEFT, int nestDepth = 1);

    //gets nested depth
    int getNestDepth();

    //checks, if table is a nested table
    bool isNestedTable();

    //gets rtf container instance
    CppRtf_Container_Base *getContainer();

    //gets rtf instance
    CppRtf* getRtf();

    //Sets that table won't be splited by a page break. By default page break splits table.
    void setPreventPageBreak();

    //returns true, if a table should not be splited by a page break
    bool isPreventPageBreak();

    //sets left position of table
    void setLeftPosition(float leftPosition);

    //gets left position of table
    float getLeftPosition();

    //Sets first row as header row. First row will be repeated at the top of each page.
    void setFirstRowAsHeader();
    //Returns true, if first row should be used as header
    bool isFirstRowHeader();

    //gets aligment
    CppRtf_Table::TableAligment getAligment();

    //prevents adding an empty paragraph after table
    void preventEmptyParagraph(bool value = true);

    //returns true, if no empty paragraph should be added after table
    bool getPreventEmptyParagraph();

    /*adds row
       *height: row height. When 0, the height is sufficient for all the text in the line;
       when positive, the height is guaranteed to be at least the specified height; when negative,
       the absolute value of the height is used, regardless of the height of the text in the line.    */
      CppRtf_Table_Row* addRow(float height = 0);

      //add rows
      void addRows(int rowCnt, float height = 0);

      //adds list of rows to a table.
      void addRowList(vector<float> heights);

      //gets number of rows in table
      int getRowsCount();

      //gets table rows
      vector<CppRtf_Table_Row*> getRows();

      //gets row instance
      CppRtf_Table_Row* getRow(int rowIndex);

      //adds column
      CppRtf_Table_Column* addColumn(float width);

      //gets number of columns in table
      int getColumnsCount();

      //gets table columns
      vector<CppRtf_Table_Column*>getColumns();

      //gets column
      CppRtf_Table_Column* getColumn(int columnIndex);

      //adds list of columns
      void addColumnsList(vector<float> widths);

      //returns true, if rowIndex and columnIndex do exists in table
      bool checkIfCellExists(int rowIndex,int columnIndex);

      //gets the instance of cell
      CppRtf_Table_Cell* getCell(int rowIndex,int columnIndex);

      /* writes text to cell
          * rowIndex           row index of cell
          * columnIndex        column index of cell
          * text               Text. Also you can use html style tags. @see PHPRtfLite_Container#writeText()
          * font               Font of text
          * parFormat          Paragraph format
          * convertTagsToRtf   If false, then html style tags are not replaced with rtf code.
          */
      CppRtf_Element* writeToCell(int rowIndex, int columnIndex, string text, CppRtf_Font* font = 0, CppRtf_ParFormat *parFormat = 0, bool convertTagsToRtf = true);

      /* adds image to cell
           * rowIndex       row index of cell
           * columnIndex    column index of cell
           * file           image file.
           * parFormat      paragraph format
           * width          if null image is displayed by it's original height.
           * height         if null image is displayed by it's original width. If boths parameters are null, image is displayed as it is.
           *
           * imageString    image source code
           * type           image type (GD, WMF) //TODO: добавить больше типов
           */
      CppRtf_Image* addImageToCell(int rowIndex, int columnIndex, string file, CppRtf_ParFormat* parFormat = 0, float width = -1, float height =-1);
      CppRtf_Image* addImageFromStringToCell(int rowIndex, int columnIndex, string imageString, string type, CppRtf_ParFormat* parFormat = 0, float width = -1, float height = -1);

      //corrects cell range to be valid
      static vector<int> getValidCellRange(int startRow, int startColumn, int endRow, int endColumn);

      vector<CppRtf_Table_Cell*> getCellsByCellRange(int startRow, int startColumn, int endRow, int endColumn);

      /* sets vertical alignment to cells of a given cell range
           *
           * @param   string  $verticalAlignment Vertical alignment of cell (default top). Represented by PHPRtfLite_Container::VERTICAL_ALIGN_*<br>
           *   Possible values:<br>
           *     CppRtf_Container::VERTICAL_ALIGN_TOP     => 'top'    - top alignment;<br>
           *     CppRtf_Container::VERTICAL_ALIGN_CENTER  => 'center' - center alignment;<br>
           *     CppRtf_Container::VERTICAL_ALIGN_BOTTOM  => 'bottom' - bottom alignment.
           * startRow       start row
           * startColumn    start column
           * endRow         end row, if null, then vertical alignment is set only to the row range.
           * endColumn      end column, if null, then vertical alignment is set just to the column range.
           */
      void setVerticalAlignmentForCellRange(CppRtf_Table_Cell::VerticalAligment verticalAlignment, int startRow, int startColumn, int endRow = -1, int endColumn = -1);


      /* sets alignments to empty cells of a given cell range
       * alignment      alignment of cell. The method CppRtf_Table_Cell->writeToCell() overrides it with CppRtf_ParFormat alignment.<br>
       *   Alignment is represented by class constants CppRtf_Container::TEXT_ALIGN_*<br>
       *   Possible values:<br>
       *     CppRtf_Container::TEXT_ALIGN_LEFT    => 'left'   - left alignment<br>
       *     CppRtf_Container::TEXT_ALIGN_RIGHT   => 'right'  - right alignment<br>
       *     CppRtf_Container::TEXT_ALIGN_CENTER  => 'center' - center alignment<br>
       *     CppRtf_Container::TEXT_ALIGN_JUSTIFY => 'justify' - justify alignment
       */
      void setTextAlignmentForCellRange(CppRtf_Table_Cell::TextAligment alignment, int startRow, int startColumn, int endRow = -1, int endColumn = -1);

      /* sets font to empty cells of a given cell range
           * font           font for empty cells. The method PHPRtfLite_Table_Cell->writeToCell() overrides it with another PHPRtfLite_Font.
           * startRow       start row
           * startColumn    start column
           * endRow         end row, if null, then font is set only to the row range.
           * endColumn      end column, if null, then font is set just to the column range.
           */
      void setFontForCellRange(CppRtf_Font* font, int startRow, int startColumn,  int endRow = -1, int endColumn = -1);

      /* rotates cells of a given cell range
           * rotateTo       direction of rotation<br>
           *   Possible values (represented by CppRtf_Table_Cell::ROTATE_*):<br>
           *     CppRtf_Table_Cell::ROTATE_RIGHT  => 'right'<br>
           *     CppRtf_Table_Cell::ROTATE_LEFT   => 'left'
           * startRow       start row
           * startColumn    start column
           * endRow         end row, if null, then rotation is set only to the row range.
           * endColumn      end column, if null, then rotation is set just to the column range.
           */
      void rotateCellRange(CppRtf_Table_Cell::RotationDirections rotateTo,int startRow, int startColumn,  int endRow = -1, int endColumn = -1);

      //sets background color of cells of a given cell range
      void setBackgroundForCellRange(string  backgroundColor,int startRow, int startColumn,  int endRow = -1, int endColumn = -1);

      //sets border to cells of a given cell range
      void setBorderForCellRange(CppRtf_Border*  border,int startRow, int startColumn,  int endRow = -1, int endColumn = -1);

      //merges cells of a given cell range
      void mergeCellRange(int startRow, int startColumn,  int endRow, int endColumn);

      //writes rtf code for table
      void render();

      //renders row definition
      void renderRowDefinition(CppRtf_Table_Row* row);

      //renders row cells
      void renderRowCells(CppRtf_Table_Row* row);



protected:
    CppRtf_Container_Base* m_container;
    vector<CppRtf_Table_Row*> m_rows;
    vector<CppRtf_Table_Column*> m_columns;
    TableAligment m_aligment;
    /*
     * nest depth
     * 0: main document
     * 1: table cell
     * 2: nested table cell
     * 3: double nested table cell
     * 4: three times nested table cell
     * .. and so on ..
     */
    int m_nestDepth;
    bool m_preventPageBreak;
    bool m_firstRowIsHeader;
    bool m_repeatFirstRowHeader;
    int m_leftPosition;
    bool m_preventEmptyParagraph; //flag for preventing an empty paragraph after table

};

#endif // TABLE_H
