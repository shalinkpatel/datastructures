#include <fstream>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <climits>
#define VI vector<int>
#define VV vector<Vertex>
#define VB vector<bool>
#define UM unordered_map<int,int>
using std::vector;
using std::cout;
using std::cin;
using std::unordered_map;
using std::min;

struct Vertex{
    Vertex(): adj(){}

    VI adj;
};

struct Graph{
    explicit Graph(int nv);
    void addEdge(int n, int m);
    void CPUtil(int u, int mytime);
    void DFS1();
    void CompUtil(int u, int id, UM& locs);
    int DFS2(UM& locs);

    VV g;
    VB visited;
    VI times;
    VI low;
    VI parents;
    VB CP;
};

Graph::Graph(int nv){
    g = VV(nv);
    visited = VB(nv, false);
    times = VI(nv);
    low = VI(nv);
    parents = VI(nv, -1);
    CP = VB(nv, false);
}

void Graph::addEdge(int n, int m){
    g[m].adj.push_back(n);
    g[n].adj.push_back(m);
}

void Graph::CPUtil(int u, int mytime){
    int c = 0;
    visited[u] = true;
    times[u] = low[u] = ++mytime;
    
    for(int i : g[u].adj){
        if(!visited[i]){
            c++; 
            parents[i] = u;
            CPUtil(i, mytime);
            low[u] = min(low[u], low[i]);
            if(parents[u] == -1 && c > 1) CP[u] = true;
            else if(parents[u] != -1 && low[i] >= times[u]) CP[u] = true;
        }

        else if(i != parents[u]) low[u] = min(low[u], times[i]);
    }
}

void Graph::DFS1(){
    for(size_t i = 0; i < g.size(); ++i){
        int mytime = 0;
        if(!visited[i]) CPUtil(i, mytime);
    }
}

void Graph::CompUtil(int u, int id, UM& locs){
    visited[u] = true;
    if(!CP[u]){
        locs.insert({u, id});
    }
    for(int i : g[u].adj){
        if(!visited[i] && !CP[i]) CompUtil(i, id, locs);
    }
}

int Graph::DFS2(UM& locs){
    for(size_t i = 0; i < g.size(); ++i){
        visited[i] = (false || CP[i]);
    }

    int id = 0;
    for(size_t i = 0; i < g.size(); ++i){
        if(!visited[i]) CompUtil(i, id++, locs);
    }
    return id;
}

int transporters(int n, VI& tubes){
    Graph g(n);
    for(size_t i = 0; i < tubes.size()/2; ++i) g.addEdge(tubes[2*i], tubes[2*i+1]);
    g.DFS1();
    UM locs;
    int ncomps = g.DFS2(locs);
    VI connections(ncomps, 0);
    for(int i = 0; i < n; ++i){
        if(g.CP[i]){
            VB connect(ncomps, false);
            for(int j : g.g[i].adj){
                if(locs.find(j) != locs.end() && !connect[locs[j]]){
                    connections[locs[j]]++;
                    connect[locs[j]] = true;
                }
            }
        }
    }

    int cost = 0;
    for(int i = 0; i < ncomps; ++i){
        if(connections[i] == 0) cost += 2;
        else if(connections[i] == 1) cost++;
    } 
    return cost;
}

