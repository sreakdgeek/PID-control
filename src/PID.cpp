#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {

	// Initialize the PID coefficients.
	Kp = Kp_;
	Ki = Ki_;
	Kd = Kd_;

	time_steps = 0;

	// Initialize the errors
	//p_error = 0;
	//i_error = 0;
	//d_error = 0;

	// Set min and max terms
	double max_val = std::numeric_limits<double>::max()	;
	double min_val = std::numeric_limits<double>::max()	;

	training_steps = 100;
	eval_steps = 2500;
	is_twiddle_required = false;
	best_error = max_val;
	total_error = 0.0;
	
	//tolerance_ = 0.2;
	tolerance_ = 0.000001;
	pid_index = 0;
	num_params = 3;

	is_dp_added = false;
	is_dp_subtracted = false;

	std::cout << "Before starting Twiddle." << std::endl;

	twiddler = new Twiddle(tolerance_, 0.0001, 0.0001, 0.0001);

	std::cout << "After starting Twiddle." << std::endl;
}

int PID::getTimeSteps()
{
	return time_steps;
}

void PID::UpdateError(double cte) {

	double delta_t = 1.0;
	d_error = (cte - p_error) / delta_t;
	p_error = cte;
	i_error += cte;
	time_steps++;

	
	if (is_twiddle_required) {

		std::cout << "DEBUG: twiddle required." << std::endl;

		vector<double> best_params;
		best_params.push_back(Kp);
		best_params.push_back(Ki);
		best_params.push_back(Kd);
		best_params.push_back(total_error);
		best_params.push_back(best_error);
		best_params.push_back(is_dp_added);
		best_params.push_back(is_dp_subtracted);

		std::cout << "DEBUG: After pushing back best parameters" << std::endl;

		std::cout << "DEBUG: Before calling twiddle" << std::endl;

		vector<double> best_params_evaluated = twiddler->twiddle(best_params,
									 cte, total_error, 
									 tolerance_, best_error, 
									 is_dp_added, is_dp_subtracted, 
									 time_steps, training_steps, 
									 eval_steps, pid_index);

		std::cout << "DEBUG best_params_evaluated size = " << best_params_evaluated.size() << std::endl;

		if (best_params_evaluated.size() == 7)
		{
			if (time_steps > training_steps)
			{
				Kp = best_params_evaluated[0];
				Ki = best_params_evaluated[1];
				Kd = best_params_evaluated[2];
			}

			total_error = best_params_evaluated[3];
			best_error = best_params_evaluated[4];
			is_dp_added = best_params_evaluated[5];
			is_dp_subtracted = best_params_evaluated[6];

			std::cout << "DEBUG: After finding best parameters." << std::endl;

			std::cout << "DEBUG: Total error = ." << total_error << std::endl;
			std::cout << "DEBUG: Best error = " << best_error << endl;
			std::cout << "DEBUG: Updated Kp = << " << Kp << std::endl;
			std::cout << "DEBUG: Updated Ki = << " << Ki << std::endl;
			std::cout << "DEBUG: Updated Kd = << " << Kd << std::endl;
			std::cout << "DEBUG: is_dp_added = << " << is_dp_added << std::endl;
			std::cout << "DEBUG: is_dp_subtracted = << " << is_dp_subtracted << std::endl;

		}

		if (time_steps % (training_steps + eval_steps) == 0)
		{
			total_error = 0.0;
		}
	}

}

void PID::AppendMovingWindow(double steering_value) {
	steeringWindow->push(steering_value);
}

double PID::getMovingAverage() {
	if (abs(steeringWindow->stddev()) < 0.3)
		return steeringWindow->mean();
	else
		return (-Kp * p_error - Ki * i_error - Kd * d_error);
}

double PID::TotalError() {
	return (-Kp * p_error - Ki * i_error - Kd * d_error);
}

