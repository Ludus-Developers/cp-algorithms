#include <bits/stdc++.h>
#define INF 1000000000
 
using namespace std;
 
typedef long long ll;
typedef vector<int> vi;

class SegmentTree{
    private:
        int n;
        vi st;
        int left(int v){
            return (v << 1);
        }
        int right(int v){
            return (v << 1) + 1;
        }
        void build(int id, int value, int v, int l, int r){
            if(l == r){
                st[v] = value;
                return;
            }
            int m = (l + r) / 2;
            if(id <= m){
                build(id, value, left(v), l, m);
            }
            else{
                build(id, value, right(v), m + 1, r);
            }
            st[v] = min(st[left(v)], st[right(v)]);
        }

        int query(int sl, int sr, int v, int l, int r){
            if(sl > r || sr < l){
                return INF;
            }
 
            if(l >= sl && r <= sr){
                return st[v];
            }
 
            int m = (l + r) / 2;
 
            return min(query(sl, sr, left(v), l, m), query(sl, sr, right(v), m + 1, r));
        }
 
    public:
        SegmentTree(int N){
            n = N;
            st.assign(4 * n, 0);
        }
 
        int query(int l, int r){
            return query(l, r, 1, 0, n - 1);
        }
 
        void update(int id, int value){
            build(id, value, 1, 0, n - 1);
        }
};

struct Grafo{
    int V;
    vector<vi> adj;
    vi in, out;
    int tiempo;

    void init(int _V){
        V = _V;
        adj.assign(V, vi());
        in.assign(V, -1);
        out.assign(V, -1);
        tiempo = 0;
    }

    void ae(int a, int b){ adj[a].push_back(b); }

    void dfs(int u, int p){
        in[u] = tiempo++;
        
        for(int v : adj[u]){
            if(v == p){
                continue;
            }
            dfs(v, u);
        }
    
        out[u] = tiempo++;
    }
};
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
	int n, q;
    cin >> n >> q;

    Grafo g;

    g.init(n);

    for(int k = 1; k < n; k++){
        int a, b;
        cin >> a >> b;
        g.ae(a, b);
        g.ae(b, a);
    }

    g.dfs(0, -1);

    SegmentTree st(n * 2);
    for(int k = 0; k < n; k++){
        int x;
        cin >> x;
        st.update(g.in[k], x);
        st.update(g.out[k], x);
    }

    while(q--){
        int x;
        cin >> x;
        cout << st.query(g.in[x], g.out[x]) << "\n";
    }
 
	return 0;
}
