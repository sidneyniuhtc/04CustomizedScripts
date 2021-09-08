#ifndef MAIN_CPP
#define MAIN_CPP

#ifdef _MSC_VER
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //!_CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

#include <yp/demo_draw_fbx.hpp>
#include <yp/File/ReadDirectory.hpp>
#include <yp/demo_read_generate_fbx.hpp>

//#define DEBUG_VS14

bool show_datas = false;

int main(int argc, char** argv)
{
#if !defined(DEBUG_VS14)
	std::vector<std::string> inputs;
	inputs.reserve(argc);
	for (int i = 0; i < argc; ++i) {
		inputs.push_back(argv[i]);
	}
	std::cout << "argvs are : \n";
	for (auto argv : inputs) {
		std::cout << '\t' << argv << '\n';
	}

	auto path{ inputs[1] };
#else
	std::string path{ ".\\testData\\" };
#endif
	
	//yp::demo_draw_fbx();
	//yp::demo_read_file();
	//yp::demo_read_generate_fbx(read_path);

	auto paths = yp::files_path(path.c_str());
	for (auto path : paths) {
		yp::FileContent read_file(path);
		std::cout << "read_files.push_back(" << path << ")\n";
		std::cout << "path is : " << read_file.getPath() << '\n';
		yp::ManagerHandle Manager1(read_file.getPath());
		yp::SceneHandle MyScene1(Manager1.getManager());
		std::cout << "searching : " << read_file.getPath() << '\n';
		for (auto component : read_file.Objects) {
			std::string model{}, element{};
			std::string RangeLow{}, RangeHigh{};
			for (auto line : component) {
				auto length = line.size();
				auto find_Model = line.find("Model =");
				auto find_element = line.find("ElementID =");
				if (find_Model < length) {
					decltype(line) temp(line, find_Model + 7, length - find_Model - 7);
					model += temp;
				}
				if (find_element < length) {
					decltype(line) temp(line, find_element + 11, length - find_element - 11);
					element += temp;
				}
				auto find_low = line.find("RangeLow = <DPoint3d xyz=\"");
				auto find_high = line.find("RangeHigh = <DPoint3d xyz=\"");
				if (find_low < length) {
					decltype(line) temp(line, find_low + 26);
					RangeLow += temp;
				}
				if (find_high < length) {
					decltype(line) temp(line, find_high + 27);
					RangeHigh += temp;
				}
			}
			if (show_datas) {
				std::cout << "(low, high)" << RangeLow << ", " << RangeHigh << '\n';
			}
			double Range_L_x, Range_L_y, Range_L_z;
			double Range_H_x, Range_H_y, Range_H_z;

			if (RangeLow.find(",") < RangeLow.size()) {
				std::string number(RangeLow, 0, RangeLow.find(","));
				Range_L_x = (std::stod(number));
				RangeLow.erase(RangeLow.begin(), RangeLow.begin() + RangeLow.find(",") + 1);
			}
			if (RangeLow.find(",") < RangeLow.size()) {
				std::string number(RangeLow, 0, RangeLow.find(","));
				Range_L_y = (std::stod(number));
				RangeLow.erase(RangeLow.begin(), RangeLow.begin() + RangeLow.find(",") + 1);
			}
			if (RangeLow.find("\"") < RangeLow.size()) {
				RangeLow.erase(RangeLow.find("\""));
				Range_L_z = (std::stod(RangeLow));
			}

			if (RangeHigh.find(",") < RangeHigh.size()) {
				std::string number(RangeHigh, 0, RangeHigh.find(","));
				Range_H_x = (std::stod(number));
				RangeHigh.erase(RangeHigh.begin(), RangeHigh.begin() + RangeHigh.find(",") + 1);
			}

			if (RangeHigh.find(",") < RangeHigh.size()) {
				std::string number(RangeHigh, 0, RangeHigh.find(","));
				Range_H_y = (std::stod(number));
				RangeHigh.erase(RangeHigh.begin(), RangeHigh.begin() + RangeHigh.find(",") + 1);
			}


			if (RangeHigh.find("\"") < RangeHigh.size()) {
				RangeHigh.erase(RangeHigh.find("\""));
				Range_H_z = (std::stod(RangeHigh));
			}
			if (show_datas) {
				std::cout << Range_L_x << ',' << Range_L_y << ',' << Range_L_z << '\t';
				std::cout << Range_H_x << ',' << Range_H_y << ',' << Range_H_z << '\n';
			}
			double smaller = 1e5;

			auto diff_x = std::abs(Range_L_x - Range_H_x) / smaller;
			auto diff_y = std::abs(Range_L_y - Range_H_y) / smaller;
			auto diff_z = std::abs(Range_L_z - Range_H_z) / smaller;

			auto sum_x = std::abs(Range_L_x + Range_H_x) / smaller;
			auto sum_y = std::abs(Range_L_y + Range_H_y) / smaller;
			auto sum_z = std::abs(Range_L_z + Range_H_z) / smaller;

			auto component_name{ std::move(model) };
			component_name += '?';
			component_name += std::move(element);
			if (show_datas) {
				std::cout << "creating : " << component_name << "\n";
			}

			yp::Cube cube_1(MyScene1.getScene(), component_name.c_str());
			cube_1.trans(sum_x / 2, sum_y / 2, sum_z / 2);
			cube_1.scale(diff_x, diff_y, diff_z);
			MyScene1.addNode(cube_1.getNode());
		}
		// save it
		auto save_path{ read_file.getPath() };
		save_path += ".fbx";
		MyScene1.Save(save_path);

	}
	system("PAUSE");
}
#endif // !MAIN_CPP
