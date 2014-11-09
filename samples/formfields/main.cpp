#include <CppRtf>

int main()
{
    CppRtf* rtf = new CppRtf();

    CppRtf_Container_Section* sect = rtf->addSection();
    CppRtf_Table*table = sect->addTable();
    table->addRows(1, 1);
    table->addRows(1, 2);
    vector<float> widths; widths.push_back(5); widths.push_back(5); widths.push_back(5);
    table->addColumnsList(widths);


    CppRtf_Table_Cell* cell = table->getCell(1, 1);
    cell->writeText("<b>Checkbox</b>");

    cell = table->getCell(2, 1);
    CppRtf_Font* fontCheckbox = new CppRtf_Font(20, "Arial", "#cc3333", "#8888cc");
    CppRtf_FormField_Checkbox* checkbox = cell->addCheckbox(fontCheckbox);
    cell->writeText("red checkbox with blue background");
    cell->addEmptyParagraph();

    checkbox = cell->addCheckbox();
    checkbox->setChecked();
    cell->writeText("checked checkbox");
    cell->addEmptyParagraph();

    checkbox = cell->addCheckbox();
    checkbox->setChecked();
    checkbox->setSize(40);
    cell->writeText("big checked checkbox");


    cell = table->getCell(1, 2);
    cell->writeText("<b>Dropdown</b>");

    cell = table->getCell(2, 2);
    cell->writeText("dropdown labels");
    CppRtf_Font* fontDropdown = new CppRtf_Font(12, "Arial", "#cc3333", "#cccccc");
    CppRtf_FormField_Dropdown* dropdown = cell->addDropdown(fontDropdown);
    dropdown->addItem("Хороший день");
    dropdown->addItem("अच्छा दिन");
    dropdown->addItem("Buenos días");
    dropdown->addItem("Guten Tag");
    dropdown->setDefaultValue("Guten Tag");


    cell = table->getCell(1, 3);
    cell->writeText("<b>Textfeld</b>");

    cell = table->getCell(2, 3);
    cell->writeText("textfield label");
    CppRtf_Font* fontTextfield = new CppRtf_Font(12, "Arial", "#cc3333", "#cceecc");
    CppRtf_FormField_Text* textfield = cell->addTextField(fontTextfield);
    textfield->setDefaultValue("Lorem ipsum.");


    // save rtf document
    rtf->save("formfields.rtf");
}

