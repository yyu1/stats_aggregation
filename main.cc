#define INPUT_BUFFER_SIZE 512   //512 characters per line of buffer for input
#define FIELD_BUFFER_SIZE 64

#include <iostream>

#include "GlobalStatsGrid.hh"

namespace ba = boost::accumulators;

int main()
{

		GlobalStatsGrid *global_grid = new GlobalStatsGrid();


		//open input csv file
		std::string in_file = "/Volumes/YifanLaCie1T/global/glas/lefsky/12_10_2012/global_hlorey_121012_wwfbiome_globcover_vcf_type_srtm_agb.csv";

		char tmp_line[INPUT_BUFFER_SIZE];
		char field_buffer[FIELD_BUFFER_SIZE];
		std::ifstream input(in_file);
		
		std::vector<std::string> fields;

		//read header line
		input.getline(tmp_line, INPUT_BUFFER_SIZE);

		register float longitude, latitude, agb;
		//test read 20 lines
//		for (int i=0; i<20; i++) {
//			fields.clear();
//			input.getline(tmp_line, INPUT_BUFFER_SIZE);

		unsigned long line_counter = 2;
		while(input.getline(tmp_line, INPUT_BUFFER_SIZE)) {
			fields.clear();
			
			std::stringstream linestream(tmp_line);

			while(linestream.getline(field_buffer,FIELD_BUFFER_SIZE,',')) {
				fields.push_back(field_buffer);
			}

			std::vector<std::string>::iterator it = fields.begin();
			//while(it != fields.end()) {
			//	std::cout << (*it) << " ";
			//	it++;
			//}
			//std::cout << std::endl;

			//Convert fields to longitude, latitude, and AGB
			try {
				longitude = std::stof(fields[0]);
				latitude = std::stof(fields[1]);
				agb = std::stof(fields[11]);  //AGB
				//agb = std::stof(fields[2]);  //hlorey
				if (agb > 0) global_grid->addValue(agb, longitude, latitude);
			} catch (const std::invalid_argument& ia) {
	  		std::cerr << "Invalid argument: " << ia.what() << "at line " << line_counter << std::endl;
  		}
			line_counter++;
		}
		

		std::string out_file = "./glas_stats_out_agb_4.2.5_1deg_nomin.txt";

		std::ofstream out_file_stream;
		out_file_stream.open(out_file);
		global_grid->writeToFile(&out_file_stream);


		delete global_grid;
    return 0;

}


