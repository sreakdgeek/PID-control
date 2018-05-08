#include<boost/circular_buffer.hpp>
#include <iostream>
#include <math.h>

class MovingWindow {
	private:
		boost::circular_buffer<double> *q;
		double sum;
		double ssq;
	public:
		MovingWindow(int n);
		void push(double v);
		double size();
		double mean();
		double stddev();
		double get_back();
		double get_front();
		bool empty();
};
