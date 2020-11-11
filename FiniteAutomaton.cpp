#include "FiniteAutomaton.h"

typedef std::multimap<std::pair<int,char>, int>::iterator MMAPIterator;

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
    /*this->transitions.emplace(std::pair<std::pair<int,char>, int>(std::pair<int, char>(firstState, theEvent), secondState));*/

    this->transitions.emplace(std::pair<std::pair<int, char>, int>(std::pair<int, char>(firstState, theEvent), secondState));
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

std::multimap<std::pair<int, char>, int> FiniteAutomaton::getTransitions()
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

std::string FiniteAutomaton::prettyPrintVerifySequence(std::string path)
{
    if (this->verifyIfSequenceAccepted(path) == true)
    {
        return std::string("Sequence accepted");
    }
    return std::string("Sequence not accepted");
}


bool FiniteAutomaton::IsNonDeterministicSingle(int firstState, std::string::iterator pathIterator)
{
    std::pair<MMAPIterator, MMAPIterator> result = this->transitions.equal_range(std::pair<int,char>(firstState,*pathIterator));

    /*if (1 != std::distance(result.first, result.second))
    {
        return true;
    }*/
    int isGood = 0;
    for (auto itr = result.first; itr != result.second; ++itr)
    {
        if (itr->first.first == firstState && itr->first.second == *pathIterator)
        {
            isGood++;
        }
    }

    if (1 != isGood)
    {
        return true;
    }
    return false;

}

bool FiniteAutomaton::verifyIfSequenceAccepted(std::string pathToSequence)
{
    std::string sequence;
    std::ifstream sequenceFile(pathToSequence);

    if (!(sequenceFile >> sequence))
    {
        return false;
    }

    int initialState = this->initialState;

    int currentState = initialState;

    for (std::string::iterator it = sequence.begin(); it != sequence.end(); ++it)
    {
        if (true == IsNonDeterministicSingle(currentState, it))
        {
            return false;
        }
        auto itr = this->transitions.find(std::pair<int, char>(currentState, *it));
        if (this->transitions.end() == itr)
        {
            return false;
        }

        currentState = itr->second;
    }

    if (this->finalStates.end() != std::find(this->finalStates.begin(), this->finalStates.end(), currentState))
    {
        return true;
    }
    return false;

}
