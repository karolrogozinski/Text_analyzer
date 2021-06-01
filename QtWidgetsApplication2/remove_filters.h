#pragma once

#include "ui_remove_filters.h"
#include <vector>

class DialogRemove : public QDialog {
public:
	std::vector <std::pair<char, std::string>> filters;
	std::vector <std::pair<char, std::string>> union_filters;

	DialogRemove(std::vector <std::pair<char, std::string>> filters,
		std::vector <std::pair<char, std::string>> union_filters,
		QWidget* parent = Q_NULLPTR);

	bool checkBox() { return ui.checkBox->checkState(); };
	bool checkBox2() { return ui.checkBox_2->checkState(); };
	bool checkBox3() { return ui.checkBox_3->checkState(); };
	int typeFilters() { return ui.comboBox->currentIndex(); }
	int typeFilters2() { return ui.comboBox_2->currentIndex(); }
	void set_filtres();

private:
	Ui::DialogRemove ui;
};
