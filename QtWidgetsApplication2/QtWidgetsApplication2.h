#pragma once

#include <vector>
#include <tuple>
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication2.h"
#include <memory>
#include "../Text Analizer/paradigms.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    void set_filters_description();

public slots:
    void readFile();
    void newFilters();
    void runAnalyze();
    void removeFilters();

private:
    Ui::MainWindow ui;
    std::vector <std::shared_ptr<IParadigm>> filters;
    std::vector <std::shared_ptr<IParadigm>> union_filters;
    std::vector <std::string> current_text;
};
