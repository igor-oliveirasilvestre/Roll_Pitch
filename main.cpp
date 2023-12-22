#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>


// Function to calculate roll angle
double calculateRoll(double accel_x, double accel_y, double accel_z) {
    return atan2(accel_y, accel_z);
}

// Function to calculate pitch angle
double calculatePitch(double accel_x, double accel_y, double accel_z) {
    return atan2(-accel_x, sqrt(accel_y * accel_y + accel_z * accel_z));
}


/* Structure to store sensor data
 time_stamp_ms, accel_x, accel_y, accel_z
*/
struct SensorData {
    long long time_stamp_ms;
    double accel_x;
    double accel_y;
    double accel_z;
};

int main() {
    std::ifstream inputFile("attitude_exam.log");
    std::ofstream outputFile("attitude_result.txt");

    if (!inputFile.is_open()) {
        std::cout << "Error opening input file." << std::endl;
        return 1;
    }

    if (!outputFile.is_open()) {
    std::cout << "Error opening output file." << std::endl;
    return 1;
}

    std::vector<SensorData> sensorDataList;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        SensorData data;

        char delimiter;
        if (!(iss >> data.time_stamp_ms >> delimiter >> data.accel_x >> delimiter >>
              data.accel_y >> delimiter >> data.accel_z)) {
            std::cout << "Error parsing line: " << line << std::endl;
            continue;
        }

        // Convert millig-units to units (if needed)
        data.accel_x /= 1000.0; // Conversion to g units (if accelerometer data is in millig)
        data.accel_y /= 1000.0;
        data.accel_z /= 1000.0;

        // Calculate roll and pitch angles
        double roll = calculateRoll(data.accel_x, data.accel_y, data.accel_z);
        double pitch = calculatePitch(data.accel_x, data.accel_y, data.accel_z);

        // Write results to the output file
        outputFile << "Timestamp: " << data.time_stamp_ms << " ms, Roll: " << roll << " rad, Pitch: " << pitch << " rad" << std::endl;

        sensorDataList.push_back(data);
    }

    inputFile.close();
    outputFile.close();

    // Print parsed data as an example
    for (const auto& data : sensorDataList) {
        std::cout << "Time: " << data.time_stamp_ms << " ms, Accel X: " << data.accel_x
                  << ", Accel Y: " << data.accel_y << ", Accel Z: " << data.accel_z << std::endl;
    }

    return 0;
}