#include <iostream>

#include "genericfsm.h"

using namespace std;

enum State
{
    error = 0,
    foo1 = 1,
    foo2,
    foo3,
    foo4,
    foo5
};

enum Status
{
    OK = 1,
    NOT_OK = 0
};

class MyFSM: public FSM::GenericFSM<MyFSM>
{
public:
    MyFSM(): GenericFSM(this) { init(); }

    void fStFoo1();
    void fStFoo2();
    void fStFoo3();
    void fStFoo4();
    void fStFoo5();
    void fStError();

    void init();
};

void MyFSM::fStFoo1()
{
    cout << "foo1()" << endl;
    transit(OK);
}

void MyFSM::fStFoo2()
{
    cout << "foo2()" << endl;
    transit(OK);
}

void MyFSM::fStFoo3()
{
    cout << "foo3()" << endl;
    transit(NOT_OK);
}

void MyFSM::fStFoo4()
{
    cout << "foo4()" << endl;
    transit(OK);
}

void MyFSM::fStFoo5()
{
    cout << "foo5()" << endl;
    transit(NOT_OK);
}

void MyFSM::fStError()
{
    cout << "Error!"<< endl;
}

void MyFSM::init()
{
    // dodajemy wszystkie stany (łączymy "etykietki" stanów z funkacjami)
    addInitialState(foo1, &fStFoo1);
    addState(foo2, &fStFoo2);
    addState(foo3, &fStFoo3);
    addState(foo4, &fStFoo4);
    addState(foo5, &fStFoo5);
    addState(error, &fStError);

    // definiujemy jak maja wyglądać przejścia pomiędzy funkcjami
    addTransition(foo1, foo2, OK);
    addDefaultTransition(foo1, error);

    addTransition(foo2, foo3, OK);
    addDefaultTransition(foo2, error);

    addTransition(foo3, foo4, OK);
    addDefaultTransition(foo3, error);

    addTransition(foo4, foo5, OK);
    addDefaultTransition(foo4, error);

    addTransition(foo5, foo1, OK);
    addDefaultTransition(foo5, error);
}


int main()
{
    cout << "Hello World!" << endl;

    MyFSM fsm;
    fsm.start();

    return 0;
}
