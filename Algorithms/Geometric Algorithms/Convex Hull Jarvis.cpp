#include<iostream>
#include<vector>
using namespace std;

struct Point
{
    int x,y;
};

//This function takes 3 points as input and returns:
//0: Collinear
//1: Clockwise
//2: Anti-clockwise
int orientation(Point p, Point q, Point r)
{
    //Slope of pq(m1)=(q.y-p.y)/(q.x-p.x)
    //Slope of qr(m2)=(r.y-q.y)/(r.x-q.x)
    //If m1-m2=0 -> Collinear
    //If m1-m2>0 -> Clockwise
    //If m1-m2<0 -> Anti-clockwise
    int diff=(q.y-p.y)*(r.x-q.x) - (r.y-q.y)*(q.x-p.x);
    if(diff==0)
        return 0;
    return diff>0? 1:2;
}

vector<int> ConvexHull(Point points[],int n)
{
    //Finding the convex hull involves the following steps:
    //-Find the left most point(p)
    //-Starting from that point do
    //  -Choose point q such that pqr is counter-clockwise,
    //  where, r is any other point.
    //  - p<-q
    //-until p=starting point

    //For storing the result
    vector<int> hull;

    //Finding the left most point:--------------
    int lmost=0;
    for(int i=1;i<n;i++)
    {
        if(points[lmost].x>points[i].x)
            lmost=i;
    }
    //------------------------------------------

    int p,q;
    p=lmost;
    do
    {
        //Adding the current point to result
        hull.push_back(p);
        //Immediate next point
        q=(p+1)%n;
        for(int i=0;i<n;i++)
        {
            //Checking if piq is counterclockwise
            //If yes, update q<-i
            if(orientation(points[p],points[i],points[q])==2)
                q=i;
        }
        //Updating p
        p=q;
    }while(p!=lmost);

    //return the result
    return hull;
}

int main()
{
    //Input:------------------------
    int n;
    cout<<"Enter no. of points:";
    cin>>n;
    Point P[n];
    for(int i=0;i<n;i++)
        cin>>P[i].x>>P[i].y;
    //------------------------------

    vector<int> hull(ConvexHull(P,n));

    //Displaying the result:-----------------
    for(size_t i=0;i<hull.size();i++)
    {
        cout<<P[hull[i]].x<<" "<<P[hull[i]].y<<"\n";
    }
    //---------------------------------------
}
