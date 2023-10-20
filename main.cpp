#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>

using namespace std;
int a, b;
vector<vector<char>>arr;



int main()
{
    
    ifstream readonly("blobs1.txt", ios::in);
    readonly >> a;
    readonly >> b;
    arr.resize(a);
    for (int i = 0; i < a; i++) {
        arr[i].resize(b);
    }
    for (int c = 0; c < a; c++) {
        for (int d = 0; d < b; d++) {
            readonly  >> noskipws >> arr[c][d];
        }
    }
    for (int c = 0; c < a; c++) {
        for (int d = 0; d < b; d++) {
            cout << arr[c][d];
        }
    }
}