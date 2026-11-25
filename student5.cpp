#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <limits>
using namespace std;

class Student
{
public:
    string name;
    int mark;
    char grade;
};

int main()
{
    int n;
    cout << "Enter number of students: ";
    while (!(cin >> n) || n <= 0)
    {
        cout << "Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<Student> students(n);

    for (int i = 0; i < n; i++)
    {
        cout << "\nStudent " << i + 1 << " name: ";
        cin >> students[i].name;

        cout << "Student " << i + 1 << " mark (0-100): ";
        while (!(cin >> students[i].mark) ||
               students[i].mark < 0 || students[i].mark > 100)
        {
            
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        students[i].grade = ' ';
    }

    int threshold;
    cout << "\nEnter mark threshold to search (find_if): ";
    cin >> threshold;

    // Sort students based on marks (descending)
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b)
         {
             return a.mark > b.mark;
         });

    // Assign grades using transform
    transform(students.begin(), students.end(),
              students.begin(),
              [](Student s)
              {
                  if (s.mark >= 90)
                      s.grade = 'A';
                  else if (s.mark >= 75)
                      s.grade = 'B';
                  else if (s.mark >= 50)
                      s.grade = 'C';
                  else
                      s.grade = 'F';
                  return s;
              });

    // Find first student scoring above threshold
    auto it = find_if(students.begin(), students.end(),
                      [threshold](const Student& s)
                      {
                          return s.mark > threshold;
                      });

    // Total using accumulate
    int total = accumulate(students.begin(), students.end(), 0,
                           [](int sum, const Student& s)
                           {
                               return sum + s.mark;
                           });

    float average = (float)total / students.size();

    cout << "\nStudent Grade Analyzer\n";
    cout << "---------------------\n";
    cout << "Name\tMark\tGrade\n";

    for (const Student& s : students)
    {
        cout << s.name << "\t" << s.mark << "\t" << s.grade << endl;
    }

    if (it != students.end())
        cout << "\nFirst student scoring above " << threshold
             << ": " << it->name << endl;
    else
        cout << "\nNo student scored above " << threshold << endl;

    cout << "Total Marks: " << total << endl;
    cout << "Average Mark: " << average << endl;

    return 0;
}
