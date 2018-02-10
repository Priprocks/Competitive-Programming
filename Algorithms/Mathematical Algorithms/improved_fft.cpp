#include<iostream> //For standard I/O operations
#include<complex>  //For complex numbers
#include<vector>   //For storing the vectors
#define PI 3.14159
#define e 2.71828
#define MAXN 10000
using namespace std;
typedef complex < double > base ;
int rev [ MAXN ] ;
base wlen_pw [ MAXN ] ;

//Prepares the reverse bits array
void calc_rev(int n,int log_n)
{
	for(int i=0;i<n;++i)
    {
		rev[i]=0;
		for(int j=0;j<log_n;++j)
			if(i&(1<<j))
				rev[i]|=1<<(log_n-1-j);
	}
}

//Calculates FFT when invert= false
//Inverse FFT when invert= true
void fft(base a[], int n, bool invert)
{
    //Reordering the positions:------
	for(int i=0; i<n; ++i)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
    //-------------------------------

    //Iterative implementation of Divide and Conquer approach:------------------
	for(int len=2; len<=n; len<<=1)
    {
		double ang=2*PI/len*(invert? -1:+1);
		int len2=len>>1;

		base wlen(cos(ang),sin(ang));
		wlen_pw[0]=base(1,0);
		for(int i=1; i<len2; ++i)
			wlen_pw[i]=wlen_pw[i-1]*wlen;

		for(int i=0; i<n; i+=len)
        {
			base t, *pu=a+i, *pv=a+i+len2, *pu_end=a+i+len2, *pw=wlen_pw;
			for (; pu!=pu_end; ++pu,++pv,++pw)
            {
				t=(*pv)*(*pw);
				*pv=*pu-t;
				*pu+=t;
			}
		}
	}
    //--------------------------------------------------------------------------

    //Handling inverse fft:--------
	if(invert)
		for(int i=0; i<n; ++i)
			a[i]/=n;
    //-----------------------------
}

size_t n=1;
//Multiplies the polynomials in a and b and returns the result in res
void multiply(int *a, int *b,size_t n1,size_t n2, int *res)
{
    //Getting n in power of 2:-----------
	while(n< max(n1,n2))
        n <<= 1 ;
	n <<= 1 ;
    //-----------------------------------

    //Preparing the reverse bit array:---
    size_t lg_n=0;
	while(((size_t)1 <<lg_n)< n)
        ++lg_n;
    calc_rev(n,lg_n);
    //-----------------------------------

    //Storing the polygons in arrays of complex numbers:----------
	base ca[MAXN], cb[MAXN];
    for(size_t i=0;i<n;i++)
    {
        if(i<n1)
            ca[i]=a[i];
        else
            ca[i]=0;
        if(i<n2)
            cb[i]=b[i];
        else
            cb[i]=0;
    }
    //------------------------------------------------------------

    //FFT call:-------------
	fft(ca,n,false);
    fft(cb,n,false);
    //----------------------

    //Convolution:----------
	for(size_t i=0;i<n;++i)
		ca[i]*=cb[i];
    //----------------------

    //Inverse FFT call:-----
	fft(ca,n,true);
    //----------------------

    //Storing the result in an integer vector:--
	//res.resize(n);
	for (size_t i=0;i<n;++i)
		res[i]=int(ca[i].real()+0.5);
    //------------------------------------------
}

int main()
{
    //First polynomial
    int n1;
    cin>>n1;
    int poly1[n1]; //Polynomial array 1
    for(int i=0;i<n1;i++)
    {
        cin>>poly1[i];
    }
    //------------------

    //Second polynomial
    int n2;
    cin>>n2;
    int poly2[n2]; //Polynomial array 2
    for(int i=0;i<n2;i++)
    {
        cin>>poly2[i];
    }
    //------------------

    //Product polynomial
    int res[MAXN];
    multiply(poly1,poly2,n1,n2,res);
    for(size_t i=0;i<n;i++)
        cout<<res[i]<<" ";
    cout<<endl;

    return 0;
}
