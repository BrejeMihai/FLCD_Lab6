#include "FiniteAutomaton.h"

FiniteAutomaton::FiniteAutomaton()
{
    this->initialState = NULL;
}

FiniteAutomaton::~FiniteAutomaton()
{
}

FiniteAutomaton::FiniteAutomaton(int initialState)
{
    this->initialState = initialState;
}

void FiniteAutomaton::addTransition(int firstState, int secondState, char theEvent)
{
    this->transitions.emplace(std::pair<std::pair<int,char>, int>(std::pair<int, char>(firstState, theEvent), secondState));
    this->alphabet.insert(theEvent);
}

void FiniteAutomaton::addInitialState(int initialState)
{
    this->initialState = initialState;
}

void FiniteAutomaton::addFinalState(int finalState)
{
    this->finalStates.push_back(finalState);
}

std::set<char> FiniteAutomaton::getAlphabet()
{
    return this->alphabet;
}

std::map<std::pair<int, char>, int> FiniteAutomaton::getTransitions()
{
    return this->transitions;
}

int FiniteAutomaton::getInitialState()
{
    return this->initialState;
}

std::vector<int> FiniteAutomaton::getFinalStates()
{
    return this->finalStates;
}

std::string FiniteAutomaton::prettyPrintTransitions()
{
    std::string initial;
    for (const auto& c : this->transitions)
    {
        initial += "From state " + std::to_string(c.first.first) + " to " + std::to_string(c.second) + " via " + c.first.second + "\n";
    }
    return initial;
}

std::string FiniteAutomaton::prettyPrintFinalStates()
{
    std::string initial = "Final states are: \n";
    for (auto c : this->finalStates)
    {
        initial += std::to_string(c) + " ";
    }
    return initial;
}

std::string FiniteAutomaton::prettyPrintAlphabet()
{
    std::string initial = "The alphabet consists of: \n";
    for (auto c : this->alphabet)
    {
        initial += std::string(1,c) + " ";
    }
    return initial;
}
