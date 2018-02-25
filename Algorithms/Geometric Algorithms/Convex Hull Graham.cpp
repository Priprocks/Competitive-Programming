#include<iostream>
#include<math.h>
#include<stack>
#include<algorithm>
using namespace std;

struct Point
{
    int x,y;
};
Point pivot; //Global point to store the lowermost point

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

int compare(Point a,Point b)
{
    int o=orientation(pivot,a,b);

    //Points are collinear:----------
    if(o==0)
    {
        //Farther point from pivot is kept at higher index.
        //Lower index points are deleted
        int dista=pow(pivot.x-a.x,2)+ pow(pivot.y-a.y,2);
        int distb=pow(pivot.x-b.x,2)+ pow(pivot.y-b.y,2);
        return dista<distb;
    }
    return o==2;
}

stack<Point> ConvexHull(Point points[],int n)
{
    //Finding the lowermost point:----------------------------------------------
    int lmost=0;
    for(int i=1;i<n;i++)
    {
        if(points[lmost].y>points[i].y)
            lmost=i;
        else if(points[lmost].y==points[i].y && points[lmost].x>points[i].x)
            lmost=i;
    }
    //--------------------------------------------------------------------------

    //Bringing the lmost point to 0th index:------
    Point temp;
    temp=points[0];
    points[0]=points[lmost];
    points[lmost]=temp;
    //--------------------------------------------

    //Sort the remaining points based on polar order about lmost point:-
    pivot=points[0];
    sort(points+1,points+n,compare);
    //------------------------------------------------------------------

    //Remove the collinear points with pivot except the last one:---------
    int k=1;
    for(int i=0;i<n;i++)
    {
        if(i==(n-1) || orientation(pivot,points[i],points[i+1])!=0)
            points[k++]=points[i];
    }
    //--------------------------------------------------------------------

    //For storing the result
    stack<Point> hull;

    //Base condition
    if(k<3)
        return hull;

    //Getting the hull:----------------------
    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);
    for(int i=3;i<k;i++)
    {
        Point top=hull.top();
        hull.pop();
        while(orientation(hull.top(), top, points[i])!=2)
        {
            top = hull.top();
            hull.pop();
        }
        hull.push(top);
        hull.push(points[i]);
    }

    //Returning the result
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

    stack<Point> hull(ConvexHull(P,n));

    //Displaying the result:-----------------
    while(!hull.empty())
    {
        cout<<hull.top().x<<" "<<hull.top().y<<"\n";
        hull.pop();
    }
    //---------------------------------------
}
