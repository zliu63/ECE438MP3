#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include "Solver.h"
using namespace std;

int main(int argc, char** argv) {
    //printf("Number of arguments: %d", argc);
    if (argc != 4) {
        printf("Usage: ./linkstate topofile messagefile changesfile\n");
        return -1;
    }
    string graphfile(argv[1]);
    string messagefile(argv[2]);
    string changesfile(argv[3]);
    string outfile = "output.txt";
    
    Graph g(graphfile);
    Solver solver;
    int count=1;
    solver.LinkState(g);
    solver.OutputMessage(outfile, messagefile);
    ifstream cfile(changesfile);
    int s,d,w;
    while(cfile>>s>>d>>w){
        count++;
        g.UpdateGraph(Edge(s,d,w));
        solver.LinkState(g);
        solver.OutputMessage(outfile, messagefile);
    }
    
    return 0;
    return 0;
}

