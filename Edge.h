//
//  Edge.h
//  ECE438MP3
//
//  Created by Ziyang Liu on 11/9/17.
//  Copyright © 2017 Ziyang Liu. All rights reserved.
//

#ifndef Edge_h
#define Edge_h

#include <iostream>
#include <vector>
#define INFINITY 999999999
#define UNDEFINED -1

class Edge {
    
public:
    int left,right,weight;
    
    Edge(){
        left = UNDEFINED;
        right = UNDEFINED;
        weight = 1;
    }
    
    Edge(int s, int d, int w){
        if(s < d){
            left = s;
            right = d;
        }else{
            left = d;
            right = s;
        }
        weight = w;
    }
    
    Edge(int s, int d){
        if(s < d){
            left = s;
            right = d;
        }else{
            left = d;
            right = s;
        }
        weight = 1;
    }
    
    Edge operator= (const Edge& e) const{
        Edge ret(e.left,e.right,e.weight);
        return ret;
    }
};


#endif /* Edge_h */
