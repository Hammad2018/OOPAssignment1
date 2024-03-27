#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// Forward declaration of classes
class Teacher;
class Student;
class Room;
class Course;

// Enum for days of the week
enum class Day { Monday, Tuesday, Wednesday, Thursday, Friday };

// Class representing a time slot
class TimeSlot {
private:
    Day day;
    string startTime;
    string endTime;

public:
    TimeSlot(Day _day, const string& _startTime, const string& _endTime)
        : day(_day), startTime(_startTime), endTime(_endTime) {}

    Day getDay() const { return day; }
    string getStartTime() const { return startTime; }
    string getEndTime() const { return endTime; }
};

// Class representing a teacher
class Teacher {
private:
    string name;
    vector<Course*> courses;

public:
    Teacher(const string& _name) : name(_name) {}

    void addCourse(Course* course) { courses.push_back(course); }

    const string& getName() const { return name; }
    const vector<Course*>& getCourses() const { return courses; }
};

// Class representing a student
class Student {
private:
    string name;
    string section;

public:
    Student(const string& _name, const string& _section) : name(_name), section(_section) {}

    const string& getName() const { return name; }
    const string& getSection() const { return section; }
};

// Class representing a room
class Room {
private:
    string name;

public:
    Room(const string& _name) : name(_name) {}

    const string& getName() const { return name; }
};

// Class representing a course
class Course {
private:
    string name;
    Teacher* teacher;
    vector<Student*> students;
    TimeSlot* timeSlot;
    Room* room;

public:
    Course(const string& _name, Teacher* _teacher, TimeSlot* _timeSlot, Room* _room)
        : name(_name), teacher(_teacher), timeSlot(_timeSlot), room(_room) {}

    void addStudent(Student* student) { students.push_back(student); }

    const string& getName() const { return name; }
    Teacher* getTeacher() const { return teacher; }
    const vector<Student*>& getStudents() const { return students; }
    TimeSlot* getTimeSlot() const { return timeSlot; }
    Room* getRoom() const { return room; }
};

// Function to print time table for a given day
void printTimeTableForDay(const vector<Course*>& courses, Day day) {
    cout << "Time table for ";
    switch (day) {
    case Day::Monday:
        cout << "Monday:" << endl;
        break;
    case Day::Tuesday:
        cout << "Tuesday:" << endl;
        break;
    case Day::Wednesday:
        cout << "Wednesday:" << endl;
        break;
    case Day::Thursday:
        cout << "Thursday:" << endl;
        break;
    case Day::Friday:
        cout << "Friday:" << endl;
        break;
    default:
        cout << "Invalid day" << endl;
        return;
    }

    for (Course* course : courses) {
        if (course->getTimeSlot()->getDay() == day) {
            cout << "Course: " << course->getName() << ", Teacher: " << course->getTeacher()->getName()
                << ", Time: " << course->getTimeSlot()->getStartTime() << " - " << course->getTimeSlot()->getEndTime()
                << ", Room: " << course->getRoom()->getName() << endl;
        }
    }
}

int main() {
    // Create teachers
    Teacher* seTeacher1 = new Teacher("Mr. Smith");
    Teacher* seTeacher2 = new Teacher("Ms. Johnson");

    // Create students
    vector<Student*> students;
    students.push_back(new Student("Alice", "4-17"));
    students.push_back(new Student("Bob", "4-17"));
    students.push_back(new Student("Charlie", "4-18"));
    students.push_back(new Student("David", "4-18"));
    students.push_back(new Student("Eva", "4-19"));
    // Add more students as needed

    // Create rooms
    Room* room1 = new Room("4-17");
    Room* room2 = new Room("4-18");
    Room* lab1 = new Room("Lab1");
    Room* lab2 = new Room("Lab2");

    // Create time slots
    TimeSlot* timeSlot1 = new TimeSlot(Day::Monday, "8:30", "10:00");
    TimeSlot* timeSlot2 = new TimeSlot(Day::Tuesday, "9:00", "10:30");

    // Create courses
    Course* courseSE1 = new Course("SE101", seTeacher1, timeSlot1, room1);
    Course* courseSE2 = new Course("SE102", seTeacher2, timeSlot2, room2);
    Course* labSE1 = new Course("LabSE1", seTeacher1, timeSlot1, lab1);
    Course* labSE2 = new Course("LabSE2", seTeacher2, timeSlot2, lab2);

    // Assign students to courses
    for (Student* student : students) {
        if (student->getSection() == "4-17" || student->getSection() == "4-18" || student->getSection() == "4-19") {
            courseSE1->addStudent(student);
            courseSE2->addStudent(student);
        }
    }

    // Add courses to teachers
    seTeacher1->addCourse(courseSE1);
    seTeacher1->addCourse(labSE1);
    seTeacher2->addCourse(courseSE2);
    seTeacher2->addCourse(labSE2);

    // Query: Who is teaching on 8:30 on Monday?
    cout << "Teachers teaching at 8:30 on Monday:" << endl;
    for (Course* course : seTeacher1->getCourses()) {
        if (course->getTimeSlot()->getDay() == Day::Monday && course->getTimeSlot()->getStartTime() == "8:30") {
            cout << course->getTeacher()->getName() << endl;
            break;
        }
    }

    // Query: What is the time table for Tuesday?
    printTimeTableForDay(seTeacher2->getCourses(), Day::Tuesday);

    // Clean up memory
    delete seTeacher1;
    delete seTeacher2;
    for (Student* student : students) {
        delete student;
    }
    delete room1;
    delete room2;
    delete lab1;
    delete lab2;
    delete timeSlot1;
    delete timeSlot2;
    delete courseSE1;
    delete courseSE2;
    delete labSE1;
    delete labSE2;

    return 0;
}
