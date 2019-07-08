//角度转弧度
double torad(double deg)
{
	return deg / 180 * acos(-1); //acos(-1)==pi
}
//经纬度（角度）转化为空间坐标
void get_coord(double R, double lat, double lng, double &x, double &y, double &z)
{
	lat = torad(lat);
	lng = torad(lng);
	x = R * cos(lat) * cos(lng);
	y = R * cos(lat) * sin(lng);
	z = R * sin(lat);
}