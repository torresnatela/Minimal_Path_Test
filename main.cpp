#include <iostream>
#include <list>
#include "headers/node.h"

using namespace std;

typedef list<Node> LISTNODE;

//Debugers
void debug_array(int **array, int arraySize)
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
void debug_list(LISTNODE *listNode)
{
    LISTNODE::iterator i; //Node iterator

    for (i = listNode->begin(); i != listNode->end(); i++)
    {
        std::cout << i->get_nodeValue() << " " << i->get_nodePath() << " "
        << i->get_minimalDistance() << endl;
    } 
}
void debug_all(LISTNODE exploredList, LISTNODE priorityList)
{   
    cout << "Lista de prioridade" << endl;
    debug_list(&priorityList);
    cout << "Lista de descoberta" << endl;
    debug_list(&exploredList);
}

void splice_list(LISTNODE *exploredList, LISTNODE *priorityList, int nodeValue)
{
    LISTNODE::iterator iterator;


    //Search nodeValue in priorityList
    for  (iterator = priorityList->begin(); iterator != priorityList->end(); iterator++)
    {
        if(iterator->get_nodeValue() == nodeValue)
        {
            exploredList->splice(exploredList->begin(), *priorityList, iterator);
            return;
        }
    }
    
}

//retorna o Node com a distancia minima e que possui uma aresta com um node na Explored List
int extract_min(LISTNODE *priorityList)
{
    LISTNODE::iterator nodeIterator, nodeIteratorReturn;

    nodeIterator = priorityList->begin(); nodeIteratorReturn = priorityList->begin();
    nodeIterator++;

    int nodeValue = nodeIteratorReturn->get_nodeValue();

    int minimalDistance2 = nodeIteratorReturn->get_minimalDistance();

    for (long unsigned int i = 1; i < priorityList->size(); i++)
    {
        int minimalDistance1 = nodeIterator->get_minimalDistance();

        if (minimalDistance1 < minimalDistance2 && minimalDistance1 != -1)
        {
            nodeValue = nodeIterator->get_nodeValue();
            minimalDistance2 = minimalDistance1;
        }
        nodeIterator++;
    }
    return nodeValue;
    
}

//Atualiza as distancias mínimas dos vertices do grafico.
void update_minimal_distances(LISTNODE *priorityQueue, LISTNODE *exploredNodes, int **edgesArray)
{       
        LISTNODE::iterator listIterator;

        listIterator = exploredNodes->begin();
        int nodeValueAux = listIterator->get_nodeValue();
        int DistanceSearchNode = listIterator->get_minimalDistance();

        listIterator = priorityQueue->begin();

        //Updating minimalDistance of the Nodes using EdgeArray.
        for (long unsigned int i = 0; i < priorityQueue->size(); i++)
        {
            int DistanceNodeAux = listIterator->get_minimalDistance(); 
            int EdgeValueAux = edgesArray[nodeValueAux][listIterator->get_nodeValue()];

            //If Node with the nodeValueAux has an edge with node i
            if(EdgeValueAux != 0)
            {   
                //d'(v) min function
                if(DistanceSearchNode + EdgeValueAux < DistanceNodeAux || 
                DistanceNodeAux == -1)
                {
                    listIterator->set_minimalDistance(DistanceSearchNode + EdgeValueAux);
                    listIterator->set_nodePath(nodeValueAux);
                }
            }
            listIterator++;
        }
}

int main(){

    LISTNODE priorityQueue;
    LISTNODE exploredNodes;

    long unsigned int numberOfNodes, numberOfEdges;
    std::cin >> numberOfNodes >> numberOfEdges;

    //Array that represents de graph's edges
    int **edgesArray = new int*[numberOfNodes]; 
    for (long unsigned int i = 0; i < numberOfNodes; i++) //Dynamic alocation
    {
        edgesArray[i] = new int[numberOfNodes];
    }

    //Edge array construction
    for (long unsigned int i = 0; i < numberOfEdges; i++)
    {
        int nodeOne, nodeTwo; //Edge e[nodeOne, nodeTwo]
        int edgeValue;

        cin >> nodeOne >> nodeTwo >> edgeValue;

        edgesArray[nodeOne][nodeTwo] = edgeValue;
        edgesArray[nodeTwo][nodeOne] = edgeValue; //Undirect graph || Simetric Array 
    }
     
    //Priority Queue construction
    for (long unsigned int i = 0; i < numberOfNodes; i++)
    {   
        Node *auxNode = new Node();
        auxNode->set_nodeValue(i);

        priorityQueue.insert(priorityQueue.end(), *auxNode);

        delete auxNode;
    }
    

    /* ---------------- Algorimo Minimal Path ----------------- */
    int startNode, endNode;

    cout << "Digite os valores do Node de inicio e de destino" << endl;
    cin >> startNode >> endNode;

    LISTNODE::iterator listIterator = priorityQueue.begin();

    //Put startNode on exploredNodes list
    for (int i = 0; i < startNode; i++)
    {
        listIterator++;
    }

    listIterator->set_minimalDistance(0); //set  the first d(s) = 0

    //Transfer the first node to exploredNodes list;
    exploredNodes.splice(exploredNodes.begin(), priorityQueue, listIterator);
    
    while (exploredNodes.size() != numberOfNodes)
    {   
        
        /*--- First Step || Update the minimalDistance ---*/
        update_minimal_distances(&priorityQueue, &exploredNodes, edgesArray);

        /*--- Second Step || Build the Priority List ---*/
        int minimalNodeValue = extract_min(&priorityQueue);

        /*--- Third Step || Send node to Explored List ---*/
        splice_list(&exploredNodes, &priorityQueue, minimalNodeValue);
    }
    debug_all(exploredNodes, priorityQueue);
}
