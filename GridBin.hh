//-------include guard-------
#ifndef __GRIDBIN_HH_INCLUDED__
#define __GRIDBIN_HH_INCLUDED__


//------forward declarations





//-----included dependencies
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/tail_quantile.hpp>





//-----Class definitions
namespace ba = boost::accumulators;

class GlobalStatsGrid
{
private:
	ba::accumulator_set<double, ba::features<ba::tag::mean, ba::tag::max, ba::tag::min, ba::tag::count, ba::tag::median, ba::tag::variance> grid_accumulator;

public:
	void addValue(double val);
	void addValue(float val);

	double getMean();
	double getMax();
	double getMin();
	double getMedian();
	std::size_t getCount();
	double getVariance();
	

};

#endif //__GRIDBIN_HH_INCLUDED__
