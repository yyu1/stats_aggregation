//Matches up grid values from GLAS stats output and Image stats output

//Use key-value map where key = longitude * 1000 + latitude (in degrees)


#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

inline int get_key(int x_ind, int y_ind) {
	return x_ind * 1000 + y_ind;
}

std::pair<int,int> get_index(int key) {
	std::pair<int,int> return_pair(key/1000, key % 1000);
	return return_pair;
}

int main()
{

//	std::map<int,float> glas_mean_values, image_mean_values;
	std::map<int,std::vector<float> > glas_values, image_values;

	const std::string glas_file("/Volumes/Global_250m/stats/glas_stats_out_agb_4.2.5_1deg_nomin.txt");
	const std::string maxent_file("/Volumes/Global_250m/stats/maxent_agb_v4.2.5_wd3_1deg_stats.txt");
	//const std::string glas_file("/Volumes/Global_250m/stats/glas_stats_out_hlorey.txt");
	//const std::string maxent_file("/Volumes/Global_250m/stats/maxent_hlorey_v4.2.5_1deg_stats.txt");
	//const std::string glas_file("/Volumes/Global_250m/stats/glas_stats_out_hlorey_2deg.txt");
	//const std::string maxent_file("/Volumes/Global_250m/stats/maxent_hlorey_v4.2.5_2deg_stats.txt");

	//input buffer
	const int input_buffer_size = 512;
	const int field_buffer_size = 64;
	const int min_count = 1000;
	char line_buffer[input_buffer_size];
	char field_buffer[field_buffer_size];


	//temporary variables
	register float value;
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
			value = std::stof(fields[3]);  //4th field for mean value 
			if (count >= min_count) {
				std::vector<float> tmp_vector;
				tmp_vector.push_back(value);
				tmp_vector.push_back((float)count);
				glas_values[get_key(x_ind,y_ind)] = tmp_vector;
			}
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
			count = std::stoi(fields[2]);
			value = std::stof(fields[3]);  //4th field for mean value
			if (count >= min_count) {
				std::vector<float> tmp_vector;
				tmp_vector.push_back(value);
				tmp_vector.push_back(count);
				image_values[get_key(x_ind,y_ind)] = tmp_vector;
			}
		} catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << "at line " << line_counter << std::endl;
    }
		line_counter++;
	}

	input_stream_image.close();



	//write output

	//const std::string out_file("/Volumes/Global_250m/stats/glas_maxent_mean_agb_matched_v4.2.5_2000min.txt");
	//const std::string out_file("/Volumes/Global_250m/stats/glas_maxent_mean_hlorey_matched_v4.2.5_2deg.txt");
	const std::string out_file("/Volumes/Global_250m/stats/glas_maxent_mean_agb_matched_v4.2.5_1deg_1000min.txt");

	std::ofstream out_file_stream(out_file);

	out_file_stream << "x_index,y_index,glas_mean_value,glas_count,maxent_mean_value,maxent_count" << std::endl;

	std::map<int,std::vector<float> >::iterator it = glas_values.begin();

	while(it != glas_values.end()) {
		std::map<int,std::vector<float> >::iterator image_it = image_values.find((*it).first);
		if (image_it != image_values.end()) {
			std::pair<int,int> index_pair = get_index((*it).first);
			out_file_stream << index_pair.first << "," << index_pair.second << ",";
			out_file_stream << (*it).second[0] << "," << (*it).second[1] << ",";
			out_file_stream << (*image_it).second[0] << "," << (*image_it).second[1] << std::endl;
		}
		it++;
	}
	out_file_stream.close();

	return 0;
}
