/*
Author: Pritam Pathak
https://github.com/Priprocks

Problem: http://codeforces.com/problemset/problem/166/B
*/

#include<iostream>
#include<math.h>
#include<stack>
#include<algorithm>
#define ll long long int
#define MAX 1000005
using namespace std;

struct Point
{
    ll x,y;
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
    ll diff=(q.y-p.y)*(r.x-q.x) - (r.y-q.y)*(q.x-p.x);
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
        ll dista=pow(pivot.x-a.x,2)+ pow(pivot.y-a.y,2);
        ll distb=pow(pivot.x-b.x,2)+ pow(pivot.y-b.y,2);
        return dista<distb;
    }
    return o==2;
}

stack<Point> ConvexHull(Point points[],ll n)
{
    //Finding the lowermost point:----------------------------------------------
    ll lmost=0;
    for(ll i=1;i<n;i++)
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
    ll k=1;
    for(ll i=0;i<n;i++)
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
    for(ll i=3;i<k;i++)
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
    //Input:---------------------------------
    Point total[MAX];
    ll n;
    cin>>n;
    for(ll i=0;i<n;i++)
        cin>>total[i].x>>total[i].y;
    ll m;
    cin>>m;
    Point B[m];
    for(ll i=0;i<m;i++)
    {
        cin>>total[i+n].x>>total[i+n].y;
        B[i]=total[i+n];
    }
    //----------------------------------------

    stack<Point> hull(ConvexHull(total,n+m));
    int flag=0;
    Point p1,p2,start=hull.top();
    p1=start;
    ll hull_size=hull.size();
    //cout<<"Hull Size:"<<hull_size<<"\n";
    hull.pop();
    for(ll _=0;_<hull_size;_++)
    {
        if(!hull.empty())
        {
            p2=hull.top();
            hull.pop();
        }
        else
            p2=start;

        for(ll i=0;i<m;i++)
        {
            ll on_line=(B[i].y-p2.y)*(p1.x-p2.x)==(B[i].x-p2.x)*(p1.y-p2.y);
            ll ycheck=B[i].y>=min(p1.y,p2.y) && B[i].y<=max(p1.y,p2.y);
            ll xcheck=B[i].x>=min(p1.x,p2.x) && B[i].x<=max(p1.x,p2.x);
            //cout<<"B[i]:"<<B[i].x<<" - "<<B[i].y<<"\n";
            //cout<<"p1:"<<p1.x<<" - "<<p1.y<<"\n";
            //cout<<"p2:"<<p2.x<<" - "<<p2.y<<"\n";
            //cout<<on_line<<" "<<ycheck<<" "<<xcheck<<"\n\n";
            if(on_line && ycheck && xcheck)
            {

                flag=1;
                break;
            }
        }
        p1=p2;
        if(flag==1)
            break;
    }

    if(flag==0)
        cout<<"YES\n";
    else
        cout<<"NO\n";

}
