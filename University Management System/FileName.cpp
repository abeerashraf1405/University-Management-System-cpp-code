#include <iostream>
#include <string>
#include <iomanip>
#include<fstream>
using namespace std;
//global variables
const int max_teach = 100, max_stu = 30, subjects = 5;
int teach_id[max_teach], teach_count = 0, stu_ids[max_stu], stu_count = 0;
string teach_name[max_teach], teach_sub[max_teach], stu_name[max_stu], stu_class[max_stu];
double stu_CGPA[max_stu], stu_grade[max_stu][subjects]; // Grades for 5 subjects
//functions
void admin_menu();
void teach_menu();
void stu_menu(int stu_id);
void add_teach();
void del_teach();
void add_stu();
void del_stu();
void cal_CGPA();
void assign_marks();
void pass_stu();
void fail_stu();
void view_grade(int stu_id);
void view_CGPA(int stu_id);
//color codes
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
void load_teachers()
{
    ifstream file("teachers.txt");
    if (!file.is_open())
    {
        cout << RED << "Error: Couldn't open teachers.txt." << RESET << endl;
        return;
    }
    teach_count = 0;
    while (file >> teach_id[teach_count])
    {
        file.ignore(); // Ignore newline or space
        getline(file, teach_name[teach_count]);
        getline(file, teach_sub[teach_count]);
        teach_count++;
    }
    file.close();
}
void save_teachers()
{
    ofstream file("teachers.txt");
    if (file.is_open())
    {
        for (int i = 0; i < teach_count; i++)
        {
            file << teach_id[i] << "\t\t\t" << teach_name[i] << "\t\t\t" << teach_sub[i] << "\n";
        }
        file.close();
    }
}
void load_students()
{
    ifstream file("students.txt");
    if (!file.is_open())
    {
        cout << RED << "Error: Couldn't open students.txt." << RESET << endl;
    }
    stu_count = 0;
    while (file >> stu_ids[stu_count])
    {
        file.ignore(); // Ignore newline or space
        getline(file, stu_name[stu_count]);
        getline(file, stu_class[stu_count]);
        for (int i = 0; i < subjects; ++i)
        {
            file >> stu_grade[stu_count][i];
        }
        file >> stu_CGPA[stu_count];
        stu_count++;
    }
    file.close();
}
void save_students()
{
    ofstream file("students.txt");
    if (file.is_open())
    {
        for (int i = 0; i < stu_count; i++)
        {
            file << "ID: " << stu_ids[i] << "\n" << "Name: " << stu_name[i] << "\n" << "Class: " << stu_class[i] << "\n";
            for (int j = 0; j < subjects; ++j)
            {
                file << "Grade:" << stu_grade[i][j] << " ";
            }
            file << "\nCGPA: " << "\n" << stu_CGPA[i] << "\n";
        }
        file.close();
    }
}
int main()
{
    load_teachers();
    load_students();
    int choice;
    do {
        cout << MAGENTA << "\t\t\t------------|  Welcome to University Management System  |------------" << RESET << endl;
        cout << CYAN << "\t1. Admin Login\n\t2. Teacher Login\n\t3. Student Login\n\t4. Exit" << RESET << endl;
        cout << YELLOW << "\t\t----------------------------------" << RESET << endl;
        cout << WHITE << "Enter your choice: " << RESET;
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            admin_menu();
            break;
        case 2:
            teach_menu();
            break;
        case 3:
        {
            int stu_id;
            cout << BLUE << "Enter student ID: " << RESET;
            cin >> stu_id;
            stu_menu(stu_id);
            break;
        }
        case 4:
            cout << GREEN << "Exiting the system. Goodbye!" << RESET << endl;
            break;
        default:
            cout << RED << "Invalid choice. Try again!" << RESET << endl;
        }
    } while (choice != 4);
    save_teachers();
    save_students();
    system("pause");
    return 0;
}
//Admin Menu
void admin_menu()
{
    int choice;
    do {
        cout << MAGENTA << "\t\t\t------|  Admin Menu  |------" << RESET << endl;
        cout << CYAN << "\t1. Add Teacher\n\t2. Delete Teacher\n\t3. Return to Main Menu" << RESET << endl;
        cout << YELLOW << "\t\t-----------------------------------" << RESET << endl;
        cout << WHITE << "Enter your choice: " << RESET;
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            add_teach();
            break;
        case 2:
            del_teach();
            break;
        case 3:
            return;
        default:
            cout << RED << "Invalid choice. Try again!" << RESET << endl;
        }
    } while (choice != 3);
}
//Add Teacher
void add_teach()
{
    if (teach_count >= max_teach)
    {
        cout << RED << "Maximum teacher limit reached. Cannot add more teachers." << RESET << endl;
        return;
    }
    cout << BLUE << "Enter Teacher ID: " << RESET;
    cin >> teach_id[teach_count];
    cout << BLUE << "Enter Teacher Name: " << RESET;
    cin.ignore();
    getline(cin, teach_name[teach_count]);
    cout << BLUE << "Enter Teacher Subject: " << RESET;
    getline(cin, teach_sub[teach_count]);
    teach_count++;
    cout << GREEN << "New teacher added successfully!" << RESET << endl;
    save_teachers(); // Ensure data is saved to the file
}

//Delete Teacher
void del_teach()
{
    int id;
    cout << BLUE << "Enter Teacher ID to delete: " << RESET;
    cin >> id;
    for (int i = 0; i < teach_count; i++)
    {
        if (teach_id[i] == id)
        {
            for (int j = i; j < teach_count - 1; j++)
            {
                teach_id[j] = teach_id[j + 1];
                teach_name[j] = teach_name[j + 1];
                teach_sub[j] = teach_sub[j + 1];
            }
            teach_count--;
            save_teachers(); // Ensure data is saved to the file after deletion
            cout << GREEN << "Teacher deleted successfully!" << RESET << endl;
            return;
        }
    }
    cout << RED << "Teacher with ID " << id << " not found!" << RESET << endl;
}
//Student Menu
void stu_menu(int stu_id)
{
    int choice;
    do {
        cout << MAGENTA << "\t\t\t------|  Student Menu  |------" << RESET << endl;
        cout << CYAN << "\t1.View CGPA\n\t2.View Grades\n\t3.Return to Main Menu" << RESET << endl;
        cout << YELLOW << "\t\t-------------------------------------" << RESET << endl;
        cout << WHITE << "Enter your choice: " << RESET;
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            view_CGPA(stu_id);
            break;
        case 2:
            view_grade(stu_id);
            break;
        case 3:
            return;
        default:
            cout << RED << "Invalid choice. Try again!" << RESET << endl;
        }
    } while (choice != 3);
}
//View CGPA
void view_CGPA(int stu_id)
{
    for (int i = 0; i < stu_count; i++)
    {
        if (stu_ids[i] == stu_id)
        {
            cout << stu_name[i] << endl;
            cout << GREEN << "Student ID: " << stu_ids[i] << ", CGPA: " << stu_CGPA[i] << RESET << endl;
            return;
        }
    }
    cout << RED << "Student with ID " << stu_id << " not found!" << RESET << endl;
}
//View Grades
void view_grade(int stu_id)
{
    for (int i = 0; i < stu_count; i++)
    {
        if (stu_ids[i] == stu_id)
        {
            cout << stu_name[i] << endl;
            cout << WHITE << "Grades for Student ID " << stu_ids[i] << ":" << RESET << endl;
            for (int j = 0; j < subjects; j++)
            {
                cout << WHITE << "Subject " << (j + 1) << ": " << stu_grade[i][j] << RESET << endl;
            }
            return;
        }
    }
    cout << RED << "Student with ID " << stu_id << " not found!" << RESET << endl;
}
//Teacher Menu
void teach_menu()
{
    int choice;
    do {
        cout << MAGENTA << "\t\t\t------|  Teacher Menu  |------" << RESET << endl;
        cout << CYAN << "\t1. Add Student \n\t2. Delete Student\n\t3. Assign Marks\n\t4. Calculate CGPA\n\t5. List Passed Students\n\t6. List Failed Students\n\t7. Return to Main Menu" << RESET << endl;
        cout << YELLOW << "\t\t------------------------------------" << RESET << endl;
        cout << WHITE << "Enter your choice: " << RESET;
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            add_stu();
            break;
        case 2:
            del_stu();
            break;
        case 3:
            assign_marks();
            break;
        case 4:
            cal_CGPA();
            break;
        case 5:
            pass_stu();
            break;
        case 6:
            fail_stu();
            break;
        case 7:
            return;
        default:
            cout << RED << "Invalid choice. Try again." << RESET << endl;
        }
    } while (choice != 7);
}
//Add Students
void add_stu()
{
    if (stu_count >= max_stu)
    {
        cout << RED << "Maximum student limit reached!" << RESET << endl;
        return;
    }
    cout << BLUE << "Enter Student ID: " << RESET;
    cin >> stu_ids[stu_count];
    cout << BLUE << "Enter Student Name: " << RESET;
    cin.ignore();
    getline(cin, stu_name[stu_count]);
    cout << BLUE << "Enter Class (e.g., BSCS-1A): " << RESET;
    getline(cin, stu_class[stu_count]);

    for (int i = 0; i < subjects; ++i)
    {
        stu_grade[stu_count][i] = 0; // Initialize grades to 0
    }
    stu_CGPA[stu_count] = 0;
    stu_count++;
    cout << GREEN << "Student added successfully!" << RESET << endl;
    save_students(); // Ensure data is saved to the file
}
//Delete Student
void del_stu()
{
    int id;
    cout << BLUE << "Enter Student ID to delete: " << RESET;
    cin >> id;
    for (int i = 0; i < stu_count; ++i)
    {
        if (stu_ids[i] == id)
        {
            for (int j = i; j < stu_count - 1; ++j)
            {
                stu_ids[j] = stu_ids[j + 1];
                stu_name[j] = stu_name[j + 1];
                stu_class[j] = stu_class[j + 1];
                for (int k = 0; k < subjects; ++k)
                {
                    stu_grade[j][k] = stu_grade[j + 1][k];
                }
                stu_CGPA[j] = stu_CGPA[j + 1];
            }
            stu_count--;
            save_students(); // Ensure data is saved to the file after deletion
            cout << GREEN << "Student deleted successfully!" << RESET << endl;
            return;
        }
    }
    cout << RED << "Student with ID " << id << " not found." << RESET << endl;
}
//Assign Marks
void assign_marks()
{
    int id, choice;
    cout << BLUE << "Enter Student ID: " << RESET;
    cin >> id;

    for (int i = 0; i < stu_count; ++i)
    {
        if (stu_ids[i] == id)
        {
            cout << CYAN << "Select Assign Marks Type:\n1. Quiz (10 absolute)\n2. Assignment (10 absolute)\n3. Midterm (30 absolute)\n4. Final (50 absolute)" << RESET << endl;
            cout << WHITE << "Enter your choice: " << RESET;
            cin >> choice;

            double weight = 0;
            switch (choice)
            {
            case 1:
                weight = 10.0;
                break;
            case 2:
                weight = 10.0;
                break;
            case 3:
                weight = 30.0;
                break;
            case 4:
                weight = 50.0;
                break;
            default:
                cout << RED << "Invalid choice!" << RESET << endl;
                return;
            }

            cout << BLUE << "Enter marks for 5 subjects (out of " << weight << "):" << RESET << endl;
            for (int j = 0; j < subjects; ++j)
            {
                cout << WHITE << "Subject " << j + 1 << ": " << RESET;
                double marks;
                cin >> marks;

                if (marks < 0 || marks > weight)
                {
                    cout << RED << "Invalid marks! Must be between 0 and " << weight << "." << RESET << endl;
                    --j; // Retry for the same subject
                }
                else
                {
                    stu_grade[i][j] += marks; // Accumulate marks
                }
            }
            cout << GREEN << "Marks assigned successfully!" << RESET << endl;
            save_students(); // Save changes to file
            return;
        }
    }
    cout << RED << "Student with ID " << id << " not found." << RESET << endl;
}
//Calculate CGPA
void cal_CGPA()
{
    for (int i = 0; i < stu_count; ++i)
    {
        double totalGradePoints = 0.0;
        for (int j = 0; j < subjects; ++j)
        {
            double total_marks = stu_grade[i][j];
            double gradePoint;

            // Assign grade points based on marks
            if (total_marks >= 90)
                gradePoint = 4.0;
            else if (total_marks >= 70)
                gradePoint = 3.0;
            else if (total_marks >= 60)
                gradePoint = 2.0;
            else if (total_marks >= 50)
                gradePoint = 1.0;
            else
                gradePoint = 0.0;

            totalGradePoints += gradePoint;
        }
        stu_CGPA[i] = totalGradePoints / subjects; // Average grade points
        stu_CGPA[i] = round(stu_CGPA[i] * 100) / 100.0; // Round to 2 decimal places
    }
    cout << GREEN << "CGPA calculated for all students." << RESET << endl;
    save_students(); // Save updated CGPA to file
}
//list of passed student
void pass_stu()
{
    cout << WHITE << "Students with CGPA >= 2.0:" << RESET << endl;
    for (int i = 0; i < stu_count; ++i)
    {
        if (stu_CGPA[i] >= 2.0)
        {
            cout << GREEN << "ID: " << stu_ids[i] << ", Name: " << stu_name[i] << ", CGPA: " << stu_CGPA[i] << RESET << endl;
        }
    }
}
//list of failed student
void fail_stu()
{
    cout << WHITE << "Students with CGPA < 2.0:" << RESET << endl;
    for (int i = 0; i < stu_count; ++i)
    {
        if (stu_CGPA[i] < 2.0)
        {
            cout << GREEN << "ID: " << stu_ids[i] << ", Name: " << stu_name[i] << ", CGPA: " << stu_CGPA[i] << RESET << endl;
        }
    }
}