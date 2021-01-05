#include "helper.h"
#include "Eigen/Dense"

using Eigen::VectorXd;
using Eigen::MatrixXd;
vector<double > JMT(vector<double> &start, vector<double> &end, double T) {
	/**
	Calculates the Jerk Minimizing Trajectory that connects the initial state to 
	the final state in time T
	@param start - the vehicle start location given as a length 3 array corresponding 
	to the initial values on [s, s_dot, s_double_dot]
	@param end - the desired end state for the vehicle. Like "start" this is also a
	length 3 array.
	@param T - The duration, in seconds, in which this maneuver should occur.

	@output an array of length 6, each value corresponding to a coefficinet in
	the polynomial:
	s(t) = a_0 + a_1 * t + a_2 * t**2 + a_3 * t**3 + a_4 * t**4 + a_5 * t**5

	Example:
	> JMT([0,10,0], [10,10,0], 1)
	  [0.0, 10.0, 0.0, 0.0, 0.0, 0.0]
	**/ 

	double T_2 = T * T;
	double T_3 = T_2 * T;
	double T_4 = T_3 * T;
	double T_5 = T_4 * T;
	MatrixXd A = MatrixXd(3,3);
	A << T_3, T_4, T_5,
		 3 * T_2, 4 * T_3, 5 * T_4,
		 6 * T, 12 * T_2, 20 * T_3;
	
	MatrixXd b = MatrixXd(3,1);
	b << end[0] - (start[0] + start[1] * T + 0.5 * start[2] * T_2),
		 end[1] - (start[1] + start[2] * T),
		 end[2] - start[2];
	
	MatrixXd x = MatrixXd(3,1);
	x = A.inverse() * b; 

	vector<double> a(6,0.0);
	a[0] = start[0];
	a[1] = start[1];
	a[2] = (0.5) * start[2];
	a[3] = x(0,0);
	a[4] = x(1,0);
	a[5] = x(2,0);
	// for debugging - print vector a
	// for(int i = 0; i < a.size(); ++i) {
	// 	std::cout << a[i] << " ";
	// }
	// std::cout << std::endl;
	return a;
}

int main() {
	std::cout << "Hello Quintic Polynomial Solver" << std::endl;
	
	// create test cases
	vector <test_case>	tc = create_tests();
	bool total_correct = true;

	for(int i = 0; i < tc.size(); ++i) {
		vector<double> jmt = JMT(tc[i].start,tc[i].end, tc[i].T);
		bool corret = close_enough(jmt, answers[i]);
		total_correct &= corret;
	}

	if(!total_correct) {
		std::cout << "JMT output not corect " << std::endl;
	} else {
		std::cout << "JMT output is correct " << std::endl;
	}

	return 0;
}
