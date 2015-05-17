#include <string>
#include <vector>

#include <CornerTable.h>

std::vector<int> LoadResults(std::string fileName, int numElements)
{
	FILE * file;
	file = fopen(fileName.c_str(), "r");

    int element;
    std::vector<int> results;
	for(int i = 0; i < numElements; i++)
	{
		fscanf(file, "%d", &element);
        results.push_back(element);
	}

	fclose(file);
    return results;
}

bool TestFile(std::string fileName)
{
    std::vector<int> table = CornerTable::BuildCornerTable(
            "./test/input/" + fileName + ".txt");
    std::vector<int> results =
    LoadResults("./test/results/" + fileName + "_result.txt", table.size());

    for(unsigned int i = 0; i < results.size(); i++)
        if(table[i] != results[i])
            return false;

    return true;
}

int main(void)
{
    if(TestFile("triangle"))
        printf("All test passed!\n");
    else 
        printf("Test failed...\n");
}
