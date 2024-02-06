#include <bits/stdc++.h>
//Pura gente del coach moy
 
using namespace std;
 
typedef vector<int> vi;

//Tamaño del alfabeto
const int K = 26;
 
struct Vertex {
    vi next;
    bool output = false; //Guarda si el nodo actual marca el final de una palabra
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
    
    //Convierte la letra del alfabeto a numero
    //Cambiar si es necesario (en este caso solo sirve para tener
    //letras minusculas)
    int convert(char ch){
		return ch - 'a';
    }
    
    //Agregar una palabra. Complejidad O(n)
    //n: tamaño de la palabra
    void add_string(string const& s) {
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
    
    //Te dirige al siguiente nodo del autamata segun cual sea
    //la letra que insertes
    //Normalemente se empieza del 0 (la raiz)
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
    
    //Devuelve al nodo que represente el prefijo mas largo
    //del nodo actual y que sea una palabra en el diccionario
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
	
    return 0;
}
