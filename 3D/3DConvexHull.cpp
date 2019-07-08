double rand01() { return rand() / (double)RAND_MAX; }
double randeps() { return (rand01() - 0.5) * eps; }
//加噪声
Point3 add_noise(const Point3 &p)
{
	return Point3(p.x + randeps(), p.y + randeps(), p.z + randeps());
}
//面
struct Face
{
	int v[3];
	Face(int a, int b, int c)
	{
		v[0] = a;
		v[1] = b;
		v[2] = c;
	}
	Vector3 Normal(const vector<Point3> &P) const
	{
		return Cross(P[v[1]] - P[v[0]], P[v[2]] - P[v[0]]);
	}
	// f是否能看见P[i]
	int CanSee(const vector<Point3> &P, int i) const
	{
		return Dot(P[i] - P[v[0]], Normal(P)) > 0;
	}
};
// 增量法求三维凸包
//遍历所有面，判断是否可见；然后遍历所有边，判断是否在阴影边界上
// 注意：没有考虑各种特殊情况（如四点共面）。实践中，请在调用前对输入点进行微小扰动
vector<Face> CH3D(const vector<Point3> &P)
{
	int n = P.size();
	vector<vector<int>> vis(n);
	for (int i = 0; i < n; i++)
		vis[i].resize(n);

	vector<Face> cur;
	cur.push_back(Face(0, 1, 2)); // 由于已经进行扰动，前三个点不共线
	cur.push_back(Face(2, 1, 0));
	for (int i = 3; i < n; i++)
	{
		vector<Face> next;
		// 计算每条边的“左面”的可见性
		for (int j = 0; j < cur.size(); j++)
		{
			Face &f = cur[j];
			int res = f.CanSee(P, i);
			if (!res)
				next.push_back(f);
			for (int k = 0; k < 3; k++)
				vis[f.v[k]][f.v[(k + 1) % 3]] = res;
		}
		for (int j = 0; j < cur.size(); j++)
			for (int k = 0; k < 3; k++)
			{
				int a = cur[j].v[k], b = cur[j].v[(k + 1) % 3];
				if (vis[a][b] != vis[b][a] && vis[a][b]) // (a,b)是分界线，左边对P[i]可见
					next.push_back(Face(a, b, i));
			}
		cur = next;
	}
	return cur;
}
//三维凸包结构体
struct ConvexPolyhedron
{
	int n;
	vector<Point3> P, P2;
	vector<Face> faces;
	//读入
	bool read()
	{
		if (scanf("%d", &n) != 1)
			return false;
		P.resize(n);
		P2.resize(n);
		for (int i = 0; i < n; i++)
		{
			P[i] = read_point3();
			P2[i] = add_noise(P[i]);
		}
		faces = CH3D(P2);
		return true;
	}
	//求重心
	Point3 centroid()
	{
		Point3 C = P[0];
		double totv = 0;
		Point3 tot(0, 0, 0);
		for (int i = 0; i < faces.size(); i++)
		{
			Point3 p1 = P[faces[i].v[0]], p2 = P[faces[i].v[1]], p3 = P[faces[i].v[2]];
			double v = -Volume6(p1, p2, p3, C);
			totv += v;
			tot = tot + Centroid(p1, p2, p3, C) * v;
		}
		return tot / totv;
	}
	//求重心到所有面的最短距离
	double mindist(Point3 C)
	{
		double ans = 1e30;
		for (int i = 0; i < faces.size(); i++)
		{
			Point3 p1 = P[faces[i].v[0]], p2 = P[faces[i].v[1]], p3 = P[faces[i].v[2]];
			ans = min(ans, fabs(-Volume6(p1, p2, p3, C) / Area2(p1, p2, p3)));
		}
		return ans;
	}
};