

#include "AlgorithmRegistration.h"
#include "AbstractPlayer.h"

// in Registration.cpp
map<string, std::function<AbstractPlayer*(void)>> Registration::algoFactory;

