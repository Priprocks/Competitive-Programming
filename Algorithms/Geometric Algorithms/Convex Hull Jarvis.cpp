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

vector<Point> ConvexHull(Point points[],int n)
{
    
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

    vector<Point> hull(ConvexHull(P,n));

}
