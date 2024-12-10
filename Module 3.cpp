
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    int neighbors[10];
    int neighborCount;

    void findHops(Student students[], int numStudents, int studentIndex) {
        int oneHop[10], twoHop[10], threeHop[10];
        int oneHopCount = 0, twoHopCount = 0, threeHopCount = 0;
        bool visited[numStudents];

        for (int i = 0; i < numStudents; i++) {
            visited[i] = false;
        }

        int currentLevel[10], nextLevel[10];
        int currentLevelSize = 0, nextLevelSize = 0;

        visited[studentIndex] = true;
        currentLevel[currentLevelSize++] = studentIndex;

        int hopLevel = 0;

        while (currentLevelSize > 0 && hopLevel < 3) {
            nextLevelSize = 0;

            for (int i = 0; i < currentLevelSize; i++) {
                int studentIndex = currentLevel[i];

                if (hopLevel == 0) {
                    continue;
                } else if (hopLevel == 1) {
                    oneHop[oneHopCount++] = studentIndex;
                } else if (hopLevel == 2) {
                    twoHop[twoHopCount++] = studentIndex;
                } else if (hopLevel == 3) {
                    threeHop[threeHopCount++] = studentIndex;
                }

                for (int j = 0; j < students[studentIndex].neighborCount; j++) {
                    int neighbor = students[studentIndex].neighbors[j];

                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        nextLevel[nextLevelSize++] = neighbor;
                    }
                }
            }

            currentLevelSize = nextLevelSize;

            for (int i = 0; i < currentLevelSize; i++) {
                currentLevel[i] = nextLevel[i];
            }

            hopLevel++;
        }

        cout << "1-hop students: ";
        for (int i = 0; i < oneHopCount; i++) {
            cout << oneHop[i] << " ";
        }
        cout << endl;

        cout << "2-hop students: ";
        for (int i = 0; i < twoHopCount; i++) {
            cout << twoHop[i] << " ";
        }
        cout << endl;

        cout << "3-hop students: ";
        for (int i = 0; i < threeHopCount; i++) {
            cout << threeHop[i] << " ";
        }
        cout << endl;
    }
};

void readGraphData(Student students[], int &numStudents, const string &filename) {
    ifstream infile(filename);

    if (!infile) {
        cout << "Error opening file!" << endl;
        return;
    }

    infile >> numStudents;

    for (int i = 0; i < numStudents; i++) {
        infile >> students[i].neighborCount;

        for (int j = 0; j < students[i].neighborCount; j++) {
            infile >> students[i].neighbors[j];
        }
    }

    infile.close();
}

int main() {
    Student students[10];
    int numStudents;

    string filename = "C:\\Users\\Dell\\OneDrive\\Documents\\Discrete\\Friends Dataset.csv";

    readGraphData(students, numStudents, filename);

    int studentIndex;

    cout << "Enter the student index to find 1-hop, 2-hop, 3-hop: ";
    cin >> studentIndex;

    students[studentIndex].findHops(students, numStudents, studentIndex);

    return 0;
}

