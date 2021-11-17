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


pair<int, vector<Item> > knapsack_enumerate(vector<Item> &vec, int cap)
{
    int n = vec.size();
    int dp[n+1][cap+1];
    vector<Item> out;

    int i,j;
    for(i=0;i<=cap;++i)dp[0][i]=0;
    for(i=0;i<=n;++i)dp[i][0]=0;
    
    for(i=1;i<=n;++i)
    {
        for(j=1;j<=cap;++j)
        {
            Item itm=vec[i-1];
            dp[i][j] = dp[i-1][j];
            if(itm.w<=j)
            {
                dp[i][j] = max(dp[i-1][j],dp[i-1][j-itm.w]+itm.v);
            }
        }
    }
    int res = dp[n][cap];
    int w = cap;
    for(int i = n; i > 0 && res > 0; --i) {
        if(res == dp[i - 1][w]) {
            continue;
        } else {
            out.push_back(vec[i - 1]);
            res = res - vec[i - 1].v;
            w = w - vec[i - 1].w;
        }
    }
    return pair<int, vector<Item> >(dp[n][cap], out);
}

int main () {
    pair<int, vector<Item> > testcase = read_testcase_file("./testcase_gen/testcases/test_1.txt");
    
    auto start = high_resolution_clock::now();
    pair<int, vector<Item> > ans = knapsack_enumerate(testcase.second, testcase.first);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << endl;
    cout << "Time taken by dynamic programming: " << duration.count() << endl;
    
    cout << "Maximum profit from dynamic programming: " << ans.first << endl;
    cout << "Solution items- ";
    for(Item i : ans.second) {
        cout << "(" << i.w << ", " << i.v << "), ";
    }
    cout << endl;
    cout << endl;
}