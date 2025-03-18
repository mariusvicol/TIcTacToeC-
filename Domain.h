#include <stdexcept>
#include <string>
using namespace std;
class Joc {
private:
    int id;
    int dim;
    string joc;
    string jucator;
    string stare;
public:
    Joc(int id, int dim, string joc, string jucator, string stare): id{id}, dim{dim}, joc{joc}, jucator{jucator}, stare{stare}{
        validate();
    }

    int getId() {
        return id;
    }

    int getDim() {
        return dim;
    }

    string getJoc() {
        return joc;
    }

    string getJucator() {
        return jucator;
    }

    string getStare() {
        return stare;
    }

    void setDim(int newDim) {
        if (newDim != 3 && newDim != 4 && newDim != 5) {
            throw invalid_argument("Dimensiunea trebuie sa fie 3, 4 sau 5.");
        }
        dim = newDim;
    }

    void setJoc(string newJoc) {
        if (newJoc.length() != dim * dim) {
            throw invalid_argument("Lungimea string-ului joc trebuie sa fie egala cu dim * dim.");
        }
        for (char c : newJoc) {
            if (c != 'X' && c != 'O' && c != '-') {
                throw invalid_argument("Jocul poate contine doar caracterele 'X', 'O' sau '-'.");
            }
        }
        joc = newJoc;
    }

    void setJucator(string newJucator) {
        if (newJucator != "X" && newJucator != "O") {
            throw invalid_argument("Jucatorul poate fi doar 'X' sau 'O'.");
        }
        jucator = newJucator;
    }

    void setStare(string newStare) {
        if (newStare != "Neinceput" && newStare != "In derulare" && newStare != "Terminat") {
            throw invalid_argument("Starea poate fi doar 'Neinceput', 'In derulare' sau 'Terminat'.");
        }
        stare = newStare;
    }

    void validate() {
        setDim(dim);
        setJoc(joc);
        setJucator(jucator);
        setStare(stare);
    }

    bool operator==(Joc other) {
        return id == other.id;
    }
};
