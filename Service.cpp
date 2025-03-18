#include "Service.h"
#include <algorithm>
bool comparator(Joc j1, Joc j2){
    return j1.getStare() < j2.getStare();
}

vector<Joc> &Service::getAllService() {
    sort(repo.getAll().begin(), repo.getAll().end(), comparator);
    return repo.getAll();
}

void Service::addService(Joc& joc) {
    repo.add(joc);
}

void Service::modifyService(int id, int dim, string joc, string jucator, string stare) {
    for (Joc& j : repo.getAll()) {
        if (j.getId() == id) {
            j.setDim(dim);
            j.setJoc(joc);
            j.setJucator(jucator);
            if(jucator.find('-') != string::npos){
                j.setStare(stare);
            }
            else
                j.setStare("Terminat");
            repo.save();
            return;
        }
    }
    throw invalid_argument("Jocul cu id-ul specificat nu a fost gasit.");
}