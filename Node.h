//
//  Node.h
//  ECE438MP3
//
//  Created by Ziyang Liu on 11/9/17.
//  Copyright © 2017 Ziyang Liu. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <iostream>
#include <vector>
#include "Edge.h"
using namespace std;

class Node {

public:
    int ID;
    vector<Edge> Edges;
    
    Node(){
        ID = UNDEFINED;
        Edges.clear();
    }
    
    Node(int Id){
        ID = Id;
        Edges.clear();
    }
    
    Node(int Id, vector<Edge> edges){
        Edges = edges;
        ID = Id;
    }
    
    int AddEdge(Edge e){
        if (e.left != ID && e.right != ID)
            return -1;
        Edges.push_back(e);
        return 1;
    }
    
    int UpdateEdge(Edge e){
        for(int i = 0; i<Edges.size(); i++){
            if(Edges[i].left == e.left && Edges[i].right == e.right){
                if(e.weight == -999){
                    Edges.erase(Edges.begin()+i);
                    return 1;
                }else{
                    Edges[i].weight = e.weight;
                    return 1;
                }
            }
        }
        cout<<"Warning(Node.UpdateEdge):Edge not found; TODO:Add edge"<<endl;
        AddEdge(e);
        return 1;
    }
    
};



#endif /* Node_h */
