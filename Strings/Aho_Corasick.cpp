#include <bits/stdc++.h>
 
using namespace std;
 
typedef vector<int> vi;
 
const int K = 26;
 
struct Vertex {
    vi next;
    bool output = false;
	int id = -1;
    int p = -1;
    char pch;
    int link = -1;
    int terminal = -1;
    vi go;
 
    Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
        next.assign(K, -1);
        go.assign(K, -1);
    }
};
 
 
int go(int v, char ch);
 
struct Aho_Corasick{
    vector<Vertex> t;
 
    void init(){
        t.emplace_back(Vertex());
    }
 
    int convert(char ch){
		return ch - 'a';
    }
 
    void add_string(string const& s, int id) {
        int v = 0;
        for (char ch : s) {
            int c = convert(ch);
			//cout << v << " " << c << "\n";
            if (t[v].next[c] == -1) {
                t[v].next[c] = t.size();
                t.emplace_back(v, ch);
            }
            v = t[v].next[c];
        }
        t[v].output = true;
		t[v].id = id;
    }
 
    int get_link(int v) {
        if (t[v].link == -1) {
            if (v == 0 || t[v].p == 0)
                t[v].link = 0;
            else
                t[v].link = go(get_link(t[v].p), t[v].pch);
        }
        return t[v].link;
    }
 
    int go(int v, char ch) {
        int c = convert(ch);
        if (t[v].go[c] == -1) {
            if (t[v].next[c] != -1)
                t[v].go[c] = t[v].next[c];
            else
                t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
        }
        return t[v].go[c];
    }
 
    int terminal(int v){
        if(t[v].terminal == -1){
            if(v == 0){
                t[v].terminal = 0;
            }
            else{
                t[v].terminal = terminal(get_link(v));
                if(t[get_link(v)].output){
                    t[v].terminal = get_link(v);
                }
            }
        }
        return t[v].terminal;
    }
}; 
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 
    Aho_Corasick ah;
    ah.init();
 
	string T;
	cin >> T;
	int n;
	cin >> n;
	vector<vi> ocur(n, vi());
	int minOc[n], tam[n];
	for(int k = 0; k < n; k++){
		cin >> minOc[k];
		string ax;
		cin >> ax;
        tam[k] = ax.length();
		ah.add_string(ax, k);
	}
 
	int v = 0;
	for(int k = 0; k < (int) T.length(); k++){
		v = ah.go(v, T[k]);
		int ax = v;
		while(ax != 0){
            if(ah.t[ax].output){
                ocur[ah.t[ax].id].push_back(k);
            }
			ax = ah.terminal(ax);
		}
	}
 
	for(int k = 0; k < n; k++){
		if((int) ocur[k].size() < minOc[k]){
			cout << "-1\n";
			continue;
		}
		int m = ocur[k].size();
 
        int res = T.length();
        for(int j = 0; j <= m - minOc[k]; j++){
            int dif = tam[k] + (ocur[k][j + minOc[k] - 1] - ocur[k][j]);
            res = min(res, dif);
        }
		
        cout << res << "\n";
	}
	
    return 0;
}
