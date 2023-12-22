# Attitude Estimator


## How the task was performed

The task was performed using VS Code. In this section, I'll outline the steps taken to create a C++ program that parses accelerometer data from a log file, converts it into Roll and Pitch angles using an aerospace rotation sequence, and ultimately stores this information in an output file.
My initial focus was on developing a C++ program dedicated to parsing data extracted from the log file named 'attitude_exam.log.' To accomplish this, I began by creating a 'SensorData' struct to encapsulate the information present in the log file. Within the 'main{}' function, I instantiated 'data' to initialize this structure.
```  
struct  SensorData {
long  long  time_stamp_ms;
double  accel_x;
double  accel_y;
double  accel_z;
};
```
Given that, I check if the stream to the log file is open by another program, if it isn't, I initiated the process of reading and parsing information from the log file.
```
std::vector<SensorData> sensorDataList;
std::string line;
while (std::getline(inputFile, line)) {
	std::istringstream iss(line);
	SensorData  data;
```

Having completed the parsing phase, I shifted my attention to the robotics aspect. Specifically, I began converting the accelerations from milli g-units to g-units.
Once the accelerations were in g-units, I moved forward by creating two functions to compute Roll and Pitch angles, following the aerospace rotation sequence equations:
$$tan(\phi_{xyz})= (\frac{G_{py}}{G_{pz}})$$ 
$$tan(\theta_{xyz})= (\frac{-G_{px}}{\sqrt{{G_{py}}^2+{G_{pz}}^2}})$$ 
Therefore, I used atan2 function from C++ to write the following functions:
```
double  calculateRoll(double  accel_x, double  accel_y, double  accel_z) {
	return  atan2(accel_y, accel_z);
}

double  calculatePitch(double  accel_x, double  accel_y, double  accel_z) {
	return  atan2(-accel_x, sqrt(accel_y  *  accel_y  +  accel_z  *  accel_z));

}
```
After computing both angles, the final step was to record them in an output file. I accomplished this by writing the timestamp along with the Roll and Pitch angles to the "attitude_result.txt" file. Upon completing the writing process, I closed both the log and output file streams to ensure proper termination.



## How to compile and run the code

I'll start this sections by briefly stating the software used during development:
- Visual Studio Code
- g++ Version

I wrote and compiled using VS Code, but given that the user has a C++ compiler, like g++, the program can be compiled by opening a terminal on the same folder as the "main.cpp" archive and give the terminal the following prompt:
```
g++ -o main.exe main.cpp
```
This should generate an exe file called "main.exe" which can be run by giving the terminal the following prompt:
```
./main
```

## User notes

- In the start of the main function, it is checked if there are any streams open to the log file and the output file. If present, the program will exit will treat as an exception and stop.
- During lines 66:69 I convert the accelerometer data from mili g-units to g-units before calling the Roll and Pitch calculations functions. If the accelerometer used in your project already gives accelerations in native units of g remove those lines.
- I've decided to write the output file with Roll and Pitch angles using radians, if you so desire, I've written alternate calculations formulas on both "CalculateRoll" and "CalculatePitch" that returns those angles using degrees. To use them, comment out both of each function first return line (line 10 and 16) and remove the comment on the second
