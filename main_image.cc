#define IMAGE_T unsigned int

#include <iostream>
#include <fstream>

#include "GlobalStatsGrid.hh"

namespace ba = boost::accumulators;

int main()
{

	//configuration constants
	const unsigned int latitude_span = 180;
	const unsigned long xdim_pixels = 172800;
	const unsigned long ydim_pixels = 86400;

	const unsigned int nrows_per_deg = xdim_pixels/latitude_span;
	const double pixel_size = 0.00208333333333333;

	const std:string in_file("/Volumes/wd_3t/maxent/250m/v4.2/biomass/maxent_agb_global_vcf5mask_v4.2.5_wd3_latlon.int");
	const std:string out_file("/Volumes/Global_250m/stats/maxent_agb_v4.2.5_wd3_1deg_stats.txt");

	//---------------end config

	IMAGE_T input_buffer[nrows_per_deg][xdim_pixels];
	

	GlobalStatsGrid *global_grid = new GlobalStatsGrid();


	//open input image file
	std::ifstream in_file_stream(in_file, std::ios::binary|std::ios::in);

	//Read input image by 1 degree latitude block at a time and input >0 agb pixels into grid data

	register int longitude;

	for (int latitude=0; latitude < latitude_span; latitude++) {
		//read the input block 1 row at a time into buffer
		for (int i=0; i<nrows_per_deg; i++) {
			in_file.read((char *) input_buffer[latitude], xdim_pixels);
		}

		//cycle through buffer and add >0 AGB values (can't use non-zero since -1 can be used for special purposes like water)
		for (int i=0; i<xdim_pixels; i++) {
			longitude = (unsigned int) (pixel_size * (double)xdim_pixels);
			if (longitude == 360) longitude = 359; //fix edge of last pixel
			for (int j=0; j<nrows_per_deg; j++) {
				if (input_buffer[j][i] > 0) {
					global_grid->addValue(((float)input_buffer[j][i]/10), (float)longitude, (float)latitude);
				}
			}
		}
	}

	//finished processing input file.  Close stream
	in_file_stream.close();
	

	std::ofstream out_file_stream;
	out_file_stream.open(out_file);
	global_grid->writeToFile(&out_file_stream);

	out_file_stream.close();

	delete global_grid;
  return 0;

}


