//
//  graphnode.h
//  dev4
//
//  Created by Ashok  on 3/5/14.
//  Copyright (c) 2014 Ashok . All rights reserved.
//

#ifndef __dev4__graphnode__
#define __dev4__graphnode__


#include <iostream>
#include <vector>

#endif


/* defined(__dev4__graphnode__) */



class graphnode
{
    std::vector<int> m_neighbours;
    int m_id;
    
    
public:
    
    
    graphnode(int id):m_id(id){};
    std::vector<int>& getadjacent()
    {
        return m_neighbours;
    }
    
    void addneighbour(int add)
    {
        m_neighbours.push_back(add);
    }
    
    int getid()
    {
        return m_id;
    }
    
};