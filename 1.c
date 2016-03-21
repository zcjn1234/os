#include<iostream>
#include<cmath>
#include<cstdlib>
#include<stdlib.h>
#include<string.h>
#include<set>
#include<vector>
using namespace std;

#define  MEM_SIZE 10
int main()
{
    int n=-1;
    int t=4;
    cout<<"缺页率"<<endl;
    cout<<"页号："<<endl;
   
    vector<int>mem;
    
    bool find=false;
    int t1=0;
    int t2=-1;
    set<int>myset;
    while(cin>>n)
    {
           cout<<n<<endl;
           myset.insert(n);
           t2++;
           find=false;
           for( vector<int>::iterator i=mem.begin();i!=mem.end();i++)
           {
                  if(n==*i)
                  {
                               
                     cout<<"内存中存在:"<<n<<endl;
                     find =true;            
                   }  
           }
         
           if (find) continue;
       
            int aa[MEM_SIZE];
            for(int i=0;i<MEM_SIZE;i++) aa[i]=-1;
            int r=0;
           if((t2-t1)>t)
           {
                        t1=t2;
                        for(set<int>::iterator it=myset.begin();it!=myset.end();it++)
                        {
                                           
                              aa[r]=*it;
                              r++;
                              if(r>=MEM_SIZE) r=0;
                                               
                        }    
                   myset.clear();    
                   int rr=-1;
                   for( vector<int>::iterator i=mem.begin();i!=mem.end();i++)
                   {     bool findmem=false;
                        rr++;
                         for(int j=0;j<MEM_SIZE;j++)
                         {
                              if(*i==aa[j])
                              {
                               findmem=true;
                               break;                                                
                              }
                                  
                         }
                         if(!findmem) mem.erase(i);
          
                   }                          
                   for(int i=0;i<MEM_SIZE;i++)
                   {
                    if(mem[i]==-1)
                     {
                       mem[i]=n;      
                     }    
                   }                                                                
            }
       
    }
    return 0;   
} 