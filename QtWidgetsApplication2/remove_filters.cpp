#include "remove_filters.h"
#include <vector>
#include <qmessagebox.h>
#include "../Text Analizer/paradigms.h"


DialogRemove::DialogRemove(std::vector <std::shared_ptr<IParadigm>> filters_,
						   std::vector <std::shared_ptr<IParadigm>> union_filters_,
						   QWidget* parent) :
						   QDialog(parent) {

	ui.setupUi(this);
	filters = filters_;
	union_filters = union_filters_;

	set_filtres();
};


void DialogRemove::set_filtres() {
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