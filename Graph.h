//
//  Graph.h
//  ECE438MP3
//
//  Created by Ziyang Liu on 11/9/17.
//  Copyright © 2017 Ziyang Liu. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include "Node.h"
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

class Graph {
public:
    unordered_map<int, Node> Nodes;
    vector<Edge> Edges;
    int MaxNodeID;
    
    Graph(){
        Nodes.clear();
        Edges.clear();
        MaxNodeID = UNDEFINED;
    }
    
    Graph(string filename){
        ifstream infile(filename);
        int s, d, w;
        while (infile >> s >> d>> w)
        {   
            Edge e(s,d,w);
            if(s == d && HasNode(s)){
                continue;
            }else if (s==d && !HasNode(s)){
                Nodes.insert(make_pair(s,Node(s)));
                continue;
            }
            Edges.push_back(e);
            if(!HasNode(s)){
                Node n(s);
                n.AddEdge(e);
                Nodes.insert(make_pair(s,n));
            }else{
                Nodes[s].AddEdge(e);
            }
            
            if(!HasNode(d)){
                Node n(d);
                n.AddEdge(e);
                Nodes.insert(make_pair(d,n));
            }else{
                Nodes[d].AddEdge(e);
            }
        }
        MaxNodeID = UNDEFINED;
        for(auto it = Nodes.begin(); it != Nodes.end(); ++it){
            if(it->first >MaxNodeID)
                MaxNodeID = it->first;
        }
    }
    
    void UpdateGraph(Edge deltaEdge){
        if(deltaEdge.left == deltaEdge.right && !HasNode(deltaEdge.left)){
            //actually node and doesn't have it.
            Node n(deltaEdge.left);
            Nodes.insert(make_pair(deltaEdge.left,n));
            return;
        }
        
        //Nodes[deltaEdge.left] = Nodes[deltaEdge.left].UpdateEdge(deltaEdge);
        Node tmp1 = Nodes[deltaEdge.left];
        tmp1.UpdateEdge(deltaEdge);
        Nodes.erase(deltaEdge.left);
        Nodes.insert(make_pair(deltaEdge.left,tmp1));
        //Nodes[deltaEdge.right] = Nodes[deltaEdge.right].UpdateEdge(deltaEdge);
        Node tmp2 = Nodes[deltaEdge.right];
        tmp2.UpdateEdge(deltaEdge);
        Nodes.erase(deltaEdge.right);
        Nodes.insert(make_pair(deltaEdge.right,tmp2));
        
        
        for(int i = 0; i < Edges.size(); i++){
            if(Edges[i].left == deltaEdge.left && Edges[i].right == deltaEdge.right && deltaEdge.weight == -999){
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
                //Edges.erase(Edges.begin()+i);
                return;
            }else if (Edges[i].left == deltaEdge.left && Edges[i].right == deltaEdge.right){
                Edges[i].weight = deltaEdge.weight;
                return;
            }
        }
        Edges.push_back(deltaEdge);
        return;
    }
    
    bool HasNode(int i){
        if (Nodes.find(i) != Nodes.end())
            return true;
        return false;
    }
    
    
    void PrintGraph(){
        cout<<"Print Graph:Nodes"<<endl;
        for ( auto it = Nodes.begin(); it != Nodes.end(); ++it ){
            cout << "ID:" << it->first <<endl;
            for(int j = 0; j < it->second.Edges.size();j++){
                cout << "   " << it->second.Edges[j].left <<"-->"<<it->second.Edges[j].right<<":"<<it->second.Edges[j].weight<<endl;
            }
        }
        cout<<"Print Graph:Edges"<<endl;
        for(int i = 0; i < Edges.size(); i++){
            cout << "   " << Edges[i].left <<"-->"<<Edges[i].right<<":"<<Edges[i].weight<<endl;
        }
    }    
};
#endif /* Graph_h */
