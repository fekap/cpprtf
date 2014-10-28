#ifndef NOTE_H
#define NOTE_H
#include <string>

using namespace std;

//class for doucment head definition for footnotes and endnotes
class CppRtf_DocHead_Note
{
public:
    CppRtf_DocHead_Note();

    //sets footnote numbering type
    void setFootnoteNumberingType(int numberingType);

    //gets footnote numbering type
    int getFootnoteNumberingType();

    //sets endnote numbering type
    void setEndnoteNumberingType(int numberingType);

    //gets endnote numbering type
    int getEndnoteNumberingType();

    //sets footnote start number
    void setFootnoteStartNumber(int startNumber);

    //gets footnote start number
    int getFootnoteStartNumber();

    //sets endnote start number
    void setEndnoteStartNumber(int startNumber);

    //gets endnote start number
    int getEndnoteStartNumber();

    //sets restart footnote number on each page
    void setRestartFootnoteNumberEachPage(bool restart=true);

    //checks, if footnote numbering shall be started on each page
    bool isRestartFootnoteNumberEachPage();

    //sets restart endnote number on each page
    void setRestartEndnoteNumberEachPage(bool restart=true);

    //checks, if endnote numbering shall be started on each page
    bool isRestartEndnoteNumberEachPage();

    //gets numbering type for notes
    static string getNumberingTypeAsRtf(int numbering, string prefix = "\\ftnn");

    //renders document definition head for footnotes/endnotes
    string getContent();

protected:
    //footnote type
    int m_footnoteNumberingType;

    //endnote type
    int m_endnoteNumberingType;

    //flag for restarting footnote numbering on each page
    bool m_footnoteRestartEachPage;

    //flag for restarting endnote numbering on each page
    bool m_endnoteRestartEachPage;

    //start number for footnotes
    int m_footnoteStartNumber;

    //start number for endnotes
    int m_endnoteStartNumber;
};

#endif // NOTE_H
