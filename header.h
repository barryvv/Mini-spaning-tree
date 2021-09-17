#ifndef HEADER__H__

#include<vector>
#include<list>
#include<string>

class adjacency_matrix {
private:
    int n; //row column
    int edge_count;
    std::vector<std::vector<double>> matrix;
    std::vector<int> degree;

public:
    adjacency_matrix(int n);
    void addEdge(int i, int j, double value);
    void deleteEdge(int i, int j);
    double getEdge(int i, int j);
    void minimumEdge(int i, int &j, double &value); //minimum edge connect with i;
    int getRow(){ return n; }
    int getColumn(){ return n; }
    int getEdgeCount() { return 2 * edge_count; }
    int getDegree(int i) { return degree[i]; }
    void clear();
    void printMatrix(); //debug function
};

class MST{
private:
    int startNode;
    double weight;
    struct edge{
        int u, v;
        double w;
        edge(int u, int v, double w) {
            this->u = u;
            this->v = v;
            this->w = w;
        }
    };
    std::vector<edge> edges;
    std::vector<int> setU;
    std::vector<int> setT;

public:
    MST(){};
    double mst(int sn, adjacency_matrix *matrix);
    void printEdge(); //debug function
    double getWeight() { return weight; }
};



class illegal_exception {
private:
    std::string message;
public:
    illegal_exception() { message = "illegal argument"; }
    illegal_exception(std::string &str){ message = str; }
    illegal_exception(const char *str){ message = str; }
    std::string what(){ return message; }
};

class Operator {
private:
    //std::string commands[9] = {"n", "i", "e", "adjacent", "degree", "edge_count", "clear", "mst", "exit"};
    adjacency_matrix *matrix;
    MST *mst;
    int nodes;
    
public:
    Operator();
    ~Operator();
    
    bool comdN(int m);
    bool comdI(int u, int v, double w);
    bool comdE(int u, int v);
    bool comdAdjacent(int u, int v, double w);
    int comdDegree(int u);
    int comdEdgeCount();
    bool comdClear();
    double comdMst(int u);
    void run();
};
#endif
