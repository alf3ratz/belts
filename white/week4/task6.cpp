#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include "iomanip"

using namespace std;

int main() {
    ifstream input("input.txt");
    vector<vector<int>> matrix;
    int num;
    int N, M;
    input >> N >> M;
    for (int i = 0; i < N; ++i) {
        matrix.emplace_back(vector<int>());
        for (int j = 0; j < M; ++j) {
            input >> num;
            input.ignore(1);
            matrix[i].emplace_back(num);
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << setw(10) << matrix[i][j];
            if (j != M - 1)
                cout << " ";
        }
        if (i != N - 1)
            cout << "\n";
    }
    return 0;
}