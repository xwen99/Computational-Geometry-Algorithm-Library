struct Line
{
	Point v;
	Vector p;
	Line(Point v, Vector p) : v(v), p(p) {}
	Point point(double t)
	{
		return v + p * t;
	}
};

struct Circle
{
	Point c;
	double r;
	Circle(Point c, double r) : c(c), r(r) {}
	Point point(double a)
	{
		return Point(c.x + r * cos(a), c.y + r * sin(a));
	}
};

int getLineCircleIntersection(Line L, Circle C, vector<Point> &sol)
{
	double d = DistanceToLine(C.c, L.v, L.v + L.p);
	if (dcmp(d - C.r) > 0)
		return 0;
	else if (dcmp(d - C.r) == 0)
	{
		Point P = L.v + L.p * (c - L.v, L.p) / Dot(L.p, L.p);
		sol.push_back(P);
		return 1;
	}
	else
	{
		double l = sqrt(r * C.r - d * d);
		Point P = L.v + L.p * (c - L.v, L.p) / Dot(L.p, L.p);
		Vector e = Normal(L.p);
		sol.push_back(P - e * l);
		sol.push_bcak(P + e * l);
		return 2;
	}
}
int getLineCircleIntersection(Line L, Circle C, double &t1, double &t2, vector<Point> &sol)
{
	double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
	double e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - C.r * C.r;
	double delta = f * f - 4 * e * g;
	if (dcmp(delta) < 0)
		return 0;
	if (dcmp(delta) == 0)
	{
		t1 = t2 = -f / (2 * e);
		sol.push_back(L.point(t1));
		return 1;
	}
	t1 = (-f - sqrt(delta)) / (2 * e);
	sol.push_back(L.point(t1));
	t2 = (-f + sqrt(delta)) / (2 * e);
	sol.push_back(L.point(t2));
	return 2;
}

double angle(Vector v) { return atan2(v.y, v.x); }

int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point> &sol)
{
	double d = Length(C1.c - C2.c);
	if (dcmp(d) == 0)
	{
		if (dcmp(C1.r - C2.r) == 0)
			return -1; //两圆重合
		return 0;
	}
	if (dcmp(C1.r + C2.r - d) < 0)
		return 0;
	if (dcmp(fabs(C1.r - C2.r) - d) > 0)
		return 0;

	double a = angle(C2.c - C1.c); //向量C1C2的极角
	double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));
	//C1C2到C1P1的角
	Point p1 = C1.point(a - da), p2 = C1.point(a + da);

	sol.push_back(p1);
	if (p1 == p2)
		return 1;
	sol.push_back(p2);
	return 2;
}
//过点p到圆C的切线。v[i]是第i条切线的向量。返回切线条数
int getTangents(Point p, Circle C, Vector *v)
{
	Vector u = C.c - p;
	double dist = Length(u);
	if (dist < C.r)
		return 0;
	else if (dcmp(dist - C.r) == 0)
	{ //p在圆上，只有一条切线
		v[0] = Rotate(u, pi / 2);
		return 1
	}
	else
	{
		double ang = asin(C.r / dist);
		v[0] = Rotate(u, -ang);
		v[1] = Rotate(u, +ang);
		return 2;
	}
}
//两圆公切线 返回切线的条数，-1代表无穷条
//a[i]和b[i]分别是第i条切线在圆A和圆B上的切点
int getTangents(Circle A, Circle B, Point *a, Point *b)
{
	int cnt = 0;
	if (A.r < B.r)
	{
		swap(A, B);
		swap(a, b);
	}
	int d2 = (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
	int rdiff = A.r - B.r;
	int rsum = A.r + B.r;
	if (d2 < rdiff * rdiff)
		return 0; //内含

	double base = atan2(B.y - A.y, B.x - A.x);
	if (d2 == 0 && A.r == B.r)
		return -1; //无穷多条切线
	if (d2 == rdiff * rdiff)
	{ //内切，1条切线
		a[cnt] = A.point(base);
		b[cnt] = B.point(base);
		cnt++;
		return 1;
	}
	//有外公切线
	double ang = acos((A.r - B.r) / sqrt(d2));
	a[cnt] = A.point(base + ang);
	b[cnt] = B.point(base + ang);
	cnt++;
	a[cnt] = A.point(base - ang);
	b[cnt] = B.point(base - ang);
	cnt++;
	if (d2 == rsum * rsum)
	{ //一条内公切线
		a[cnt] = A.point(base);
		b[cnt] = B.point(pi + base);
		cnt++;
	}
	else if (d2 > rsum * rsum)
	{ //两条内公切线
		double ang = acos((A.r + B.r) / sqrt(d2));
		a[cnt] = A.point(base + ang);
		b[cnt] = B.point(pi + base + ang);
		cnt++;
		a[cnt] = A.point(base - ang);
		b[cnt] = B.point(pi + base - ang);
		cnt++;
	}
	return cnt;
}
//三角形外接圆
Circle CircumscribedCircle(Point p1, Point p2, Point p3)
{
	double Bx = p2.x - p1.x, By = p2.y - p1.y;
	double Cx = p3.x - p1.x, Cy = p3.y - p1.y;
	double D = 2 * (Bx * Cy - By * Cx);
	double cx = (Cy * (Bx * Bx + By * By) - By * (Cx * Cx + Cy * Cy)) / D + p1.x;
	double cy = (Bx * (Cx * Cx + Cy * Cy) - Cy * (Bx * Bx + By * By)) / D + p1.y;
	Point p = Point(cx, cy);
	return Circle(p, Length(p1 - p));
}
//三角形内切圆
Circle InscribedCircle(Point p1, Point p2, Point p3)
{
	double a = Length(p2 - p3);
	double b = Length(p3 - p1);
	double c = Length(p1 - p2);
	Point p = (p1 * a + p2 * b + p3 * c) / (a + b + c);
	return Circle(p, DistanceToLine(p, p1, p2));
}