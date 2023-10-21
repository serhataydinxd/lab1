#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>

void readFile(void);
void print(void);
void findBlobs(int a = 0, int b = 0);

using namespace std;
int row, column;
string fileName;
vector<vector<char>> arr;
vector<vector<char>> arrYedek;
vector<int> blobRow;
vector<int> blobColumn;
bool foundBlob = false;
struct blob
{
    int rowMin = NULL;
    int rowMax = NULL;
    int columnMin = NULL;
    int columnMax = NULL;
    int size = NULL;
    int COM = NULL;
};

int main(void)
{
    readFile();
    print();
    arrYedek = arr;
    findBlobs();
    return 0;
}

void readFile(void)
{
    cout << "Enter the file name: ";
    cin >> fileName;
    ifstream readonly(fileName, ios::in);
    readonly >> row >> column;
    arr.resize(row);
    for (int i = 0; i < row; i++)
    {
        arr[i].resize(column);
    }
    for (int c = 0; c < row; c++)
    {
        for (int d = 0; d < column; d++)
        {
            readonly >> noskipws >> arr[c][d];
            if (arr[c][d] == 10)
            {
                arr[c][d] = NULL;
                --d;
            }
        }
    }
}

void print(void)
{
    for (int c = 0; c < row; c++)
    {
        cout << "  ";
        for (int d = 0; d < column; d++)
        {
            cout << d % 10;
        }
        cout << endl
             << " +";
        for (int d = 0; d < column; d++)
        {
            cout << "-";
        }
        cout << "+" << endl;
        break;
    }
    for (int c = 0; c < row; c++)
    {
        cout << c % 10 << "|";
        for (int d = 0; d < column; d++)
        {
            cout << arr[c][d];
        }
        cout << "|" << c % 10 << endl;
    }
    for (int c = 0; c < row; c++)
    {
        cout << " +";
        for (int d = 0; d < column; d++)
        {
            cout << "-";
        }
        cout << "+" << endl;
        cout << "  ";
        for (int d = 0; d < column; d++)
        {
            cout << d % 10;
        }
        cout << endl;
        break;
    }
}

void findBlobs(int a, int b)
{
    if (foundBlob)
    {
        for (int i=a;i<row;i++){
            for (int j=b;j<column;j++){
                if (arrYedek[i][j] == 'x')
                {
                    arrYedek[i][j] = 'o';
                    blobRow.push_back(i);
                    blobColumn.push_back(j);
                    findBlobs(i, j);
                }
            }
        }
    }
    else
    {
        for (int c = 0; c < row; c++)
        {
            for (int d = 0; d < column; d++)
            {
                if (arrYedek[c][d] == 'x')
                {
                    arrYedek[c][d] = 'o';
                    foundBlob = true;
                    blobRow.push_back(c);
                    blobColumn.push_back(d);
                    findBlobs(c, d);
                }
            }
        }
    }
}