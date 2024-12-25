#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100;  
const int MAX_FRIENDS = 50;    


struct Student {
    string name;                
    string friends[MAX_FRIENDS]; 
    int numFriends = 0;         
};


void readStudents(Student students[], int &numStudents, const string &filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    numStudents = 0;

    
    for (int i = 0; getline(infile, students[numStudents].name); ++numStudents) {
        students[numStudents].numFriends = 0;

      
        string friendName;
        while (infile >> friendName) {
            students[numStudents].friends[students[numStudents].numFriends] = friendName;
            students[numStudents].numFriends++;
            if (infile.peek() == '\n') break; 
        }

        infile.ignore();
    }

    infile.close();
}


int calculateCommonFriends(const Student &student1, const Student &student2) {
    int commonCount = 0;

    
    for (int i = 0; i < student1.numFriends; ++i) {
        for (int j = 0; j < student2.numFriends; ++j) {
            if (student1.friends[i] == student2.friends[j]) {
                commonCount++;
            }
        }
    }

    return commonCount;
}


void findPotentialFriendships(const Student students[], int numStudents, int threshold) {
    
    for (int i = 0; i < numStudents; ++i) {
        for (int j = i + 1; j < numStudents; ++j) {
           
            bool areDirectFriends = false;
            for (int k = 0; k < students[i].numFriends; ++k) {
                if (students[i].friends[k] == students[j].name) {
                    areDirectFriends = true;
                    break;
                }
            }

            
            if (!areDirectFriends) {
                int commonFriends = calculateCommonFriends(students[i], students[j]);
                if (commonFriends >= threshold) {
                    cout << "Potential friendship between " << students[i].name << " and " << students[j].name
                         << " with " << commonFriends << " common friends." << endl;
                }
            }
        }
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int numStudents;
    int threshold;

   
    readStudents(students, numStudents, "C:\\Users\\Dell\\OneDrive\\Documents\\Discrete\\Friends Dataset.csv");

   
    cout << "Enter the minimum number of common friends for a potential friendship: ";
    cin >> threshold;

   
    findPotentialFriendships(students, numStudents, threshold);

    return 0;
}