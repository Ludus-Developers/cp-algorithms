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
  
  T norm_sq() { return x * x + y * y; }
  double norm() { // hypot(x, y) mas lento pero mas precision 
    return sqrt( norm_sq() ); 
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

// Devuelve true si Punto P esta a la derecha de la linea AB
bool cw(Point a, Point b, Point p) { 
  return orient(a, b, p) < EPS; 
}

// Para aceptar puntos colineales cambiar > 0
// Devuelve true si Punto P esta a la izquierda de la linea AB
bool ccw(Point a, Point b, Point p) { 
  return orient(a, b, p) > -EPS; 
}

Point unit(Point p) { //Usar con double 
  return p / p.norm();
}
Point translate(Point p, Point v) { 
  return {p + v}; 
}
//Escalar el punto P 
Point scale(Point p, double factor) { 
  return p * factor; 
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

// Ecuacion ax + by = c
struct Line { double a, b, c; };                

// Dado los puntos P1 y P2 crea la linea l por referencia
void pointsToLine(Point p1, Point p2, Line &l) {
  if (fabs(p1.x-p2.x) < EPS)                     // vertical Line is fine
    l = {1.0, 0.0, -p1.x};                       // default values
  else {
    double a = -(double)(p1.y-p2.y) / (p1.x-p2.x);
    l = {a, 1.0, -(double)(a*p1.x) - p1.y};      // NOTE: b always 1.0
  }
}

// Ecuacion y = mx + c | m es la pendiente y c ordenada al origen
struct Line2 { double m, c; };

int pointsToLine2(Point p1, Point p2, Line2 &l) {
  if (p1.x == p2.x) {                            // Linea vertical
    l.m = INF;                                   // this is to denote a
    l.c = p1.x;                                  // Line x = x_value
    return 0;                                    // differentiate result
  }else {
    l.m = (double)(p1.y-p2.y) / (p1.x-p2.x);
    l.c = p1.y - l.m*p1.x;
    return 1;                                    // standard y = mx + c
  }
}

//Checa si la linea L2 y L2 son paralelas
bool areParallel(Line l1, Line l2) {             
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

//Checa si son la misma linea
bool areSame(Line l1, Line l2) {                 // also check  c
  return areParallel(l1 ,l2) && (fabs(l1.c-l2.c) < EPS);
}

// Devuelve si intersecta la linea L1 y L2 + Punto  p de interseccion
bool areIntersect(Line l1, Line l2, Point &p) {
  if (areParallel(l1, l2)) return false;         // No intersectan
  // Resolver sistema de ecuaciones 2x2 con 2 variables desconocidas
  p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
  // Caso especial: Probar Linea vertical para evitar division por cero
  if (fabs(l1.b) > EPS) 
    p.y = -(l1.a*p.x + l1.c);
  else                 
    p.y = -(l2.a*p.x + l2.c);
  return true;
}

// Convierte un Punto y pendiente y lo convierte linea 
// Formula pendiente: m = (y2 - y1) / (x2 - x1)
void pointSlopeToLine(Point p, double m, Line &l) {
  l.a = -m;                                // Siempre -m
  l.b = 1;                                 // Siempre 1
  l.c = -((l.a * p.x) + (l.b * p.y));      // C = -(a*x + b*y)
}

void closestPoint(Line l, Point p, Point &ans) {
  // Line perpendicular a L y pasa por P
  Line perpendicular;                            
  if (fabs(l.b) < EPS) {                         // Linea vertical
    ans.x = -(l.c);
    ans.y = p.y;
    return;
  }
  if (fabs(l.a) < EPS) {                         // Linea horizontal
    ans.x = p.x;
    ans.y = -(l.c);
    return;
  }
  pointSlopeToLine(p, 1/l.a, perpendicular);     // Linea normal
  // Intersectar Linea L con la linea perpendicular
  // El punto de interseccion es el punto mas cercano
  areIntersect(l, perpendicular, ans);
}

// Devuelve el punto de refleccion del punto P en la linea L 
void reflectionPoint(Line l, Point p, Point &ans) {
  Point b;
  closestPoint(l, p, b);                         // Similar a distToLine
  Point v = toVec(p, b);                         // create a vector
  ans = translate(translate(p, v), v);           // Trasladar P al doble
}

// Devuelve la distancia de P a la linea AB (A != B)
// Punto mas cercano almacenado en C
double distToLine(Point p, Point a, Point b, Point &c) {
  Point ap = toVec(a, p), ab = toVec(a, b);
  double u = ap.dot(ab) / ab.norm_sq();
  // Formula: c = a + u*ab
  c = translate(a, scale(ab, u));                // Trasladar A a C
  return dist(p, c);                             
}

// Devuelve la distancia de P al segmento AB (A != B)
// Punto mas cercano almacenado en C
double distToLineSegment(Point p, Point a, Point b, Point &c) {
  Point ap = toVec(a, p), ab = toVec(a, b);
  double u = ap.dot(ab) / ab.norm_sq();
  if (u < 0.0) {                                 // Mas cerca a A
    c = Point(a.x, a.y);
    return dist(p, a);                           
  }
  if (u > 1.0) {                                 // Mas cerca a B
    c = Point(b.x, b.y);
    return dist(p, b);                           
  }
  return distToLine(p, a, b, c);                 
}




int main(){
  cout << (fixed) << setprecision(8);


  return 0;
}