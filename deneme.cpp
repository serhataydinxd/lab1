#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdio>

using namespace std;

void readFile();
void print();
void findBlobs();
void exploreBlob(int x, int y, int label);
void findBlobCenter();

int row, column;
string fileName;
vector<vector<char>> arr;
vector<vector<bool>> visited;
vector<pair<int, int>> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
vector<vector<pair<int, int>>> blobs;
vector<pair<int, int>> blobCenters;

int main()
{
    readFile();
    system("cls");
    print();
    findBlobs();
    findBlobCenter();
    return 0;
}

void readFile()
{
    cout << "Enter the file name: ";
    cin >> fileName;
    ifstream readonly(fileName);
    if (!readonly)
    {
        cout << "File couldn't found. Please make sure you write it correctly!" << endl;
        this_thread::sleep_for(chrono::seconds(4));
        system("cls");
        readFile(); // Use readFile() instead of return readFile()
    }
    else
    {
        readonly >> row >> column;
        arr.resize(row, vector<char>(column));
        visited.resize(row, vector<bool>(column, false));
        char ch;
        for (int c = 0; c < row; c++)
        {
            for (int d = 0; d < column; d++)
            {
                readonly >> noskipws >> ch;
                if (ch == '\n')
                {
                    d--;
                    continue;
                }
                arr[c][d] = ch;
            }
        }
    }
}

void print()
{
    cout << " ";
    for (int d = 0; d < column; d++)
    {
        cout << d % 10;
    }
    cout << endl << "+";
    for (int d = 0; d < column; d++)
    {
        cout << "-";
    }
    cout << "+" << endl;
    for (int c = 0; c < row; c++)
    {
        cout << c % 10 << "|";
        for (int d = 0; d < column; d++)
        {
            cout << arr[c][d];
        }
        cout << "|" << c % 10 << endl;
    }
    cout << "+";
    for (int d = 0; d < column; d++)
    {
        cout << "-";
    }
    cout << "+" << endl << " ";
    for (int d = 0; d < column; d++)
    {
        cout << d % 10;
    }
    cout << endl;
}

void exploreBlob(int x, int y, int label)
{
    visited[x][y] = true;
    blobs[label].push_back({ x, y });
    for (auto& dir : directions)
    {
        int newX = x + dir.first;
        int newY = y + dir.second;
        if (newX >= 0 && newX < row && newY >= 0 && newY < column && !visited[newX][newY] && arr[newX][newY] == 'x')
        {
            exploreBlob(newX, newY, label);
        }
    }
}

void findBlobs()
{
    blobs.clear();
    blobCenters.clear();
    visited.assign(row, vector<bool>(column, false));
    int label = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (arr[i][j] == 'x' && !visited[i][j])
            {
                blobs.push_back(vector<pair<int, int>>());
                exploreBlob(i, j, label);
                label++;
            }
        }
    }
}

void findBlobCenter()
{
    cout << "Center of mass for blobs:" << endl;
    for (int i = 0; i < blobs.size(); i++)
    {
        float sumX = 0, sumY = 0;
        for (auto& point : blobs[i])
        {
            sumX += point.first;
            sumY += point.second;
        }
        float centerOfMassX = sumX / blobs[i].size();
        float centerOfMassY = sumY / blobs[i].size();
        cout << "b" << i + 1 << ": (" << centerOfMassX << ", " << centerOfMassY << ")" << endl;
    }
}
