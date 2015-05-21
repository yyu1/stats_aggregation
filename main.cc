#include <iostream>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

namespace ba = boost::accumulators;

int main()
{

    // Define an accumulator set for calculating the mean and the
    // 2nd moment ...
    ba::accumulator_set<double, ba::stats<ba::tag::mean, ba::tag::moment<2> > > acc;

    // push in some data ...
    acc(1.2);
    acc(2.3);
    acc(3.4);
    acc(4.5);

    // Display the results ...
    std::cout << "Mean:   " << ba::mean(acc) << std::endl;
    std::cout << "Moment: " << ba::moment<2>(acc) << std::endl;

    return 0;

}


