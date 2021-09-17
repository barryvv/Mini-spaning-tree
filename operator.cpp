#include<iostream>
#include<iomanip>
#include"header.h"

using namespace std;

Operator::Operator(){
    matrix = nullptr;
    mst = new MST();
    nodes = 0;
};
Operator::~Operator(){ 
    if(matrix) delete matrix;
    delete mst;
    matrix = nullptr;
    mst = nullptr;
};

bool Operator::comdN(int m){
    nodes = m;
    if(matrix) delete matrix;
    matrix = new adjacency_matrix(m);
    return true;
}

bool Operator::comdI(int u, int v, double w) {
    if(u == v || w <= 0 || u < 0 || v < 0 || u >= nodes || v >= nodes) 
        throw illegal_exception();
    matrix->addEdge(u, v, w);
    return true;
}

bool Operator::comdE(int u, int v) {
    if(u == v || u < 0 || v < 0 || u >= nodes || v >= nodes) 
        throw illegal_exception();
    double temp = matrix->getEdge(u, v);
    if(temp == -1) return false;
    matrix->deleteEdge(u, v);
    return true;
}

bool Operator::comdAdjacent(int u, int v, double w) {
    if(u == v || w <= 0 || u < 0 || v < 0 || u >= nodes || v >= nodes) 
        throw illegal_exception();
    double temp = matrix->getEdge(u, v);
    if(temp == w) return true;
    return false;
}

int Operator::comdDegree(int u) {
    if(u < 0 || u >= nodes) 
        throw illegal_exception();
    return matrix->getDegree(u);
}

int Operator::comdEdgeCount() {
    return matrix->getEdgeCount();
}

bool Operator::comdClear() {
    if(matrix) matrix->clear();
    return true;
}

double Operator::comdMst(int u) {
    return mst->mst(u, matrix);
    //mst->printEdge();
    //matrix->printMatrix();
}

void Operator::run() {
    string comd;
    int u, v, m;
    char semicolon;
    double w, temp;
    while(true) {
        cin >> comd;
        if(comd == "exit") break;
        if(comd == "n") {
            cin >> m;
            if(comdN(m)) cout << "success" << endl;
            else cout << "failure" << endl;
        }
        else if(comd == "i") {
            cin >> u >> semicolon >> v >> semicolon >> w;
            try {
                if(comdI(u, v, w)) cout << "success" << endl;
                else cout << "failure" << endl;
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }
        }
        else if(comd == "e") {
            cin >> u >> semicolon >> v;
            try {
                if(comdE(u, v)) cout << "success" << endl;
                else cout << "failure" << endl;
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }  
        }
        else if(comd == "adjacent") {
            cin >> u >> semicolon >> v >> semicolon >> w;
            try {
                if(comdAdjacent(u, v, w)) cout << "adjacent " << u << " " << v << " " << fixed << setprecision(2) << w << endl;
                else cout << "not adjacent " << u << " " << v << " " << fixed << setprecision(2) << w << endl;
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }
        }
        else if(comd == "degree") {
            cin >> u;
            try {
                cout << "degree of " << u << " is " << comdDegree(u) << endl;
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }  
        }
        else if(comd == "edge_count") {
            cout << "edge count is " << comdEdgeCount() << endl;
        }
        else if(comd == "clear") {
            if(comdClear()) cout << "success" << endl;
            else cout << "failure" << endl;
        }
        else if(comd == "mst") {
            cin >> u;
            try {
                double weight = comdMst(u);
                cout << "mst " << fixed << setprecision(2) << weight << endl;
            } catch(illegal_exception &e) {
                cout << e.what() << endl;
            }
        }
    }
}
