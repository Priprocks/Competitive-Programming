#include<iostream>
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

//This function takes 2 points and returns whether
//they intersect or not
int intersect(Point p1, Point q1, Point p2, Point q2)
{
    //Line segment 1:
    //p1-q1
    //Line segment 2:
    //p2-q2
    //When points are not collinear:--------------------------------------------
    //– o1=(p1, q1, p2) and o2=(p1, q1, q2) have different orientations and
    //– o3=(p2, q2, p1) and o4=(p2, q2, q1) have different orientations.
    int o1=orientation(p1,q1,p2);
    int o2=orientation(p1,q1,q2);
    int o3=orientation(p2,q2,p1);
    int o4=orientation(p2,q2,q1);
    //Points of each line are on either side of the other line
    if(o1!=o2 && o3!=o4)
        return 1;
    //--------------------------------------------------------------------------

    //Special Case:-------------------------------------------------------------
    //– (p1, q1, p2), (p1, q1, q2), (p2, q2, p1), and (p2, q2, q1)
    //  are all collinear and
    //– the x-projections of (p1, q1) and (p2, q2) intersect
    //– the y-projections of (p1, q1) and (p2, q2) intersect
    if(o1==0 && o2==0 && o3==0 && 04==0)
    {
        int min1,max1,min2,max2;
        int flagx=0, flagy=0;
        //Checking x-projections:-----------------
        min1=min(p1.x,q1.x); max1=max(p1.x,q1.x);
        min2=min(p2.x,q2.x); max2=max(p2.x,q2.x);
        if(min1<=min2 && max1>=min2)
            flagx=1;
        else if(min2<=min1 && max2>=min1)
            flagx=1;
        //----------------------------------------

        //Checking y-projections:-----------------
        min1=min(p1.y,q1.y); max1=max(p1.y,q1.y);
        min2=min(p2.y,q2.y); max2=max(p2.y,q2.y);
        if(min1<=min2 && max1>=min2)
            flagy=1;
        else if(min2<=min1 && max2>=min1)
            flagy=1;
        //----------------------------------------

        if(flagx==1 && flagy==1)
            return 1;
    }
    //--------------------------------------------------------------------------

    return 0;
}

int main()
{
    //Line segment 1: P1-Q1
    //Point P1:--------------------------
    Point P1;
    cout<<"Coordinates of point P1:\n";
    cin>>P1.x>>P1.y;
    //------------------------------------
    //Point Q1:--------------------------
    Point Q1;
    cout<<"Coordinates of point Q1:\n";
    cin>>Q1.x>>Q1.y;
    //------------------------------------

    //Line segment 1: P2-Q2
    //Point P2:--------------------------
    Point P2;
    cout<<"Coordinates of point P1:\n";
    cin>>P2.x>>P2.y;
    //------------------------------------
    //Point Q2:--------------------------
    Point Q2;
    cout<<"Coordinates of point P1:\n";
    cin>>Q2.x>>Q2.y;
    //------------------------------------

    intersect(P1,Q1,P2,Q2)? cout<<"Yes\n" : cout<<"No\n";

}
