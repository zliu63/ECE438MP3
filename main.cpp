//
//  main.cpp
//  ECE438MP3
//
//  Created by Ziyang Liu on 11/9/17.
//  Copyright © 2017 Ziyang Liu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include "Solver.h"
using namespace std;

int main(int argc, const char * argv[]) {
    string graphfile = "/Users/ziyangliu/Documents/ECE438MP3/ECE438MP3/ECE438MP3/topofile";
    string messagefile = "/Users/ziyangliu/Documents/ECE438MP3/ECE438MP3/ECE438MP3/messagefile";
    string changesfile ="/Users/ziyangliu/Documents/ECE438MP3/ECE438MP3/ECE438MP3/changesfile";
    Graph g(graphfile);
    Solver solver;
    int count=1;
    cout<<"Round"<<count<<endl;
    //solver.LinkState(g);
    solver.DistanceVector(g);
    ifstream cfile(changesfile);
    int s,d,w;
    while(cfile>>s>>d>>w){
        count++;
        cout<<"Round"<<count<<endl;
        g.UpdateGraph(Edge(s,d,w));
        //solver.LinkState(g);
        solver.DistanceVector(g);
    }
}
