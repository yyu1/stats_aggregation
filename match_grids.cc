//Matches up grid values from GLAS stats output and Image stats output

//Use key-value map where key = longitude * 1000 + latitude (in degrees)


#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>

inline int get_key(int x_ind, int y_ind) {
	return x_ind * 1000 + y_ind;
}

std::pair<int,int> get_index(int key) {
	std::pair<int,int> return_pair(key/1000, key % 1000);
	return return_pair;
}

int main()
{

	std::map<int,float> glas_mean_values, image_mean_values;

	const std::string glas_file("/Volumes/Global_250m/stats/glas_v4.2.5_1deg_stats.txt");
	const std::string maxent_file("/Volumes/Global_250m/stats/maxent_agb_v4.2.5_wd3_1deg_stats.txt");

	//input buffer
	const int input_buffer_size = 256;
	const int field_buffer_size = 64;
	const int min_count = 2000;
	char line_buffer[input_buffer_size];
	char field_buffer[field_buffer_size];


	//temporary variables
	register float agb;
	register int x_ind, y_ind, count;
	std::vector<std::string> fields;
	
	//Read GLAS txt file and update map.
	std::ifstream input_stream_glas(glas_file);

	//Read header line	
	input_stream_glas.getline(line_buffer, input_buffer_size);

	unsigned long line_counter = 2;	
	while(input_stream_glas.getline(line_buffer, input_buffer_size)) {
		fields.clear();
		std::stringstream linestream(line_buffer);

		while(linestream.getline(field_buffer,field_buffer_size,',')) {
			fields.push_back(field_buffer);
		}

		//convert needed values to correct types
		try {
			x_ind = std::stoi(fields[0]);
			y_ind = std::stoi(fields[1]);
			count = std::stoi(fields[2]);
			agb = std::stof(fields[3]);  //4th field for mean agb
			if (count >= min_count) glas_mean_values[get_key(x_ind,y_ind)] = agb;
		} catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << "at line " << line_counter << std::endl;
    }
		line_counter++;
	}
	input_stream_glas.close();

	//Read Image txt file and update map
	std::ifstream input_stream_image(maxent_file);

	//Read header line	
	input_stream_image.getline(line_buffer, input_buffer_size);

	line_counter = 2;	
	while(input_stream_image.getline(line_buffer, input_buffer_size)) {
		fields.clear();
		std::stringstream linestream(line_buffer);

		while(linestream.getline(field_buffer,field_buffer_size,',')) {
			fields.push_back(field_buffer);
		}

		//convert needed values to correct types
		try {
			x_ind = std::stoi(fields[0]);
			y_ind = std::stoi(fields[1]);
			agb = std::stof(fields[3]);  //4th field for mean agb
			image_mean_values[get_key(x_ind,y_ind)] = agb;
		} catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << "at line " << line_counter << std::endl;
    }
		line_counter++;
	}

	input_stream_image.close();


	//std::cout << glas_mean_values.size() << ' ' << image_mean_values.size() << std::endl; //debug

	//write output

	const std::string out_file("/Volumes/Global_250m/stats/glas_maxent_mean_agb_matched_v4.2.5_2000min.txt");

	std::ofstream out_file_stream(out_file);

	out_file_stream << "x_index,y_index,glas_mean_agb,maxent_mean_agb" << std::endl;

	std::map<int,float>::iterator it = glas_mean_values.begin();

	while(it != glas_mean_values.end()) {
		std::map<int,float>::iterator image_it = image_mean_values.find((*it).first);
		if (image_it != image_mean_values.end()) {
			std::pair<int,int> index_pair = get_index((*it).first);
			out_file_stream << index_pair.first << "," << index_pair.second << ",";
			out_file_stream << (*it).second << "," << (*image_it).second << std::endl;
		}
		it++;
	}
	out_file_stream.close();

	return 0;
}
