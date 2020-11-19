// NMSIAdrianFirstAppGrafA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct node {
    int number;
    double x;
    double y;
    double distance;

    public:
    void setDistanceFromDestinationNode(node& destinationNode) {
        
    }
};


void fillTheMap(string content, map<int, node>& nodes)
{
    cout << "Source content for Nodes Map: " << content << "\n" << "\n";

    string delimiter = "(", delimiter2 = ",";

    size_t pos = 0, pos2 = 0;
    string token, token2;
    int counter = 1;

    while ((pos = content.find(delimiter)) != std::string::npos) {
        node* newNode = new node();
        token = content.substr(0, pos);
        if (!token.empty()) 
        { 
            token = token.substr(0, token.length() - 2);
        }
        //cout << token << std::endl;

        while ((pos2 = token.find(delimiter2)) != std::string::npos && !token.empty()) {
        token2 = token.substr(0, pos2);
        newNode->number = counter;
        newNode->x = atof(token2.c_str());
        token.erase(0, pos2 + delimiter2.length()+1);
        newNode->y = atof(token.c_str());
        nodes[newNode->number] = *newNode;
        counter++;
        }

        content.erase(0, pos + delimiter.length());
        
    }

    for (int i = 1; i < 9; i++)
    {
        cout << "Node [" << nodes[i].number << "] x:" << nodes[i].x << " y:" << nodes[i].y << " \n";
    }
}

void setStartingAndDestinationNodes(string content, int& start, int& destination) {
    cout << "\nStarting and Destination Nodes setup: " << content << "\n" << "\n";

    string delimiter = " ";

    start = 0; 
    destination = 0;

    size_t pos = 0;
    string token;
    int counter = 1;

    while (((pos = content.find(delimiter)) != std::string::npos || !content.empty()) && destination == 0) {
        token = content.substr(0, pos); 
        if (!token.empty())
        {
            token = token.substr(0, token.length() - 2);
        }

        start == 0 ? start = atof(token.c_str()) : destination = atof(token.c_str());
        pos++;
        content.erase(0, pos + delimiter.length()-1);

    }

    cout << "Starting Node Number: "<<start<<" Destination Node Number: " << destination << "\n" << "\n";
}

void showTheMatrix(int** neighbours, int size) {
    cout << "Show the matrix: \n";
    for (int i = 0; i < size; i++)
    {
        cout << "\nNode [" << i+1 << "]: ";
        for (int j = 0; j < size; j++)
        {
            cout << neighbours[i][j] << " ";
        }
    }
    cout << "\n";
}

void fillTheMatrix(string content, int nodeNumber, int size, int** table) {
    string original = content;

    string delimiter = " ";
    size_t pos = 0;
    string token;
    int counter = 0;

    while (((pos = content.find(delimiter)) != std::string::npos) && nodeNumber<=size && !content.empty()) {
        token = content.substr(0, pos);
        if (!token.empty())
        {
            token = token.substr(0, token.length() - 2);
        }
        table[nodeNumber][counter] = atof(token.c_str());
        content.erase(0, pos + delimiter.length());
        counter++;
    }
}


int main()
{
    ifstream iFile;
    iFile.open("graf.txt");

    map<int, node> nodes;
    int** neighbours;

    string content;
    getline(iFile, content);
    fillTheMap(content, nodes);
    int startNodeNumber, destinationNodeNumber;
    getline(iFile, content);
    setStartingAndDestinationNodes(content, startNodeNumber, destinationNodeNumber);

    neighbours = new int*[nodes.size()];
    for (int j = 0; j < nodes.size(); j++) {
        neighbours[j] = new int[nodes.size()];
    }

    for (int j = 0; j < nodes.size(); j++) {
        getline(iFile, content);
        fillTheMatrix(content, j, nodes.size(), neighbours);
    }


    showTheMatrix(neighbours, nodes.size());

}

