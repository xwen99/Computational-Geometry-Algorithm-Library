struct Point3
{
	double x, y, z;
	Point3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

typedef Point3 Vector3;

Vector3 operator+(const Vector3 &A, const Vector3 &B) { return Vector3(A.x + B.x, A.y + B.y, A.z + B.z); }
Vector3 operator-(const Point3 &A, const Point3 &B) { return Vector3(A.x - B.x, A.y - B.y, A.z - B.z); }
Vector3 operator*(const Vector3 &A, double p) { return Vector3(A.x * p, A.y * p, A.z * p); }
Vector3 operator/(const Vector3 &A, double p) { return Vector3(A.x / p, A.y / p, A.z / p); }

const double eps = 1e-8;
int dcmp(double x)
{
	if (fabs(x) < eps)
		return 0;
	else
		return x < 0 ? -1 : 1;
}

double Dot(const Vector3 &A, const Vector3 &B) { return A.x * B.x + A.y * B.y + A.z * B.z; }
double Length(const Vector3 &A) { return sqrt(Dot(A, A)); }
double Angle(const Vector3 &A, const Vector3 &B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
Vector3 Cross(const Vector3 &A, const Vector3 &B) { return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x); }

Point3 read_point3()
{
	Point3 p;
	scanf("%lf%lf%lf", &p.x, &p.y, &p.z);
	return p;
}