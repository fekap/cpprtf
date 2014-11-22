#include <CppRtf>
#include <container/section.h>

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
    //Rtf document
    CppRtf rtf;

    //Font
    CppRtf_Font times12(12, "Times new Roman");

    //Section
    CppRtf_Container_Section* sect = rtf.addSection();
    //Write utf-8 encoded text+
    //Text is from file+ But you can use another resouce: db, sockets and other
    string path = string(SRC_PATH)+"sources/utf8.txt";
    sect->writeText(readFile(path), &times12);

    // save rft document
    rtf.save("utf8.rtf");

}

