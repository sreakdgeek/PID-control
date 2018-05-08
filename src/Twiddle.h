#ifndef Twiddle_H
#define Twiddle_H

#include <cmath>
#include <limits>
#include <cstddef>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string>

class Twiddle {

public:
  /*
  * parameter deviations vector
  */
  std::vector<double> dp;

  /* Twiddle tolerance parameter */
  double tolerance;

  /*
  * Constructor
  */
  Twiddle(double tolerance_, double dp_0, double dp_1, double dp_2);

  /*
  * Destructor.
  */
  virtual ~Twiddle();

  std::vector<double> twiddle(std::vector<double>& best_params, double cte, double total_error, double tolerance_, double best_error, bool is_dp_added, bool is_dp_subtracted, int num_steps, int training_steps, int eval_steps, int index);

};
#endif /* Twiddle_H */
