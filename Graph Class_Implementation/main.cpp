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
//#include "graphnode.h"
#include "Header.h"
#include "limits.h"

#ifndef RC_DEBUG
//#define RC_DEBUG
#endif

#define gridsize 9
#define matrixsize 3



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

class mcomparator
{
bool reverse ;
public:
    mcomparator(const bool &rev = false):
    reverse(rev)
    {
        
    };
    
    bool operator()(int &lhs , int &rhs)
    {
        if(!reverse)
        {
            return lhs < rhs;
        }
        else{
            return lhs > rhs;
        }
    }
    
};

bool sudokusolver(int arr[][gridsize] , int i , int j);

void sudoku(int arr[][gridsize])
{
    std::cout << "calling sudoku solver" << '\n';
    sudokusolver(arr , 0 , 0);
    
}

bool checkvalidity(int arr[gridsize][gridsize] , int row , int col , int val)
{
  
    
    for(int r = 0 ; r < gridsize ; r ++)
    {
        
        if(arr[r][col] == val)
        {
            return false;
        }
    }
    
    for(int c = 0 ; c < gridsize ; c ++)
    {
        if(arr[row][c] == val)
        {
            return false;
        }
    }
    
    for(int i = row - row % matrixsize ;  i < row - row % matrixsize + matrixsize ; i ++)
    {
      for(int j= col - col % matrixsize ;  j < matrixsize + col- col % matrixsize ; j ++)
      {
          
          if(arr[i][j] == val)
          {
              return false;
          }
      }
    }
    
    return true;
}
bool sudokusolver(int arr[gridsize][gridsize] , int i , int j)
{
    if( i == gridsize)
    {
        i = 0;
      
        if(++j == gridsize)
        {
            std::cout << "Returning true" << std::endl;
            for(int a = 0 ; a <gridsize ; a ++)
            {
                for(int b =0 ; b <gridsize ; b++)
                {
                    std::cout << arr[a][b] << '\t';
                   
                }
                
                
                
                std::cout << std::endl;
            }
            
            return true;
        }
       
    }
    
  
    for (int c = 1 ; c <= 9 ; c++)
    {
        if(checkvalidity(arr , i , j , c))
        {
            
            arr[i][j] = c;
            
            if(sudokusolver(arr , i + 1 , j ))
            {
                return true;
            }
        }
        //std::cout << i<<":"<<j;
     
        
    }
    
   arr[i][j] = 0;
   return false;
}

template<class T>
struct treenode
{
    T data;
    struct treenode *left;
    struct treenode *right;
    
    treenode(T data)
    {
        this->data = data;
    }
    
    
    
} ;

template <class T>
std::vector<std::list<treenode<T>>> levelorder(treenode<T> *r , int count)
{
    std::vector<std::list<treenode<T>>> lists;
    std::list<treenode<T>> *current = new std::list<treenode<T>>();
    
    if(r != NULL)
    {
        (*current).push_back(*r);
        
    }
    
   
    
    while(!(*current).empty())
    {
        lists.push_back(*current);
       
        if(lists.size() == count )
        {
            typename std::list<treenode <T>> p = lists.at(count-1);
            for(typename std::list<treenode<T>>::iterator l = p.begin();l !=p.end(); l++ )
            {
               std::cout << (*l).data << std::endl;
            }
        }
        
        std::list<treenode<T>> *parent = current;
        current = new std::list<treenode<T>>();
        for(typename std::list<treenode<T>>::iterator it = (*parent).begin() ; it !=(*parent).end() ; it++ )
        {
            if(it->left != NULL)
            {
                (*current).push_back(*(it->left));
              
            }
            
            if (it->right != NULL) {
              (*current).push_back(*(it->right));
            }
            
                
        }
        
    }
    return lists;
}



template<class T>
void postorder(treenode<T> *t)
{
    if(t == NULL)
        return;
    postorder(t->left);
    postorder(t->right);
    
    std::cout << t->data << std::endl;
}

int main(int argc, const char * argv[])
{
    
   
    /*
    // insert code here...
    treenode<int> *first = new treenode<int>(1);
    first->left = new treenode<int>(10);
    first->right = new treenode<int>(11);
    
    treenode<int> * l = first->left;
    l->left = new treenode<int>(13);
    //postorder(first);
    //levelorder(first, 3);
    
    int arr[gridsize][gridsize] ;
    
    typedef std::priority_queue<int , std::vector<int> , mcomparator> m_queue;
    m_queue mq(mcomparator(true));
    
    std::vector<int> cont;
    for(int i = 0 ; i < 55 ; i++)
        cont.push_back(i);
    
    for(std::vector<int>::iterator it = cont.begin() ; it != cont.end() ; it++)
    {
        
        
        if(mq.size() == 5)
        {mq.pop();
        }
        mq.push(*it);
    }
    
    while(!mq.empty())
    {
        std::cout << mq.top() <<std::endl;
        mq.pop();
    }
    */
    
    //sudoku(arr);
    
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

