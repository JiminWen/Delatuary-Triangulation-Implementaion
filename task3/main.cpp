#include <iostream>
#include "component.h"
using namespace std;

int main()
{
    Component<double> a(5,10);
    Component<double> b(1,2);
    Component<double> c;
    c=a*b;


    cout<<c.get_minvalue()<<"    "<<c.get_maxvalue()<<endl;
    //cout<<a.get_minvalue()<<"    "<<a.get_maxvalue()<<endl;
}
