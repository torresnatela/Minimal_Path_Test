#include "node.h"

Node::Node()
{
    //Construtor padrão
    this->nodeValue = 0; 
    this->nodePath = -1;
    this->minimalDistance = -1;
}

//Getters anda Setters
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
void Node::set_nodePath(int node)
{
    this->nodePath = node;
}
int Node::get_nodePath()
{
    return this->nodePath;
}