#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
    #ifdef PRE_RELEASE
    std::string email;
    #endif
};

int main() {
    std::vector<STUDENT_DATA> students;

    #ifdef PRE_RELEASE
    std::cout << "Running Pre-Release Version" << std::endl;
    std::ifstream inputFile("StudentData_Emails.txt");
    #else
    std::cout << "Running Standard Version" << std::endl;
    std::ifstream inputFile("StudentData.txt");
    #endif

    if (inputFile.is_open()) {
        std::string line;

        while (std::getline(inputFile, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string lastName, firstName;

#ifdef PRE_RELEASE
            std::string email;
            if (std::getline(ss, lastName, ',') && std::getline(ss, firstName, ',') && std::getline(ss, email)) {
#else
            if (std::getline(ss, lastName, ',') && std::getline(ss, firstName)) {
#endif

                if (!firstName.empty() && firstName[0] == ' ') {
                    firstName.erase(0, 1);
                }

                STUDENT_DATA student;
                student.lastName = lastName;
                student.firstName = firstName;

#ifdef PRE_RELEASE
                student.email = email;
#endif

                students.push_back(student);
            }
            }
        inputFile.close();

#ifdef _DEBUG
        std::cout << "--- DEBUG BUILD: Printing Student Data ---" << std::endl;
        for (const auto& student : students) {
#ifdef PRE_RELEASE
            std::cout << student.lastName << ", " << student.firstName << " | " << student.email << std::endl;
#else
            std::cout << student.lastName << ", " << student.firstName << std::endl;
#endif
        }
        std::cout << "------------------------------------------" << std::endl;
#endif

        }
    else {
        std::cout << "Error: Unable to open the data file." << std::endl;
    }

    return 1;
    }