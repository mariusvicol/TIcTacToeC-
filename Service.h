#include "Repo.h"

class Service {
private:
    Repo& repo;
public:
    Service(Repo& repo): repo{repo}{}

    vector<Joc>& getAllService();

    void addService(Joc& joc);

    void modifyService(int id, int dim, string joc, string jucator, string stare);
};

