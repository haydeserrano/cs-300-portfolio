#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

map<string, Course> courseMap;

void loadCourses(string fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;

        getline(ss, token, ',');
        course.courseNumber = token;

        getline(ss, token, ',');
        course.courseTitle = token;

        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        courseMap[course.courseNumber] = course;
    }

    file.close();
    cout << "Data loaded successfully." << endl;
}

void printCourseList() {
    cout << "Here is a sample schedule:" << endl;

    for (auto& pair : courseMap) {
        cout << pair.second.courseNumber << ", "
            << pair.second.courseTitle << endl;
    }
}

void printCourse(string courseNumber) {
    auto it = courseMap.find(courseNumber);

    if (it == courseMap.end()) {
        cout << "Course not found." << endl;
        return;
    }

    Course course = it->second;

    cout << course.courseNumber << ", "
        << course.courseTitle << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1)
                cout << ", ";
        }
        cout << endl;
    }
}

int main() {
    int choice = 0;
    string fileName;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {

        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";

        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter file name: ";
            cin.ignore();
            getline(cin, fileName);
            loadCourses(fileName);
            break;

        case 2:
            printCourseList();
            break;

        case 3: {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            printCourse(courseNumber);
            break;
        }

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}