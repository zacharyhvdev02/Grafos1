#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Graph {
private:
    vector<T> nodeArray;
    vector<T> edge1Array;
    vector<T> edge2Array;

public:
    void addNode(T node) {
        if (!checkNode(node)) {
            nodeArray.push_back(node);
            cout << "Adding node: " << node << endl;
        }
        else {
            cout << "The node already exists.\n";
        }
    }

    void addEdge(T node1, T node2) {
        if (!checkEdge(node1, node2) && checkNode(node1) && checkNode(node2)) {
            edge1Array.push_back(node1);
            edge2Array.push_back(node2);
            cout << "Adding edge: (" << node1 << "," << node2 << ")\n";
        }
        else if (checkEdge(node1, node2)) {
            cout << "The edge already exists.\n";
        }
        else if (!checkNode(node1)) {
            cout << "The node " << node1 << " doesn't exist.\n";
        }
        else {
            cout << "The node " << node2 << " doesn't exist.\n";
        }
    }

    void addUnEdge(T node1, T node2) {
        addEdge(node1, node2);
        addEdge(node2, node1);
    }

    bool checkNode(T node) const {
        for (const auto& n : nodeArray) {
            if (n == node) return true;
        }
        return false;
    }

    bool checkEdge(T node1, T node2) const {
        for (size_t i = 0; i < edge1Array.size(); ++i) {
            if (edge1Array[i] == node1 && edge2Array[i] == node2) {
                cout << "The required edge (" << node1 << "," << node2 << ") exists." << endl;
                return true;
            }
        }
        return false;
    }

    void deleteNode(T node) {
        if (checkNode(node)) {
            for (size_t i = 0; i < nodeArray.size(); ++i) {
                if (nodeArray[i] == node) {
                    nodeArray.erase(nodeArray.begin() + i);
                    cout << "Node deleted successfully\n";
                    break;
                }
            }
            for (size_t i = 0; i < nodeArray.size(); ++i) {
                deleteUnEdge(node, nodeArray[i]);
            }
        }
        else {
            cout << "The required node doesn't exist.\n";
        }
    }

    void printNodeList() const {
        for (const auto& node : nodeArray) {
            cout << "Node :" << node << endl;
        }
    }

    void deleteEdge(T node1, T node2) {
        for (size_t i = 0; i < edge1Array.size(); ++i) {
            if (edge1Array[i] == node1 && edge2Array[i] == node2) {
                cout << "Edge (" << node1 << "," << node2 << ") deleted successfully.\n";
                edge1Array.erase(edge1Array.begin() + i);
                edge2Array.erase(edge2Array.begin() + i);
                break;
            }
        }
    }

    void deleteUnEdge(T node1, T node2) {
        deleteEdge(node1, node2);
        deleteEdge(node2, node1);
    }

    void printEdgeList() const {
        cout << "Edge List:\n";
        for (size_t i = 0; i < edge1Array.size(); ++i) {
            cout << "(" << edge1Array[i] << "," << edge2Array[i] << ")" << endl;
        }
    }

    void breadthfirstTraversal(T node) const {
        if (!checkNode(node)) return;
        vector<T> friends;
        cout << "Friends of " << node << ":" << endl;
        for (size_t i = 0; i < edge1Array.size(); ++i) {
            if (edge1Array[i] == node) {
                friends.push_back(edge2Array[i]);
                cout << edge2Array[i] << endl;
            }
        }

        cout << "Friends of friends of " << node << " are as follows." << endl;
        for (const auto& f : friends) {
            cout << "Friends of " << f << ":" << endl;
            for (size_t i = 0; i < edge1Array.size(); ++i) {
                if (edge1Array[i] == f && edge2Array[i] != node) {
                    cout << edge2Array[i] << endl;
                }
            }
        }
    }

    void printAdjacent(T node) const {
        bool found = false;
        cout << "Adjacent vertices to " << node << ": ";
        for (size_t i = 0; i < edge1Array.size(); ++i) {
            if (edge1Array[i] == node) {
                cout << edge2Array[i] << " ";
                found = true;
            }
        }
        if (!found) cout << "None";
        cout << endl;
    }

    void edgeExists(T node1, T node2) const {
        if (checkEdge(node1, node2)) {
            cout << "Edge exists between " << node1 << " and " << node2 << ".\n";
        }
        else {
            cout << "No edge exists between " << node1 << " and " << node2 << ".\n";
        }
    }
};

// define the template for strings
template class Graph<std::string>;