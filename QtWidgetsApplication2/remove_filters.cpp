#include "remove_filters.h"
#include <vector>
#include <qmessagebox.h>
#include "../Text Analizer/paradigms.h"


DialogRemove::DialogRemove(std::vector <std::unique_ptr<IParadigm>>& filters,
						   std::vector <std::unique_ptr<IParadigm>>& union_filters,
						   QWidget* parent) : QDialog(parent) {

	ui.setupUi(this);

	set_filtres(filters, union_filters);
};


void DialogRemove::set_filtres(std::vector <std::unique_ptr<IParadigm>>& filters,
							   std::vector <std::unique_ptr<IParadigm>>& union_filters) {
	if (!filters.empty()) {
		std::vector <std::string> desc = describe_filters(filters);
		for (auto a : desc) {
			ui.comboBox->addItem(QString::fromLocal8Bit(a.c_str()));
		};
	};
	if (!union_filters.empty()) {
		std::vector <std::string> desc = describe_filters(union_filters);
		for (auto a : desc) {
			ui.comboBox_2->addItem(QString::fromLocal8Bit(a.c_str()));
		};
	};
};