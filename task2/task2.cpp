#include <iostream>
#include <sys/time.h>
using namespace std;
int main()
{   int i,j;
    int n=1000000;
    int m=1000;
    double *a;
    double *b;
    double *c;
    a=new double [n];
    b=new double [n];
    c=new double [n];
    int offset=0;
    struct timeval start_time,end_time;






    for (i=0;i<n;i+=1)
    {
        b[i]=i;
        c[i]=i;
    }
    gettimeofday(&start_time,NULL);
    for (j=0;j<=m;j+=1)
    {
    for (i=1;i<n-offset;i+=1)
    {
     a[i]=b[i]+c[i+offset];
    }
    }
    gettimeofday(&end_time,NULL);
cout<<"\n\ngettimeofday wall time="<<end_time.tv_sec - start_time.tv_sec+(end_time.tv_usec-start_time.tv_usec)/1e6<<endl;


}
