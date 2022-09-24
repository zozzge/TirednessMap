#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string RemoveFirstAndLastSpaces(string inStr)
{
    if (inStr.size() > 0)
    {
        if (inStr[0] == ' ')
            inStr.erase(0, 1);
        if (inStr[inStr.size() - 1] == ' ')
            inStr.erase(inStr.size() - 1, 1);
    }

    return inStr;
}

int CalculateWordCount(string inStr)
{
    int wordCount = 0;

    if (inStr.size() > 0)
    {
        //All strings has at least one word
        wordCount = 1;

        for (int i = 0; i < inStr.size(); i++) {
            if (inStr[i] == ' ' && i != inStr.size() - 1)
            {
                wordCount++;
            }
        }
    }

    return wordCount;
}

string ExtractWord(string inStr, int pos)
{
    string word = "";
    int wordCount = 0;

    for (int i = 0; i < inStr.size(); i++) {
        if (inStr[i] != ' ')
        {
            word += inStr[i];
        }
        else {
            wordCount++;
            if (wordCount == pos)
            {
                return word;
            }
            else {
                word = "";
            }
        }
    }
    return word;
}

void ResetAllCells(int inFieldMap[40][40])
{
    for (int x = 0; x < 40; x++)
    {
        for (int y = 0; y < 40; y++)
        {
            inFieldMap[x][y] = 0;
        }
    }
}

void CopyAllTirednessCells(int inSourcFieldMap[40][40], int inTargetFieldMap[40][40])
{
    for (int x = 0; x < 40; x++)
    {
        for (int y = 0; y < 40; y++)
        {
            if (inSourcFieldMap[x][y] > 0)
            {
                inTargetFieldMap[x][y] += inSourcFieldMap[x][y];
            }
            else {
                if (inTargetFieldMap[x][y] > 0)
                    inTargetFieldMap[x][y]--;
            }
        }
    }
}


int main()
{
    string dataFilename = "C:\\Users\\FinallyFree\\source\\repos\\FieldTirednessMap\\FieldTirednessMap\\x64\\Debug\\fieldinfo2.txt";
    string dataLine;

    ifstream dataFile(dataFilename);

    if (!dataFile.good())
    {
        cout << "Data file cannot be found!";
        exit(1);
    }

    int fieldWidth = 0;
    int fieldHeight = 0;

    if (getline(dataFile, dataLine))
    {
        dataLine = RemoveFirstAndLastSpaces(dataLine);

        if (CalculateWordCount(dataLine) != 2)
        {
            cout << "Field size cannot be found in data file!";
            exit(1);
        }

        fieldWidth = stoi(ExtractWord(dataLine, 1));
        fieldHeight = stoi(ExtractWord(dataLine, 2));
    }

    int plantingYear = 0;
    int plantingCount = 0;
    int fieldMap[40][40];

    ResetAllCells(fieldMap);

    while (getline(dataFile, dataLine)) {

        dataLine = RemoveFirstAndLastSpaces(dataLine);

        if (CalculateWordCount(dataLine) != 2)
        {
            cout << "Planting year and count cannot be found in data file!";
            exit(1);
        }

        plantingYear = stoi(ExtractWord(dataLine, 1));
        plantingCount = stoi(ExtractWord(dataLine, 2));

        int startXCoord = 0;
        int startYCoord = 0;
        int endXCoord = 0;
        int endYCoord = 0;
        int newFieldMap[40][40];

        ResetAllCells(newFieldMap);

        for (int i = 0; i < plantingCount; i++)
        {
            getline(dataFile, dataLine);
            dataLine = RemoveFirstAndLastSpaces(dataLine);

            if (CalculateWordCount(dataLine) != 4)
            {
                cout << "Planting coordinates cannot be found in data file!";
                exit(1);
            }

            startXCoord = stoi(ExtractWord(dataLine, 1));
            startYCoord = stoi(ExtractWord(dataLine, 2));
            endXCoord = stoi(ExtractWord(dataLine, 3));
            endYCoord = stoi(ExtractWord(dataLine, 4));

            //Increase field map cells.
            for (int x = startXCoord; x <= endXCoord; x++)
            {
                for (int y = startYCoord; y <= endYCoord; y++)
                {
                    if (newFieldMap[x][y] == 0)
                    {
                        newFieldMap[x][y]++;
                    }
                    else {
                        cout << "No plantings given for the same year can overlap with one another!";
                        exit(1);
                    }
                }
            }
        }

        CopyAllTirednessCells(newFieldMap, fieldMap);
    }

    //print out field map.
    for (int y = 0; y < fieldHeight; y++)
    {
        for (int x = 0; x < fieldWidth; x++)
        {
            cout << fieldMap[x][y] << "  ";
        }

        cout << endl;
    }

    dataFile.close();



}
