#include "MovingWindow.hpp"

using namespace std;
using namespace boost;

MovingWindow::MovingWindow(int n)
{
	sum = 0;
	ssq = 0;
	q = new boost::circular_buffer<double>(n);

}

/*~MovingWindow::MovingWindow() 
{
	delete q;
}*/

void MovingWindow::push(double v) 
{
	if (q->size() == q->capacity()) {
		double t = q->front();
		sum -= t;
		ssq -= t*t;
		q->pop_front();
	}
	q->push_back(v);
	sum += v;
	ssq += v*v;
}

double MovingWindow::size()
{
	return q->size();
}

double MovingWindow::mean() 
{
	return sum/size();
}

double MovingWindow::get_back()
{
	return q->back();
}

double MovingWindow::get_front()
{
	return q->front();
}

double MovingWindow::stddev()
{
	double numer = sqrt(((double)(size()) * ssq) - pow((double)(sum), 2));
	double denom = ((double)(size())) * ((double)(size() - 1));
	return (double)numer/denom;
}

bool MovingWindow::empty()
{
	return q->empty();
}	

/*int main()
{
	MovingWindow mvg_calc(6);
	for (int i=0; i<6; i++) {
		mvg_calc.push((double)i);
		cout << "mvg_calc.mean() == " << mvg_calc.mean();
		cout << " mvg_calc.stddev() == " << mvg_calc.stddev() << endl;
	}
	cout << "mvg_calc back: " << mvg_calc.get_back() << endl;
	cout << "mvg_calc front: " << mvg_calc.get_front() << endl;

}*/

