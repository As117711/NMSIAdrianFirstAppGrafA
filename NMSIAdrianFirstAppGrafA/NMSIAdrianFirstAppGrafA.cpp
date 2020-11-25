// NMSIAdrianFirstAppGrafA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <queue>

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
    int counter = 0;

    while (((pos = content.find(delimiter)) != std::string::npos) || (content.find(delimiter) == std::string::npos && !content.empty())) {
        node* newNode = new node();
        token = content.substr(0, pos);
        if (!token.empty() && !(content.find(delimiter) == std::string::npos && !content.empty()))
        { 
            token = token.substr(0, token.length() - 2);
        }
        if (content.find(delimiter) == std::string::npos && !content.empty()) {
            token.erase(token.length() - 1, token.length());
        }
        cout << token << std::endl;

        while (((pos2 = token.find(delimiter2)) != std::string::npos && !token.empty())) {
        token2 = token.substr(0, pos2);
        newNode->number = counter;
        newNode->x = atof(token2.c_str());
        token.erase(0, pos2 + delimiter2.length()+1);
        newNode->y = atof(token.c_str());
        nodes[newNode->number] = *newNode;
        counter++;
        }


        if ((content.find(delimiter) == std::string::npos && !content.empty())) { break; }
        content.erase(0, pos + delimiter.length());
    }

    for (int i = 0; i < nodes.size(); i++)
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
    start--; destination--;
    cout << "Starting Node Number: "<<start<<" Destination Node Number: " << destination << "\n" << "\n";
}

void showTheMatrix(int** neighbours, int size) {
    cout << "Show the matrix: \n";
    for (int i = 0; i < size; i++)
    {
        cout << "\nNode [" << i << "]: ";
        for (int j = 0; j < size; j++)
        {
            cout << neighbours[i][j] << " ";
        }
    }
    cout << "\n";
}

void showTheMatrixDouble(map<int, double> neighbours, int size, string msg) {
    cout << "\nShow the matrix: " << msg << "\n";
    for (int i = 0; i < size; i++)
    {
        cout << "\nNode [" << i << "]: " << neighbours[i] << " ";
        
    }
    cout << "\n";
}

void showTheMatrixInt(map<int, int> neighbours, int size, string msg) {
    cout << "\nShow the matrix: " << msg << "\n";
    for (int i = 0; i < size; i++)
    {
        cout << "\nNode [" << i << "]: " << neighbours[i] << " ";

    }
    cout << "\n";
}

double calculateFValue(double g, double h) {
    return g + h;
}

int compareNodesFValue(map<int, node> nodes, int first, int second, map<int, double> g, map<int, double> f, map<int, double> h) {
    
    double firstValue = calculateFValue(g[first], h[first]);
    double secondValue = calculateFValue(g[second], h[second]);
    
    if (firstValue <= secondValue) { return firstValue; }
    return secondValue;
}

int findSmallestFNodeValueForMap(map<int, node> nodes, int size, map<int, double> f) {

    int smallestFNodeNumber = -1; 
    double smallestFNodeValue = -1;

    for (std::map<int, node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        if (f[it->first] < smallestFNodeValue || smallestFNodeNumber == -1) {
            smallestFNodeNumber = it->first;
            smallestFNodeValue = f[it->first];
        }
    }

    return smallestFNodeNumber;
}

void showThePath(map<int, int> previous, int destinationNode) {
    
    if (previous[destinationNode] != -1) {
        cout << previous[destinationNode] << " ";
        showThePath(previous, previous[destinationNode]);
    }
}

void fillTheMatrix(string content, int nodeNumber, int size, int** table) {
    string original = content;

    string delimiter = " ";
    size_t pos = 0;
    string token;
    int counter = 0;

    while (((pos = content.find(delimiter)) != std::string::npos) && nodeNumber<=size && !content.empty() || (content.find(delimiter) == std::string::npos && !content.empty())) {
        token = content.substr(0, pos);
        if (!token.empty())
        {
            token = token.substr(0, token.length() - 2);
        }
        table[nodeNumber][counter] = atof(token.c_str());

        if (content.find(delimiter) == std::string::npos && !content.empty()) { break; }
        content.erase(0, pos + delimiter.length());
        counter++;
    }
}

double calculateDistance(double x, double y, double xt, double yt) {
    return sqrt((xt - x) * (xt - x) + (yt - y) * (yt - y));
}

bool mapContainsKey(map<int, node> considered, int key)
{
    if (considered.find(key) == considered.end()) return false;
    return true;
}

int main()
{
    ifstream iFile;
    iFile.open("graf.txt");

    map<int, node> nodes, considered;
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


    /* Begine the procedure */

    considered[startNodeNumber] = nodes[startNodeNumber];
    int smallestFNode = startNodeNumber;

    map<int, double> g, f, h;
    map<int, int> previusNodes;

    for (int i = 0; i < nodes.size(); i++) {
        h[i] = calculateDistance(nodes[i].x, nodes[i].y, nodes[destinationNodeNumber].x, nodes[destinationNodeNumber].y);
        g[i] = -1;
        f[i] = -1;
        previusNodes[i] = -1;
    }

    showTheMatrixDouble(h, nodes.size(), "h");

    g[startNodeNumber] = 0;
    f[startNodeNumber] = h[startNodeNumber];

    showTheMatrixDouble(g, nodes.size(), "g");
    showTheMatrixDouble(f, nodes.size(), "f");

    while (!considered.empty()) {
        smallestFNode = findSmallestFNodeValueForMap(considered, nodes.size(), f);
        node actual = nodes[smallestFNode];
        if (actual.number == destinationNodeNumber) {
            cout << "\nShow the path: \n";
            showThePath(previusNodes, destinationNodeNumber);
            cout << "\n";
            break;
        }
        considered.erase(smallestFNode);
        for (int i = 0; i < nodes.size(); i++) {
            int temporaru = neighbours[actual.number][i];
            if (neighbours[actual.number][i] != 0) {
                double tempG = g[actual.number] + neighbours[actual.number][i];
                if (tempG < g[i] || g[i] == -1) {
                    previusNodes[i] = actual.number;
                    g[i] = tempG;
                    f[i] = g[i] + h[i];
                    if (mapContainsKey(considered,i) != true) {
                        considered[i] = nodes[i];
                    }
                }
                cout << "\nStep [" << i << "]\n";
                showTheMatrixDouble(g, nodes.size(), "g");
                showTheMatrixDouble(f, nodes.size(), "f");
                //getchar();
            }
            
        }

    }
}

