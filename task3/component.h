//#include <math.h>
//#include <algorithm>
//#include <studio>
template<typename U>
U takeminvalue(U a, U b, U c, U d)
{
    U e,f;
    e=((a>b)?b:a);
    f=((c>d)?d:c);
    return ((e>f)?f:e);
}

template<typename U>
U takemaxvalue(U a, U b, U c, U d)
{
    int e,f;
    e=((a<b)?b:a);
    f=((c<d)?d:c);
    return ((e<f)?f:e);
}

template <class T>
class Component
{
    public:
    Component(T a, T b);
    Component();
    ~Component();
    Component (const Component &f):minvalue(f.minvalue),maxvalue(f.maxvalue){}
    const Component& operator=(const Component& f);
    const Component& operator+(const Component& f);
    const Component& operator-(const Component& f);
    const Component& operator*(const Component& f)
    {
        Component s;
    s.minvalue=takeminvalue( minvalue*f.minvalue,minvalue*f.maxvalue, maxvalue*f.minvalue,maxvalue*f.maxvalue);
    s.maxvalue=takemaxvalue( minvalue*f.minvalue,minvalue*f.maxvalue, maxvalue*f.minvalue,maxvalue*f.maxvalue);
    return (s);
    }
    const Component& operator/(const Component& f);
    T get_minvalue();
    T get_maxvalue();


    private:
    T minvalue;
    T maxvalue;

};
template <class T>
Component<T>::Component( T a, T b)
{
   minvalue=a;
   maxvalue=b;
}
template <class T>
Component<T>::Component():minvalue(0),maxvalue(0)
{

}
template <class T>
Component<T>::~Component()
{

}
//template <class T>
//Component<T>::Component() (const Component &f)
//{
//    minvaluef.minvalue;
//    maxvalue=f.maxvalue;
//   // return *this;
//}
template <class T>
const Component<T>&Component<T>:: operator=(const Component& f)
{
    if(this==&f) return(*this);
    else
    {
    minvalue=f.minvalue;
    maxvalue=f.maxvalue;
    }
    return *this;
}
template <class T>
const Component<T>&Component<T>::operator+(const Component& f)
{
    Component Sum;
    Sum.minvalue=f.minvalue+minvalue;
    Sum.maxvalue=f.maxvalue+maxvalue;
    return Sum;
}
template <class T>
const Component<T>&Component<T>::operator-(const Component& f)
{   Component Sum;
    Sum.minvalue=f.minvalue-minvalue;
    Sum.maxvalue=f.maxvalue-maxvalue;
    return Sum;
}

template <class T>
const Component<T>&Component<T>::operator/(const Component& f)
{   if ((f.minvalue==0)||(f.maxvalue==0)){}
    Component Sum(1/f.maxvalue,1/f.minvalue);
    Sum=(*this)*Sum;
    return Sum;
}
template <class T>
T Component<T>::get_minvalue()
{
    return minvalue;
}
template <class T>
T Component<T>::get_maxvalue()
{
    return maxvalue;
}

