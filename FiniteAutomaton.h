#pragma once
#include <map>
#include <vector>
#include <string>
#include <set>

class FiniteAutomaton
{
private:
    int initialState;
    std::map<std::pair<int, char>, int> transitions;
    std::vector<int> finalStates;
    std::set<char> alphabet;
public:
    FiniteAutomaton();
    ~FiniteAutomaton();
    FiniteAutomaton(int initialState);
    void addTransition(int firstState, int secondState, char theEvent);
    void addInitialState(int initialState);
    void addFinalState(int finalState);

    std::set<char> getAlphabet();
    std::map<std::pair<int, char>, int> getTransitions();
    int getInitialState();
    std::vector<int> getFinalStates();

    std::string prettyPrintTransitions();
    std::string prettyPrintFinalStates();
    std::string prettyPrintAlphabet();
};