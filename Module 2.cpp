#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const int MAX_STUDENTS = 500;

struct Student {
    std::string name;
    int friendCount;
};


int findStudent(Student students[], int studentCount, const std::string& name) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].name == name) {
            return i;
        }
    }
    return -1;
}

int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;

    
    std::ifstream file("C:\\Users\\Dell\\OneDrive\\Documents\\Discrete\\Friends Dataset.csv");
    if (!file) {
        std::cerr << "Error: Cannot open the file." << std::endl;
        return 1;
    }

   
    std::string headerLine;
    std::getline(file, headerLine);

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string name;
        std::string friendName;

       
        std::getline(ss, name, ',');

        
        int mainStudentIndex = findStudent(students, studentCount, name);
        
        if (mainStudentIndex == -1) {
            
            mainStudentIndex = studentCount;
            students[studentCount].name = name;
            students[studentCount].friendCount = 0;
            studentCount++;
        }

       
        while (std::getline(ss, friendName, ',')) {
            if (!friendName.empty()) {
               
                int friendIndex = findStudent(students, studentCount, friendName);
                
                if (friendIndex == -1) {
                   
                    students[studentCount].name = friendName;
                    students[studentCount].friendCount = 1;
                    studentCount++;
                } else {
                    students[friendIndex].friendCount++;
                }
            }
        }
    }
    file.close();

   
    std::cout << "All Students:" << std::endl;
    for (int i = 0; i < studentCount; ++i) {
        std::cout << students[i].name << " (Friends: " << students[i].friendCount << ")" << std::endl;
    }

    return 0;
}