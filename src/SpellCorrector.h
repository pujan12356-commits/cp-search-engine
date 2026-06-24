#pragma once
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class SpellCorrector{
     int EditDistance(string a,string b){
        int n = a.size(), m = b.size();
        vector<vector<int>> dp(n+1,vector<int>(m+1));
        for(int i=0;i<=n;i++) dp[i][0] = i;
        for(int j=0;j<=m;j++) dp[0][j] = j;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i-1]==b[j-1]) dp[i][j] = dp[i-1][j-1];
                else{
                    dp[i][j] = 1 + min({dp[i-1][j],dp[i-1][j-1],dp[i][j-1]});
                }
            }
        }
        return dp[n][m];
     }

public:
    string suggest(string query, const vector<string> &vocabulary){
        string best = "";
        int bestDist = 3;
        for(auto &word: vocabulary){
            int d = EditDistance(query,word);
            if(d<bestDist){
                bestDist = d;
                best = word;
            }
        }
        return best;
    }     

};