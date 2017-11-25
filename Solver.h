//
//  Solver.h
//  ECE438MP3
//
//  Created by Ziyang Liu on 11/21/17.
//  Copyright © 2017 Ziyang Liu. All rights reserved.
//

#ifndef Solver_h
#define Solver_h

#include "Graph.h"
#include <fstream>

class Solver {
public:
    unordered_map<int, unordered_map<int, int>> CostTable;
    unordered_map<int, unordered_map<int, int>> ForwardTable;
    
    Solver(){
        CostTable.clear();
        ForwardTable.clear();
    }
    
    void LinkState(Graph g){
        CostTable.clear();
        ForwardTable.clear();
        for(auto it = g.Nodes.begin(); it != g.Nodes.end(); ++it){
            int src = it->first;
            unordered_map<int,int> dist,prev;
            Dijkstra(g,src,dist,prev);
            //OutTopology(g,src,dist,prev);
            //PrintForwardTable(g, src, dist, prev);
            PrintDist(g, src, dist);
            CostTable.insert(make_pair(src, dist));
            ForwardTable.insert(make_pair(src,prev));
        }
    }
    
    void DistanceVector(Graph g){
        CostTable.clear();
        ForwardTable.clear();
        for(auto it = g.Nodes.begin(); it != g.Nodes.end(); ++it){
            int src = it->first;
            unordered_map<int,int> dist,prev;
            BellmanFord(g, src, dist, prev);
            //PrintForwardTable(g, src, dist, prev);
            PrintDist(g, src, dist);
            CostTable.insert(make_pair(src, dist));
            ForwardTable.insert(make_pair(src,prev));
        }
    }
    
    void OutputPath(string outfilename,int src, int dst){
        ofstream outfile;
        outfile.open(outfilename, ios_base::app);
        vector<int> stack;
        int tmp = dst;
        stack.push_back(dst);
        while(tmp != src){
            stack.push_back(ForwardTable[src][tmp]);
            tmp = ForwardTable[src][tmp];
        }
        for(int i = int(stack.size()-1); i>= 0; i--){
            outfile<<stack[i]<<"  ";
        }

    }
    
    
private:
    void Dijkstra(Graph g, int src, unordered_map<int,int> & dist, unordered_map<int,int> & prev){
        if(dist.size() != 0 || prev.size() != 0){
            cout<<"Error(Dijkstra):Invalid input"<<endl;
            return;
        }
        unordered_map<int,Node> Q;
        //Initialization
        for ( auto it = g.Nodes.begin(); it != g.Nodes.end(); ++it ){ //
            dist[it->first] = INFINITY;
            prev[it->first] = UNDEFINED;
            Q.insert(make_pair(it->first,it->second));
        }
        
        dist[src] = 0;
        while(Q.size()!= 0){
            int uID = GetMinDistID(Q,dist);
            Node u = Q[uID];
            Q.erase(uID);
            for(int i = 0; i < u.Edges.size(); i++){
                Edge e = u.Edges[i];
                int vID;
                if (e.left == uID){
                    vID = e.right;
                }
                else {
                    vID = e.left;
                }
                if (Q.find(vID) == Q.end())
                    continue;
                int alt = dist[uID] + e.weight;
                if (alt < dist[vID]){
                    dist[vID] = alt;
                    prev[vID] = uID;
                }
            }
        }
        return;
    }
    
    int GetMinDistID(unordered_map<int,Node> Q,unordered_map<int,int> dist){
        int MinDistValue = INFINITY;
        int ret = -1;
        for ( auto it = dist.begin(); it != dist.end(); ++it ){
            if(it->second < MinDistValue && Q.find(it->first) != Q.end()){
                ret = it->first;
                MinDistValue = it->second;
            }else if (it->second == MinDistValue && Q.find(it->first) != Q.end()){  //Tie Break 2 or 3?;
                if (ret > it->first){
                    ret = it->first;
                }
            }
        }
        return ret;
    }
    
    
    void BellmanFord(Graph g, int src, unordered_map<int,int> & dist, unordered_map<int,int> & prev){
        if(dist.size() != 0 || prev.size() != 0){
            cout<<"Error(BellmanFord):Invalid input"<<endl;
            return;
        }
        //Initialization
        for ( auto it = g.Nodes.begin(); it != g.Nodes.end(); ++it ){ //
            dist[it->first] = INFINITY;
            prev[it->first] = UNDEFINED;
        }
        
        dist[src] = 0;
        

        for (int i = 1; i < g.Nodes.size(); i++){
            for(int j = 0; j < g.Edges.size(); j++){
                int u = g.Edges[j].left;
                int v = g.Edges[j].right;
                int w = g.Edges[j].weight;
                if(dist[u] + w < dist[v]){
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                }else if (dist[u]+w == dist[v] && u < prev[v]){ //tie break 2,3?
                    prev[v] = u;
                }
                if(dist[v] + w < dist[u]){
                    dist[u] = dist[v] + w;
                    prev[u] = v;
                }else if (dist[v] + w == dist[u] && v < prev[u]){
                    prev[u] = v;
                }
            }
        }
        return;
    }
    
    void PrintDist(Graph g, int src, unordered_map<int,int> & dist){
        cout<<"dist table for node "<<src<<endl;
        for(auto it = dist.begin(); it != dist.end(); it++){
            cout<<"dst "<<it->first<<" to src "<<src<<" cost "<<it->second<<endl;
        }
    }
    
    void PrintForwardTable(Graph g, int src, unordered_map<int,int> & dist, unordered_map<int,int> & prev){
        cout<<endl;
        cout<<"Forward Table for Node "<<src<<":"<<endl;
        vector<int> stack;
        int dst = 0;
        while(dst <= g.MaxNodeID){
            if(!g.HasNode(dst)){
                dst++;
                continue;
            }
            stack.clear();
            int tmp = dst;
            stack.push_back(dst);
            while(tmp != src){
                stack.push_back(prev[tmp]);
                tmp = prev[tmp];
            }
            cout<<"dst:"<<dst<<"  cost:"<<dist[dst]<<endl;
            cout<<"    ";
            for(int i = int(stack.size()-1); i>= 0; i--){
                cout<<stack[i]<<"  ";
            }
            cout<<endl;
            dst++;
        }
    }
    void OutTopology(Graph g, int src,unordered_map<int,int> & dist, unordered_map<int,int> & prev){
        ofstream outfile;
        outfile.open("/Users/ziyangliu/Documents/ECE438MP3/ECE438MP3/ECE438MP3/output.txt", ios_base::app);
        outfile<<endl;
        vector<int> stack;
        int dst = 0;
        while(dst <= g.MaxNodeID){
            if(!g.HasNode(dst)){
                dst++;
                continue;
            }
            stack.clear();
            int tmp = dst;
            stack.push_back(dst);
            while(tmp != src){
                stack.push_back(prev[tmp]);
                tmp = prev[tmp];
            }
            if(stack.size()==1){
                outfile<<dst<<" "<<stack[0]<<" "<<dist[dst]<<endl;
            }else{
                outfile<<dst<<" "<<stack[stack.size()-2]<<" "<<dist[dst]<<endl;
            }
            dst++;
        }
        outfile<<endl;
    }
};


#endif /* Solver_h */