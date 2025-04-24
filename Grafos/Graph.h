#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <algorithm>

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
			std::cout << "Añadiendo vertice: (" << node1 << "," << node2 << ")\n";
		}
		else if (a == 1) {
			std::cout << "El vertice ya existe.\n";
		}
		else if (check1 != 1) {
			std::cout << "El nodo " << node1 << " no existe.\n";
		}
		else {
			std::cout << "El nodo " << node2 << " no existe.\n";
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
				std::cout << "El vertice requerido (" << node1 << "," << node2 << ") existe." << std::endl;
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
					std::cout << "Nodo eliminado exitosamente\n";
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
					std::cout << "Vertice (" << *(edge1Array.begin() + count) << "," << *(edge2Array.begin() + count) << ") eliminado exitosamente.\n";
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
			std::cout << "Nodo: " << *i << std::endl;
		}
	}

	void printEdgeList() {
		std::cout << "Lista de vertices:\n";
		for (int i = 0; i < edge1Array.size(); i++) {
			std::cout << "(" << edge1Array[i] << "," << edge2Array[i] << ")" << std::endl;
		}
	}

	void breadthfirstTraversal(T node) {
		int x = checkNode(node);
		std::vector<T> friendArray;
		if (x == 1) {
			int count = 0;
			std::cout << "Amigos de " << node << ":\n";
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
		std::cout << "Vertices adjacentes de " << node << ": ";
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

	// I'm going to try to create a function that checks how far apart 2 nodes are. It should return a number.
	int checkDistance(T node1, T node2) {
		int count = 0;
		for (int i = 0; i < edge1Array.size(); i++) {
			if (edge1Array[i] == node1 && edge2Array[i] == node2) {
				count++;
			}
		}
		return count;
	}

	std::vector<T> shortestPath(const T& src, const T& dst) {
		// build index map and adj-list
		std::unordered_map<T, int> idx;
		for (int i = 0; i < nodeArray.size(); ++i) { idx[nodeArray[i]] = i; }
		int N = nodeArray.size();

		// creamos la lista de adjacencia. En este caso, hacemos una lista de listas, que captura que nodo tiene acceso a cual nodo. Muy versatil.
		std::vector<std::vector<int>> adj(N);
		for (int i = 0; i < edge1Array.size(); ++i) {
			adj[idx[edge1Array[i]]].push_back(idx[edge2Array[i]]);
		}

		// este vector servirá tanto para ir por todo los nodos como para ir monitoreando el paso hacia el nodo objetivo.
		std::vector<int> parent(N, -1);
		std::queue<int> q;
		int s = idx[src], t = idx[dst];
		q.push(s);

		while (!q.empty()) {
			int u = q.front(); q.pop();
			if (u == t) break;
			for (int v : adj[u]) {
				if (parent[v] == -1 && v != s) {
					parent[v] = u;
					q.push(v);
				}
			}
		}

		// reconstruct
		std::vector<T> path;
		if (parent[t] == -1 && s != t) return path; // no path
		// nota: el foor loop ejecuta la cadena de código DESPUES de la primera iteración. Esto puede ser confuso la primera vez.
		for (int cur = t; cur != -1; cur = parent[cur]) // muy inteligente. Vamos por cada nodo desde el punto final y vamos averiguando el camino.
			path.push_back(nodeArray[cur]);
		std::reverse(path.begin(), path.end());
		return path;
	}

	void edgeExists(T node1, T node2) {
		if (checkEdge(node1, node2) == 1) {
			std::cout << "El vertice existen entre " << node1 << " y " << node2 << ".\n";
		}
		else {
			std::cout << "No existe vertice entre " << node1 << " y " << node2 << ".\n";
		}
	}
};

#endif
