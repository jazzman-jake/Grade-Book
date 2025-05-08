#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// Global Constants for upper bounds of test scores/students
const int MAX_STUDENTS = 100;
const int MAX_TESTS = 20;

//Prototypes for functions
int getData(ifstream& File, string names[], double scores[][MAX_TESTS], int& num_tests);
void grade_avg(double scores[][MAX_TESTS], double averages[], int num_students, int num_tests);
char lettergrade(double average);
void display(const string names[], const double averages[], int num_students);

int main() {
    ifstream File;
    File.open("C:/Users/SPro/Downloads/StudentGrades.txt");
    if (!File) {
        cout << "Error opening file.\n";
        return 1;
    }

    string names[MAX_STUDENTS];
    double scores[MAX_STUDENTS][MAX_TESTS];
    double averages[MAX_STUDENTS];
    int num_students = 0;
    int num_tests = 0;

    num_students = getData(File, names, scores, num_tests);
    grade_avg(scores, averages, num_students, num_tests);
    display(names, averages, num_students);

    File.close();
    return 0;
}

// Function Definitions:

//read data from txt file to store in parallel arrays
int getData(ifstream& inFile, string names[], double scores[][MAX_TESTS], int& num_tests) {
    int student_count = 0;
    string line;

    while (getline(inFile, line) && student_count < MAX_STUDENTS) {
        istringstream iss(line);
        iss >> names[student_count];

        double score;
        int test_count = 0;

        while (iss >> score && test_count < MAX_TESTS) {
            scores[student_count][test_count++] = score;
        }

        // Set num_tests based on first student
        if (student_count == 0) {
            num_tests = test_count;
        }
        else if (test_count != num_tests) {
            cerr << "Inconsistent number of test scores for student: " << names[student_count] << endl;
            exit(1);
        }

        student_count++;
    }

    return student_count;
}
//this function averages the test scores
void grade_avg(double scores[][MAX_TESTS], double averages[], int num_students, int num_tests) {
    for (int i = 0; i < num_students; i++) {
        double sum = 0;
        for (int j = 0; j < num_tests; j++) {
            sum += scores[i][j];
        }
        averages[i] = sum / num_tests;
    }
}
//this function categorizes scores into a letter grade
char lettergrade(double avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 80) return 'B';
    else if (avg >= 70) return 'C';
    else if (avg >= 60) return 'D';
    else return 'F';
}
//this function displays data from file after averaging
void display(const string names[], const double averages[], int num_students) {
    cout << left << setw(15) << "Name" << setw(10) << "Average" << "Grade" << endl;
    cout << "----------------------------------" << endl;
    for (int i = 0; i < num_students; i++) {
        cout << left << setw(15) << names[i]
            << setw(10) << fixed << setprecision(2) << averages[i]
            << lettergrade(averages[i]) << endl;
    }
}
