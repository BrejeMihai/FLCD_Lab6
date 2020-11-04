#pragma once
#include <string>
#include "FiniteAutomaton.h"

void TalkToUser(std::string path);
void readFiniteAutomatonFromFile(FiniteAutomaton& automaton, std::string path);