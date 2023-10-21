#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>

void readFile(void);
void print(void);

using namespace std;
int a, b;
vector<vector<char>>arr;

int main(void){
    readFile();
    print();
    return 0;
}

void readFile (void){
    ifstream readonly("blobs1.txt", ios::in);
    readonly >> a >> b;
    arr.resize(a);
    for (int i = 0; i < a; i++) {
        arr[i].resize(b);
    }
    for (int c = 0; c < a; c++) {
        for (int d = 0; d < b; d++) {
            readonly  >> noskipws >>arr[c][d];
            if (arr[c][d] == 10) {
                arr[c][d] = NULL;
                --d;
            }
        }
    }
}

void print(void){
    for (int c = 0; c < a; c++) {
        for (int d = 0; d < b; d++) {
            cout << arr[c][d];
        }
        cout << endl;
    }
}