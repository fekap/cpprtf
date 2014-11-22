#include <CppRtf>
#include <container/section.h>

void writeSectionText(CppRtf_Container_Section* sect, CppRtf_Font* arial14, CppRtf_Font* times12, string text, string text2, string text3) {
    CppRtf_ParFormat parFormat;
    sect->writeText("Sample RTF document", arial14, &parFormat);
    sect->writeText(text, times12, &parFormat);

    sect->writeText("Character encoding", arial14, &parFormat);
    sect->writeText(text2, times12, &parFormat);

    sect->writeText("Common implementations", arial14, &parFormat);
    sect->writeText(text3, times12, &parFormat);
}

using namespace std;

string readFile(string fileName){
    FILE * pFile;
    char buffer [100];
    string res="";
    pFile = fopen(fileName.c_str() , "r");
    if (pFile == NULL) perror ("Error opening file");
    else
    {
        while ( ! feof (pFile) )
        {
            if ( fgets (buffer , 100 , pFile) == NULL ) break;
            fputs (buffer , stdout);
            res += buffer;
        }
        fclose (pFile);
    }
    return res;
}

int main()
{
    string source_path = string(SRC_PATH)+"document_sections/";
    string text1 = readFile(source_path+"text1");

    string text2=readFile(source_path+"text2");
    string text3=readFile(source_path+"text3");

    //
    CppRtf_Font times12(13, "Times new Roman");
    CppRtf_Font arial14(14, "Arial", "#000066");

    CppRtf_ParFormat parFormat;

    //rtf document
    CppRtf rtf;

    //borders
    CppRtf_Border_Format borderFormatBlue(1, "#0000ff");
    CppRtf_Border_Format borderFormatRed(2, "#ff0000");
    CppRtf_Border* border = new CppRtf_Border(&rtf, &borderFormatBlue, &borderFormatRed, &borderFormatBlue, &borderFormatRed);
    rtf.setBorder(border);
    rtf.setBorderSurroundsHeader();
    rtf.setBorderSurroundsFooter();

    //headers
    rtf.setOddEvenDifferent();

    CppRtf_Container_Header* header = rtf.addHeader(CppRtf_Container_Header::TYPE_LEFT);
    header->writeText("PHPRtfLite class library. Left document header. This is page - <pagenum> of <pagetotal> -", &times12, &parFormat);

    header = rtf.addHeader(CppRtf_Container_Header::TYPE_RIGHT);
    header->writeText("PHPRtfLite class library. Right document header. This is page - <pagenum> of <pagetotal> -", &times12, &parFormat);

//    //section 1
    CppRtf_Container_Section* sect = rtf.addSection();
    sect->setPaperHeight(16);
    sect->setPaperWidth(25);

    //Borders overridden: No Borders
    delete border;
    border = CppRtf_Border::create(&rtf, 0);
    sect->setBorder(border);
    sect->setSpaceBetweenColumns(1);
    sect->setNumberOfColumns(2);
    sect->setLineBetweenColumns();

    writeSectionText(sect, &arial14, &times12, text1, text2, text3);

    //section 2
    sect = rtf.addSection();
    sect->setBorderSurroundsHeader();
    sect->setBorderSurroundsFooter();

    //Header overridden
    header = sect->addHeader(CppRtf_Container_Header::TYPE_RIGHT);
    header->writeText("PHPRtfLite class library. Overriden right section header. This is page - <pagenum> of <pagetotal> -", &times12, &parFormat);
    header = sect->addHeader(CppRtf_Container_Header::TYPE_LEFT);
    header->writeText("PHPRtfLite class library. Overriden left section header. This is page - <pagenum> of <pagetotal> -", &times12, &parFormat);
    //Borders overridden: Green border
    delete border;
    border = CppRtf_Border::create(&rtf, 1, "#00ff00", CppRtf_Border_Format::TYPE_DASH,1);
    sect->setBorder(border);

    writeSectionText(sect, &arial14, &times12, text1, text2, text3);

    //section 3
    sect = rtf.addSection();
    vector<float> array;
    array.push_back(3);
    array.push_back(3);
    array.push_back(8);
    sect->setColumnWidths(array);
    //Border from rtf
    //....

    writeSectionText(sect, &arial14, &times12, text1, text2, text3);

    // save rtf document
    rtf.save("document_sections.rtf");

    delete border;
    return 0;
}

