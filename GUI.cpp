#include "GUI.h"
#include <random>

void GUI::initializare() {
    QHBoxLayout* main = new QHBoxLayout{this};
    editLine->addRow(labelDim, editDim);
    editLine->addRow(labelJoc, editJoc);
    editLine->addRow(labelJucator, editJucator);
    leftLayout->addLayout(editLine);
    leftLayout->addWidget(btnAdauga);

    modifyLine->addRow(modifyDim, labelModifyDim);
    modifyLine->addRow(modifyJoc, labelModifyJoc);
    modifyLine->addRow(modifyJucator, labelModifyJucator);
    modifyLine->addRow(modifyStare, labelModifyStare);
    leftLayout->addLayout(modifyLine);
    leftLayout->addWidget(btnModify);

    gridLayout = new QGridLayout();
    leftLayout->addLayout(gridLayout);

    QWidget* right = new QWidget;
    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(tableView);

    left->setLayout(leftLayout);
    right->setLayout(rightLayout);

    main->addWidget(left);
    main->addWidget(right);
}

void GUI::conectare() {
    QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
        int id = rand();
        int dim = editDim->text().toInt();
        string joc = editJoc->text().toStdString();
        string jucator = editJucator->text().toStdString();
        string stare = "Neinceput";
        Joc j{id, dim, joc, jucator, stare};
        service.addService(j);
        incarca(service.getAllService());
        editDim->clear();
        editJoc->clear();
        editJucator->clear();
    });

    QObject::connect(selectionModel, &QItemSelectionModel::selectionChanged, [&](){
        if (tableView->selectionModel()->selectedIndexes().isEmpty()) {
            return;
        }
        int selRow = tableView->selectionModel()->selectedIndexes().at(0).row();
        auto cel0Index = tableView->model()->index(selRow, 0);
        auto cel0Value = tableView->model()->data(cel0Index, Qt::DisplayRole).toInt();
        int id = cel0Value;

        auto cel1Index = tableView->model()->index(selRow, 1);
        auto cel1Value = tableView->model()->data(cel1Index, Qt::DisplayRole).toString();
        int dim = cel1Value.toInt();

        auto cel2Index = tableView->model()->index(selRow, 2);
        auto cel2Value = tableView->model()->data(cel2Index, Qt::DisplayRole).toString();
        string joc = cel2Value.toStdString();

        auto cel3Index = tableView->model()->index(selRow, 3);
        auto cel3Value = tableView->model()->data(cel3Index, Qt::DisplayRole).toString();
        string jucator = cel3Value.toStdString();

        auto cel4Index = tableView->model()->index(selRow, 4);
        auto cel4Value = tableView->model()->data(cel4Index, Qt::DisplayRole).toString();
        string stare = cel4Value.toStdString();

        modifyId->setText(QString::number(id));
        modifyDim->setText(QString::number(dim));
        modifyJoc->setText(QString::fromStdString(joc));
        modifyJucator->setText(QString::fromStdString(jucator));
        modifyStare->setText(QString::fromStdString(stare));
    });

    QObject::connect(btnModify, &QPushButton::clicked, [&](){

        int id = modifyId->text().toInt();
        int newDim = modifyDim->text().toInt();
        string newJoc = modifyJoc->text().toStdString();
        string newJucator = modifyJucator->text().toStdString();
        string newStare = modifyStare->text().toStdString();

        try{
            service.modifyService(id, newDim, newJoc, newJucator, newStare);
            incarca(service.getAllService());
            modifyId->clear();
            modifyDim->clear();
            modifyStare->clear();
            modifyJoc->clear();
            modifyJucator->clear();
        }
        catch (invalid_argument& ex){
            QMessageBox::warning(this, "Warning", ex.what());
        }
    });
    QObject::connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &GUI::tabla);
}

void GUI::incarca(vector<Joc> &all) {
    modelTabel->setJocuri(all);
}