#include<iostream> //For standard I/O operations
#include<complex>  //For complex numbers
#include<vector>   //For storing the vectors
#define PI 3.14159
#define e 2.71828
using namespace std;
typedef complex < double > base ;

//Calculates FFT when invert= false
//Inverse FFT when invert= true
void fft ( vector < base > & a, bool invert ) {
    //Getting the size
	int n=(int) a.size();

    //Base Case:-------------
	if(n==1)
        return;
    //-----------------------

    //a0<-even elements
    //a1<-odd elements
	vector<base> a0(n/2), a1(n/2);

    //Filling up a0 and a1:-------------
	for(int i=0,j=0; i<n; i+=2,++j)
    {
		a0[j]=a[i];
		a1[j]=a[i+1];
	}
    //----------------------------------

    //Recurive calls(Divide portion):--
	fft(a0,invert);
	fft(a1,invert);
    //---------------------------------

    //Getting the roots of unity:------
	double ang=2*PI/n*(invert? -1: 1); //Handles the inverse part
	base w(1), wn(cos(ang),sin(ang));
    //---------------------------------

    //Conquer portion:--------------------------
	for(int i=0;i<n/2;++i)
    {
		a[i]=a0[i]+w*a1[i];
		a[i+n/2]=a0[i]-w*a1[i];

        //Handles the inverse part:--
		if(invert)
        {
			a[i]/=2;
            a[i+n/2]/=2;
        }
        //----------------------------
		w *=wn ;
	}
    //--------------------------------------------
}

//Multiplies the polynomials in a and b and returns the result in res
void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res)
{
    //Storing the polygons in a vector of complex numbers:--------
	vector<base> fa(a.begin(),a.end()), fb(b.begin(),b.end());
    //------------------------------------------------------------

    //Getting n in power of 2:-----------
	size_t n=1;
	while(n< max(a.size(),b.size()))
        n <<= 1 ;
	n <<= 1 ;
    //-----------------------------------

    //Resizing the vectors
	fa.resize(n), fb.resize(n);

    //FFT call:-------------
	fft(fa,false);
    fft(fb,false);
    //----------------------

    //Convolution:----------
	for(size_t i=0;i<n;++i)
		fa[i]*=fb[i];
    //----------------------

    //Inverse FFT call:-----
	fft(fa,true);
    //----------------------

    //Storing the result in an integer vector:--
	res.resize(n);
	for (size_t i=0;i<n;++i)
		res[i]=int(fa[i].real()+0.5);
    //------------------------------------------
}

int main()
{
    int temp;
    //First polynomial
    int n1;
    cin>>n1;
    vector<int> poly1; //Polynomial array 1
    for(int i=0;i<n1;i++)
    {
        cin>>temp;
        poly1.push_back(temp);
    }
    //------------------

    //Second polynomial
    int n2;
    cin>>n2;
    vector<int> poly2; //Polynomial array 2
    for(int i=0;i<n2;i++)
    {
        cin>>temp;
        poly2.push_back(temp);
    }
    //------------------

    //Product polynomial
    vector<int> res;
    multiply(poly1,poly2,res);
    int n=res.size();
    for(int i=0;i<n;i++)
        cout<<res[i]<<" ";
    cout<<endl;

    return 0;
}
