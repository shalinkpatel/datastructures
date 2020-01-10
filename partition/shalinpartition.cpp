#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::sort;
using std::reverse;

typedef unsigned long long ULL;
typedef vector<int> VI;

vector<ULL> q(417, 0);
vector<vector<ULL>> qtot(417,vector<ULL>(417, 0));

ULL part_q(int n); //breaks otherwise, stupid recursion 

//Helper to part_q
ULL part_qagg(int n, int max){
    if(n == 0 || n == 1) return 1;
    if(q[n] == 0) part_q(n); //make sure we didn't screw up

    if(max >= n) return q[n];
    
    ULL count = 0;
    for(int i = 1; i < max + 1; ++i) count += qtot[n][i];
    return count;
}

//Counts number of partitions of n
ULL part_q(int n){
    if(n == 0 || n == 1) return 1;
    if(q[n] != 0) return q[n];

    ULL count = 0;
    for(int i = 1; i < n+1; ++i){
        qtot[n][i] = part_qagg(n-i, i);
        count += qtot[n][i];
    }

    q[n] = count;
    return count;
}

//Helper to part_k
VI part_kagg(int n, int max, ULL k){
    VI ret;
    if(n == 0) return ret;
    else if(n == 1){
        ret.push_back(1);
        return ret;
    }

    ULL count = 0;
    int idx = max;
    while(qtot[n][idx] + count <= k){
        count += qtot[n][idx];
        --idx;
    }

    ret.push_back(idx);

    VI remaining = part_kagg(n-idx, idx, k - count);
    ret.insert(ret.end(), remaining.begin(), remaining.end());
    return ret;
}

//Returns vector of ints for the kth partition of n
VI part_k(int n, ULL k){
    part_q(n);
    return part_kagg(n,n,k);
}

//Helper for part_i
ULL part_iagg(const VI& vec, int idx, int num, int rest, int max){
    if(idx == vec.size()) return 0;
    else if(rest == 0) return 0;

    ULL count = 0;
    int j = max;
    while(j > vec[idx]){
        count += qtot[rest][j];
        --j;
    }
    count += part_iagg(vec, idx+1, num + vec[idx], rest - vec[idx], vec[idx]);
    return count;
}

//Returns index of a given partition
ULL part_i(const VI& p){
    VI vec = p;
    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());
    int num = 0;
    for(int i = 0; i < vec.size(); ++i) num += p[i];
    part_q(num);
    return part_iagg(vec, 0, num, num, num);
}