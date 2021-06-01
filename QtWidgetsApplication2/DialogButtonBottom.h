#pragma once

#include "ui_DialogButtonBottom.h"

class Dialog : public QDialog {
public:
	Dialog(QWidget* parent = Q_NULLPTR);
	bool checkBox1() { return ui.checkBox->checkState(); };
	bool checkBox2() { return ui.checkBox_2->checkState(); };
	bool checkBox3() { return ui.checkBox_3->checkState(); };
	bool checkBox4() { return ui.checkBox_4->checkState(); };
	bool checkBox5() { return ui.checkBox_5->checkState(); };
	bool checkBox6() { return ui.checkBox_6->checkState(); };
	bool checkBox7() { return ui.checkBox_7->checkState(); };

	int valueFilter1() { return ui.spinBox->value(); };
	int valueFilter2() { return ui.spinBox_2->value(); };
	int valueFilter3() { return ui.spinBox_3->value(); };
	std::string valueFilter4() { return ui.lineEdit->text().toStdString(); }
	std::string valueFilter5() { return ui.lineEdit_2->text().toStdString(); }
	std::string valueFilter6() { return ui.lineEdit_3->text().toStdString(); }
	std::string valueFilter7() { return ui.lineEdit_4->text().toStdString(); }

	int typeFilters() { return ui.comboBox->currentIndex(); }

protected:
	Ui::Dialog ui;
};