#include "node.h"

Node::Node()
{
    //Construtor padrão
    this->nodeValue = 0; 
}

void Node::set_nodeValue(int nodeValue)
{
    this->nodeValue = nodeValue;
}

int Node::get_nodeValue()
{
    return this->nodeValue;
}

void Node::set_minimalDistance(int minimalDistance)
{
    this->minimalDistance = minimalDistance;
}

int Node::get_minimalDistance()
{
    return this->minimalDistance;
}
