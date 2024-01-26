#include <bits/stdc++.h>
//Pura gente del coach moy
using namespace std;

const double INF = 1e9;
const double EPS = 1e-9, PI = acos(-1.0);

double DEG_to_RAD(double d) { return d*PI/180.0; }
double RAD_to_DEG(double r) { return r*180.0/PI; }

typedef double T;
struct Point {
  T x, y;
  Point(T x=0, T y=0) : x(x), y(y) {}// Point p(x,y)
  
  Point operator+(const Point &p)const{return Point(x+p.x,y+p.y);}
  Point operator-(const Point &p)const{return Point(x-p.x,y-p.y);}
  Point operator*(double a) const {return Point(x*a,y*a);}
  Point operator/(T d) const { return {x / d, y / d}; } //Usar con double
  
  T dot(Point p) { return x * p.x + y * p.y; }
  T cross(Point p) const { return x * p.y - y * p.x; }
  T cross(Point a, Point b) const { return (a - *this).cross(b - *this); }
  
  T sq() { return x * x + y * y; }
  double norm() { // hypot(x, y) mas lento pero mas precision 
    return sqrt( sq() ); 
  } 

  bool operator<(Point &p) const { // Ordena por X y Y
    return tie(x, y) < tie(p.x, p.y);
  }

  bool operator == (Point p) const { // Numeros Flotantes
    return (fabs(x - p.x) < EPS && (fabs(y - p.y) < EPS));
  }
  bool operator == (const Point &p){ // Numeros Enteros
    return x==p.x && y==p.y; 
  }
  bool operator!=(Point p) const { 
    return !(*this == p); 
  }
  
  void read() { cin >> x >> y; } 
  void out(){ cout << x << " " << y << '\n'; }
};

// ----------------------- Distancias -----------------------
double dist(const Point &p1, const Point &p2) { 
  // return (p1-p2).norm(); // mas rapido, menos precision
  return hypot(p1.x-p2.x, p1.y-p2.y); 
}
double distManhattan(const Point &p1, const Point &p2){
  return abs(p1.x-p2.x) + abs(p1.y-p2.y); //Usar fabs con double
}
// ----------------------------------------------------------

// ------------------ Operaciones vectores ------------------
Point toVec(Point a, Point b) {
  return b-a;
}
// -1 Negativo | 0 Cero | 1 Positivo 
int sgn(T x) { 
  return (T(0) < x) - (x < T(0)); 
}
// Positivo P en la izquierda | Colineal | Negativo P en la derecha |  
T orient(Point a, Point b, Point p) {
  return p.cross(a, b);
}
bool cw(Point a, Point b, Point c) { return orient(a, b, c) < EPS; }
bool ccw(Point a, Point b, Point c) { return orient(a, b, c) > -EPS; }

Point unit(Point p) { //Usar con double 
  return p / p.norm();
}
Point translate(Point p, Point v) { 
  return {p + v}; 
}
//Escalar el punto P alrededor del origen C
Point scale(Point p, Point c, double factor) { 
  return c + (p - c) * factor; 
}

// ----------------------------------------------------------

// ------------------ Rotaciones y angulos ------------------ 
double angle(Point p) { 
  return atan2(p.y, p.x); 
}
//Devuelve angulo entre dos vectores en radianes
double angle(Point v, Point w) { 
  return acos(clamp(v.dot(w) / v.norm() / w.norm(), -1.0, 1.0)); 
}
//True si el punto P esta en el angulo de AB Y AC
bool inAngle(Point a, Point b, Point c, Point p) {
  assert(orient(a,b,c) != 0);
  if (orient(a,b,c) < 0) swap(b,c);
  return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}
//Devuelve el angulo exterior en radianes
double orientedAngle(Point a, Point b, Point c) {
  if (ccw(a, b, c))
    return angle(b - a, c - a);
  return 2 * PI - angle(b - a, c - a);
}
//Punto A double, Angulo en radianes
Point rotateCCW(Point p, double t) { 
  return {p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t) }; 
}
//Punto A double, Angulo en radianes
Point rotateCW(Point p, double t) {
  return { p.x * cos(t) + p.y * sin(t), -p.x * sin(t) + p.y * cos(t) }; 
}
//Rota P double al rededor de C, Angulo en radianes
Point rotAround(Point p, double ang, Point c) { // p = rotAround(p, ang, c);
    return c + rotateCCW(p - c, ang); //Modificar CCW o CW
}
Point rotateCW90(Point p) { // p = rotateCW90();
  return { p.y,-p.x };
} 
Point rotateCCW90(Point p) { // p = rotateCCW90();
  return { -p.y, p.x }; 
} 
Point rotate180(Point p) { // p = rotate180();
  return { -p.x, -p.y }; 
} 
// ----------------------------------------------------------


int main(){
  cout << (fixed) << setprecision(8);


  return 0;
}