//-------include guard-------
#ifndef __GLOBALSTATSGRID_HH_INCLUDED__
#define __GLOBALSTATSGRID_HH_INCLUDED__


//------forward declarations





//-----included dependencies
#include <iostream>
#include <fstream>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/tail_quantile.hpp>
#include <math.h>


//-----Class definitions
//#define GLOBALGRID_XDIM 360
//#define GLOBALGRID_YDIM 180
#define GLOBALGRID_XDIM 360  
#define GLOBALGRID_YDIM 180 
#define MIN_POINTS_PER_BIN 1

namespace ba = boost::accumulators;

class GlobalStatsGrid
{
private:
  ba::accumulator_set<double, ba::features<ba::tag::mean, ba::tag::max, ba::tag::min, ba::tag::count, ba::tag::median, ba::tag::variance> > grid_accumulator[GLOBALGRID_XDIM][GLOBALGRID_YDIM];

	bool inbounds(int xind, int yind);

public:
	void addValue(double val, float longitude, float latitude);
	void addValue(float val, float longitude, float latitude);

	double getMean(int x_ind, int y_ind);
	double getMax(int x_ind, int y_ind);
	double getMin(int x_ind, int y_ind);
	double getMedian(int x_ind, int y_ind);
	std::size_t getCount(int x_ind, int y_ind);
	double getVariance(int x_ind, int y_ind);

	void writeToFile(std::ofstream *outfile);

};

#endif //__GLOBALSTATSGRID_HH_INCLUDED__
