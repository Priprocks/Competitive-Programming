# Mathematical Algorithms

## Implementations-

* **FFT**

* **Improved FFT**


## Approach-

* **Sum of series: 5 + 55 + 555 + ...**

    ![=5/9(5+55+555+...)](http://latex.codecogs.com/gif.latex?%3D5/9%20%289&plus;99&plus;999&plus;...%29)

    ![=5/9{(10+10^2+10^3+...)-n}](http://latex.codecogs.com/gif.latex?%3D5/9%20%7B%2810&plus;10%5E2&plus;10%5E3&plus;...%29-n%7D)

    ![=50(10^n-1)/81 - 5n/9](http://latex.codecogs.com/gif.latex?%3D50%2810%5En-1%29/81%20-%205n/9)

* **HCF of fractional Numbers**

    -LCM of numerators:  a

    -HCF of denominators:b

    -Answer: Reduced form of a/b

* **n<sup>th</sup> term of series 3,9,21,41,...**

    ![\sum n^2+\sum n+1](http://latex.codecogs.com/gif.latex?%5Csum%20n%5E2&plus;%5Csum%20n&plus;1)

* **Sum of series: (n<sup>2</sup> - 1<sup>2</sup>)  + 2(n<sup>2</sup> - 2<sup>2</sup>) + ... + n(n<sup>2</sup> - n<sup>2</sup>)**

    ![1/4 (n^2)(n^2-1)](http://latex.codecogs.com/gif.latex?1/4%20%28n%5E2%29%28n%5E2-1%29)

* **Day of the week**

    Tomohiko Sakamoto Algorithm:

        -Increment for year(y)- (y + y/4- y/100+ y/400)

        -Increment for month(m)- [0,3,2,5,0,3,5,1,4,6,2,4]

        -Increment for day(d)- d

    [Note: If the month is January or February, the year must be decremented by 1 to account for the leap year problem]
