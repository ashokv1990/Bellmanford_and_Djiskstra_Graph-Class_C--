//
//  Header.h
//  dev4
//
//  Created by Ashok  on 3/6/14.
//  Copyright (c) 2014 Ashok . All rights reserved.
//

#ifndef dev4_Header_h
#define dev4_Header_h

#include "graphnode.h"

#endif


class graphnodew: public graphnode
{
  
    
    std::vector<std::pair<int , int>> m_neighbours;
    
    
    public:
    
    graphnodew(int id):graphnode(id)
    {
        
    };
    
    std::vector<std::pair<int,int>>& getadjacent()
    {
        return m_neighbours;
    }
    
    void addneighbour(int add1 , int add2)
    {
        m_neighbours.push_back(std::pair<int,int>(add1,add2));
    }
    
    std::vector<int> getfirst()
    {
        std::vector<int> numbers;
        for(std::vector<std::pair<int, int>>::iterator it = m_neighbours.begin() ; it != m_neighbours.end() ; it++ )
        {
            numbers.push_back(it->first);
        }
        
        return numbers;
    }
    
};
