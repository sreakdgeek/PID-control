#include "Twiddle.h"


/*
* Complete the Twiddle class.
*/

Twiddle::Twiddle(double tolerance_, double dp_0, double dp_1, double dp_2) {

	std::cout << "DEBUG: dp_0 = " << dp_0 << std::endl;
	std::cout << "DEBUG: dp_1 = " << dp_1 << std::endl;
	std::cout << "DEBUG: dp_2 = " << dp_2 << std::endl;

	tolerance = tolerance_;

	dp.push_back(dp_0);
	dp.push_back(dp_1);
	dp.push_back(dp_2);

	double sum = std::accumulate(dp.begin(), dp.end(), 0.0);
	std::cout << "dp sum in constructor = " << sum << std::endl;
}

Twiddle::~Twiddle() {}

/* Twiddle Kp, Ki, Kd Parameters that produce best error (should I say lowest?) */
std::vector<double> Twiddle::twiddle(std::vector<double>& best_params, double cte, double total_error, double tolerance_, double best_error, bool is_dp_added, bool is_dp_subtracted, int num_steps, int training_steps, int eval_steps, int index) {

	std::vector<double> best_params_found;

	double dp_sum = std::accumulate(dp.begin(), dp.end(), 0.0);

	std::cout << "Number of steps = " << num_steps << std::endl;
	std::cout << "dp_sum = " << dp_sum << std::endl;
	std::cout << "tolerance_ = " << tolerance << std::endl;
	
	if (dp_sum < tolerance_)
		return best_params;

	/* Training time - Compute the total error with the current configuration. */

	std::cout << "DEBUG: Entered training.." << std::endl;
	if (num_steps % (training_steps + eval_steps) >= training_steps)
	{
		total_error += cte;
		total_error *= total_error;
		total_error = sqrt(total_error);
		total_error /= (training_steps + eval_steps);
	}

	std::cout << "DEBUG: Total error computed = " << total_error << std::endl;

	best_params_found.push_back(best_params[0]);
	best_params_found.push_back(best_params[1]);
	best_params_found.push_back(best_params[2]);
	best_params_found.push_back(total_error);
	best_params_found.push_back(best_params[4]);
	best_params_found.push_back(is_dp_added);
	best_params_found.push_back(is_dp_subtracted);

	if (num_steps < training_steps)
		return best_params_found;

	std::cout << "DEBUG: Finished training.." << std::endl;

	if (num_steps % (training_steps + eval_steps) == 0)
	{
		std::cout << "Total error in evaluation = " << total_error << std::endl;
		std::cout << "Best error in evaluation = " << best_error << std::endl;
		if (total_error < best_error)
		{
			best_error = total_error;
			std::cout << "Changed best error = " << best_error << std::endl;

			if (num_steps != (training_steps + eval_steps))
				dp[index] *= 1.1;

			index = (index + 1) % 3;
			is_dp_added = false;
			is_dp_subtracted = false;
		}

		if (!is_dp_added && !is_dp_subtracted)
		{
			best_params_found[index] += dp[index];
			std::cout << "DEBUG: best_params_found[index] changed for addition = " << best_params_found[index] << std::endl;
			std::cout << "DEBUG: Addition for index = " << index << std::endl;
			is_dp_added = true;
		}
		else if (is_dp_added && !is_dp_subtracted)
		{
			std::cout << "DEBUG: doing subtraction." << std::endl;
			best_params_found[index] -= 2*dp[index];
			std::cout << "DEBUG: best_params_found[index] changed = " << best_params_found[index] << std::endl;
			std::cout << "DEBUG: Subtraction for index = " << index << std::endl;
			is_dp_subtracted = true;
		}
		else
		{
			std::cout << "DEBUG: Decreasing dp." << std::endl;
			dp[index] *= 0.9;
			is_dp_added = false;	
			is_dp_subtracted = false;
			index = (index + 1) % 3;
		}
			
		best_params_found[3] = total_error;
		best_params_found[4] = best_error;
		best_params_found[5] = is_dp_added;
		best_params_found[6] = is_dp_subtracted;
	}
	std::cout << "Returning best parameters found with size = " << best_params_found.size() << std::endl;
	return best_params_found;
}
