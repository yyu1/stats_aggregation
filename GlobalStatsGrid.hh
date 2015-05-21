//-------include guard-------
#ifndef __GLOBALSTATSGRID_HH_INCLUDED__
#define __GLOBALSTATSGRID_HH_INCLUDED__


//------forward declarations





//-----included dependencies
#include "GridBin.hh"




//-----Class definitions
class GlobalStatsGrid
{
private:
	GridBin global_grid[360][180];

public:
	void addValue(double val, float longitude, float latitude);
	void addValue(float val, float longitude, float latitude);

	double getMean(int x_ind, int y_ind);
	double getMax(int x_ind, int y_ind);
	double getMin(int x_ind, int y_ind);
	double getMedian(int x_ind, int y_ind);
	std::size_t getCount(int x_ind, int y_ind);
	double getVariance(int x_ind, int y_ind);

};

#endif //__GLOBALSTATSGRID_HH_INCLUDED__
