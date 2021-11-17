#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

struct Item {
    int w;
    int v;
};

pair<int, vector<Item> > read_testcase_file(string filename) {
    vector<Item> out;
    string line;
    ifstream testcase_file(filename);
    int m;
    if(testcase_file.is_open()) {
        getline(testcase_file, line);
        m = stoi(line);
        while(getline(testcase_file, line)) {
            string weight = line.substr(0, line.find(','));
            string value = line.substr(line.find(',') + 1);
            Item i;
            i.w = stoi(weight);
            i.v = stoi(value);
            out.push_back(i);
        }
        testcase_file.close();
    } else {
        cout << "File not found" << endl;
    }
    return pair<int, vector<Item> >(m, out);
}

int main () {
    pair<int, vector<Item> > testcase = read_testcase_file("./testcase_gen/testcases/test_1.txt");
    cout << "M: " << testcase.first << endl;
    for(Item i : testcase.second) {
        cout << i.w << endl;
        cout << i.v << endl;
    }
}