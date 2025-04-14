#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;
int main() {

	Graph firstGraph;
	int a, b, input;

	do
	{
		std::cout << "Enter the number to peform the following operations:" << std::endl;
		std::cout << "1.Add node to the graph.\n2.Add undirected edge\n3.Check if node exists.\n4.Check if edge exists.\n5.Delete node\n6.Delete undirected edge\n7.Print the node list.\n8.Print the edge list.\n9.Find the friends and friends of friends of a node. (Breadth First Search)\n"
			"Press 0 to exit\n" << std::flush;
		std::cin >> input;
		switch (input)
		{
		case 1:
		{

			std::cout << "Enter the node you want to add" << std::endl;
			std::cin >> a;
			firstGraph.addNode(a);
			break;
		}
		case 2:
		{
			std::cout << "Enter the nodes which you want to connect( as friends)" << std::endl;
			std::cin >> a;
			std::cin >> b;
			firstGraph.addUnEdge(a, b);
			break;
		}
		case 3:
		{
			std::cout << "Enter the node to check" << std::endl;
			std::cin >> a;
			if (firstGraph.checkNode(a))
			{
				std::cout << "The node " << a << "exists" << std::endl;
			}
			else
			{
				std::cout << "The node doesnot exist" << std::endl;
			}
			break;

		}
		case 4:
		{
			std::cout << "Enter the nodes to check edge" << std::endl;
			std::cin >> a >> b;
			if (firstGraph.checkEdge(a, b))
			{
				std::cout << "The edge (" << a << "," << b << ") exists" << std::endl;
			}
			else
				std::cout << "The edge doesnot exist" << std::endl;
			break;
		}
		case 5:
		{
			std::cout << "Enter the node to delete" << std::endl;
			std::cin >> a;
			firstGraph.deleteNode(a);
			break;
		}
		case 6:
		{
			std::cout << "Enter the nodes of edge you want to remove" << std::endl;
			std::cin >> a >> b;
			firstGraph.deleteUnEdge(a, b);
			break;
		}
		case 7:
		{
			firstGraph.printNodeList();
			break;

		}
		case 8:
		{
			firstGraph.printEdgeList();
			break;

		}
		case 9:
		{
			std::cout << "Enter the node whose friends you want to find" << std::endl;
			std::cin >> a;
			firstGraph.breadthfirstTraversal(a);
			break;
		}

		case 0:
			break;
		default:
			std::cout << "Please enter the valid number" << std::endl;
		}
	} while (input != 0);
	return 0;
}
