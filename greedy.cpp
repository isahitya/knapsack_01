#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>
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


bool item_comparator_by_most_value(Item &a, Item &b) {
    return a.v > b.v;
}

bool item_comparator_by_least_weight(Item &a, Item &b) {
    return a.w < b.w;
}

bool item_comparator_by_value_per_unit_weight(Item &a, Item &b) {
    return ((double)a.v / (double)a.w) > ((double)b.v / (double)b.w);
}

int knapsack(vector<Item> items, int M) {
    sort(items.begin(), items.end(), item_comparator_by_value_per_unit_weight);
    int val = 0;
    int i = 0;
    while(M > 0 && i < items.size()) {
        if(items[i].w <= M) {
            val += items[i].v;
            M -= items[i].w;
        }
        i += 1;
    }
    return val;
}

int main () {
    vector<Item> testcase = read_testcase_file("./testcase_gen/testcases/test_1.txt");
    
    auto start = high_resolution_clock::now();
    cout << knapsack(testcase, 1000) << endl;
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by greedy approach: " << duration.count() << endl;
    
}
