#pragma once
class Graph {
private:
	std::vector<int> nodeArray;
	std::vector<int> edge1Array;
	std::vector<int> edge2Array;
	void addEdge(int node1, int node2);
	void deleteEdge(int node1, int node2);
public:
	void addNode(int node);
	void addUnEdge(int node1, int node2);
	int checkNode(int node);
	int checkEdge(int node1, int node2);
	void deleteNode(int node);
	void deleteUnEdge(int node1, int node2);
	void printNodeList(void);
	void breadthfirstTraversal(int node);
	void printEdgeList();
};
