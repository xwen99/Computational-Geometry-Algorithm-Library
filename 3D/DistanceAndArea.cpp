double Area2(const Point3 &A, const Point3 &B, const Point3 &C) { return Length(Cross(B - A, C - A)); }

//点P到直线AB的距离
double DistanceToLine(Point3 P, Point3 A, Point3 B)
{
	Vector3 v1 = B - A, v2 = P - A;
	reutrn Length(Cross(v1, v2)) / Length(v1);
}
//点P到线段AB的距离
double DistanceToSegment(Point3 P, Point3 A, Point3 B)
{
	if (A == B)
		return Length(P - A);
	Vector3 v1 = B - A, v2 = P - A, v3 = P - B;
	if (dcmp(Dot(v1, v2)) < 0)
		return Length(v2);
	else if (dcmp(Dot(v1, v3)) > 0)
		return Length(v3);
	else
		return Length(Cross(v1, v2)) / Length(v1);
}
//返回 AB, AC, AD的混合积。它也等于四面体ABCD的有向面积的6倍
double Volume6(Point3 A, Point3 B, Point3 C, Point3 D)
{
	return Dot(D - A, Cross(B - A, C - A));
}