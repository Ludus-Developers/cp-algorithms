#include <bits/stdc++.h>
//Pura gente del coach moy
#define INF 1000000000
 
using namespace std;
 
typedef long long ll;
typedef vector<int> vi;

//Acompañado del Euler Tour normalmente viene un Segment Tree
//Este es de minimos. Modificar si es necesario
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
    vi in, out; //En in se guardará el tiempo de entrada y en out de salida del nodo
    int tiempo;

    void init(int _V){
        V = _V;
        adj.assign(V, vi());
        in.assign(V, -1);
        out.assign(V, -1);
        tiempo = 0;
    }

    void ae(int a, int b){ adj[a].push_back(b); }

    //Se debe empezar con la raiz del arbol y con p = -1
    //(dando a entender que no tiene padre)
    //La complejidad es de un dfs nomarl O(V + E)
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
 
	return 0;
}
