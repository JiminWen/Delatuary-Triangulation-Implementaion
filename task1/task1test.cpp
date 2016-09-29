#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string.h>
using namespace std;

int main(int argc, char* argv[]) {
        int const nx(10000);

        int const ny(200);

        int const nt(200);
        int i,j,t,m,k;
        double** vi=new double*[nx];

        double** vr=new double*[nx];

        double const pi=(4.*atan(1.))/double(nx);//Set as constant to save time

        for(int i=0;i<nx;i++) {

                vi[i]=new double[ny];

                vr[i]=new double[ny];

        }

        for(int i=0;i<nx;i++) {

                for(int j=0;j<ny;j++) {

                        vi[i][j]=double(i*i)*double(j)*sin(pi*double(i));
                        vr[i][j]=0.;
                }
        }


        ofstream fout("data_out.txt");

        for( t=0;t<nt;++t) {//Rewrite the loop to avoid judgments

                cout<<"\n"<<t;cout.flush();

                i=0;
                for(j=1;j<ny-1;++j)
                {
                 vr[i][j]=(vi[i+1][j]+10.+vi[i][j-1]+vi[i][j+1])*0.25;

                }
                i=nx-1;
                for(j=1;j<ny-1;++j)
                {
                 vr[i][j]=(5.+vi[i-1][j]+vi[i][j-1]+vi[i][j+1])*0.25;
                }
                j=0;
                for(i=1;i<nx-1;++i)
                {
                vr[i][j]=(vi[i+1][j]+vi[i-1][j]+15.45+vi[i][j+1])*0.25;
                }
                j=ny-1;
                for(i=1;i<nx-1;++i)
                {
                  vr[i][j]=(vi[i+1][j]+vi[i-1][j]+vi[i][j-1]-6.7)*0.25;
                }
                for( i=1;i<nx-1;++i) {
                        for( j=1;j<ny-1;++j) {
                                vr[i][j]=(vi[i+1][j]+vi[i-1][j]+vi[i][j-1]+vi[i][j+1])*0.25;

                        }
                }

                for( i=0;i<nx;++i) {//These two loops are combined together

                        for( j=0;j<ny;++j) {

                                if(fabs(fabs(vr[i][j])-fabs(vi[i][j]))<1e-2) fout<<"\n"<<t<<" "<<i<<" "<<j<<" "<<fabs(vi[i][j])<<" "<<fabs(vr[i][j]);
                                vi[i][j]=(vi[i][j]+vr[i][j])*0.5;
                        }
                }

//                for( i=0;i<nx;++i) {
//
//                        for( j=0;j<ny;++j)
//
//                }
        }
}
