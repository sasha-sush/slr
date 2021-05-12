#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QDate>

#define STUDENT_MARKS_COUNT 5

class Student
{
private:
    QString name;
    QString surname;
    QDate birth;
    int marks[STUDENT_MARKS_COUNT] = {0};
public:
    Student();
    Student(QString name, QString surname, QDate birth);
    Student(QString name, QString surname, QDate birth, int marks[STUDENT_MARKS_COUNT]);

    void setName(QString name);
    QString getName();

    void setSurname(QString surname);
    QString getSurname();

    void setBirth(QDate birth);
    QDate getBirth();

    void setMark(int index, int mark);
    int getMark(int index);

    QString toQString();

    enum ComparingType{
        ByName, BySurname, ByAge, ByMarks
    };

    static bool compare(Student s1, Student s2, ComparingType type);
};



#endif // STUDENT_H
