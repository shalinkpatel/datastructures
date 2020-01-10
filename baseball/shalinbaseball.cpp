#include <vector>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <climits>
#include <string>
#include <queue>
#define VI vector<int>
#define VV vector<Vertex>
#define VB vector<bool>
#define UM unordered_map<int,int>
using std::vector;
using std::cout;
using std::cin;
using std::unordered_map;
using std::min;
using std::queue;
using std::string;

struct Vertex{
    Vertex(): adj(){}

    VI adj;
    UM weights;
    VI teams;
};

struct Graph{
    explicit Graph(int nv);
    void addEdge(int n, int m, int w);
    bool BFS(VI& path);
    VI BFS2(int n);
    int ff();

    VV g;
    VV rg;
    VB visited;
    int s;
    int t;
 };


Graph::Graph(int nv){
    g = VV(nv);
    rg = VV(nv);    
    visited = VB(nv, false);
    s = 0;
    t = nv-1;
}

void Graph::addEdge(int n, int m, int w){
    g[n].adj.push_back(m);
    g[n].weights[m] = w;
    rg[n].adj.push_back(m);
    rg[m].adj.push_back(n);
    rg[n].weights[m] = w;
    rg[m].weights[n] = 0;
}

bool Graph::BFS(VI& path){
    visited = VB(g.size(), false);

    queue<int> q;
    q.push(s);
    int count = 1;
    visited[s] = true;
    path[s] = -1;

    while(!q.empty()){
        int n = q.front(); q.pop();

        for(int i = 0; i < rg[n].adj.size(); ++i){
            if(!visited[rg[n].adj[i]] && rg[n].weights[rg[n].adj[i]] > 0){
                q.push(rg[n].adj[i]);
                path[rg[n].adj[i]] = n;
                visited[rg[n].adj[i]] = true;
            }
        }
    }

    return visited[t];
}

VI Graph::BFS2(int n){
    visited = VB(g.size(), false);

    queue<int> q;
    q.push(s);
    visited[s] = true;

    while(!q.empty()){
        int n = q.front(); q.pop();

        for(int i = 0; i < rg[n].adj.size(); ++i){
            if(!visited[rg[n].adj[i]] && rg[n].weights[rg[n].adj[i]] > 0){
                q.push(rg[n].adj[i]);
                visited[rg[n].adj[i]] = true;
            }
        }
    }

    VI elimination;
    for(int i = 1 + (n-1)*(n-2)/2; i < 1 + (n-1)*(n-2)/2 + n; ++i){
        if(visited[i]) elimination.push_back(g[i].teams[0]);
    }

    return elimination;
}

int Graph::ff(){
    VI path(g.size(), INT_MAX);

    int flow = 0;
    while (BFS(path)){
        int f = INT_MAX;
        for(int n = t; n != s; n = path[n]){
            f = min(f, rg[path[n]].weights[n]);
        } 

        for(int n = t; n != s; n = path[n]){
            rg[path[n]].weights[n] -= f;
            rg[n].weights[path[n]] += f;
        }

        flow += f;
    }
    return flow;
}

VI evalTeam(int n, int team, VI& w, VI& l, VI& r, vector<VI>& g){
    VI fin;
    Graph graph(1 + (n-1)*(n-2)/2 + n );
    int count = 1;
    int agg = 0;
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(i != j && i != team && j != team){
                graph.addEdge(0, count, g[i][j]);
                graph.g[count].teams.push_back(i);
                graph.g[count].teams.push_back(j);
                agg += g[i][j];
                count++;
            }
        }
    }

    UM mapping;
    int counter = 0;
    for(int i = 0; i < n; ++i){
        if(i != team){
            mapping[i] = counter++;
        }
    }

    for(int i = 1; i < count; ++i){
        for(int j : graph.g[i].teams){
            graph.addEdge(i, count + mapping[j], INT_MAX);
            graph.g[count + mapping[j]].teams.push_back(j);
        }
    }

    int sum = w[team] + r[team];

    for(int i = 0; i < n-1; ++i){
        graph.addEdge(count + i, graph.t, sum - w[graph.g[count + i].teams[0]]);
    }

    //check trivial elimination
    int pos = w[team] + r[team];
    bool good = true;
    for(int i = 0; i < n; ++i) good = good && pos >= w[i];
    if(!good){
        fin.push_back(0);
        for(int i = 0; i < n; ++i){
            if(w[i] > pos) fin.push_back(i);
        }
        return fin;
    }

    int finalf = graph.ff();
    if(agg == finalf) fin.push_back(1);
    else fin.push_back(0);
    VI R = graph.BFS2(n);
    for(int i : R) fin.push_back(i);
    return fin;
}

void baseball(){
    int N;
    cin >> N;
    vector<string> names;
    VI w;
    VI l;
    VI r;
    vector<VI> g;
    for(int i = 0; i < N; ++i){
        int wp, lp, rp;
        string np;
        cin >> np;
        cin >> wp >> lp >> rp;
        VI gp;
        for(int j = 0; j < N; ++j){
            int gpp;
            cin >> gpp;
            gp.push_back(gpp);
        }
        names.push_back(np);
        w.push_back(wp);
        l.push_back(lp);
        r.push_back(rp);
        g.push_back(gp);
    }

    for(int i = 0; i < N; ++i){
        VI ans = evalTeam(N, i, w, l, r, g);
        if(ans[0] == 1) cout << names[i] << " is not eliminated" << '\n';
        else{
            cout << names[i] << " is eliminated by the subset R = { ";
            for(int j = 1; j < ans.size(); ++j) cout << names[ans[j]] << " ";
            cout << "}" << '\n';
        }
    }  
}

int main(){
    baseball();
    return 0;
}