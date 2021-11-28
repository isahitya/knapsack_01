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



int knapsack_enumerate_helper(vector<Item> &items, vector< vector<Item> > &out, vector<Item> cur_items, int M, int N) {
     if(N == 0 || M == 0) {
        out.push_back(cur_items);
        return 0;
     }

     if(items[N - 1].w > M) {
        return knapsack_enumerate_helper(items, out, cur_items, M, N - 1);
     } else {
        vector<Item> cur_items_a(cur_items);
        cur_items_a.push_back(items[N - 1]);
        int a = items[N - 1].v + knapsack_enumerate_helper(items, out, cur_items_a, M - items[N - 1].w, N - 1);
        int b = knapsack_enumerate_helper(items, out, cur_items, M, N - 1);
        return max(a, b);
     }
}

pair<int, vector< vector<Item> > > knapsack_enumerate(vector<Item> items, int M){
    vector< vector<Item> > out;
    vector<Item> cur_items;
    int res = knapsack_enumerate_helper(items, out, cur_items, M, items.size());
    return pair<int, vector< vector<Item> > >(res, out);  
}


int main () {
    pair<int, vector<Item> > testcase = read_testcase_file("./testcase_gen/testcases/test_1.txt");
    
    cout << endl;
    auto start = high_resolution_clock::now();
    pair<int, vector< vector<Item> > > ans = knapsack_enumerate(testcase.second, testcase.first);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout << "Time taken: " << duration.count() << endl;
    cout << "Profit obtained from the optimal subset : " << ans.first << endl;
    cout << "Enumeration of all feasible subsets- " << endl;
    int each_profit = 0;
    int each_weight = 0;
    int greedy_subset_index = 0;
    int i = 0;
    for(vector<Item> subset : ans.second) {
        each_profit = 0;
        each_weight = 0;
        for(Item i : subset) {
            cout << "(" << i.w << ", " << i.v << "), ";
            each_profit += i.v;
            each_weight = i.w;
        }
        if(each_profit == ans.first) {
            greedy_subset_index = i;
        }
        //cout << endl << " Total Weight : " << each_weight << " Total Profit : " << each_profit;
        cout << endl;
        i++;
    }

    cout << "Optimal subset by greedy method: " << endl;
    each_profit = 0;
    each_weight = 0;
    for(Item i : ans.second[greedy_subset_index]) {
        cout << "(" << i.w << ", " << i.v << "), ";
        each_profit += i.v;
        each_weight = i.w;
    }
    cout << endl;
    cout << "Total Weight : " << each_weight << " Total Profit : " << each_profit;
    cout << endl;


    cout << endl;
    
}
