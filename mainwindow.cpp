#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->lineEdit_add_name, SIGNAL(textChanged(QString)), this, SLOT(refresh_add_input()));
    connect(ui->lineEdit_add_surname, SIGNAL(textChanged(QString)), this, SLOT(refresh_add_input()));

    connect(ui->lineEdit_edit_name, SIGNAL(textChanged(QString)), this, SLOT(refresh_edit_input()));
    connect(ui->lineEdit_edit_surname, SIGNAL(textChanged(QString)), this, SLOT(refresh_edit_input()));

    connect(ui->spinBox_edit_student, SIGNAL(valueChanged(int)), this, SLOT(refresh_edit_content()));
    connect(ui->pushButton_edit_reset, SIGNAL(clicked()), this, SLOT(refresh_edit_content()));

    connect(ui->pushButton_sort_age_down, SIGNAL(clicked()), this, SLOT(sort()));
    connect(ui->pushButton_sort_age_up, SIGNAL(clicked()), this, SLOT(sort()));
    connect(ui->pushButton_sort_marks_down, SIGNAL(clicked()), this, SLOT(sort()));
    connect(ui->pushButton_sort_marks_up, SIGNAL(clicked()), this, SLOT(sort()));
    connect(ui->pushButton_sort_name_down, SIGNAL(clicked()), this, SLOT(sort()));
    connect(ui->pushButton_sort_name_up, SIGNAL(clicked()), this, SLOT(sort()));
    connect(ui->pushButton_sort_surname_down, SIGNAL(clicked()), this, SLOT(sort()));
    connect(ui->pushButton_sort_surname_up, SIGNAL(clicked()), this, SLOT(sort()));

    refresh_add_input();
    refresh_edit_input();
    refresh_edit_content();
    refresh_table();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clr_table()
{
    QAbstractItemModel* mdl = ui->tableWidget->model();
    mdl->removeRows(0,mdl->rowCount());
    mdl->removeColumns(0,mdl->columnCount());

    ui->tableWidget->setColumnCount(3+STUDENT_MARKS_COUNT);

    QStringList headers;
    headers << "Name" << "Surname" << "Birth date";
    for(int i = 0; i < STUDENT_MARKS_COUNT; i++){
        headers << "";
    }

    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

void MainWindow::fill_table()
{
    int list_size = this->Students.size();

    for(int i = 0; i < list_size; i++){
        ui->tableWidget->insertRow(0);
    }

    int row = 0;
    for(auto it = this->Students.begin(); it != this->Students.end(); ++it, row++){
        QTableWidgetItem *item_name = new QTableWidgetItem(it->getName());
        ui->tableWidget->setItem(row, 0, item_name);
        QTableWidgetItem *item_surname = new QTableWidgetItem(it->getSurname());
        ui->tableWidget->setItem(row, 1, item_surname);
        QTableWidgetItem *item_bday = new QTableWidgetItem(it->getBirth().toString("dd.MM.yyyy"));
        ui->tableWidget->setItem(row, 2, item_bday);

        for(int i = 0; i < STUDENT_MARKS_COUNT; ++i){
            QString markstring = QString::number(it->getMark(i));
            QTableWidgetItem *item = new QTableWidgetItem(markstring);
            ui->tableWidget->setItem(row, 3+i, item);
        }

    }
}

void MainWindow::size_table()
{
    ui->tableWidget->horizontalHeader()->resizeSection(0, 60);
    ui->tableWidget->horizontalHeader()->resizeSection(1, 60);
    ui->tableWidget->horizontalHeader()->resizeSection(2, 70);
    for(int i = 0; i < STUDENT_MARKS_COUNT; i++){
        ui->tableWidget->horizontalHeader()->resizeSection(3+i, 10);
    }
}

void MainWindow::refresh_table()
{
    clr_table();
    fill_table();
    size_table();

    ui->spinBox_edit_student->setMinimum(1);
    ui->spinBox_edit_student->setMaximum(this->Students.size());

    refresh_edit_content();
}

void MainWindow::refresh_add_input()
{
    bool correct = true;
    correct = correct && ui->lineEdit_add_name->text().contains(QRegularExpression("^[A-Z]"));
    correct = correct && ui->lineEdit_add_surname->text().contains(QRegularExpression("^[A-Z]"));

    ui->pushButton_add->setEnabled(correct);
}

void MainWindow::refresh_edit_input()
{
    bool correct = true;
    correct = correct && ui->lineEdit_edit_name->text().contains(QRegularExpression("^[A-Z]"));
    correct = correct && ui->lineEdit_edit_surname->text().contains(QRegularExpression("^[A-Z]"));

    ui->pushButton_edit_save->setEnabled(correct);
}

void MainWindow::refresh_edit_content()
{
    if(this->Students.isEmpty()){
        ui->lineEdit_edit_name->setText("");
        ui->lineEdit_edit_surname->setText("");
        ui->dateEdit_edit_date->setDate(QDate(2000,1,1));

        ui->spinBox_edit_mark_1->setValue(1);
        ui->spinBox_edit_mark_2->setValue(1);
        ui->spinBox_edit_mark_3->setValue(1);
        ui->spinBox_edit_mark_4->setValue(1);
        ui->spinBox_edit_mark_5->setValue(1);

        ui->lineEdit_edit_name->setEnabled(false);
        ui->lineEdit_edit_surname->setEnabled(false);
        ui->dateEdit_edit_date->setEnabled(false);
        ui->spinBox_edit_mark_1->setEnabled(false);
        ui->spinBox_edit_mark_2->setEnabled(false);
        ui->spinBox_edit_mark_3->setEnabled(false);
        ui->spinBox_edit_mark_4->setEnabled(false);
        ui->spinBox_edit_mark_5->setEnabled(false);
    } else {
        ui->lineEdit_edit_name->setEnabled(true);
        ui->lineEdit_edit_surname->setEnabled(true);
        ui->dateEdit_edit_date->setEnabled(true);
        ui->spinBox_edit_mark_1->setEnabled(true);
        ui->spinBox_edit_mark_2->setEnabled(true);
        ui->spinBox_edit_mark_3->setEnabled(true);
        ui->spinBox_edit_mark_4->setEnabled(true);
        ui->spinBox_edit_mark_5->setEnabled(true);

        int index = ui->spinBox_edit_student->value()-1;
        auto it = this->Students.begin();
        it += index;
        Student current = *it;

        ui->lineEdit_edit_name->setText(current.getName());
        ui->lineEdit_edit_surname->setText(current.getSurname());
        ui->dateEdit_edit_date->setDate(current.getBirth());

        ui->spinBox_edit_mark_1->setValue(current.getMark(0));
        ui->spinBox_edit_mark_2->setValue(current.getMark(1));
        ui->spinBox_edit_mark_3->setValue(current.getMark(2));
        ui->spinBox_edit_mark_4->setValue(current.getMark(3));
        ui->spinBox_edit_mark_5->setValue(current.getMark(4));
    }
}

void MainWindow::sort()
{
    QPushButton *button = (QPushButton*)sender();
    Student::ComparingType type;
    bool invert = false;

    if(button->objectName() == "pushButton_sort_age_down"){
        type = Student::ByAge;
        invert = false;
    } else if(button->objectName() == "pushButton_sort_age_up"){
        type = Student::ByAge;
        invert = true;
    } else if(button->objectName() == "pushButton_sort_marks_down"){
        type = Student::ByMarks;
        invert = false;
    } else if(button->objectName() == "pushButton_sort_marks_up"){
        type = Student::ByMarks;
        invert = true;
    } else if(button->objectName() == "pushButton_sort_name_down"){
        type = Student::ByName;
        invert = false;
    } else if(button->objectName() == "pushButton_sort_name_up"){
        type = Student::ByName;
        invert = true;
    } else if(button->objectName() == "pushButton_sort_surname_down"){
        type = Student::BySurname;
        invert = false;
    } else if(button->objectName() == "pushButton_sort_surname_up"){
        type = Student::BySurname;
        invert = true;
    }

    for(auto it1 = this->Students.begin(); it1 != this->Students.end(); ++it1){
        for(auto it2 = it1; it2 != this->Students.end(); ++it2){
            bool compare = Student::compare(*it1, *it2, type);
            if(invert) compare = !compare;

            if(compare){
                Student tmp = *it1;
                *it1 = *it2;
                *it2 = tmp;
            }
        }
    }

    refresh_table();
}


void MainWindow::on_action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "", "", "*.txt");
    QFile file(filename);
    int line_count = 0;

    int err_count = 0;
    QString err_msges;

    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this, "Error", "Could not open file \"" + filename + "\"");
        return ;
    }

    this->Students.clear();

    while(!file.atEnd()){
        QString line = file.readLine();
        ++line_count;

        QTextStream linestream(&line);

        QString name = "", surname = "", date_string = "";
        QDate date;
        int marks[STUDENT_MARKS_COUNT]={0};

        linestream  >> name >> surname >> date_string;
        date = QDate::fromString(date_string, "dd.MM.yyyy");

        for(int i = 0; i < STUDENT_MARKS_COUNT; i++){
            linestream >> marks[i];
        }

        QString regex = "^\\w+\\s\\w+\\s\\d{2}\\.\\d{2}\\.\\d{4}(\\s[1-5]){" + QString::number(STUDENT_MARKS_COUNT) + "}";
//        qDebug() << "REGEX\n" << line << "\n" << line.contains(QRegularExpression(regex));

        bool right_formatting = line.contains(QRegularExpression(regex)) && date.isValid();

        if(right_formatting){
            Student tmpstudent(name, surname, date, marks);
            this->Students.push_back(tmpstudent);
        } else{
            ++err_count;
            err_msges += "Wrong format on line " + QString::number(line_count) + "\n\"" + line + "\"\n";
        }
    }

    file.close();

    refresh_table();

    if(err_count > 0){
        QString dial_containment = QString::number(err_count) + " records have invalid format\n\n" + err_msges;
        QMessageBox::warning(this, "Warning", dial_containment);
    }
}

void MainWindow::on_action_Save_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "", "", "*.txt");
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::critical(this, "Error", "Could not save file \"" + filename + "\"");
        return ;
    }

    for(auto element : this->Students){
        QString line = element.toQString() + "\n";
        QTextStream out(&file);
        out << line;
    }

    file.close();
}

void MainWindow::on_pushButton_add_clicked()
{
    QString new_name = ui->lineEdit_add_name->text();
    QString new_surname = ui->lineEdit_add_surname->text();
    QDate new_bday = ui->dateEdit_add_date->date();
    int new_marks[STUDENT_MARKS_COUNT] = {
        ui->spinBox_add_mark_1->value(),
        ui->spinBox_add_mark_2->value(),
        ui->spinBox_add_mark_3->value(),
        ui->spinBox_add_mark_4->value(),
        ui->spinBox_add_mark_5->value()
    };

    Student new_student(new_name, new_surname, new_bday, new_marks);

    this->Students.push_back(new_student);

    refresh_table();
}

void MainWindow::on_pushButton_add_clear_clicked()
{
    ui->lineEdit_add_name->setText("");
    ui->lineEdit_add_surname->setText("");
    ui->dateEdit_add_date->setDateTime(QDateTime(QDate(1,1,2000), QTime(0,0,0)));
    ui->spinBox_add_mark_1->setValue(1);
    ui->spinBox_add_mark_2->setValue(1);
    ui->spinBox_add_mark_3->setValue(1);
    ui->spinBox_add_mark_4->setValue(1);
    ui->spinBox_add_mark_5->setValue(1);
}

void MainWindow::on_pushButton_edit_save_clicked()
{
    QString name = ui->lineEdit_edit_name->text();
    QString surname = ui->lineEdit_edit_surname->text();
    QDate bday = ui->dateEdit_edit_date->date();
    int marks[STUDENT_MARKS_COUNT] = {
        ui->spinBox_edit_mark_1->value(),
        ui->spinBox_edit_mark_2->value(),
        ui->spinBox_edit_mark_3->value(),
        ui->spinBox_edit_mark_4->value(),
        ui->spinBox_edit_mark_5->value()
    };

    Student new_student(name, surname, bday, marks);

    auto it = this->Students.begin();
    it += ui->spinBox_edit_student->value()-1;

    *it = new_student;

    refresh_table();
}
