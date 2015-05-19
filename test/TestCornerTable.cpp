#include <string>
#include <vector>

#include <CornerTable.h>

std::vector<int> LoadResults(std::string fileName, int numElements)
{
	FILE * file = fopen(fileName.c_str(), "r");

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
    std::vector<int> table = CornerTable::BuildOpposites(CornerTable::Corner,
            "./test/input/" + fileName + ".txt");
    std::vector<int> results =
    LoadResults("./test/results/corner_" + fileName + ".txt", table.size());

    for(unsigned int i = 0; i < results.size(); i++)
    {
        if(table[i] != results[i])
        {
            for(unsigned int i = 0; i < results.size(); i++)
                printf("%d ", results[i]);
            printf("\n");

            return false;
        }
    }

    return true;
}

int main(void)
{
    int passed = 0;
    int failed = 0;
    
    (TestFile("triangle"))  ? passed++ : failed++;
    (TestFile("hexagon"))   ? passed++ : failed++;
    (TestFile("icosaedro")) ? passed++ : failed++;
    (TestFile("domo"))      ? passed++ : failed++;

    printf("%d tests passed, %d tests failed\n", passed, failed);

    return 1;
}
