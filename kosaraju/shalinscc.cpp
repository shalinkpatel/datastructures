#include <vector>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#define VI vector<int>
#define VV vector<Vertex>
#define VB vector<bool>
#define SI stack<int>
#define US unordered_set<int>
#define VUS vector<US>

using std::vector;
using std::stack;
using std::cout;
using std::cin;
using std::unordered_set;
using std::unordered_map;

struct Vertex{
    Vertex(): adj(){}

    US adj;
};

struct Graph{
    explicit Graph(int nv);
    US DFS(int v, SI &st, bool pt, bool ord, US &comp);
    bool addEdge(int n, int m);
    Graph rev();
    void kosaraju();
    
    VV g;
    VB visited;
};

Graph::Graph(int nv){
    g = VV(nv);
    visited = VB(nv, false);
}

bool Graph::addEdge(int n, int m){
    return std::get<1>(g[n].adj.insert(m));
}

US Graph::DFS(int v, SI &st, bool pt, bool ord, US &comp){
    visited[v] = true;
    if(pt) comp.insert(v);

    for(US::iterator i = g[v].adj.begin(); i != g[v].adj.end(); ++i){
        if(!visited[*i]) DFS(*i, st, pt, ord, comp);
    }

    if(ord) st.push(v);
    return comp;
}

Graph Graph::rev(){
    Graph gr(g.size());
    for(int i = 0; i < g.size(); ++i){
        for(US::iterator j = g[i].adj.begin(); j != g[i].adj.end(); ++j){
            gr.addEdge(*j, i);
        }
    }
    return gr;
}

void Graph::kosaraju(){
    VUS comps;
    SI order;

    for(int i = 0; i < g.size(); ++i){
        if(!visited[i]){
            US comp;
            DFS(i, order, false, true, comp);
        }
    }

    Graph gr = rev();

    while(!order.empty()){
        int v = order.top(); order.pop();

        if(!gr.visited[v]){
            US comp;
            comps.push_back(gr.DFS(v, order, true, false, comp));
        }
    }

    int nsc = comps.size();
    cout << nsc << '\n';
    Graph dag(nsc);
    unordered_map<int, int> locs;
    int ne = 0;
    for(int i = 0; i < nsc; ++i){
        cout << comps[i].size() << ' ';
        for(US::iterator j = comps[i].begin(); j != comps[i].end(); ++j){
            cout << (*j) << ' ';
            locs.insert({*j, i});
        }
        cout << '\n';
    }

    for(int i = 0; i < nsc; ++i){
        for(US::iterator j = comps[i].begin(); j != comps[i].end(); ++j){
            for(US::iterator k = g[*j].adj.begin(); k != g[*j].adj.end(); ++k){
                if(comps[i].find(*k) == comps[i].end() && dag.addEdge(i, locs[*k])) ne++;
            }
        }
    }

    cout << ne << '\n';
    for(int i = 0; i < nsc; ++i){
        for(US::iterator j = dag.g[i].adj.begin(); j != dag.g[i].adj.end(); ++j){
            cout << i << " " << (*j) << '\n';   
        }
    }
}

int main(){
    int N, E;
    cin >> N >> E;
    Graph g(N);
    for(int i = 0; i < E; ++i){
        int m,n;
        cin >> m >> n;
        g.addEdge(m, n);
    }
    g.kosaraju();
    return 0;
}