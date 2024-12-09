#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    string name;
    int friendCount;
};

int findStudentIndex(Student students[], int count, const string &name) {
    for (int i = 0; i < count; i++) {
        if (students[i].name == name) {
            return i;
        }
    }
    return -1;
}

void findMostPopularStudents(Student students[], int count) {
    int maxFriends = 0;

    
    for (int i = 0; i < count; i++) {
        if (students[i].friendCount > maxFriends) {
            maxFriends = students[i].friendCount;
        }
    }

    cout << "Most Popular Students (Friend Count: " << maxFriends << "):\n";
    for (int i = 0; i < count; i++) {
        if (students[i].friendCount == maxFriends) {
            cout << students[i].name << endl;
        }
    }
}

int main() {
    const int MAX_STUDENTS = 500;  
    Student students[MAX_STUDENTS];
    int studentCount = 0;  

    ifstream inputFile("C:\\Users\\Dell\\OneDrive\\Documents\\Discrete\\Friends Dataset.csv");
    if (!inputFile) {  
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    string studentA, studentB;

    while (inputFile >> studentA >> studentB) {
        
        int indexA = findStudentIndex(students, studentCount, studentA);
        if (indexA == -1) {
            
            if (studentCount >= MAX_STUDENTS) {
                cerr << "Error: Maximum student limit reached." << endl;
                break;
            }
            students[studentCount] = {studentA, 1}; 
            studentCount++;
        } else {
            
            students[indexA].friendCount++;
        }

        
        int indexB = findStudentIndex(students, studentCount, studentB);
        if (indexB == -1) {
            
            if (studentCount >= MAX_STUDENTS) {
                cerr << "Error: Maximum student limit reached." << endl;
                break;
            }
            students[studentCount] = {studentB, 1};  
            studentCount++;
        } else {
            
            students[indexB].friendCount++;
        }
    }

    inputFile.close(); 

    
    findMostPopularStudents(students, studentCount);

    return 0;
}
