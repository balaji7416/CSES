#include <bits/stdc++.h>
using namespace std;
#define int long long

// Created: 2026-06-29 11:25
// ================== Point ==================
struct Point
{
    long long x, y;

    Point() {}
    Point(long long x, long long y) : x(x), y(y) {}

    Point operator+(const Point &p) const
    {
        return {x + p.x, y + p.y};
    }

    Point operator-(const Point &p) const
    {
        return {x - p.x, y - p.y};
    }

    Point operator*(long long k) const
    {
        return {x * k, y * k};
    }

    bool operator==(const Point &p) const
    {
        return x == p.x && y == p.y;
    }
};

int orient(Point A, Point B, Point C)
{
    Point AB = B - A;
    Point AC = C - A;

    int cross_prod = AB.x * AC.y - AB.y * AC.x;
    return cross_prod;
}

int32_t
main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
    {
        int x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        Point A(x1, y1), B(x2, y2), C(x3, y3);
        int o = orient(A, B, C);

        if (o > 0)
            cout << "LEFT" << endl;
        else if (o < 0)
            cout << "RIGHT" << endl;
        else
            cout << "TOUCH" << endl;
    }
    return 0;
}