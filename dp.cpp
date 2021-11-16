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


int knapsack(vector<Item> &vec, int cap)
{
    int n = vec.size();
    int dp[n+1][cap+1];
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
    return dp[n][cap];
}

int main () {
    vector<Item> testcase = read_testcase_file("./testcase_gen/testcases/test_1.txt");
    
    auto start = high_resolution_clock::now();
    cout << knapsack(testcase, 1000) << endl;
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by dynamic programming: " << duration.count() << endl;
    
}