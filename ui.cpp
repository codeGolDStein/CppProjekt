#include "ui.hpp"

//Soll die Api Response mit Zeilenumbrüchen zurückgeben 
void prettyResponse(string response)
{
    string formattedString = response;

    size_t pos = formattedString.find('\n');
    while (pos != string::npos)
    {
        formattedString.replace(pos, 1, "\n");
        pos = formattedString.find('\n', pos + 1);
    }

    cout << formattedString << endl;
}


void printDir(Directory dir)
{

    // Ausgabe aller Files sortiert nach ihrem Typen/Endung:

    cout << "Dateien: \n"
         << endl;

    for (const auto filetype : dir.getSortedByType().first)
    {

        if (filetype.first == "")
        {
            cout << "\t"
                 << "Andere: \n"
                 << endl;
        }
        else
        {
            //             z.b. hpp:
            cout << "\t" << filetype.first << ": \n"
                 << endl;
        }

        for (const FileEntry entry : filetype.second)
        {
            //        z.b.   complex
            cout << "\t\t" << entry.name << endl;
        };

        cout << "\n"
             << endl;
    };

    // Ausgabe aller Ordner:

    cout << "Ordner: \n " << endl;

    if (dir.getSortedByType().second.size() == 0)
    {
        cout << " \t keine \n"
             << endl;
    }
    else
    {
        for (const FileEntry dir : dir.getSortedByType().second)
        {
            //            Ordnername
            cout << dir.name << "\n"
                 << endl;
        };
    }
};

