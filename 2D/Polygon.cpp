typedef Point *Polygon;
//or
//vector<Point>
//多边形面积
double PolygonArea(Point *p, int n)
{
	double area = 0;
	for (int i = 1; i < n - 1; i++)
		area += Cross(p[i] - p[0], p[i + 1] - p[0]);
	return area / 2;
}
//点在多边形内判定（用到叉积）
bool IsPointInPolygon(Point p, Polygon poly, int n)
{
	int wn = 0;
	for (int i = 0; i < n; ++i)
	{
		if (OnSegment(p, poly[(i + 1) % n], poly[i]))
			return true;
		int k = dcmp(Cross(poly[(i + 1) % n] - poly[i], p - poly[i]));
		int d1 = dcmp(poly[i].y - p.y);
		int d2 = dcmp(poly[(i + 1) % n].y - p.y);
		if (k > 0 && d1 <= 0 && d2 > 0)
			++wn;
		if (k < 0 && d2 <= 0 && d1 > 0)
			--wn;
	}
	if (wn != 0)
		return true;
	return false;
}
//计算凸包，输入点数组p，个数为n，输出点数组ch。函数返回凸包顶点数。
//输入不能有重复点。函数执行完后输入点的顺序被破坏
//如果不希望在凸包的边上有输入点，把两个<=改成<
//在精度较高时建议使用dcmp
int ConvexHull(Polygon p, int n, Polygon ch)
{
	sort(p, p + n);
	int m = 0;
	for (int i = 0; i < n; i++)
	{
		while (m > 1 && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)
			m--;
		ch[m++] = p[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; i--)
	{
		while (m > k && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)
			m--;
		ch[m++] = p[i];
	}
	if (n > 1)
		m--;
	return m;
}
// 点集凸包
// 如果不希望在凸包的边上有输入点，把两个 <= 改成 <
// 注意：输入点集会被修改
vector<Point> ConvexHull(vector<Point> &p)
{
	// 预处理，删除重复点
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());

	int n = p.size();
	int m = 0;
	vector<Point> ch(n + 1);
	for (int i = 0; i < n; i++)
	{
		while (m > 1 && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)
			m--;
		ch[m++] = p[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; i--)
	{
		while (m > k && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)
			m--;
		ch[m++] = p[i];
	}
	if (n > 1)
		m--;
	ch.resize(m);
	return ch;
}
// 旋转卡壳
// 返回点集直径的平方（对踵点对）
int diameter2(vector<Point> &points)
{
	vector<Point> p = ConvexHull(points);
	int n = p.size();
	if (n == 1)
		return 0;
	if (n == 2)
		return Distance2(p[0], p[1]);
	p.push_back(p[0]); // 免得取模
	int ans = 0;
	for (int u = 0, v = 1; u < n; u++)
	{
		// 一条直线贴住边p[u]-p[u+1]
		for (;;)
		{
			// 当Area(p[u], p[u+1], p[v+1]) <= Area(p[u], p[u+1], p[v])时停止旋转
			// 即Cross(p[u+1]-p[u], p[v+1]-p[u]) - Cross(p[u+1]-p[u], p[v]-p[u]) <= 0
			// 根据Cross(A,B) - Cross(A,C) = Cross(A,B-C)
			// 化简得Cross(p[u+1]-p[u], p[v+1]-p[v]) <= 0
			int diff = Cross(p[u + 1] - p[u], p[v + 1] - p[v]);
			if (diff <= 0)
			{
				ans = max(ans, Distance2(p[u], p[v])); // u和v是对踵点
				if (diff == 0)
					ans = max(ans, Distance2(p[u], p[v + 1])); // diff == 0时u和v+1也是对踵点
				break;
			}
			v = (v + 1) % n;
		}
	}
	return ans;
}