#include"header.h"
#include<iostream>
using namespace std;

adjacency_matrix::adjacency_matrix(int n) {
    this->n = n;
    edge_count = 0;
    degree.resize(n);
    matrix.resize(n);
    for(int i = 0; i < n; i++){
        degree[i] = 0;
        matrix[i].resize(n);
        for(int j = 0; j < n; j++)
            matrix[i][j] = -1;
    }
}

void adjacency_matrix::addEdge(int i, int j, double value){
    if(matrix[i][j] == -1) {
        edge_count += 1;
        degree[i]++;
        degree[j]++;
    }
    matrix[i][j] = value;
    matrix[j][i] = value;
}

void adjacency_matrix::deleteEdge(int i, int j) {
    if(matrix[i][j] == -1 || matrix[j][i] == -1) return;
    matrix[i][j] = -1;
    matrix[j][i] = -1;
    edge_count -= 1;
    degree[i]--;
    degree[j]--;
}

double adjacency_matrix::getEdge(int i, int j) {
    return matrix[i][j];
}

void adjacency_matrix::minimumEdge(int i, int &j, double &value) {
    j = -1;
    value = -1;
    for(int k = 0; k < n; k++) {
        if(matrix[i][k] == -1) continue;
        if((j != -1 && matrix[i][j] > matrix[i][k]) || j == -1) {
            j = k;
            value = matrix[i][k];
        }
    }
}

void adjacency_matrix::clear() {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            matrix[i][j] = -1;
    }
    edge_count = 0;
    for(int i = 0; i < n; i++)
        degree[i] = 0;
}

void adjacency_matrix::printMatrix() {
    cout << endl << "------------------" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
        
}

double MST::mst(int sn, adjacency_matrix *matrix) {
    edges.clear();
    setU.clear();
    setT.clear();
    startNode = sn;
    weight = 0;
    setU.push_back(sn);
    for(int i = 0; i < matrix->getRow(); i++) {
        if(i == sn) continue;
        setT.push_back(i);
    }
    int u, v;
    double w;
    vector<int>::iterator it;
    while(!setT.empty()) {
        u = -1;
        v = -1;
        w = -1;
        for(int i = 0; i < setU.size(); i++) {
            for(int j = 0; j < setT.size(); j++) {
                if(matrix->getEdge(setU[i], setT[j]) == -1) continue;
                else if(u == -1 || v == -1 || (w != -1 && w > matrix->getEdge(setU[i], setT[j]))) {
                    u = setU[i];
                    v = setT[j];
                    it = setT.begin() + j;
                    w = matrix->getEdge(setU[i], setT[j]);
                }
            }
        }
        if(u == -1 || v == -1)
            throw illegal_exception("not connected");
        else {
            edges.emplace_back(edge(u, v, w));
            setU.push_back(v);
            setT.erase(it);
            weight += w;
            //cout << u << " " << v << " " << w << " " << setT.size() << endl;
        }
    }
    return weight;
}

void MST::printEdge() {
    cout << endl << "-------------------" << endl;
    for(int i = 0; i < edges.size(); i++)
        cout << edges[i].u << " " << edges[i].v << " " << edges[i].w << endl;
}
