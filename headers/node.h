#ifndef ___Node___
#define ___Node___

class Node 
{
private:

    int nodeValue;
    int minimalDistance;
    int nodePath;

public:

    Node();

    void set_nodeValue(int nodeValue);
    int get_nodeValue();

    void set_minimalDistance(int);
    int get_minimalDistance();

    void set_nodePath(int);
    int get_nodePath();

};

#endif