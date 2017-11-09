#ifndef GENERICFSM
#define GENERICFSM

#include <iostream>
#include <map>


namespace FSM
{
typedef unsigned int uint;


template <class T>
class GenericFSM
{
    typedef std::pair<uint, uint> StateAndEvent;
    typedef std::map<StateAndEvent, uint> TransitionTable;
    typedef std::map<uint, void (T::*)()> FunctionTable;
    typedef std::map<uint, uint> DefaultTransitionTable;

public:
    explicit GenericFSM(T* ptr);

    void addTransition(uint fromState, uint toState, uint status);
    void addDefaultTransition(uint fromState, uint toState);

    void addState(uint stateId, void (T::*fun)());
    void addInitialState(uint stateId, void (T::*fun)());

    virtual void init() = 0;
    void start();
    void transit(uint status);


private:
    DefaultTransitionTable m_defTransitionTable;
    TransitionTable m_transitionTable;
    FunctionTable m_functionTable;
    T* m_selfPointer;

    uint m_currentState;
    uint m_initialState;
};

template <class T>
GenericFSM<T>::GenericFSM(T* ptr):
    m_selfPointer(ptr)
{
}

template <class T>
void GenericFSM<T>::addTransition(uint fromState, uint toState, uint status)
{
    m_transitionTable[std::make_pair(status, fromState)] = toState;
}

template <class T>
void GenericFSM<T>::addDefaultTransition(uint from, uint toState)
{
    m_defTransitionTable[from] = toState;
}

template <class T>
void GenericFSM<T>::addState(uint stateId, void (T::*fun)())
{
    m_functionTable[stateId] = fun;
}

template <class T>
void GenericFSM<T>::addInitialState(uint stateId, void (T::*fun)())
{
    addState(stateId, fun);

    m_initialState = stateId;
    m_currentState = stateId;
}

template <class T>
void GenericFSM<T>::start()
{
    auto it = m_functionTable.find(m_initialState);

    if(it != m_functionTable.end())
        (m_selfPointer->*it->second)();
    else
        std::cout << "Cannot start FSM!: Initial state does not exist!" << std::endl;
}

template <class T>
void GenericFSM<T>::transit(uint status)
{
    std::cout << "transit -> " << status << std::endl;

    auto transitionIt = m_transitionTable.find(std::make_pair(status, m_currentState));
    auto defaultTransitionIt = m_defTransitionTable.find(m_currentState);

    if(transitionIt != m_transitionTable.end())
    {
        m_currentState = transitionIt->second;
        (m_selfPointer->*m_functionTable[transitionIt->second])();
    }
    else if(defaultTransitionIt != m_defTransitionTable.end())
    {
        m_currentState = defaultTransitionIt->second;
        (m_selfPointer->*m_functionTable[defaultTransitionIt->second])();
    }
}


} // end of FSM namespace

#endif // GENERICFSM

