#include<iostream>
#include<fstream>
#include<vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Item {
    int w;
    int v;
};

vector<Item> read_testcase_file(string filename) {
    vector<Item> out;
    string line;
    ifstream testcase_file(filename);

    if(testcase_file.is_open()) {
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
    return out;
}


int knapsack(vector<Item> items, int M, int N) {
     if(N == 0 || M == 0) return 0;

     if(items[N - 1].w > M) {
         return knapsack(items, M, N - 1);
     } else {
        int a = items[N - 1].v + knapsack(items, M - items[N - 1].w, N - 1);
        int b = knapsack(items, M, N - 1);
        return max(a, b);
     }
}

int main () {
    vector<Item> testcase = read_testcase_file("./testcase_gen/testcases/test_1.txt");
    
    auto start = high_resolution_clock::now();
    cout << knapsack(testcase, 1000, testcase.size()) << endl;
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by brute force: " << duration.count() << endl;
}
