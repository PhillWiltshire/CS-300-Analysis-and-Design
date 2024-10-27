#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Struct to store course details
struct Course {
    string courseId;       // Unique course identifier
    string name;           // Course name
    vector<string> prereqs; // List of prerequisite course IDs
};

// Class representing a vector-based table to store courses
class VectorTable {
private:
    vector<Course> courses; // Vector to store Course objects

public:
    // Method to add a course to the vector
    void add(const Course& course) {
        courses.push_back(course); // Add course to the vector
    }

    // Method to find a course by courseId
    Course* find(const string& courseId) {
        for (auto& course : courses) {
            if (course.courseId == courseId) {
                return &course; // Return pointer to course if found
            }
        }
        return nullptr; // Return nullptr if not found
    }

    // Method to print all Computer Science (CS) courses in alphanumeric order
    void printAllCSCourses() {
        vector<Course> csCourses;

        // Filter only CS courses
        for (const auto& course : courses) {
            if (course.courseId.rfind("CS", 0) == 0) { // Check if ID starts with "CS"
                csCourses.push_back(course);
            }
        }

        // Sort CS courses by courseId (alphanumeric order)
        sort(csCourses.begin(), csCourses.end(), [](const Course& a, const Course& b) {
            return a.courseId < b.courseId;
            });

        // Print all CS courses
        for (const auto& course : csCourses) {
            cout << "Course ID: " << course.courseId << ", Course Name: " << course.name << endl;
        }
    }

    // Method to print course details and prerequisites
    void printCourseAndPrereqs(const string& courseId) {
        Course* course = find(courseId);

        if (course == nullptr) {
            cout << "Course not found." << endl;
            return;
        }

        cout << "Course Title: " << course->name << endl;
        if (!course->prereqs.empty()) {
            cout << "Prerequisites: ";
            for (const auto& prereq : course->prereqs) {
                cout << prereq << " ";
            }
            cout << endl;
        }
        else {
            cout << "No prerequisites." << endl;
        }
    }
};

// Helper function to check if a prerequisite already exists
bool prerequisiteExists(const string& courseId, const string& prereqId, VectorTable& dataStructure) {
    Course* course = dataStructure.find(courseId);
    if (course == nullptr) return false;

    return find(course->prereqs.begin(), course->prereqs.end(), prereqId) != course->prereqs.end();
}

// Function to load courses from a CSV file into the VectorTable
bool loadCourses(const string& csvPath, VectorTable& dataStructure) {
    ifstream file(csvPath); // Open the CSV file
    if (!file.is_open()) {
        cerr << "Error: File not found." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseId, name, prereq;

        // Read the course name and ID
        getline(ss, name, ',');
        getline(ss, courseId, ',');

        if (name.empty() || courseId.empty()) {
            cerr << "Invalid line: Missing Course ID or Name." << endl;
            continue; // Skip invalid lines
        }

        // Create a new Course object
        Course course;
        course.name = name;
        course.courseId = courseId;

        // Read the prerequisites (if any)
        while (getline(ss, prereq, ',')) {
            if (!prerequisiteExists(courseId, prereq, dataStructure)) {
                course.prereqs.push_back(prereq); // Add unique prerequisite
            }
        }

        // Add the course to the vector table
        dataStructure.add(course);
    }

    file.close(); // Close the file
    return true;
}

// Main function
int main() {

        // Use the absolute path of the CSV file
        string csvPath = "C:\\Users\\Phill\\Documents\\ProjectTwoFinal\\CS 300 ABCU_Advising_Program_Input.csv";

        // Print the file path being used
        cout << "Attempting to open: " << csvPath << endl;

        // Test if the file exists
        ifstream file(csvPath);

        if (!file.is_open()) {  // More reliable check for file opening
            cerr << "Error: File not found at path '" << csvPath << "'" << endl;
            // Additional debugging info
            cout << "Check if the path is correct and if the file exists." << endl;
            return 1;  // Exit if file is not found
        }
        else {
            cout << "File found successfully!" << endl;
        }

        // Close the file
        file.close();

        // Proceed with your program logic here
        return 0;
    }
