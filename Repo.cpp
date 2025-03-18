#include "Repo.h"
#include <fstream>
#include <sstream>
#include <algorithm>
vector<Joc>& Repo::getAll() {
    return jocuri;
}

void Repo::load() {
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        string id, dim, joc, jucator, stare;
        istringstream sin(line);
        getline(sin, id, ',');
        getline(sin, dim, ',');
        getline(sin, joc, ',');
        getline(sin, jucator, ',');
        getline(sin, stare, ',');
        Joc j{stoi(id), stoi(dim), joc, jucator, stare};
        jocuri.push_back(j);
    }
    fin.close();
}

void Repo::save() {
    ofstream fout(filename);
    for(auto joc: jocuri){
        string text = to_string(joc.getId()) + "," + to_string(joc.getDim()) + "," + joc.getJoc() + "," + joc.getJucator() + "," + joc.getStare() + "\n";
        fout << text;
    }
    fout.close();
}

void Repo::add(Joc joc) {
    jocuri.push_back(joc);
    save();
}

void Repo::del(Joc joc) {
    auto it = find(jocuri.begin(), jocuri.end(), joc);
    if(it != jocuri.end())
        jocuri.erase(it);
    save();
}