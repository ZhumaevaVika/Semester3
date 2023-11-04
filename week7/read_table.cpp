#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class CSVReader {
public:
    CSVReader(const string& filename, char delimiter=',') : file_(filename), delimiter_(delimiter) {}

    bool read(vector<vector<int>>& data) {
        if (!file_) {
            return false;
        }

        string line;
        while (getline(file_, line)) {
            vector<int> row;
            stringstream ss(line);
            string cell;

            while (getline(ss, cell, delimiter_)) {
                row.push_back(stoi(cell));
            }

            data.push_back(row);
        }

        return true;
    }

private:
    ifstream file_;
    char delimiter_;
};

int main() {
    CSVReader reader("input.txt");
    vector<vector<int>> data;
    reader.read(data);

    int n = data[0][0];
    int m = data[0][1];

    data.erase(data.begin()); // remove the first row

    for (const auto& row : data) {
        for (const auto& cell : row) {
            cout.width(10);
            cout << cell;
        }
        cout << endl;
    }

    return 0;
}