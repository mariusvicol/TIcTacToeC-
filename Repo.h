#include "Domain.h"
#include <vector>

class Repo {
private:
    string filename;
    vector<Joc> jocuri;
public:
    Repo(string filename): filename{filename}{
        load();
    }

    void load();

    void save();

    void add(Joc joc);

    void del(Joc joc);

    vector<Joc>& getAll();
};

