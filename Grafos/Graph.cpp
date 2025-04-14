#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;
void Graph::addNode(int node) {
	int out;
	out = checkNode(node);
	if (out != 1) {							//adds new node if it doesn't exist.
		nodeArray.push_back(node);
		cout << "Adding node: " << node << endl;
	}
	else {
		cout << "The node already exists.\n";
	}
}

void Graph::addEdge(int node1, int node2) {
	int a, check1, check2;
	a = checkEdge(node1, node2);
	check1 = checkNode(node1);
	check2 = checkNode(node2);
	if (a != 1 && check1 == 1 && check2 == 1) { //adds edge if the nodes to be connected exist and edge doesn't already exist.
		edge1Array.push_back(node1);
		edge2Array.push_back(node2);
		cout << "Adding edge: (" << node1 << "," << node2 << ")\n";
	}
	else if (a == 1) {
		cout << "The edge already exists.\n";
	}
	else if (check1 != 1) {
		cout << "The node " << node1 << " doesn't exist.\n";
	}
	else {
		cout << "The node " << node2 << " doesn't exist.\n";
	}

}
void Graph::addUnEdge(int node1, int node2) {			//adds undirected edges between two nodes.
	addEdge(node1, node2);
	addEdge(node2, node1);
}

int Graph::checkNode(int node) {					//checks if node exists.

	for (int i = 0; i < nodeArray.size(); i++) {
		if (nodeArray[i] == node) {
			// cout << "The node "<<node<<" exists.\n";
			return 1;
		}
	}
	return 0;
}
int Graph::checkEdge(int node1, int node2) {				//checks if edge exists.
	for (int i = 0; i < edge1Array.size(); i++) {
		if (edge1Array[i] == node1 && edge2Array[i] == node2) {
			cout << "The required edge (" << node1 << "," << node2 << ") exists." << endl;
			return 1;
		}
	}
	return 0;
}

void Graph::deleteNode(int node) {					//deletes node if it exists.
	int out;
	out = checkNode(node);
	if (out == 1) {
		int count = 0;
		for (vector<int>::const_iterator i = nodeArray.begin(); i < (nodeArray.end()); i++) {	//deletes node from vector

			if (*i == node) {
				nodeArray.erase(nodeArray.begin() + count);
				cout << "Node deleted successfully\n";
			}
			deleteUnEdge(node, *(nodeArray.begin() + count)); //deletes the edges with this node
			if (count < nodeArray.size() - 1) {				//to delete last node of the array.
				count++;
			}
		}
	}
	else {
		cout << "The required node doesn't exist.\n";
	}
}
void Graph::printNodeList(void) {			//prints the nodes.
	for (vector<int>::const_iterator i = nodeArray.begin(); i < (nodeArray.end()); i++) {
		cout << "Node :" << (*i) << endl;
	}
}
void Graph::deleteEdge(int node1, int node2) {				//delete the edge if it exists.
	int a;
	a = checkEdge(node1, node2);
	if (a == 1) {
		int count = 0;
		for (vector<int>::const_iterator i = edge1Array.begin(); i < (edge1Array.end()); i++) {
			if (*(edge1Array.begin() + count) == node1 && *(edge2Array.begin() + count) == node2) {
				cout << "Edge (" << *(edge1Array.begin() + count) << "," << *(edge2Array.begin() + count) << ") deleted successfully.\n";
				edge1Array.erase(edge1Array.begin() + count);
				edge2Array.erase(edge2Array.begin() + count);
			}
			if (count < edge1Array.size() - 1) {			// to delete the last edge of the array.
				count++;
			}
		}
	}
}
void Graph::deleteUnEdge(int node1, int node2) {			// delete undirected edges.
	deleteEdge(node1, node2);
	deleteEdge(node2, node1);
}
void Graph::printEdgeList() {
	cout << "Edge List:\n";
	for (int i = 0; i < edge1Array.size(); i++) {
		cout << "(" << edge1Array[i] << "," << edge2Array[i] << ")" << endl;
	}
}

void Graph::breadthfirstTraversal(int node) {			//bfs to find friends of friends of a node.
	int x;
	x = checkNode(node);
	vector<int> friendArray;						// to store the friends of a node.
	if (x == 1) {
		int count = 0;
		cout << "Friends of " << node << ":" << endl;
		for (vector<int>::const_iterator i = edge1Array.begin(); i < (edge1Array.end()); i++) {		//finding friends
			if (*((edge1Array.begin() + count)) == node) {
				friendArray.push_back(*(edge2Array.begin() + count));
				cout << *(edge2Array.begin() + count) << endl;
			}
			count++;
		}
		int count1 = 0;
		cout << "Friends of friends of " << node << " are as follows." << endl;
		for (vector<int>::const_iterator i = friendArray.begin(); i < (friendArray.end()); i++) {		//finding friends of friends
			int count2 = 0;
			cout << "Friends of " << *(friendArray.begin() + count1) << ":" << endl;
			for (vector<int>::const_iterator itr = edge1Array.begin(); itr < (edge1Array.end()); itr++) {
				if (*((edge1Array.begin() + count2)) == *(friendArray.begin() + count1) && *(edge2Array.begin() + count2) != node) {
					cout << *(edge2Array.begin() + count2) << endl;
				}
				count2++;
			}
			count1++;
		}
	}

}
