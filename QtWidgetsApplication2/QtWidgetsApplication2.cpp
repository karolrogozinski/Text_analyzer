#include "QtWidgetsApplication2.h"
#include "../Text Analizer/paradigms.h"
#include "../Text Analizer/paradigm_functions.h"
#include <memory>
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
        ParadigmWords pw;
        current_text = split_string(clean_string(text));
        int amount = pw.number_of_words(current_text);
        std::string new_label = "Text (" + std::to_string(amount);
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
            std::shared_ptr<IParadigm> p(new ParadigmEqualLength(std::to_string(dialog.valueFilter1())));
            filters.push_back(p);
        };
        if (dialog.checkBox2()) {
            std::shared_ptr<IParadigm> p(new ParadigmLongerThan(std::to_string(dialog.valueFilter2())));
            filters.push_back(p);
        };
        if (dialog.checkBox3()) {
            std::shared_ptr<IParadigm> p(new ParadigmShorterThan(std::to_string(dialog.valueFilter3())));
            filters.push_back(p);
        };
        if (dialog.checkBox4()) {
            std::shared_ptr<IParadigm> p(new ParadigmStartsWithSequence(dialog.valueFilter4()));
            filters.push_back(p);
        };
        if (dialog.checkBox5()) {
            std::shared_ptr<IParadigm> p(new ParadigmEndsOnSequence(dialog.valueFilter5()));
            filters.push_back(p);
        };
        if (dialog.checkBox6()) {
            std::shared_ptr<IParadigm> p(new ParadigmContainSequence(dialog.valueFilter6()));
            filters.push_back(p);
        };
        if (dialog.checkBox7()) {
            std::shared_ptr<IParadigm> p(new ParadigmCustom(dialog.valueFilter7()));
            filters.push_back(p);
        };
    };
    if (dialog.typeFilters() == 1) {
        if (dialog.checkBox1()) {
            std::shared_ptr<IParadigm> p(new ParadigmEqualLength(std::to_string(dialog.valueFilter1())));
            union_filters.push_back(p);
        };
        if (dialog.checkBox2()) {
            std::shared_ptr<IParadigm> p(new ParadigmLongerThan(std::to_string(dialog.valueFilter2())));
            union_filters.push_back(p);
        };
        if (dialog.checkBox3()) {
            std::shared_ptr<IParadigm> p(new ParadigmShorterThan(std::to_string(dialog.valueFilter3())));
            union_filters.push_back(p);
        };
        if (dialog.checkBox4()) {
            std::shared_ptr<IParadigm> p(new ParadigmStartsWithSequence(dialog.valueFilter4()));
            union_filters.push_back(p);
        };
        if (dialog.checkBox5()) {
            std::shared_ptr<IParadigm> p(new ParadigmEndsOnSequence(dialog.valueFilter5()));
            union_filters.push_back(p);
        };
        if (dialog.checkBox6()) {
            std::shared_ptr<IParadigm> p(new ParadigmContainSequence(dialog.valueFilter6()));
            union_filters.push_back(p);
        };
        if (dialog.checkBox7()) {
            std::shared_ptr<IParadigm> p(new ParadigmCustom(dialog.valueFilter7()));
            union_filters.push_back(p);
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
        filters = erease_paradigm(filters, dialog.typeFilters());
    };
    if (dialog.checkBox2()) {
        union_filters = erease_paradigm(union_filters, dialog.typeFilters2());
    };

    set_filters_description();
};


void MainWindow::runAnalyze() {
    if (current_text.empty()) {
        QMessageBox msgBox;
        msgBox.setText("No text chosen.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        return;
    };
    if (filters.empty() && union_filters.empty()) {
        QMessageBox msgBox;
        msgBox.setText("No filters chosen.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        return;
    }

    std::vector <std::string> text;
    if (!filters.empty()) {
        text = get_intersection(current_text, filters);
    };
    if (!union_filters.empty()) {
        if (!text.empty()) {
            text = get_union(text, union_filters);
        }
        else { text = get_union(current_text, union_filters); }
    };
    std::string s_text = to_str(text);
    ui.textBrowser->setText(QString::fromLocal8Bit(s_text.c_str()));
    ParadigmWords pw;
    std::string new_label = "Filtered: (" + std::to_string(pw.number_of_words(text));
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