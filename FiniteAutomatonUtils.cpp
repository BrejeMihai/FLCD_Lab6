#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "FiniteAutomaton.h"

#define USER_MENU "FiniteAutomaton program.\nWhat do you desire?\n1.Show initial state\n2.Show final states\n3.Show the alphabet\n4.Show transitions\n0.Exit\n>>>"

void readFiniteAutomatonFromFile(FiniteAutomaton& automaton, std::string path)
{
    std::ifstream inputFile(path);

    int initialState = 2;
    int numberOfFinalStates = 0;
    int numberOfTransitions = 0;
    int finalState = 0;
    int firstState = 0;
    int secondState = 0;
    char theEvent = 0;

    std::string line;

    if (!(inputFile >> initialState))
    {
        throw "Bad input file!";
    }
    automaton.addInitialState(initialState);

    if (inputFile >> numberOfFinalStates)
    {
        std::getline(inputFile, line);
        std::getline(inputFile, line);
        std::stringstream ss(line);
        while (numberOfFinalStates--)
        {
            try
            {
                ss >> finalState;
                automaton.addFinalState(finalState);
            }
            catch(...)
            {
                throw "Bad input file!";
            }
        }
    }
    else
    {
        throw "Bad input file!";
    }
    if (inputFile >> numberOfTransitions)
    {
        try 
        {
            while (inputFile >> firstState >> secondState >> theEvent)
            {
                automaton.addTransition(firstState, secondState, theEvent);
            }
        }
        catch (...)
        {
            throw "Bad input file!";
        }
    }
    inputFile.close();
}

void TalkToUser(std::string path)
{
    FiniteAutomaton automaton = FiniteAutomaton();
    readFiniteAutomatonFromFile(automaton, path);

    bool userWantsToTalk = true;
    int input = 0;

    while (userWantsToTalk)
    {
        fprintf_s(stdout, USER_MENU);
        std::cin >> input;
        switch (input)
        {
        case 0:
            userWantsToTalk = false;
            break;
        case 1:
            fprintf_s(stdout, "The initial state is: %d", automaton.getInitialState());
            break;
        case 2:
            fprintf_s(stdout, automaton.prettyPrintFinalStates().c_str());
            break;
        case 3:
            fprintf_s(stdout, automaton.prettyPrintAlphabet().c_str());
            break;
        case 4:
            fprintf_s(stdout, automaton.prettyPrintTransitions().c_str());
            break;
        default:
            fprintf_s(stdout, "Bad input. Try again!\n");
        }
        fprintf_s(stdout, "\n\n");
    }
}