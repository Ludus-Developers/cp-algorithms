#include <bits/stdc++.h>
//Pura gente del coach moy
#define INF 200000000

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct Grafo{
    int V;
    vector<vii> adj;
    vector<bool> ready;
    vi dist; //Aqui se guardaran las distancias

    void init(int _V){
        V = _V;
        adj.assign(V, vii());
        ready.assign(V, false);
    }

    void ae(int a, int b, int c){ adj[a].push_back(ii(b, c)); }

    //Al llamar se calcularan las distancias del nodo x a todos
    //los demas nodos. Complejidad O(E + VlogV)
    void dijkstra(int x){
        dist.assign(V, INF);
        dist[x] = 0;
        priority_queue<ii> q;
        q.push({0, x});

        while (!q.empty()) {
            int u = q.top().second; q.pop();
            if (ready[u])
                continue;
            ready[u] = true;
            for (auto e : adj[u]) {
                int v = e.first, w = e.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    q.push({-dist[v], v});
                }
            }
        }
    }
};

int main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    Grafo g;
    g.init(n);

    while(m--){
        int a, b, c;
        cin >> a >> b >> c;
        g.ae(a, b, c);
        g.ae(b, a, c);
    }

    g.dijkstra(0);
    for(int k = 0; k < n; k++){
        cout << "0 -> " << k << ": " << g.dist[k] << "\n";
    }

    return 0;
}
