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
        for(int i = 0; i < edges.size(); i++){
            Edges.push_back(edges[i]);
        }
        ID = Id;
    }
    
    Node(const Node &n){
        ID = n.ID;
        for(int i = 0; i < n.Edges.size(); i++){
            Edges.push_back(n.Edges[i]);
        }
    }
    
    Node operator= (const Node& n) const{
        Node ret;
        ret.ID = n.ID;
        for(int i = 0; i < n.Edges.size();i++){
            ret.Edges.push_back(n.Edges[i]);
        }
        return ret;
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
                if(e.weight <0){
                    vector<Edge> tmp_vec;
                    for(int j = 0 ; j < Edges.size(); j++){
                        if(j != i){
                            tmp_vec.push_back(Edges[j]);
                        }
                    }
                    Edges.clear();
                    for(int j = 0; j < tmp_vec.size(); j++){
                        Edges.push_back(tmp_vec[j]);
                    }
                    //Edges.erase(Edges.begin()+(i));
                   
                    return 1;
                }else{
                    Edges[i].weight = e.weight;
                    return 1;
                }
            }
        }
        AddEdge(e);
        return 1;
    }

    
    void PrintNode(){
        cout<<"Print Node "<<ID<<endl;
        for(int i = 0; i < Edges.size(); i++){
            cout<<"  "<<Edges[i].left <<"->"<<Edges[i].right<<":"<<Edges[i].weight<<endl;
        }
    }
    
};



#endif /* Node_h */
