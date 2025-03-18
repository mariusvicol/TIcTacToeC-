#include "tests.h"
#include "Service.h"
#include <cassert>

void testDomanin(){
    Joc tic{1, 3, "X-OXO-XOO", "X", "Terminat"};
    assert(tic.getId() == 1);
    assert(tic.getDim() == 3);
    assert(tic.getJoc() == "X-OXO-XOO");
    assert(tic.getJucator() == "X");
    tic.setStare("In derulare");
    assert(tic.getStare() == "In derulare");
}

void testRepo(){
    Repo repo{"test.txt"};
    assert(repo.getAll().size() == 5);
    Joc tic{10, 3, "X-OXO-XOO", "X", "Terminat"};
    repo.add(tic);
    assert(repo.getAll().size() == 6);
    repo.del(tic);
}

void testService(){
    Repo repo{"test.txt"};
    Service service{repo};
    assert(service.getAllService().size() == 5);
    Joc tic{10, 3, "X-OXO-XOO", "X", "Terminat"};
    service.addService(tic);
    assert(service.getAllService().size() == 6);
    service.modifyService(10, 4, "----------------", "O",  "Neinceput");
    //assert(service.getAllService().at(4).getId() == 10);
    repo.del(tic);
}

void tests::testAll(){
    testDomanin();
    testRepo();
    testService();
}