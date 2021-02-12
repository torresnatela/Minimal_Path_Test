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

//retorna o Node com a distancia minima
int extract_min()
{
    return 1;
}

//Atualiza as distancias mínimas dos vertices do grafico.
void update_minimal_distances(LISTNODE *priorityQueue, LISTNODE *exploredNodes, int **edgesArray)
{       
        LISTNODE::iterator listIterator;

        listIterator = exploredNodes->end();
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
     
    //Priority Queue construction
    for (int i = 0; i < numberOfNodes; i++)
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

        /* --- Second Step || Build the Priority List */
    }
    
}
