#include <set>
#include <queue>
#include <string>
#include <iostream>

class Student
{
private:
    int id;
    std::string name;

public:
    // Constructors
    Student(){}; // default constructor
    Student(int id, std::string name) : id(id), name(name){};
    Student(const Student &s) : id(s.id), name(s.name){}; // Copy-constructor

    // Destructor
    ~Student(){};

    // Methods
    int getId() const
    {
        return id;
    }
    std::string getName() const
    {
        return name;
    }

    // Comparison operator overload for Set
    bool operator<(const Student &other) const
    {
        return id < other.id;
    }
};

class ClassRoom
{
private:
    std::set<Student> students;

public:
    // Constructors
    ClassRoom(){}; // default constructor
    ClassRoom(const std::vector<Student> &s)
    {
        for (auto temp : s)
        {
            auto i = students.insert(temp);
            if (!i.second)
                break;
        }
    };
    ClassRoom(const ClassRoom &c) : students(c.students){}; // copy-constructor

    // Destructor
    ~ClassRoom(){};

    // Methods
    std::set<Student>::const_iterator addStudent(const Student &s)
    {
        auto i = students.insert(s);
        if (!i.second)
        {
            return students.end();
        }
        return i.first;
    }
};

// Print operator overload Student
std::ostream &operator<<(std::ostream &output, const Student &s)
{
    output << "(" << s.getId() << ", " << s.getName() << ")";
    return output;
}

int main(int argc, char const *argv[])
{
    std::string arr[5] = {"Frank", "Billy", "Alice", "Bob", "Mango"};

    ClassRoom itClass;

    Student bob(5, "Bob");

    auto bobItr = itClass.addStudent(bob);

    std::cout << "Student info: " << *bobItr << std::endl;

    return 0;
}
