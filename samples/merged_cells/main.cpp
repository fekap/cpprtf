#include <CppRtf>

int main()
{
    CppRtf rtf;
    CppRtf_Container_Section* sect = rtf.addSection();

    CppRtf_Table* table = sect->addTable();
    CppRtf_Font font;
    CppRtf_ParFormat parFormat;

    table->addRows(5, 0.75);
    vector<float> widths; widths.push_back(3); widths.push_back(3); widths.push_back(3); widths.push_back(3); widths.push_back(3);
    table->addColumnsList(widths);

    table->mergeCellRange(1, 1, 3, 1);
    table->writeToCell(1, 1, "Vertical merged cells.", &font, &parFormat);
    CppRtf_Border* border = CppRtf_Border::create(&rtf, 1, "#ff0000");
    table->setBorderForCellRange(border, 1, 1, 3, 1);

    table->mergeCellRange(1, 3, 1, 5);
    table->writeToCell(1, 3, "Horizontal merged cells", &font, &parFormat);
    delete border;
    border = CppRtf_Border::create(&rtf, 1, "#0000ff");
    table->setBorderForCellRange(border, 1, 3, 1, 5);

    table->mergeCellRange(3, 3, 5, 5);
    table->writeToCell(3, 3, "Horizontal and vertical merged cells", &font, &parFormat);
    delete border;
    border = CppRtf_Border::create(&rtf, 1, "#00ff00");
    table->setBorderForCellRange(border, 3, 3, 5, 5);

    // save rtf document
    rtf.save("merged_cells.rtf");

    delete border;
}

