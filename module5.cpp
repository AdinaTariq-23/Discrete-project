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


void printGraph(const Student students[], int numStudents) {
    
    cout << "   ";
    for (int i = 0; i < numStudents; ++i) {
        cout << students[i].name << " ";
    }
    cout << endl;

    
    for (int i = 0; i < numStudents; ++i) {
        cout << students[i].name << " ";
        for (int j = 0; j < numStudents; ++j) {
            
            int weight = calculateCommonFriends(students[i], students[j]);
            cout << weight << " ";
        }
        cout << endl;
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int numStudents;

   
    readStudents(students, numStudents, "C:\\Users\\Dell\\OneDrive\\Documents\\Discrete\\Friends Dataset.csv");

    
    printGraph(students, numStudents);

    return 0;
}