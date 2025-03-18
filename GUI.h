#include "Service.h"
#include "TableModel.h"
#include <QApplication>
#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>

class GUI: public QWidget{
private:
    Service& service;

    QTableView* tableView = new QTableView;
    TableModel* modelTabel;
    QItemSelectionModel* selectionModel = tableView->selectionModel();

    QWidget* left = new QWidget;
    QVBoxLayout* leftLayout = new QVBoxLayout;

    QGridLayout *gridLayout;
    std::vector<std::vector<QPushButton*>> buttons;

    QLineEdit* editDim = new QLineEdit;
    QLabel* labelDim = new QLabel("DIMENSIUNEA");
    QLineEdit* editJoc = new QLineEdit;
    QLabel* labelJoc = new QLabel("JOC");
    QLineEdit* editJucator = new QLineEdit;
    QLabel* labelJucator = new QLabel("JUCATOR");
    QFormLayout* editLine = new QFormLayout;
    QPushButton* btnAdauga = new QPushButton("ADAUGA");

    QLineEdit* modifyId = new QLineEdit;
    QLineEdit* modifyDim = new QLineEdit;
    QLabel* labelModifyDim = new QLabel("DIMENSIUNEA");
    QLineEdit* modifyJoc = new QLineEdit;
    QLabel* labelModifyJoc = new QLabel("JOC");
    QLineEdit* modifyJucator = new QLineEdit;
    QLabel* labelModifyJucator = new QLabel("JUCATOR");
    QLineEdit* modifyStare = new QLineEdit;
    QLabel* labelModifyStare = new QLabel("STARE");
    QFormLayout* modifyLine = new QFormLayout;
    QPushButton* btnModify = new QPushButton("MODIFICA");


    void incarca(vector<Joc>& all);
    void initializare();
    void conectare();
public:
    GUI(Service& service): service{service}{
        modelTabel = new TableModel{service.getAllService()};
        tableView->setModel(modelTabel);
        selectionModel = tableView->selectionModel();
        initializare();
        incarca(service.getAllService());
        conectare();
    }

    void tabla(const QItemSelection& selected) {
        if (!selected.indexes().empty()) {
            QModelIndex index = selected.indexes().first();
            int row = index.row();

            int id = modelTabel->data(modelTabel->index(row, 0)).toInt();
            int dim = modelTabel->data(modelTabel->index(row, 1)).toInt();
            std::string joc = modelTabel->data(modelTabel->index(row, 2)).toString().toStdString();
            std::string jucator = modelTabel->data(modelTabel->index(row, 3)).toString().toStdString();
            std::string stare = modelTabel->data(modelTabel->index(row, 4)).toString().toStdString();

            for (auto &row : buttons) {
                for (auto &button : row) {
                    gridLayout->removeWidget(button);
                    delete button;
                }
            }
            buttons.clear();

            buttons.resize(dim, std::vector<QPushButton*>(dim, nullptr));

            for (int i = 0; i < dim; ++i) {
                for (int j = 0; j < dim; ++j) {
                    buttons[i][j] = new QPushButton(this);
                    gridLayout->addWidget(buttons[i][j], i, j);
                    int index = i * dim + j;
                    char state = (index < joc.size()) ? joc[index] : ' ';
                    buttons[i][j]->setText(QString(state));

                    QObject::connect(buttons[i][j], &QPushButton::clicked, [=]() {
                        if (state == '-') {
                            std::string newJoc = joc;
                            newJoc[index] = jucator[0];
                            QModelIndex dataIndex = modelTabel->index(row, 2);
                            QString newJocQString = QString::fromStdString(newJoc);
                            modelTabel->setData(dataIndex, newJocQString);

                            std::string nextPlayer = (jucator == "X") ? "O" : "X";
                            service.modifyService(id, dim, newJoc, nextPlayer, stare);
                            incarca(service.getAllService());
                            buttons[i][j]->setText(QString::fromStdString(jucator));
                            modelTabel->setJocuri(service.getAllService());
                        }
                    });
                    incarca(service.getAllService());
                }
            }
            gridLayout->update();
        }
    }

};