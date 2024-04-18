# RoboticsBoundaryMapping

Out to-do list:

Technical work:
Perpindicular dist calibration
Fitting rotational data based on 5/6 distance measurements (fit custom function, take from function fit and goodness of fit)
How well is each set of distance measurements fitted by the fitted function? 
Check that rotational fitted function fits the 6th distance measurements

Write-up:
Justification for box size
Writing up Ryan's ramblings
Graphs with error bars

1.) The robot can use measurements from its bump sensors to work out its distance from a wall when it is facing it perpendicularly.

2.) The robot can use measurements from its bump sensors to work out its angle to the wall when it is at a known distance from it.

3.) The functions from the first 2 hypotheses can be used together to estimate the robots poistion when the kinematics fail.