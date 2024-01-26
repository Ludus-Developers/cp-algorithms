#include <bits/stdc++.h>
//Pura gente del coach moy
using namespace std;
#define ENDL '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
typedef long long ll;

// x1, y1 son las coordenadas de la esquina inferior izquierda (bottom left) 
// x2, y2 son las coordenadas de la esquina superior derecha (top right)
struct Rect {
  ll x1, y1, x2, y2;
  ll area() { return (y2 - y1) * (x2 - x1); }
  void input(){ cin>>x1>>y1>>x2>>y2; }
};

//Comprobar si se intersectan 2 rectangulos
bool intersect(Rect a, Rect b) {
  if (a.x1 >= b.x2 || a.x2 <= b.x1 || a.y1 >= b.y2 || a.y2 <= b.y1) {
    return false;      // No comparten Area comun
  }
  return true;
}

//Area de interseccion de 2 rectangulos
ll intersectArea(Rect a, Rect b) {
	ll xOverlap = max(0, min(a.x2, b.x2) - max(a.x1, b.x1));
	ll yOverlap = max(0, min(a.y2, b.y2) - max(a.y1, b.y1));
	return xOverlap * yOverlap;
}

int main(){ _
    
    Rect a,b;
    a.input();
    b.input();
    //Area total de los rectangulos
    cout<<a.area()+b.area()-intersectArea(a,b)<<ENDL;

  return 0;
}