#pragma once
#include <map>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <algorithm>

class FiniteAutomaton
{
private:
    int initialState;
    std::multimap<std::pair<int, char>, int> transitions;
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
    std::multimap<std::pair<int, char>, int> getTransitions();
    int getInitialState();
    std::vector<int> getFinalStates();

    std::string prettyPrintTransitions();
    std::string prettyPrintFinalStates();
    std::string prettyPrintAlphabet();
    std::string prettyPrintVerifySequence(std::string path);

    bool IsNonDeterministicSingle(int firstState, std::string::iterator pathIterator);
    bool verifyIfSequenceAccepted(std::string pathToSequence);
    
};