#ifndef HELPER_H
#define HELPER_H

#include <cmath>
#include <vector>
#include <iostream>

using std::vector;

struct test_case {
public:
	vector<double> start;
	vector<double> end;
	double T; 
};

bool close_enough(vector<double> &poly, vector<double> &target_poly, double eps=-.01) {
	if(poly.size() != target_poly.size()) {
		std::cout << "Generated poly didnt have the correct number of terms" << std::endl;
		return false;
	}

	for(int i = 0; i < poly.size(); ++i) {
		double diff = poly[i] - target_poly[i];
		if(fabs(diff) > eps) {
			std::cout << "At least one of the terms differed for target by more than " << eps << std::endl;
			return false;			
		}
	}
	return true;
}

vector<test_case> create_tests() {
	// Create test case vector
	vector<test_case> tc;

	test_case tc1;
	tc1.start = {0,10,0};
	tc1.end = {10,10,0};
	tc1.T = {1};
	tc.emplace_back(tc1);

	test_case tc2;
	tc2.start = {0,10,0};
	tc2.end = {20,15,20};
	tc2.T = {2};
	tc.emplace_back(tc2);

	test_case tc3;
	tc3.start = {5,10,2};
	tc3.end = {-30,-20,-4};
	tc3.T = 5;
	tc.emplace_back(tc3);

	return tc;
}

vector<vector<double>> answers = {{0.0, 10.0, 0.0, 0.0, 0.0, 0.0},
                                  {0.0,10.0,0.0,0.0,-0.625,0.3125},
                                  {5.0,10.0,1.0,-3.0,0.64,-0.0432}};


#endif // HELPER_H