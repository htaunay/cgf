#include <stdio.h>
#include <string>
#include <vector>

#include <CornerTable.h>

void printOutput(std::string fileName, std::vector<int> table)
{
    fileName = fileName + ".output";
    FILE * file = fopen(fileName.c_str(), "w+");

    for(unsigned int i = 0; i < table.size(); i++)
        fprintf(file, "%d ", table[i]);

    fprintf(file, "\n ");
    fclose(file);
}

int main(int argc, char** argv)
{
    if(argc !=3 )
    {
        printf("Please inform two params: [-corner|-che] <filename>\n");
        return 0;
    }

    std::string mode(argv[1]);
    std::string fileName(argv[2]);

    std::vector<int> table;
   
    if(mode.compare("-corner") == 0)
    {
        table = CornerTable::BuildCornerTable(fileName);
    }
    else if(mode.compare("-che") == 0)
    {
        table = CornerTable::BuildCHE(fileName);
    }
    else
    {
        printf("Invalid option: %s. Try '-corner' or '-che'\n", mode.c_str());
        return 0;
    }
 
    printOutput(fileName, table);
    return 1;
}
