#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <time.h>       /* time */
#include <vector>
#include <omp.h>
using namespace std;
fstream f1;
struct point
{
   int id;
   float x;
   float y;
   float z;
};

struct triangle
{   int id;
    int n1;
    int n2;
    int n3;

};

float sign (point p1, point p2, point p3);

bool PointInTriangle (point pt, point v1, point v2, point v3);

class interface
{
private:
    int np,nd,n_o_t;
    point *points;
    triangle *tri;
    vector<int> array;
public:
    interface(){}//constructor
    ~interface(){delete [] points;delete [] tri;}
    const interface &operator=(const interface &f);
    interface(const interface &f);
    void fileinput();//read file
    void tri_contain(double &x, double &y);//Decide whether a triangle is contained
    point get_centre(int &target);//Get the centre of one triangle
    double pointDistance(point p1, point p2);//Calculate the distance between two points
    double area(point p1, point p2, point p3);//Calculate the area of a triangle
    void get_integration(double (*foo)(double,double));//Integrate the volume of the surface
};

  interface::interface(const interface &f)
  {
    np=f.np;
    nd=f.nd;
    n_o_t=f.n_o_t;
    points=f.points;
    tri=f.tri;
  }
  const interface &interface ::operator=(const interface &f)
  {
   if(this==&f) return(*this);
    else
    {
    np=f.np;
    nd=f.nd;
    n_o_t=f.n_o_t;
    points=f.points;
    tri=f.tri;
    }
    return *this;
  }
  point interface::get_centre(int &target)
    {
      int n1,n2,n3;
      n1=tri[target].n1;
      n2=tri[target].n2;
      n3=tri[target].n3;
      double x1,x2,x3,y1,y2,y3;
      x1=points[n1].x;
      y1=points[n1].y;
      x2=points[n2].x;
      y2=points[n2].y;
      x3=points[n3].x;
      y3=points[n3].y;
      double t1=x1*x1+y1*y1;
      double t2=x2*x2+y2*y2;
      double t3=x3*x3+y3*y3;
      double temp=x1*y2+x2*y3+x3*y1-x1*y3-x2*y1-x3*y2;
      point centre;
      centre.x=(t2*y3+t1*y2+t3*y1-t2*y1-t3*y2-t1*y3)/temp/2;
      centre.y=(t3*x2+t2*x1+t1*x3-t1*x2-t2*x3-t3*x1)/temp/2;
      return centre;
    }
   double interface::pointDistance(point p1, point p2)
{
    double distance = 0;
    distance = sqrt((p1.y-p2.y)*(p1.y-p2.y)+(p1.x-p2.x)*(p1.x-p2.x));
    return distance;
}
double interface::area(point p1, point p2, point p3)
{
    double area = 0;
    double a = 0, b = 0, c = 0, s = 0;
    a = pointDistance(p1, p2);
    b = pointDistance(p2, p3);
    c = pointDistance(p1, p3);
    s = 0.5*(a+b+c);
    area = sqrt(s*(s-a)*(s-b)*(s-c));
    return area;
}

float sign (point p1, point p2, point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle (point pt, point v1, point v2, point v3)
{
    bool b1, b2, b3;

    b1 = sign(pt, v1, v2) < 0.0f;
    b2 = sign(pt, v2, v3) < 0.0f;
    b3 = sign(pt, v3, v1) < 0.0f;
   // cout<<b1<<endl;
    return ((b1 == b2) && (b2 == b3));
}
void interface::fileinput()
{
    int cell;
    int i,j;
    f1.open("triangulation#1.TRI");
    f1>>np>>nd>>cell;
    points=new point[np];
    //cout<<np<<endl;
    for (i=0;i<np;i+=1)
    {
        f1>>points[i].id>>points[i].x>>points[i].y>>points[i].z;
      //  cout <<points[i].id<<" "<<points[i].x<<" "<<points[i].y<<endl;
    }
    int n_d,n_s;
    float extra;
    f1>>n_o_t>>n_d>>n_s;
    cout<<n_o_t<<endl;
    tri=new triangle[n_o_t];
        for (i=0;i<n_o_t;i+=1)
    {
        f1>>tri[i].id>>tri[i].n1>>tri[i].n2>>tri[i].n3;
        for(j=0;j<17;j+=1){f1>>extra;}

    }
    }

    void interface::tri_contain(double &x, double &y)
    {
    int i;
    struct point extrapoint;
    array.reserve(6);
    extrapoint.x=x;
    extrapoint.y=y;
    bool check;
    int v1,v2,v3,target;
    for (i=0;i<n_o_t;i+=1)
    {
    v1=tri[i].n1;
    v2=tri[i].n2;
    v3=tri[i].n3;
    check=PointInTriangle (extrapoint, points[v1], points[v2], points[v3]);
    if (check==1)
    {
        cout<<"in triangle "<<i<<endl;
        array.push_back(i);
    }
    }
    }

 void interface::get_integration(double (*foo)(double,double))
    {
      int i;
      double FO,V1,V2,F1,F2,F3;
      point centre;
      int n1,n2,n3;
      double thearea;
      for (i=0;i<n_o_t;i+=1)
      {
      n1=tri[i].n1;
      n2=tri[i].n2;
      n3=tri[i].n3;
      thearea=area(points[n1],points[n2],points[n3]);
      centre=get_centre(i);
      FO=foo(centre.x,centre.y);
      V1+=FO*thearea;
      }
      cout<<"the first method gets: "<<V1<<endl;
      double x1,y1,x2,y2,x3,y3;
      for (i=0;i<n_o_t;i+=1)
      {
      n1=tri[i].n1;
      n2=tri[i].n2;
      n3=tri[i].n3;
      x1=points[n1].x;
      y1=points[n1].y;
      x2=points[n2].x;
      y2=points[n2].y;
      x3=points[n3].x;
      y3=points[n3].y;
      F1=foo(x1,y1);
      F2=foo(x2,y2);
      F3=foo(x3,y3);
      V2+=(F1+F2+F3)*thearea/3;
      }
      cout<<"the second method gets: "<<V2<<endl;
    }

    double calculate(double x, double y)
    {
        return (3*x+6*y);
    }

int main()
{
    interface m;
    m.fileinput();
    srand (time(NULL));
    int i,j;
    double x,y;
    x=33.5101;
    y=-3.00017 ;

    for (i=0;i<=99;i+=1)
    {

    m.tri_contain(x,y);
    }

    m.get_integration(calculate);
}
