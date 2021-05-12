#include "student.h"

Student::Student(){}

Student::Student(QString name, QString surname, QDate birth)
{
    this->name = name;
    this->surname = surname;
    this->birth = birth;
}

Student::Student(QString name, QString surname, QDate birth, int marks[])
{
    this->name = name;
    this->surname = surname;
    this->birth = birth;
    for(int i = 0; i < STUDENT_MARKS_COUNT; i++){
        this->marks[i] = marks[i];
    }
}

void Student::setName(QString name){
    this->name = name;
}
QString Student::getName(){
    return this->name;
}

void Student::setSurname(QString surname){
    this->surname = surname;
}
QString Student::getSurname(){
    return this->surname;
}

void Student::setBirth(QDate birth){
    this->birth = birth;
}
QDate Student::getBirth(){
    return this->birth;
}

void Student::setMark(int index, int mark){
    if(index >= 0 && index < STUDENT_MARKS_COUNT){
        this->marks[index] = mark;
    }
}
int Student::getMark(int index){
    if(index >= 0 && index < STUDENT_MARKS_COUNT){
        return this->marks[index];
    }
}

QString Student::toQString()
{
    QString res = getName()+" "+getSurname()+
            " "+getBirth().toString("dd.MM.yyyy");

    for(int i = 0; i < STUDENT_MARKS_COUNT; ++i){
        res += " " + QString::number(getMark(i));
    }

    return res;
}


bool Student::compare(Student s1, Student s2, ComparingType type)
{
    bool ret = false;

    switch (type) {
    case ByName:
        ret = s1.getName() > s2.getName();
        break;
    case BySurname:
        ret = s1.getSurname() > s2.getSurname();
        break;
    case ByAge:
        ret = s1.getBirth() < s2.getBirth();
        break;
    case ByMarks:
        double m1 = 0, m2 = 0;
        for(int i = 0; i < STUDENT_MARKS_COUNT; i++){
            m1 += s1.getMark(i);
            m2 += s2.getMark(i);
        }
        m1 /= STUDENT_MARKS_COUNT;
        m2 /= STUDENT_MARKS_COUNT;

        ret = m1 > m2;
        break;
    }

    return ret;
}
