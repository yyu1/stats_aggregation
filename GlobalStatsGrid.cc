#include "GlobalStatsGrid.hh"
bool GlobalStatsGrid::inbounds(int xind, int yind) {
	if ((xind>=0) and (xind<GLOBALGRID_XDIM) and (yind>=0) and (yind<GLOBALGRID_YDIM)) {
		return true;
	} else {
		return false;
	}
}


//Longitude is expected to be between -180 and 180
//Latitude is expected to be between -90 and 90
void GlobalStatsGrid::addValue(double val, float longitude, float latitude)
{
	int xind = (longitude + 180) / (360/GLOBALGRID_XDIM);
	int yind = (90 - latitude) / (180/GLOBALGRID_YDIM);

	if (inbounds(xind,yind))
	{
		grid_accumulator[xind][yind](val);
	} else {
		std::cout << "Point with lat/lon:" << latitude << " " << longitude << " is out of bounds.  Skipping...";
	}
}

void GlobalStatsGrid::addValue(float val, float longitude, float latitude)
{
	int xind = (longitude + 180) / (360/GLOBALGRID_XDIM);
	int yind = (90 - latitude) / (180/GLOBALGRID_YDIM);

	if (inbounds(xind, yind)) {
		grid_accumulator[xind][yind](val);
	} else {
		std::cout << "Point with lat/lon:" << latitude << " " << longitude << " is out of bounds.  Skipping...";
	}
}


double GlobalStatsGrid::getMean(int x_ind, int y_ind) {
	if (inbounds(x_ind,y_ind)) 
	{
		return ba::mean(grid_accumulator[x_ind][y_ind]);
	} else {
		std::cout << "attempting to retrieve from xind,yind:" << x_ind << " " << y_ind << " is out of bounds, ignored.";
		return 0;
	}
}
double GlobalStatsGrid::getMax(int x_ind, int y_ind) {
	if (inbounds(x_ind,y_ind)) 
	{
		return ba::max(grid_accumulator[x_ind][y_ind]);
	} else {
		std::cout << "attempting to retrieve from xind,yind:" << x_ind << " " << y_ind << " is out of bounds, ignored.";
		return 0;
	}
}
double GlobalStatsGrid::getMin(int x_ind, int y_ind) {
	if (inbounds(x_ind,y_ind))
	{
		return ba::max(grid_accumulator[x_ind][y_ind]);
	} else {
		std::cout << "attempting to retrieve from xind,yind:" << x_ind << " " << y_ind << " is out of bounds, ignored.";
		return 0;
	}
}
double GlobalStatsGrid::getMedian(int x_ind, int y_ind) {
	if (inbounds(x_ind,y_ind))
	{
		return ba::median(grid_accumulator[x_ind][y_ind]);
	} else {
		std::cout << "attempting to retrieve from xind,yind:" << x_ind << " " << y_ind << " is out of bounds, ignored.";
		return 0;
	}
}
double GlobalStatsGrid::getVariance(int x_ind, int y_ind) {
	if (inbounds(x_ind,y_ind))
	{
		return ba::variance(grid_accumulator[x_ind][y_ind]);
	} else {
		std::cout << "attempting to retrieve from xind,yind:" << x_ind << " " << y_ind << " is out of bounds, ignored.";
		return 0;
	}
}
std::size_t GlobalStatsGrid::getCount(int x_ind, int y_ind) {
	if (inbounds(x_ind, y_ind))
	{
		return ba::count(grid_accumulator[x_ind][y_ind]);
	} else {
		std::cout << "attempting to retrieve from xind,yind:" << x_ind << " " << y_ind << " is out of bounds, ignored.";
		return 0;
	}
}