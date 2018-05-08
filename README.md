# PID control

[//]: # (Image References) 
[image1]: ./images/PID_Control.png
[image2]: ./images/IRL.png

A PID controller stands for Proportional-Integral-Derivative controller. It is typically is a control loop used in industrial applications and can be extended to applications such as
Vehicle control. Below is block diagram depicting PID controller:

![alt text][image1]

---

### PID Components

P controller is a proportional controller. This is used to control the cross track error as the error increases or decreases as the vehicle reaches the track end points.
P value is a coeffient of cross track error and helps in adjusting the steering angle in proportion to the cross-track error.

D controller is a Derivative controller. This is used to control the degree of correction that is applied in proportion to cross-track error. D controller helps in smoothening
the steering angle and avoids the vehicle steering in extereme directions.

I controller is Integral controller. Typically if there is bias when steering is applied, such a bias gets accumulated over time causing the vehicle move in a particular direction.
Coefficient of Accumulated cross-track error is used to control drift or bias of Vehicle steering.

---

### Hyper Parameter Tuning Approach

PID parameter values from the class were used as a reference starting points and parameters were tuned manually.
Given the sensitivity of the parameters, multiple experiments were done to choose the PID parameters. Fine tuning
of parameters was done using Twiddle (coordinate descent) algorithm. For a given configuration of PID values,
error was computed after 100 steps (training) and evalauted for 2500 steps. Given the initial values were pretty
good starting point, very small "dp" values were chosen {1e-4, 1e-4, 1e-4}.

Final PID values obtained are: {P = 0.199608, I = 0.0003, D = 3.0}

---

### Inverse Reinforcement Learning Approach

Short-comings of PID controller are that this approach would not generalize very well for multiple road conditions such as 
variations in track turns, road surface, slope of the road etc.

Behavior cloning through Inverse Reinforcement Learning might be much better approach where using example ideal example driving videos,
reward function is learnt. Using the learnt reward function, control policy is learnt. Below diagram shows the approach:

![alt text][image2]

---

### Result Videos

Final Video Link   : https://www.youtube.com/watch?v=MALRyioEJ6g&feature=youtu.be

Training Video Link: https://www.youtube.com/watch?v=RQtmkp1aVII&feature=youtu.be 

