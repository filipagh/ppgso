//HiResT.h
//High resolution timer

//Returns the period of the performance counter in seconds
double GetPerformanceCounterPeriod();

//Returns the current value of the performance counter in seconds
//Use only the difference between successive calls since the absolute value
//has no meaning
double GetHiResTime();
