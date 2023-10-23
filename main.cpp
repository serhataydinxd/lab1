#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

struct blob{
    int rowMin = INT_MAX;
    int rowMax = INT_MIN;
    int columnMin = INT_MAX;
    int columnMax = INT_MIN;
};

vector<float>flox, floy;
vector<vector<char>> arr,check;
string fileName;
int row, column;
vector<blob> blobs;
vector<int> blobSize;

void readFile();// read the file, create and fill the array
void print();// print the array
void findBorders(int x, int y, char crntChar, vector<vector<char>>& check, vector<vector<char>>& arr, int blobIndex, int rowNumber, int columnNumber);
// find the borders of the blobs
void findCoM(vector<vector<char>>& arr, vector<blob>& blobs);// find the CoM of the blobs
void printCoM(vector<blob>& blobs);// print the CoM of the blobs

int main(){
    readFile();
    print();
    int blobIndex = 0;
    while (true) {
        bool found = false;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (arr[i][j] == 'x' && check[i][j] != 'x') {
                    found = true;
                    blobs.resize(blobIndex + 1);
                    blobs[blobIndex].rowMin = INT_MAX;
                    blobs[blobIndex].rowMax = INT_MIN;
                    blobs[blobIndex].columnMin = INT_MAX;
                    blobs[blobIndex].columnMax = INT_MIN;
                    findBorders(i, j, 'x', check, arr, blobIndex, row, column);
                    flox.resize(blobs.size());
                    floy.resize(blobs.size());
                    findCoM(arr, blobs);
                    blobIndex++;
                }
            }
        }
        if (!found) {
            break;
        }
    }
    printCoM(blobs);
    return 0;
}

void readFile(){
    cout << "Enter the file name: ";
    cin >> fileName;
    ifstream readonly(fileName);
    if (!readonly) {
        cout << "File couldn't be found." << endl;
        Sleep(2000);
        system("cls");
        readFile();
    }
    readonly >> row >> column;
    arr.resize(row, vector<char>(column));
    check.resize(row, vector<char>(column));
    char temp;
    for (int c = 0; c < row; c++){
        for (int d = 0; d < column; d++){
            readonly >> noskipws >> arr[c][d];
            if (arr[c][d] == '\n'){
                arr[c][d] = NULL;
                --d;
            }
        }
    }
}

void print(void){
    // Top row
    cout << "  ";
    for (int d = 0; d < column; d++) {
        cout << d % 10;
    }
    cout << endl
        << " +";
    for (int d = 0; d < column; d++) {
        cout << "-";
    }
    cout << "+" << endl;
    // Inside of the array
    for (int c = 0; c < row; c++) {
        cout << c % 10 << "|";
        for (int d = 0; d < column; d++) {
            cout << arr[c][d];
        }
        cout << "|" << c % 10 << endl;
    }
    // Bottom row
    cout << " +";
    for (int d = 0; d < column; d++) {
        cout << "-";
    }
    cout << "+" << endl;
    cout << "  ";
    for (int d = 0; d < column; d++) {
        cout << d % 10;
    }
    cout << endl;
}

void findBorders(int x, int y, char crntChar, vector<vector<char>>& check, vector<vector<char>>& arr, int blobIndex, int rowNumber, int columnNumber){
    if (x < 0 || x == rowNumber) {
        return;
    }else if (y < 0 || y == columnNumber) {
        return;
    }else if (check[x][y] == 'x' || arr[x][y] != 'x') {
        return;
    }else{
        check[x][y] = crntChar;
    }
    
    // Blob boundaries
    blobs[blobIndex].rowMin = min(blobs[blobIndex].rowMin, x);
    blobs[blobIndex].rowMax = max(blobs[blobIndex].rowMax, x);
    blobs[blobIndex].columnMin = min(blobs[blobIndex].columnMin, y);
    blobs[blobIndex].columnMax = max(blobs[blobIndex].columnMax, y);

    // Recursive calls
    findBorders(x + 1, y, crntChar, check, arr, blobIndex, rowNumber, columnNumber);
    findBorders(x, y + 1, crntChar, check, arr, blobIndex, rowNumber, columnNumber);
    findBorders(x - 1, y, crntChar, check, arr, blobIndex, rowNumber, columnNumber);
    findBorders(x, y - 1, crntChar, check, arr, blobIndex, rowNumber, columnNumber);
}

void findCoM(vector<vector<char>>& arr, vector<blob>& blobs){
    int count = 0; // x count for each blob
    for (int i = 0; i < blobs.size(); i++) {
        float sumX = 0;
        float sumY = 0;
        count = 0;
        //count x's in blob and find the sum of x and y cordinates according to blob boundaries
        for (int j = blobs[i].rowMin; j <= blobs[i].rowMax; j++) { 
            for (int k = blobs[i].columnMin; k <= blobs[i].columnMax; k++) {
                if (arr[j][k] == 'x') {
                    sumX += j;
                    sumY += k;
                    count++;
                }
            }
        }
        if (count != 0) {
            flox[i] = sumX / count; // Find the COM x cordinate
            floy[i] = sumY / count; // Find the COM y cıordinate
        }
    }
    blobSize.push_back(count);//add blob size to vector to use in printCoM function
}

void printCoM(vector<blob>& blobs){
    cout << endl << endl;
    cout << "+------+------------+---------+------------+" << endl;
    cout << "| BLOB | NoOfPixels | CoM Row | CoM Column |" << endl;
    cout << "+------+------------+---------+------------+" << endl;
    for (int i = 0; i < blobs.size(); i++) {
        printf("|%6d|%12d|%9.2f|%12.2f|\n", i + 1, blobSize[i], flox[i], floy[i]);//setprecision(2) didn't work as intended so I used printf
    }
    cout << "+------+------------+---------+------------+" << endl;
}