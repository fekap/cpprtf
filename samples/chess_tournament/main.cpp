#include <CppRtf>
#include <container/section.h>
#include <table.h>

using namespace std;

int main()
{

    //Font formats
    CppRtf_Font font1(11, "Times new Roman", "#000055");
    CppRtf_Font font2(11, "Times new Roman", "#7A2900");
    CppRtf_Font fontArial(14, "Arial");

    //Rtf document
    CppRtf rtf;

    //section
    CppRtf_Container_Section* sect = rtf.addSection();
    CppRtf_ParFormat *parFormat = new CppRtf_ParFormat();
    sect->writeText("Chess tournamet information (write your data)\n", &fontArial, parFormat);

    vector<string>chessPlayers; chessPlayers.push_back("Mike Smith"); chessPlayers.push_back("Jim Morgan");
    chessPlayers.push_back("Jochgan Berg"); chessPlayers.push_back("Bill Scott"); chessPlayers.push_back("Bill Martines"); chessPlayers.push_back("John Po");
    chessPlayers.push_back("Aleck Harrison"); chessPlayers.push_back("Ann Scott"); chessPlayers.push_back("Johnatan Fredericson"); chessPlayers.push_back("Eva Carter");

    int count = chessPlayers.size();
    int countCols = count + 2;
    int countRows = count + 1;

    float colWidth = (sect->getLayoutWidth() - 5) / count;

    //table creating and rows ands columns adding
    CppRtf_Table* table = sect->addTable();
    table->addRows(1, 2);
    table->addRows(count, -0.6);

    table->addColumn(3);
    for (int i = 1; i <= count; i ++) {
        table->addColumn(colWidth);
    }
    table->addColumn(2);

    //borders
    CppRtf_Border* border = CppRtf_Border::create(&rtf, 1, "#555555");
    table->setBorderForCellRange(border, 1, 1, countRows, countCols);

    //top row
    table->rotateCellRange(CppRtf_Table_Cell::ROTATE_RIGHT, 1, 2, 1, countCols - 1);
    table->setVerticalAlignmentForCellRange(CppRtf_Table_Cell::VERTICAL_ALIGN_CENTER, 1, 2, 1, countCols);

    delete border;
    int i = 2;
    for (vector<string>::iterator it = chessPlayers.begin();it!=chessPlayers.end();it++) {
        string player = *it;
        delete parFormat;
        parFormat = new CppRtf_ParFormat();
        table->writeToCell(1, i, player, &font1);
        table->writeToCell(i, 1, player, &font1, parFormat, false);
        border = CppRtf_Border::create(&rtf, 1, "#0000ff");
        table->setBorderForCellRange(border, i, i);
        table->setBackgroundForCellRange("#dddddd", i, i);
        i++;
        delete border;
    }

    CppRtf_Font fontBold(11, "Times new Roman", "#7A2900");
    fontBold.setBold();

    table->setTextAlignmentForCellRange(CppRtf_Table_Cell::TEXT_ALIGN_CENTER, 2, 2, countRows, countCols);
    table->setFontForCellRange(&font2, 2, 2, countRows, countCols - 1);
    table->setFontForCellRange(&fontBold, 2, countCols, countRows);

    delete parFormat;
    parFormat = new CppRtf_ParFormat(CppRtf_ParFormat::TEXT_ALIGN_CENTER);
    table->writeToCell(1, countCols, "TOTAL", &font1, parFormat);

    border = CppRtf_Border::create(&rtf, 1.5, "#000000");
    table->setBorderForCellRange(border, 1, countCols, countRows, countCols);
    CppRtf_Border_Format* borderFormat = new CppRtf_Border_Format(1, "#0000ff", CppRtf_Border_Format::TYPE_DASH);
    delete border;
    border = new CppRtf_Border(&rtf,0,0,0, borderFormat);
    delete borderFormat;
    //Registry::debug = true;
    table->setBorderForCellRange(border, 2, countCols, countRows - 1, countCols);

    delete parFormat;
    parFormat = new CppRtf_ParFormat();

    sect->writeText("Chess tournamet play-offs (write your data)\n", &fontArial, parFormat);
    delete parFormat;

    int countSmall = 5;
    int countLarge = 6;

    float smallWidth = 0.75;
    float bigWidth = (sect->getLayoutWidth() - countSmall * smallWidth) / countLarge;

    table = sect->addTable();
    table->addRows(16, -0.5);
    vector<float> widths;widths.push_back(smallWidth);widths.push_back(bigWidth);widths.push_back(bigWidth);
    widths.push_back(smallWidth);widths.push_back(smallWidth);widths.push_back(bigWidth);widths.push_back(bigWidth);
    widths.push_back(smallWidth);widths.push_back(smallWidth);widths.push_back(bigWidth);widths.push_back(bigWidth);
    table->addColumnsList(widths);

    table->setTextAlignmentForCellRange(CppRtf_Table_Cell::TEXT_ALIGN_CENTER, 1, 1, 16, 11);
    table->setFontForCellRange(&font2, 1, 1, 16, 11);

    delete border;
    border = CppRtf_Border::create(&rtf, 1);
    table->setBorderForCellRange(border, 2, 1, 3, 3);
    table->setBorderForCellRange(border, 10, 1, 11, 3);
    table->setBorderForCellRange(border, 14, 1, 15, 3);
    table->setBorderForCellRange(border, 6, 1, 7, 3);

    table->setBorderForCellRange(border, 4, 5, 5, 7);
    table->setBorderForCellRange(border, 12, 5, 13, 7);

    table->setBorderForCellRange(border, 8, 9, 9, 11);
    table->setBorderForCellRange(border, 14, 9, 15, 11);

    table->setBorderForCellRange(border, 1, 10, 3, 11);

    table->writeToCell(2, 1, "P1", &font1,0);
    table->writeToCell(3, 1, "P8", &font1, 0);
    table->writeToCell(6, 1, "P2", &font1, 0);
    table->writeToCell(7, 1, "P7", &font1, 0);
    table->writeToCell(10, 1, "P3", &font1, 0);
    table->writeToCell(11, 1, "P6", &font1, 0);
    table->writeToCell(14, 1, "P4", &font1, 0);
    table->writeToCell(15, 1, "P5", &font1, 0);

    table->writeToCell(1, 1, "A1", &font1, 0);
    table->writeToCell(5, 1, "A2", &font1, 0);
    table->writeToCell(9, 1, "A3", &font1, 0);
    table->writeToCell(13, 1, "A4", &font1, 0);

    table->writeToCell(3, 5, "B1", &font1, 0);
    table->writeToCell(4, 5, "A1", &font1, 0);
    table->writeToCell(5, 5, "A2", &font1, 0);

    table->writeToCell(11, 5, "B2", &font1, 0);
    table->writeToCell(12, 5, "A3", &font1, 0);
    table->writeToCell(13, 5, "A4", &font1, 0);

    table->writeToCell(7, 10, "1-st place", &font1, 0);
    table->writeToCell(8, 9, "B1", &font1, 0);
    table->writeToCell(9, 9, "B2", &font1, 0);

    table->writeToCell(13, 10, "3-d place", &font1, 0);
    table->writeToCell(14, 9, "B1", &font1, 0);
    table->writeToCell(15, 9, "B2", &font1, 0);


    table->setBackgroundForCellRange("#ffff88", 1, 10, 1, 11);
    table->setBackgroundForCellRange("#cccccc", 2, 10, 2, 11);
    table->setBackgroundForCellRange("#ffAA66", 3, 10, 3, 11);


    table->writeToCell(1, 10, "1-st place", &font1, 0);
    table->writeToCell(2, 10, "2-st place", &font1, 0);
    table->writeToCell(3, 10, "3-d place", &font1, 0);



    // save rtf document
    rtf.save("chess_tournament.rtf");
    delete border;
    return 0;
}

