#ifndef PID_H
#define PID_H

#include <limits>
#include <cstddef>
#include <iostream>
#include "MovingWindow.hpp"
#include "Twiddle.h"

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /* Time steps
   */

  int time_steps;
  int training_steps;
  int eval_steps;

  Twiddle* twiddler;

  bool is_dp_subtracted;

  bool is_dp_added;

  double best_error;
  
  double total_error;

  /* Flag to enable/disable Twiddle
   */
  bool is_twiddle_required;

  /* PID parameter index */
  int pid_index;

  int num_params;

  double tolerance_;

  MovingWindow *steeringWindow = new MovingWindow(5);

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Get number of time steps.
  */
  int getTimeSteps();

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /* Append steering value to moving window. This will help in smoothening.
   */

  void AppendMovingWindow(double steering_value);

  /* Return moving average of last 'x' observations.
   */
  double getMovingAverage();
};

#endif /* PID_H */
