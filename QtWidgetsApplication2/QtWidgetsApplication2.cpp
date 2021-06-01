#include "QtWidgetsApplication2.h"
#include "../Text Analizer/analyzer.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "DialogButtonBottom.h"
#include "remove_filters.h"
#include <vector>
#include <tuple>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.actionOpen_new_file, SIGNAL(triggered()), this, SLOT(readFile()));
    connect(ui.actionAdd_filter, SIGNAL(triggered()), this, SLOT(newFilters()));
    connect(ui.actionRun_analyze, SIGNAL(triggered()), this, SLOT(runAnalyze()));
    connect(ui.actionRemove_filter, SIGNAL(triggered()), this, SLOT(removeFilters()));
}


void MainWindow::readFile() {
    QString file_name = QFileDialog::getOpenFileName(this, "Choose a file", "C://", tr("Image Files (*.txt)"));
    if (file_name != "") {
        ui.label_4->setText(file_name);
        std::string text = read_file(file_name.toStdString());
        ui.textBrowser->setText(QString::fromLocal8Bit(text.c_str()));
        ParadigmWords pw(text);
        current_text = text;
        std::string new_label = "Text (" + std::to_string(pw.number_of_words());
        new_label += " words):";
        ui.label_2->setText(QString::fromLocal8Bit(new_label.c_str()));
    }
};


void MainWindow::newFilters() {
    Dialog dialog;
    dialog.exec();
    if (!dialog.result()) { return; }
    if (dialog.typeFilters() == 0) {
        if (dialog.checkBox1()) {
            std::pair <char, std::string> filter = { 3, std::to_string(dialog.valueFilter1()) };
            filters.push_back(filter);
        };
        if (dialog.checkBox2()) {
            std::pair <char, std::string> filter = { 1, std::to_string(dialog.valueFilter2()) };
            filters.push_back(filter);
        };
        if (dialog.checkBox3()) {
            std::pair <char, std::string> filter = { 2, std::to_string(dialog.valueFilter3()) };
            filters.push_back(filter);
        };
        if (dialog.checkBox4()) {
            std::pair <char, std::string> filter = { 4, dialog.valueFilter4() };
            filters.push_back(filter);
        };
        if (dialog.checkBox5()) {
            std::pair <char, std::string> filter = { 5, dialog.valueFilter5() };
            filters.push_back(filter);
        };
        if (dialog.checkBox6()) {
            std::pair <char, std::string> filter = { 6, dialog.valueFilter6() };
            filters.push_back(filter);
        };
        if (dialog.checkBox7()) {
            std::pair <char, std::string> filter = { 7, dialog.valueFilter7() };
            filters.push_back(filter);
        };
    };
    if (dialog.typeFilters() == 1) {
        if (dialog.checkBox1()) {
            std::pair <char, std::string> filter = { 3, std::to_string(dialog.valueFilter1()) };
            union_filters.push_back(filter);
        };
        if (dialog.checkBox2()) {
            std::pair <char, std::string> filter = { 1, std::to_string(dialog.valueFilter2()) };
            union_filters.push_back(filter);
        };
        if (dialog.checkBox3()) {
            std::pair <char, std::string> filter = { 2, std::to_string(dialog.valueFilter3()) };
            union_filters.push_back(filter);
        };
        if (dialog.checkBox4()) {
            std::pair <char, std::string> filter = { 4, dialog.valueFilter4() };
            union_filters.push_back(filter);
        };
        if (dialog.checkBox5()) {
            std::pair <char, std::string> filter = { 5, dialog.valueFilter5() };
            union_filters.push_back(filter);
        };
        if (dialog.checkBox6()) {
            std::pair <char, std::string> filter = { 6, dialog.valueFilter6() };
            union_filters.push_back(filter);
        };
        if (dialog.checkBox7()) {
            std::pair <char, std::string> filter = { 7, dialog.valueFilter7() };
            union_filters.push_back(filter);
        };
    };

    set_filters_description();
};


void MainWindow::removeFilters() {
    DialogRemove dialog(filters, union_filters);
    dialog.exec();
    if (!dialog.result()) { return; }
    if (dialog.checkBox()) {
        filters.clear();
        union_filters.clear();
    };
    if (dialog.checkBox3()) {
        int number = filters[dialog.typeFilters()].first;
        filters = erease_paradigm(filters, number);
    };
    if (dialog.checkBox2()) {
        int number = union_filters[dialog.typeFilters2()].first;
        union_filters = erease_paradigm(union_filters, number);
    };

    set_filters_description();
};


void MainWindow::runAnalyze() {
    if (current_text == "") {
        QMessageBox msgBox;
        msgBox.setText("No text choosen.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        return;
    };
    if (filters.empty() && union_filters.empty()) {
        QMessageBox msgBox;
        msgBox.setText("No filters choosen.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        return;
    }

    std::string text = "";
    if (!filters.empty()) {
        text = get_intersection(current_text, filters);
    };
    if (!union_filters.empty()) {
        if (text != "") {
            text = get_union(text, union_filters);
        }
        else { text = get_union(current_text, union_filters); }
    };

    ui.textBrowser->setText(QString::fromLocal8Bit(text.c_str()));
    ParadigmWords pw(text);
    std::string new_label = "Filtered: (" + std::to_string(pw.number_of_words());
    new_label += " words):";
    ui.label_2->setText(QString::fromLocal8Bit(new_label.c_str()));
};


void MainWindow::set_filters_description() {
    std::string text = "";

    if (!filters.empty()) {
        text += "Intersections:\n";
        std::vector <std::string> desc = describe_filters(filters);
        for (auto a : desc) {
            text += " * ";
            text += a;
            text += '\n';
        };
        text += "\n";
    };

    if (!union_filters.empty()) {
        text += "Unions:\n";
        std::vector <std::string> desc = describe_filters(union_filters);
        for (auto a : desc) {
            text += " * ";
            text += a;
            text += '\n';
        };
    };

    if (text.empty()) {
        text = "Filtres not chosen.";
    };

    ui.textBrowser_2->setText(QString::fromLocal8Bit(text.c_str()));
};