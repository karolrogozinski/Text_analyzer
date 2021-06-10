#pragma once

#include "ui_remove_filters.h"
#include <vector>
#include <memory>
#include <QtWidgets/QMainWindow>
#include "../Text Analizer/paradigms.h"

class DialogRemove : public QDialog {
public:
	DialogRemove(std::vector <std::unique_ptr<IParadigm>>& filters,
				 std::vector <std::unique_ptr<IParadigm>>& union_filters,
				 QWidget* parent = Q_NULLPTR);

	bool checkBox() { return ui.checkBox->checkState(); };
	bool checkBox2() { return ui.checkBox_2->checkState(); };
	bool checkBox3() { return ui.checkBox_3->checkState(); };
	int typeFilters() { return ui.comboBox->currentIndex(); }
	int typeFilters2() { return ui.comboBox_2->currentIndex(); }
	void set_filtres(std::vector <std::unique_ptr<IParadigm>>& filters,
					 std::vector <std::unique_ptr<IParadigm>>& union_filters);

private:
	Ui::DialogRemove ui;
};
