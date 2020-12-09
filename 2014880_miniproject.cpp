#include <bits/stdc++.h>

using namespace std;

class Student
{
    int roll;
    char name[50];
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    double per;
    char grade;
    void calculate();

public:
    void getdata();
    void showdata() const;
    void tabular() const;
    int rerollno() const;
};

void Student::calculate()
{
    per = (p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0;
    if (per >= 60)
        grade = 'A';
    else if (per >= 50)
        grade = 'B';
    else if (per >= 33)
        grade = 'C';
    else
        grade = 'F';
}

void Student::getdata()
{
    cout << "\nEnter The roll number of student ";
    cin >> roll;
    cout << "\n\nEnter The Name of student ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter The marks in physics out of 100 : ";
    cin >> p_marks;
    cout << "\nEnter The marks in chemistry out of 100 : ";
    cin >> c_marks;
    cout << "\nEnter The marks in maths out of 100 : ";
    cin >> m_marks;
    cout << "\nEnter The marks in english out of 100 : ";
    cin >> e_marks;
    cout << "\nEnter The marks in computer science out of 100 : ";
    cin >> cs_marks;
    calculate();
}

void Student::showdata() const
{
    cout << "\nRoll number of student : " << roll;
    cout << "\nName of student : " << name;
    cout << "\nMarks in Physics : " << p_marks;
    cout << "\nMarks in Chemistry : " << c_marks;
    cout << "\nMarks in Maths : " << m_marks;
    cout << "\nMarks in English : " << e_marks;
    cout << "\nMarks in Computer Science :" << cs_marks;
    cout << "\nPercentage of the student is  :" << per;
    cout << "\nGrade of the student is :" << grade;
}

void Student::tabular() const
{
    cout << roll << setw(10) << " " << name << setw(10) << p_marks << setw(10) << c_marks << setw(10) << m_marks << setw(10)
         << e_marks << setw(10) << cs_marks << setw(10) << per << setw(10) << grade << endl;
}

int Student::rerollno() const
{
    return roll;
}

void intro()
{
    cout << "\n\n\t\t  STUDENT";
    cout << "\n\t\tREPORT CARD";
    cout << "\n\t\t  PROJECT";
    cout << "\n\n\tMADE BY : AYUSHI SHRIYAL";
    cout << "\n\tSCHOOL : GRAPHIC ERA UNIVERSITY";
    cin.get();
}

void write();
void displayAll();
void display_sp(int);
void updateStudent(int);
void deleteStudent(int);
void fileResult();
void result();
void intro();
void menu();

void write()
{
    student s;
    ofstream outFile;
    outFile.open("student.dat", ios::binary | ios::app);
    s.getdata();
    outFile.write(reinterpret_cast<char *>(&s), sizeof(student));
    outFile.close();
    cout << "\n\nStudent record has been created ";
    cin.ignore();
    cin.get();
}

void displayAll()
{
    student s;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not open!! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    while (inFile.read(reinterpret_cast<char *>(&s), sizeof(student)))
    {
        s.showdata();
        cout << "\n\n----------------------------------\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}

void display_sp(int n)
{
    student s;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not open!! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (inFile.read(reinterpret_cast<char *>(&s), sizeof(student)))
    {
        if (s.rerollno() == n)
        {
            s.showdata();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nrecord not exist";
    cin.ignore();
    cin.get();
}

void updateStudent(int n)
{
    bool found = false;
    student s;
    fstream File;
    File.open("student.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not open!! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    while (!File.eof() && found == false)
    {

        File.read(reinterpret_cast<char *>(&s), sizeof(student));
        if (s.rerollno() == n)
        {
            s.showdata();
            cout << "\n\nPlease Enter The New Details of student" << endl;
            s.getdata();
            int pos = (-1) * static_cast<int>(sizeof(s));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&s), sizeof(student));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
    cin.ignore();
    cin.get();
}

void deleteStudent(int n)
{
    student s;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not open!! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outFile;
    outFile.open("Temp.dat", ios::out);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&s), sizeof(student)))
    {
        if (st.rerollno() != n)
        {
            outFile.write(reinterpret_cast<char *>(&s), sizeof(student));
        }
    }
    outFile.close();
    inFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout << "\n\n\tRecord Deleted ..";
    cin.ignore();
    cin.get();
}

void fileResult()
{
    student s;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not open!! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\t\tALL STUDENTS RESULT \n\n";
    cout << endl
         << "Roll No.     Name      Physics   Chemistry   Maths   English   CS   Percentage   Grade\n"
         << endl;
    while (inFile.read(reinterpret_cast<char *>(&s), sizeof(student)))
    {
        s.tabular();
    }
    cin.ignore();
    cin.get();
    inFile.close();
}

void result()
{
    char ch;
    int rno;
    system("cls");
    cout << "\n\n\n\t THE RESULT MENU";
    cout << "\n\n\n\t1. Class Result";
    cout << "\n\n\t2. The Student Report Card";
    cout << "\n\n\t3. Back to the Main Menu";
    cout << "\n\n\n\tEnter your Choice(1/2/3) ? ";
    cin >> ch;
    system("cls");
    switch (ch)
    {
    case '1':
        fileResult();
        break;
    case '2':
        cout << "\n\n\tEnter the Roll Number Of the Student : ";
        cin >> rno;
        display_sp(rno);
        break;
    case '3':
        break;
    default:
        cout << "\a";
    }
}

int main()
{
    char ch;
    cout.setf(ios::fixed | ios::showpoint);
    cout << setprecision(2);
    intro();
    do
    {
        system("cls");
        cout << "\n\n\n\t   ''THE MAIN MENU'' ";
        cout << "\n\n\t1- THE RESULT MENU";
        cout << "\n\n\t2- THE ENTRY/EDIT MENU";
        cout << "\n\n\t3- EXIT";
        cout << "\n\n\tSelect Your Option(1/2/3) ";
        cin >> ch;
        switch (ch)
        {
        case '1':
            result();
            break;
        case '2':
            menu();
            break;
        case '3':
            break;
        default:
            cout << "\a";
        }
    } while (ch != '3');
    return 0;
}

void menu()
{
    char ch;
    int n;
    system("cls");
    cout << "\n\n\n\tTHE ENTRY MENU";
    cout << "\n\n\t1.CREATE THE STUDENT RECORD";
    cout << "\n\n\t2.DISPLAY ALL THE STUDENTS RECORDS";
    cout << "\n\n\t3.SEARCH THE STUDENT RECORD ";
    cout << "\n\n\t4.MODIFY THE STUDENT RECORD";
    cout << "\n\n\t5.DELETE THE STUDENT RECORD";
    cout << "\n\n\t6.BACK TO THE MAIN MENU";
    cout << "\n\n\tEnter Your Choice(1-6) ";
    cin >> ch;
    system("cls");
    switch (ch)
    {
    case '1':
        write();
        break;
    case '2':
        displayAll();
        break;
    case '3':
        cout << "\n\n\tPlease Enter The roll number of the student ";
        cin >> n;
        display_sp(n);
        break;
    case '4':
        cout << "\n\n\tPlease Enter The roll number of the student ";
        cin >> n;
        updateStudent(n);
        break;
    case '5':
        cout << "\n\n\tPlease Enter The roll number of the student";
        cin >> n;
        deleteStudent(n);
        break;
    case '6':
        break;
    default:
        cout << "\a";
        menu();
    }
}
