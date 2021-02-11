#include <iostream>
#include <list>
#include "headers/node.h"

using namespace std;

typedef list<Node> LISTNODE;

void array_debug(int **array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = 0; j < arraySize; j++)
        {
            std::cout << array[i][j] << " ";
        }
        std::cout << endl;
    }
    
}

int main(){

    list<LISTNODE*> listaDeAdjacencia;

    int numberOfNodes, numberOfEdges;
    std::cin >> numberOfNodes >> numberOfEdges;

    //Array that represents de graph's edges
    int **edgesArray = new int*[numberOfNodes]; 
    for (int i = 0; i < numberOfNodes; i++) //Dynamic alocation
    {
        edgesArray[i] = new int[numberOfNodes];
    }

    //Edge array construction
    for (int i = 0; i < numberOfEdges; i++)
    {
        int nodeOne, nodeTwo; //Edge e[nodeOne, nodeTwo]
        int edgeValue;

        cin >> nodeOne >> nodeTwo >> edgeValue;

        edgesArray[nodeOne][nodeTwo] = edgeValue;
        edgesArray[nodeTwo][nodeOne] = edgeValue; //Undirect graph || Simetric Array 
    }
     
}
