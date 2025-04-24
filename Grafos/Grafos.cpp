#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;

int main() {
	Graph<std::string> firstGraph;
	std::string a, b;
	int input;
	vector<std::string> distance;

	// Adding some initial nodes and edges
	firstGraph.addNode("Estadio1");
	firstGraph.addNode("Estadio2");
	firstGraph.addNode("Estadio3");
	firstGraph.addNode("Estadio4");
	// estadio1 -> estadio2 -> estadio3
	// add vertices
	firstGraph.addUnEdge("Estadio1", "Estadio2");
	firstGraph.addUnEdge("Estadio2", "Estadio3");
	firstGraph.addUnEdge("Estadio3", "Estadio1");
	firstGraph.addUnEdge("Estadio3", "Estadio4");

	do {
		std::cout << "Ingrese el número para realizar las siguientes operaciones:\n";
		std::cout << "1. Agregar un estadio al grafo.\n";
		std::cout << "2. Agregar un vertice no dirigido.\n";
		std::cout << "3. Verificar si el estadio existe.\n";
		std::cout << "4. Verificar si el vertice existe.\n";
		std::cout << "5. Eliminar estadio.\n";
		std::cout << "6. Eliminar vertice no dirigido.\n";
		std::cout << "7. Imprimir la lista de estadios.\n";
		std::cout << "8. Imprimir la lista de vertices.\n";
		std::cout << "9. Encontrar amigos y amigos de amigos de un estadio (BFS).\n";
		std::cout << "10. Mostrar los vértices adyacentes a un estadio.\n";
		std::cout << "11. Verificar si un vertice existe (detallado).\n";
		std::cout << "12. Verificar la distancia entre dos estadios.\n";
		std::cout << "0. Salir.\n>> ";

		std::cin >> input;

		switch (input) {
		case 1:
			std::cout << "Ingrese el estadio que desea agregar: ";
			std::cin >> a;
			firstGraph.addNode(a);
			break;
		case 2:
			std::cout << "Ingrese los estados que desea conectar (como amigos): ";
			std::cin >> a >> b;
			firstGraph.addUnEdge(a, b);
			break;
		case 3:
			std::cout << "Ingrese el nodo a verificar: ";
			std::cin >> a;
			if (firstGraph.checkNode(a))
				std::cout << "El nodo " << a << " existe.\n";
			else
				std::cout << "El nodo no existe.\n";
			break;
		case 4:
			std::cout << "Ingrese los nodos para verificar el borde: ";
			std::cin >> a >> b;
			if (firstGraph.checkEdge(a, b))
				std::cout << "El borde (" << a << "," << b << ") existe.\n";
			else
				std::cout << "El borde no existe.\n";
			break;
		case 5:
			std::cout << "Ingrese el nodo a eliminar: ";
			std::cin >> a;
			firstGraph.deleteNode(a);
			break;
		case 6:
			std::cout << "Ingrese los nodos del borde que desea eliminar: ";
			std::cin >> a >> b;
			firstGraph.deleteUnEdge(a, b);
			break;
		case 7:
			firstGraph.printNodeList();
			break;
		case 8:
			firstGraph.printEdgeList();
			break;
		case 9:
			std::cout << "Ingrese el nodo cuyos amigos desea encontrar: ";
			std::cin >> a;
			firstGraph.breadthfirstTraversal(a);
			break;
		case 10:
			std::cout << "Ingrese el nodo para mostrar los vértices adyacentes: ";
			std::cin >> a;
			firstGraph.printAdjacent(a);
			break;
		case 11:
			std::cout << "Ingrese los nodos para verificar el borde (detallado): ";
			std::cin >> a >> b;
			firstGraph.edgeExists(a, b);
			break;
		case 12:
			std::cout << "Ingrese los nodos para verificar la distancia: ";
			std::cin >> a >> b;
			distance = firstGraph.shortestPath(a, b);
			std::cout << "El borde entre " << a << " y " << b << " tiene una distancia de: " << distance.size() << std::endl;
			break;
		case 0:
			break;
		default:
			std::cout << "Por favor ingrese un número válido.\n";
		}
	} while (input != 0);


	return 0;
}
