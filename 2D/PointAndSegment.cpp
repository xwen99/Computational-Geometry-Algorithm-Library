//向量点乘
double Dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }
//向量模长
double Length(Vector A) { return sqrt(Dot(A, A)); }
//向量模长平方
double Length2(Vector A) { return Dot(A, A); }
//向量夹角
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
//向量叉乘
double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }
//三角形面积的2倍
double Area2(Point A, Point B, Point C) { return Cross(B - A, C - A); }
//向量旋转
Vector Rotate(Vector A, double rad)
{
    return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
//向量单位法向量（逆时针90°）
Vector Normal(Vector A)
{
    double L = Length(A);
    return Vector(-A.y / L, A.x / L);
}
//直线交点
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w)
{
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    return P + v * t;
}
//两点距离
double Distance(Point A, Point B) { return sqrt(Dot(B - A, B - A)); }
//两点距离平方
double Distance2(Point A, Point B) { return Dot(B - A, B - A); }
//点到直线的距离
double DistanceToLine(Point P, Point A, Point B)
{
    Vector v1 = B - A, v2 = P - A;
    return fabs(Cross(v1, v2)) / Length(v1);
}
//点到线段的距离
double DistanceToSegment(Point P, Point A, Point B)
{
    if (A == B)
        return Length(P - A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if (dcmp(Dot(v1, v2)) < 0)
        return Length(v2);
    else if (dcmp(Dot(v1, v3)) > 0)
        return Length(v3);
    else
        return fabs(Cross(v1, v2)) / Length(v1);
}
//点在直线上的垂足
Point GetLineProjection(Point P, Point A, Point B)
{
    Vector v = B - A;
    return A + v * (Dot(v, P - A) / Dot(v, v));
}
//判断线段是否规范相交（不考虑端点）
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1),
           c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
//判断点是否在线段上
bool OnSegment(Point p, Point a1, Point a2)
{
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) <= 0;
}
//判断线段是否相交
bool SegmentIntersection(Point a1, Point a2, Point b1, Point b2)
{
    if (dcmp(Cross(a2 - a1, b2 - b1)) == 0)
        return OnSegment(a1, b1, b2) || OnSegment(a2, b1, b2) || OnSegment(b1, a1, a2) || OnSegment(b2, a1, a2);
    else
    {
        Point p = GetLineIntersection(a1, a2 - a1, b1, b2 - b1);
        return OnSegment(p, a1, a2) && OnSegment(p, b1, b2);
    }
}