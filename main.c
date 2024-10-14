#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "pixel.h"

bool read_pixel_data(const std::string&filename,std::vector<Pixel>&pixel_list);
void average_colors(const std::vector<Pixel>&pixel_list);
void flip_vertically(std::vector<Pixel>&pixel_list);
void save_to_file(const std::string&filename,const std::vector<Pixel>&pixel_list);

bool read_pixel_data(const std::string& filename, std::vector<Pixel>& pixel_list) {
    std::ifstream file(filename);
    if (!file.is_open()) {
		// cerr is for printing error messages
        std::cerr << "Unable to open file: " << filename << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        Pixel pixel;

        std::getline(ss, token, ',');
        pixel.x = std::stoi(token);

        std::getline(ss, token, ',');
        pixel.y = std::stoi(token);

        std::getline(ss, token, ',');
        pixel.r = std::stof(token);

        std::getline(ss, token, ',');
        pixel.g = std::stof(token);

        std::getline(ss, token);
        pixel.b = std::stof(token);

        pixel_list.push_back(pixel);
    }
    file.close();
	return true;
}

void average_colors(const std::vector<Pixel>&pixel_list){
	if (pixel_list.empty());
	return;
	
	double total_r=0.0;
	double total_g=0.0;
	double total_b=0.0;
	
	
	for(const auto&pixel:pixel_list){
		total_r += pixel.r;
		total_g += pixel.g;
		total_b += pixel.b;
	}
	int count = pixel_list.size();
	std::cout<<"Average R: "<<total_r/count<<std::endl;
	std::cout<<"Average G: "<<total_g/count<<std::endl;
	std::cout<<"Average B: "<<total_b/count<<std::endl;
}

void flip_vertically(std::vector<Pixel>&pixel_list){
	const int y_max = 255;
	for(auto&pixel:pixel_list){
		pixel.y=y_max-pixel.y;
	}
}

void save_to_file(const std::string&filename,const std::vector<Pixel>&pixel_list){
	std::ofstream file(filename);
	if(!file.is_open()){
		std::cerr<<"Unable to open file for writing: "<<filename<<std::endl;
		return;
	}
	for(const auto&pixel:pixel_list){
		file<<pixel.x<<","<<pixel.y<<","<<pixel.r<<","<<pixel.g<<","<<pixel.b<<"\n";
	}
}

int main(int argc, char*argv[]){
	if(argc !=2){
		std::cerr<<"Usage: "<<argv[0]<<" <input_file>"<<std::endl;
		return 1;
	}
	std::vector<Pixel>pixel;
	if(!read_pixel_data(argv[1],pixel_list)){
		return 1;
	}
	average_colors(pixel_list);
	flip_vertically(pixel_list);
	save_to_file("flipped.dat",pixel_list);
	
	return 0;
}

