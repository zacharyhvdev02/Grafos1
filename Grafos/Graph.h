#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

template <typename T>
class Graph {
private:
	std::vector<T> nodeArray;
	std::vector<T> edge1Array;
	std::vector<T> edge2Array;

public:
	void addNode(T node) {
		int out = checkNode(node);
		if (out != 1) {
			nodeArray.push_back(node);
			std::cout << "Adding node: " << node << std::endl;
		}
		else {
			std::cout << "The node already exists.\n";
		}
	}

	void addEdge(T node1, T node2) {
		int a = checkEdge(node1, node2);
		int check1 = checkNode(node1);
		int check2 = checkNode(node2);
		if (a != 1 && check1 == 1 && check2 == 1) {
			edge1Array.push_back(node1);
			edge2Array.push_back(node2);
			std::cout << "Adding edge: (" << node1 << "," << node2 << ")\n";
		}
		else if (a == 1) {
			std::cout << "The edge already exists.\n";
		}
		else if (check1 != 1) {
			std::cout << "The node " << node1 << " doesn't exist.\n";
		}
		else {
			std::cout << "The node " << node2 << " doesn't exist.\n";
		}
	}

	void addUnEdge(T node1, T node2) {
		addEdge(node1, node2);
		addEdge(node2, node1);
	}

	int checkNode(T node) {
		for (int i = 0; i < nodeArray.size(); i++) {
			if (nodeArray[i] == node) {
				return 1;
			}
		}
		return 0;
	}

	int checkEdge(T node1, T node2) {
		for (int i = 0; i < edge1Array.size(); i++) {
			if (edge1Array[i] == node1 && edge2Array[i] == node2) {
				std::cout << "The required edge (" << node1 << "," << node2 << ") exists." << std::endl;
				return 1;
			}
		}
		return 0;
	}

	void deleteNode(T node) {
		int out = checkNode(node);
		if (out == 1) {
			int count = 0;
			for (auto i = nodeArray.begin(); i < nodeArray.end(); i++) {
				if (*i == node) {
					nodeArray.erase(nodeArray.begin() + count);
					std::cout << "Node deleted successfully\n";
				}
				deleteUnEdge(node, *(nodeArray.begin() + count));
				if (count < nodeArray.size() - 1) {
					count++;
				}
			}
		}
		else {
			std::cout << "The required node doesn't exist.\n";
		}
	}

	void deleteEdge(T node1, T node2) {
		int a = checkEdge(node1, node2);
		if (a == 1) {
			int count = 0;
			for (auto i = edge1Array.begin(); i < edge1Array.end(); i++) {
				if (*(edge1Array.begin() + count) == node1 && *(edge2Array.begin() + count) == node2) {
					std::cout << "Edge (" << *(edge1Array.begin() + count) << "," << *(edge2Array.begin() + count) << ") deleted successfully.\n";
					edge1Array.erase(edge1Array.begin() + count);
					edge2Array.erase(edge2Array.begin() + count);
				}
				if (count < edge1Array.size() - 1) {
					count++;
				}
			}
		}
	}

	void deleteUnEdge(T node1, T node2) {
		deleteEdge(node1, node2);
		deleteEdge(node2, node1);
	}

	void printNodeList() {
		for (auto i = nodeArray.begin(); i < nodeArray.end(); i++) {
			std::cout << "Node: " << *i << std::endl;
		}
	}

	void printEdgeList() {
		std::cout << "Edge List:\n";
		for (int i = 0; i < edge1Array.size(); i++) {
			std::cout << "(" << edge1Array[i] << "," << edge2Array[i] << ")" << std::endl;
		}
	}

	void breadthfirstTraversal(T node) {
		int x = checkNode(node);
		std::vector<T> friendArray;
		if (x == 1) {
			int count = 0;
			std::cout << "Friends of " << node << ":\n";
			for (auto i = edge1Array.begin(); i < edge1Array.end(); i++) {
				if (*(edge1Array.begin() + count) == node) {
					friendArray.push_back(*(edge2Array.begin() + count));
					std::cout << *(edge2Array.begin() + count) << std::endl;
				}
				count++;
			}
			int count1 = 0;
			std::cout << "Friends of friends of " << node << " are as follows:\n";
			for (auto i = friendArray.begin(); i < friendArray.end(); i++) {
				int count2 = 0;
				std::cout << "Friends of " << *(friendArray.begin() + count1) << ":\n";
				for (auto itr = edge1Array.begin(); itr < edge1Array.end(); itr++) {
					if (*(edge1Array.begin() + count2) == *(friendArray.begin() + count1) && *(edge2Array.begin() + count2) != node) {
						std::cout << *(edge2Array.begin() + count2) << std::endl;
					}
					count2++;
				}
				count1++;
			}
		}
	}

	void printAdjacent(T node) {
		bool found = false;
		std::cout << "Adjacent vertices to " << node << ": ";
		for (int i = 0; i < edge1Array.size(); i++) {
			if (edge1Array[i] == node) {
				std::cout << edge2Array[i] << " ";
				found = true;
			}
		}
		if (!found) {
			std::cout << "None";
		}
		std::cout << std::endl;
	}

	void edgeExists(T node1, T node2) {
		if (checkEdge(node1, node2) == 1) {
			std::cout << "Edge exists between " << node1 << " and " << node2 << ".\n";
		}
		else {
			std::cout << "No edge exists between " << node1 << " and " << node2 << ".\n";
		}
	}
};

#endif
