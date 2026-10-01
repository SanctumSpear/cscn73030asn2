#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
};

int main() {
    std::vector<STUDENT_DATA> students;

    std::ifstream inputFile("StudentData.txt");

    if (inputFile.is_open()) {
        std::string line;

        while (std::getline(inputFile, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string lastName, firstName;

            if (std::getline(ss, lastName, ',') && std::getline(ss, firstName)) {

                if (!firstName.empty() && firstName[0] == ' ') {
                    firstName.erase(0, 1);
                }

                STUDENT_DATA student;
                student.lastName = lastName;
                student.firstName = firstName;

                students.push_back(student);
            }
        }
        inputFile.close();

        std::cout << "Successfully loaded " << students.size() << " students." << std::endl;

    }
    else {
        std::cout << "Error: Unable to open StudentData.txt" << std::endl;
    }

    return 1;
}