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
};


void fillTheMap(string content, map<int, node>& nodes)
{
    cout << "Start: " << content << "\n" << "\n";

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
        cout << token << std::endl;

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
}

int main()
{
    ifstream iFile;
    iFile.open("graf.txt");

    map<int, node> nodes;
    string content;
    getline(iFile, content);

    fillTheMap(content, nodes);

    for (int i = 1; i < 9; i++)
    {
        cout << "Node [" << nodes[i].number << "] x:" << nodes[i].x << " y:" << nodes[i].y << " \n";
    }

    /*
    cout << "Hello World!\n";

    if (iFile.is_open()) {   //checking whether the file is open
        string tp;
        while (getline(iFile, tp)) { //read data frogithubm file object and put it into string.
            cout << tp << "\n"; //print the data of the string
        }
        iFile.close(); //close the file object.
    }
    */
}

