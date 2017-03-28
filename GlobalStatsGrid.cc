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
double GlobalStatsGrid::getMeanLatLon(float longitude, float latitude)
{
	int xind = (longitude + 180) / (360/GLOBALGRID_XDIM);
	int yind = (90 - latitude) / (180/GLOBALGRID_YDIM);

	return this->getMean(xind, yind);
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
		return ba::min(grid_accumulator[x_ind][y_ind]);
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

void GlobalStatsGrid::writeToFile(std::ofstream *outfile) {
	(*outfile) << "x_index,y_index,count,mean,min,max,median,variance,stdev" << std::endl;
	for (int j=0; j<GLOBALGRID_YDIM; j++) {
		for (int i=0; i<GLOBALGRID_XDIM; i++) {
//			if (this->getCount(i,j) > 0) {  //debug
//				std::cout << this->getCount(i,j) << " points at i, j" << i << " " << j << std::endl;
//			}   // debug
			if (this->getCount(i,j) >= MIN_POINTS_PER_BIN) {
				(*outfile) << i << "," << j << "," << this->getCount(i,j) << ",";
				(*outfile) << this->getMean(i,j) << ",";
				(*outfile) << this->getMin(i,j) << ",";
				(*outfile) << this->getMax(i,j) << ",";
				(*outfile) << this->getMedian(i,j) << ",";
				(*outfile) << this->getVariance(i,j) << ",";
				(*outfile) << sqrt(this->getVariance(i,j)) << std::endl;
				
			}

		}
	}

}


void GlobalStatsGrid::writeToFileWithVCF(GlobalStatsGrid *vcf_grid, std::ofstream *outfile) {
	(*outfile) << "x_index,y_index,count,agb_mean,agb_min,agb_max,agb_median,agb_variance,agb_stdev,vcf_mean,vcf_min,vcf_max,vcf_median,vcf_variance,vcf_stdev" << std::endl;
	for (int j=0; j<GLOBALGRID_YDIM; j++) {
		for (int i=0; i<GLOBALGRID_XDIM; i++) {
//			if (this->getCount(i,j) > 0) {  //debug
//				std::cout << this->getCount(i,j) << " points at i, j" << i << " " << j << std::endl;
//			}   // debug
			if (this->getCount(i,j) >= MIN_POINTS_PER_BIN) {
				(*outfile) << i << "," << j << "," << this->getCount(i,j) << ",";
				(*outfile) << this->getMean(i,j) << ",";
				(*outfile) << this->getMin(i,j) << ",";
				(*outfile) << this->getMax(i,j) << ",";
				(*outfile) << this->getMedian(i,j) << ",";
				(*outfile) << this->getVariance(i,j) << ",";
				(*outfile) << sqrt(this->getVariance(i,j)) << ",";
				(*outfile) << vcf_grid->getMean(i,j) << ",";
				(*outfile) << vcf_grid->getMin(i,j) << ",";
				(*outfile) << vcf_grid->getMax(i,j) << ",";
				(*outfile) << vcf_grid->getMedian(i,j) << ",";
				(*outfile) << vcf_grid->getVariance(i,j) << ",";
				(*outfile) << sqrt(vcf_grid->getVariance(i,j)) << std::endl;
				
			}

		}
	}

}


void GlobalStatsGrid::writeVCFWeightedMeanToFile(std::ofstream *outfile) {
	(*outfile) << "x_index,y_index,count,weighted_mean" << std::endl;
	for (int j=0; j<GLOBALGRID_YDIM; j++) {
		for (int i=0; i<GLOBALGRID_XDIM; i++) {
			if (this->getCount(i,j) >= MIN_POINTS_PER_BIN) {
				(*outfile) << i << "," << j << "," << this->getCount(i,j) << ",";
				(*outfile) << this->getMean(i,j) << std::endl;
			}

		}
	}

}


