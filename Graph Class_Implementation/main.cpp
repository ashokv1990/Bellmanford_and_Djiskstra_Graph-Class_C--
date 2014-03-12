//
//  main.cpp
//  dev4
//
//  Created by Ashok  on 3/4/14.
//  Copyright (c) 2014 Ashok . All rights reserved.
//


#include <iostream>
#include <vector>
#include<list>
#include <queue>
#include<map>

#include "Header.h"
#include "limits.h"

#ifndef RC_DEBUG
//#define RC_DEBUG
#endif

#define gridsize 9
#define matrixsize 3


/*******Simple graph class with depth first , breath first search , DJIKSTRA ,bellman ford methods in Built 
 
 Points can added using the addn method and the API has been demostrated in the main as an example
 
 *******/

class graph
{
    
    std::map<int,graphnode*> m_map;
    
    void dfsvisit(int id , std::map<int,bool> &mdfs)
    {
        
        if(m_map.find(id) == m_map.end())
        {
            return;
        }
        
        mdfs[id] = true;
        
        for(std::vector<int>::iterator it = m_map.at(id)->getadjacent().begin() ; it != m_map.at(id)->getadjacent().end() ; it++ )
        {
            if(mdfs.find(*it) == mdfs.end())
            {
                dfsvisit(*it , mdfs);
            }
        }
        
        std::cout << id << "done" << std::endl;
        
    }

    
public:
    
    void insert(int id)
    {
        if(m_map.find(id) == m_map.end())
        {
            m_map[id] = new graphnode(id);
        }
       
    }
    
    void addn(int id1, int id2)
    {
        if(m_map.find(id1) != m_map.end())
        {
           if(m_map.find(id2) == m_map.end())
           {
               insert(id2);
           }
            m_map[id1]->addneighbour(id2);
        }
    
    }
    
    
    void bfs(int id)
    {
    if(m_map.find(id) == m_map.end())
    {
        return;
    }
        
        std::queue<int> m_q;
        std::map<int , bool>bfsm;
        
        m_q.push(id);
        bfsm.insert(std::pair<int,bool>(id , true));
        
        while(!m_q.empty())
        {
            graphnode* u = m_map.find(m_q.front())->second;
            std::cout << u->getid() << std::endl;
            for(std::vector<int>::iterator it = u->getadjacent().begin() ; it != u->getadjacent().end() ; it++ )
            {
                if(bfsm.find(*it) == bfsm.end())
                {
                    m_q.push(*it);
                }
            }
            
            m_q.pop();
            
        }
    
    }
    
    
    void dfs(int id)
    {
        if(m_map.find(id) == m_map.end())
            return;
        
        std::map<int,bool>mdfs;
        
        for(std::map<int,graphnode*>::iterator it = m_map.begin() ; it != m_map.end() ; it++)
        {
            if(mdfs.find(it->first) == mdfs.end())
            {
                dfsvisit(id , mdfs);
            }
        }
    
    }
    
};


/*******Weighted graph class with depth first , breath first search , DJIKSTRA ,bellman ford methods in Built
 
 Points can added and the API has been demostrated in the main as an example , weighted graph demands a weight be associated between two points in the graph
 
 *******/

class wgraph:public graph
{
   std::map<int,graphnodew*> m_map;

    void dfsvisit(int id , std::map<int,bool> &mdfs)
    {
        
        if(m_map.find(id) == m_map.end())
        {
            return;
        }
        
        mdfs[id] = true;
        
        std::vector<int> fvec = m_map.at(id)->getfirst();
        
        for(std::vector<int>::iterator it = fvec.begin() ; it != fvec.end() ; it++ )
        {
            if(mdfs.find(*it) == mdfs.end())
            {
                dfsvisit(*it , mdfs);
            }
        }
        
        std::cout << id << "done" << std::endl;
        
    }
    
public:
    
  
    void bellmanford(int source)
    {
        class wrapper
        {
        public:
            graphnodew* elem;
            int key = 999;
            wrapper( graphnodew* w = NULL):elem(w){};
        };
        
        std::map<int, wrapper*> d; // Lookup
        
        
        for(std::map<int , graphnodew*>::iterator it = m_map.begin() ; it != m_map.end() ; it++)
        {
            wrapper * w = new wrapper(it->second);
            d.insert(std::pair<int , wrapper*>(it->first , w));
         
        }
        
        if(d.find(source) == d.end())
        {
            return;
        }
        
        d.find(source)->second->key = 0;
        
       
        
        for(int i = 0 ; i < d.size() - 1 ; i++)
        {
           
            
            //all edges
            for(std::map<int , wrapper*>::iterator it = d.begin() ; it != d.end() ; it++)
            {
                for(std::vector<std::pair<int,int>>::iterator it2 = it->second->elem->getadjacent().begin() ; it2 != it->second->elem->getadjacent().end() ; it2++)
                {
                   
                    if(d.find(it2->first)->second->key > d.find(it->first)->second->key + it2->second)
                    {
                        d.find(it2->first)->second->key = d.find(it->first)->second->key + it2->second;
                    }
                }
            }
        }
        
        for(std::map<int , wrapper*>::iterator it = d.begin() ; it != d.end() ; it++)
        {
            for(std::vector<std::pair<int,int>>::iterator it2 = it->second->elem->getadjacent().begin() ; it2 != it->second->elem->getadjacent().end() ; it2++)
            {
                
                if(d.find(it2->first)->second->key > d.find(it->first)->second->key + it2->second)
                {
                    std::cout << "Negative edge cycle" << std::endl;
                }
            }
        }
        
        
        for(std::map<int , wrapper*>::iterator it = d.begin() ; it != d.end() ; it++)
        {
            std::cout << it->second->key << ":min distance"<<it->first << std::endl;
        }
    }
    
    void djikstra(int source)
    {
        std::cout << "creating the wrapper class" << std::endl;
      
        class wrapper
        {
        public:
            graphnodew* elem;
            int key = INT32_MAX;
            wrapper( graphnodew* w = NULL):elem(w){};
        };
        
    
        
        std::cout << "creating the comparator class" << std::endl;
        class m_comparator
        {
        public:
            bool operator()(wrapper* lhs , wrapper* rhs)
            {
                if(lhs->key > rhs->key)
                {
                    return true;
                }
                else{
                    return false;
                }
            }
        };
        
       
        
        std::cout << "creating the core data structures" << std::endl;
        std::map<int, wrapper*> d; // Lookup
        typedef std::priority_queue<int , std::vector<wrapper*>, m_comparator> m_q;
        m_q first;// Priority Queue
        std::vector<std::pair<int, int>> res;
       
        
        for(std::map<int , graphnodew*>::iterator it = m_map.begin() ; it != m_map.end() ; it++)
        {
            wrapper * w = new wrapper(it->second);
            d.insert(std::pair<int , wrapper*>(it->first , w));
            first.push(w);
        }
        
        if(d.find(source) == d.end())
        {
            return;
        }
        
        std::cout << "source initialization" << std::endl;
        
        class reinsert
        {
            m_q* temp;
            std::vector<wrapper*> tempv;
            
            
        public:
            reinsert(m_q *pq)
            {
                temp = pq;
            }
            
            void rinst()
            {
               
              

                
                while(!(*temp).empty())
                {
                    tempv.push_back(temp->top());
                    temp->pop();
                    
                }
                for(std::vector<wrapper*>::iterator it = tempv.begin() ; it != tempv.end() ; it++)
                {
                    temp->push(*it);
                }
                
                
            }
        };
        
        std::map<int , wrapper*>::iterator it = d.find(source);
        it->second->key = 0;
        
      
        reinsert r(&first);
        r.rinst();
       
#ifdef RC_DEBUG
        
        for(std::map<int , wrapper*>::iterator it = d.begin() ; it != d.end() ; it++)
        {
            std::cout << "graph val:" << it->first << "djikstra score" << it->second->key <<std::endl;
        }
        
        std::cout << "check p queue " << std::endl;
        
        m_q second(first);
        
        while (!second.empty()) {
            std::cout << second.top()->key << "second" << std::endl;
            second.pop();
        }
        
        
      
        
#endif
        
        std::cout << "core loop" << std::endl;
        
        while (!first.empty()) {
            
            wrapper* u = first.top();
        
           
            graphnodew * g = u->elem;
            res.push_back(std::pair<int,int>(g->getid(),u->key));
            
            for(std::vector<std::pair<int,int>>::iterator it = g->getadjacent().begin() ; it != g->getadjacent().end() ; it++)
            {
                if(d.find(it->first)!= d.end())
                {
                    if (d.find(it->first)->second->key > u->key + it->second) {
                        
                        d.find(it->first)->second->key = u->key + it->second;
                    }
                }
                
            }
            
           
            first.pop();
            /***Strictily not necessary pop calls pop_heap ****/
            reinsert r(&first); // must pull out all elements in heap if not calling pop and reinsert if you change the priority of internal elements at run time
            r.rinst(); // reinsert push and pop calls reheap
            
        }
        
        for(std::vector<std::pair<int,int>>::iterator it = res.begin() ; it != res.end() ; it++)
        {
            std::cout << it->first << ":" << it->second <<std::endl;
        }
      
        
    }
    
    void insert(int id)
    {
        if(m_map.find(id) == m_map.end())
        {
            m_map[id] = new graphnodew(id);
        }
        
    }
    
    void addn(int a , int b , int w)
    {
        if(m_map.find(a) != m_map.end())
        {
            if(m_map.find(b) == m_map.end())
            {
                insert(b);
            }
            m_map[a]->addneighbour(b,w);
        }
        
    }
    
    
    
    void bfs(int a)
    {
        if(m_map.find(a) == m_map.end())
        {
            return;
        }
        
        std::queue<int> m_q;
        std::map<int , bool>bfsm;
        
        m_q.push(a);
        bfsm.insert(std::pair<int,bool>(a, true));
        
        while(!m_q.empty())
        {
            graphnodew* u = m_map.find(m_q.front())->second;
            std::cout << u->getid() << std::endl;
            std::vector<int> fvec = u->getfirst();
            for(std::vector<int>::iterator it = fvec.begin() ; it != fvec.end() ; it++ )
            {
                if(bfsm.find(*it) == bfsm.end())
                {
                    m_q.push(*it);
                    bfsm[*it] = true;
                }
            }
            
            m_q.pop();
            
        }
    }
    
    void dfs(int id)
    {
        if(m_map.find(id) == m_map.end())
            return;
        
        std::map<int,bool>mdfs;
        
        for(std::map<int,graphnodew*>::iterator it = m_map.begin() ; it != m_map.end() ; it++)
        {
            if(mdfs.find(it->first) == mdfs.end())
            {
                dfsvisit(id , mdfs);
            }
        }
        
    }
};





int main(int argc, const char * argv[])
{
    
 
    
    wgraph g;
    g.insert(1);
    g.addn(1,2,55);
    g.addn(2,3,34);
    g.addn(3,4,23);
    g.addn(4,1,11);
    g.addn(3,1,12);
    
    g.dfs(3);
    g.bfs(3);
    std::cout << "single source shortest path Djikstra" << std::endl;
    g.djikstra(4);
    
    
    wgraph g2;
    g2.insert(1);
    g2.addn(1,2,5);
    g2.addn(1,6,-2);
    g2.addn(6,2,2);
    g2.addn(2,3,1);
    g2.addn(6,3,4);
    g2.addn(6,5,4);
    g2.addn(3,5,-1);
    g2.addn(3,4,3);
    g2.addn(5,4,1);
   
    g2.bellmanford(1);
    std::cout << "Test Successful!\n";
    return 0;
}

