#include<iostream> //For standard I/O operations
#include<math.h> //For finding power
#include<cstring> //For memset
#define PI 3.14159
#define e 2.71828
using namespace std;

//Calculates point value form from coefficient form of the polynomial
//in array a of size n and returns in array y of size n
float * Recursive_fft(float *a,float *y,int n)
{
    //Base case
    if(n==1)
        return a;
    float w=1;
    float w_n=pow(e,2*PI/n);
    int new_n=n/2;
    float a_even[new_n],a_odd[new_n];
    for(int i=0;i<n;i++)
    {
        if(i%2==0)
            a_even[i/2]=a[i];
        else
            a_odd[i/2]=a[i];
    }
    float *y_even=NULL,*y_odd=NULL;
    y_even=Recursive_fft(a_even,y_even,new_n);
    y_odd=Recursive_fft(a_odd,y_odd,new_n);
    float y_arr[n];
    for(int i=0;i<new_n;i++)
    {
        y_arr[i]=y_even[i] + w*y_odd[i];
        y_arr[new_n+i]=y_even[i] - w*y_odd[i];
        w*=w_n;
    }
    y=y_arr;
    return y;
}
float * Inverse_fft(float *a,float *y,int n)
{
    //Base case
    if(n==1)
        return a;
    float w=1;
    float w_n=pow(e,-2*PI/n);
    int new_n=n/2;
    float a_even[new_n],a_odd[new_n];
    for(int i=0;i<n;i++)
    {
        if(i%2==0)
            a_even[i/2]=a[i];
        else
            a_odd[i/2]=a[i];
    }
    float *y_even=NULL,*y_odd=NULL;
    y_even=Recursive_fft(a_even,y_even,new_n);
    y_odd=Recursive_fft(a_odd,y_odd,new_n);
    float y_arr[n];
    for(int i=0;i<new_n;i++)
    {
        y_arr[i]=(y_even[i] + w*y_odd[i])/n;
        y_arr[new_n+i]=(y_even[i] - w*y_odd[i])/n;
        w*=w_n;
    }
    y=y_arr;
    return y;
}
float * Convolution(float *a,float *b,float *c,int n)
{
    float *a1=NULL,*b1=NULL;
    a1=Recursive_fft(a,a1,n);
    b1=Recursive_fft(b,b1,n);
    float c_arr[n];
    for(int i=0;i<n;i++)
        c_arr[i]=a[i]*b[i];
    c=Inverse_fft(c_arr,c,n);
    return c;
}
int main()
{
    //Degree of polynomials
    int n1,n2;
    cin>>n1>>n2;
    int n=max(n1,n2);
    n=pow(2,(int)log2(n)+1);
    cout<<n<<endl;

    //First polynomial
    float poly1[n]; //Polynomial array 1
    memset(poly1,0,sizeof(poly1));
    for(int i=0;i<n1;i++)
        cin>>poly1[i];
    //------------------

    //Second polynomial
    float poly2[n]; //Polynomial array 2
    memset(poly2,0,sizeof(poly2));
    for(int i=0;i<n2;i++)
        cin>>poly2[i];
    //------------------

    //Product polynomial
    float *c=NULL;
    c=Convolution(poly1,poly2,c,n);
    for(int i=0;i<n;i++)
        cout<<c[i]<<" ";
    cout<<endl;

    return 0;
}
