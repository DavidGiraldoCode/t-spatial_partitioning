#include "Messenger.hpp"

Messenger::Messenger()
{
    printAMessage("My first class in a OpenFamesworks app");
}

Messenger::~Messenger()
{
    printAMessage("Bye bye messenger");
}

void Messenger::printAMessage(std::string message)
{
    std::cout << message << '\n';
}
