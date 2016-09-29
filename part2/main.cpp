#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <time.h>       /* time */
#include <vector>
#include <omp.h>
#include <assert.h>
#include <math.h>
#include "tri.h"
using namespace std;
fstream f1;
fstream f2;
void fileinput();
void supertriangle();


int circumcontain(point p, triangle t);//Judge whether a point is in the circumtance of a triangle
     point a;
     edge b;

     triangle d;//super triangle


     vector <triangle> triangles;
     vector <point> vertics;


     int point_num, nd,cell,triangle_num,n_d,n_s;
     void triangulation();
     triangle generatetriangle(point a,point b, point c);

     triangle generatetriangle(point a,point b, point c)//Construct a triangle
     {
       triangle n;
       n.i1.id=a.id;
       n.i2.id=b.id;
       n.i3.id=c.id;
       n.i1.x=a.x;
       n.i1.y=a.y;
       n.i2.x=b.x;
       n.i2.y=b.y;
       n.i3.x=c.x;
       n.i3.y=c.y;
       n.e1.v1=a;
       n.e1.v2=b;
       n.e2.v1=b;
       n.e2.v2=c;
       n.e3.v1=c;
       n.e3.v2=a;
       return n;
     }
void triangulation() //Generate triangles based on the rules
{   int check;
    int contain;
    int i,j,k;
    int flag=0;



    for(i=0;i<vertics.size();i++)
    {
     cout <<i<<endl;
     vector <triangle> bad;
     vector <edge> polygon;

      for (j=0;j<triangles.size();j++)
      {
          check=circumcontain(vertics[i], triangles[j]);
          if (check==1)
         {
             bad.push_back(triangles[j]);
             polygon.push_back(triangles[j].e1);
             polygon.push_back(triangles[j].e2);
             polygon.push_back(triangles[j].e3);

         }
      }



      for (j=0;j<triangles.size();j++)
      {
          for(k=0;k<bad.size();k++)
          {
              if ((triangles[j].i1.id==bad[k].i1.id)&&(triangles[j].i2.id==bad[k].i2.id)&&(triangles[j].i3.id==bad[k].i3.id))
              {
                  triangles.erase(triangles.begin()+j);j--;
              }
          }

      }

      vector <edge> badedge;



      for(j=0;j<polygon.size()-1;j=j+1)
      {
          for (k=j+1;k<polygon.size();k=k+1)
          {

              flag=0;
              if ((polygon[j].v1.id==polygon[k].v1.id)&&(polygon[j].v2.id==polygon[k].v2.id)){flag=1;}
              if ((polygon[j].v1.id==polygon[k].v2.id)&&(polygon[j].v2.id==polygon[k].v1.id)){flag=1;}
              if (flag==1)
                {
                    badedge.push_back(polygon[j]);
                    badedge.push_back(polygon[k]); //!!!!!!
                }
          }
      }




       for(j=0;j<polygon.size();j++)
      {
          for (k=0;k<badedge.size();k++)
          {
              flag=0;
              if ((polygon[j].v1.id==badedge[k].v1.id)&&(polygon[j].v2.id==badedge[k].v2.id)){flag=1;}
              if ((polygon[j].v1.id==badedge[k].v2.id)&&(polygon[j].v2.id==badedge[k].v1.id)){flag=1;}
              if (flag==1){polygon.erase(polygon.begin()+j);j--;}
          }
      }

       //  cout <<triangles.size()<<endl;
         for(j=0;j<polygon.size();j++)
        {
         triangle temp;
         point t1,t2,t3;
         t1.x=polygon[j].v1.x;
         t1.y=polygon[j].v1.y;
         t1.id=polygon[j].v1.id;
         t2.x=polygon[j].v2.x;
         t2.y=polygon[j].v2.y;
         t2.id=polygon[j].v2.id;
         t3.x=vertics[i].x;
         t3.y=vertics[i].y;
         t3.id=vertics[i].id;
         temp=generatetriangle(t1,t2,t3);
         triangles.push_back(temp);

        }
    }

    for (i=0;i<triangles.size();i++)
    {


if ((triangles[i].i1.id>=point_num)||(triangles[i].i2.id>=point_num)||(triangles[i].i3.id>=point_num))
    { triangles.erase(triangles.begin()+i);i--;}

    }




}
int circumcontain(point p, triangle t)
{     double x1,y1,x2,y2,x3,y3;
      x1=t.i1.x;
      y1=t.i1.y;
      x2=t.i2.x;
      y2=t.i2.y;
      x3=t.i3.x;
      y3=t.i3.y;
      double t1=x1*x1+y1*y1;
      double t2=x2*x2+y2*y2;
      double t3=x3*x3+y3*y3;
      double temp=x1*y2+x2*y3+x3*y1-x1*y3-x2*y1-x3*y2;
      point centre;
      centre.x=(t2*y3+t1*y2+t3*y1-t2*y1-t3*y2-t1*y3)/temp/2;
      centre.y=(t3*x2+t2*x1+t1*x3-t1*x2-t2*x3-t3*x1)/temp/2;
      double circum_radius = sqrtf(((x1 - centre.x) * (x1 - centre.x)) + ((y1 - centre.y) * (y1 - centre.y)));
      double dis=sqrtf(((p.x - centre.x) * (p.x - centre.x)) + ((p.y - centre.y) * (p.y - centre.y)));
      if (circum_radius>=dis) return (1);
}
void fileinput() //Read files and store all the data
{
    int i;
    f1.open("vertices#1.node");
    f1>> point_num >>nd>>cell;

    for (i=0;i<point_num;i+=1)
    {
       f1>> a.id>> a.x>> a.y;
       vertics.push_back(a);
       cout<<vertics[i].id<<"  "<< vertics [i].x<<"  "<< vertics [i].y<<endl;
    }

}
void supertriangle()//Generate a super triangle that is large enough to contain all points
{
    int i;
    double xmin=vertics[0].x;
    double xmax=xmin;
    double ymin=vertics[0].y;
    double ymax= ymin;
    for(i=1;i<point_num;i++)
    {
        if (vertics[i].x < xmin) xmin = vertics[i].x;
    	if (vertics[i].y < ymin) ymin = vertics[i].y;
    	if (vertics[i].x > xmax) xmax = vertics[i].x;
    	if (vertics[i].y > ymax) ymax = vertics[i].y;
    }
    double dx = xmax - xmin;
	double dy = ymax - ymin;
	double deltaMax = std::max(dx, dy);
    double midx=(xmax+xmin)/2;
    double midy=(ymax+ymin)/2;
    cout<<midx<<" "<<midy<<endl;
    point s1,s2,s3;
    s1.x=midx - 20 * deltaMax;
    s1.y=midy - deltaMax;
    s1.id=point_num;
    s2.id=point_num+1;
    s3.id=point_num+2;
    s2.x=midx;
    s2.y=midy + 20 * deltaMax;
    s3.x=midx + 20 * deltaMax;
    s3.y=midy - deltaMax;
     cout<<s1.x<<" "<<s1.y<<" "<<s2.x<<" "<<s2.y<<" "<<s3.x<<" "<<s3.y<<" "<<endl;
//    d.e1.v1=d.i1;
//    d.e1.v2=d.i2;
//    d.e2.v1=d.i2;
//    d.e2.v2=d.i3;
//    d.e3.v1=d.i3;
//    d.e3.v2=d.i1;
    d=generatetriangle(s1,s2,s3);
    cout<<d.i1.x<<" "<<d.i1.y<<" "<<d.i2.x<<" "<<d.i2.y<<" "<<d.i3.x<<" "<<d.i3.y<<" "<<endl;
    triangles.push_back(d);
}

int main()
{   fileinput();
    supertriangle();
    triangulation();
    ofstream fileaa("generate.tri");

    fileaa<<point_num<<" "<<3<<" "<<0<<endl;
    int i;
    for (i=0;i<point_num;i++)
    {
        fileaa<<vertics[i].id<<" "<<vertics[i].x<<" "<<vertics[i].y<<" "<<0<<endl;
    }
    fileaa<<triangles.size()<<" "<<3<<" "<<0<<endl;
    for (i=0;i<triangles.size();i++)
    {
    fileaa<<i<<" "<<triangles[i].i1.id<<" "<<triangles[i].i2.id<<" "<<triangles[i].i3.id<<endl;
    }

}
