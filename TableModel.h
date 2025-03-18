#include <QAbstractTableModel>
#include <vector>

class TableModel: public QAbstractTableModel{
private:
    vector<Joc>& jocuri;
public:
    TableModel(vector<Joc>& jocuri): jocuri{jocuri}{}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override{
        return jocuri.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override{
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override{
        if (role == Qt::DisplayRole){
            Joc joc = jocuri[index.row()];
            switch(index.column()){
                case 0: return QString::number(joc.getId());
                case 1: return QString::number(joc.getDim());
                case 2: return QString::fromStdString(joc.getJoc());
                case 3: return QString::fromStdString(joc.getJucator());
                case 4: return QString::fromStdString(joc.getStare());
            }
        }
        return QVariant{};
    }

    void setJocuri(vector<Joc>& all){
        emit layoutAboutToBeChanged();
        jocuri = all;
        emit layoutChanged();
    }
};