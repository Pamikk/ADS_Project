#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "ds.h"
using namespace std;
int global_timer=0;
string my_copy(string s,int start,int end){
    //my version of copy to avoid type problem
    string tmp="";
    for (int i=start;i<end;i++){
        tmp+=s[i];
    }
    return tmp;
}
void parse_line(string line,command & comm){
    //parse the input line
    int l = line.length();
    size_t start = line.find(':');    
    string tmp=my_copy(line,0,start);
    //cut the timestamp
    comm.time = stoi(tmp);
    size_t second = line.find('(');
    while (line[start]<'A' or line[start]>'z') start++;
    tmp ="";//empty the tempo buffer
    while (line[start]>='A' and line[start]<='z'){
        tmp+=line[start];
        start++;
    }
    //find the first character of function name
    comm.func_flag = tmp[0];
    //P for Print and I for Insert
    start = second;
    while (line[start]<'0' or line[start]>'9') start++;
    //find the first param
    second = line.find(',');
    if ((second == -1) and (comm.func_flag=='P')){
        second = line.find(')');
        tmp = my_copy(line,start,second);
        comm.param1 = stoi(tmp);
        comm.param2 = comm.param1;
    }else{
        tmp = my_copy(line,start,second);
        comm.param1 = stoi(tmp);
        start = second;
        while (line[start]<'0' or line[start]>'9') start++;
        //find the first param
        second = line.find(')');
        tmp = my_copy(line,start,second);      
        comm.param2 = stoi(tmp);
    }    
}
void insert(command cur,min_heap& heap,br_tree &tree){
    //cout<<"tbi:"<<cur.param1<<' '<<cur.time<<endl;
    br_node * node;
    node = new br_node;    
    node->numid = cur.param1;
    node->total_time = cur.param2;
    if (tree.insert(node)){
        //insert successfully   
        heap_node n;
        n.numid = cur.param1;
        n.total_time = cur.param2;
        n.pointer = node;
        n.numid = cur.param1;
        n.pointer = node;
        heap.insert(n,heap.num);
    }else{
        //fail to insert
        //cout<<"fail"<<endl;
        tree.raise_error(cur);
    }
    return;

}
void print(command cur,br_tree tree){
    int lb = min(cur.param1,cur.param2);
    int ub = max(cur.param1,cur.param2);
    tree.print(lb,ub);
    tree.write(); 
}
int main(int argc,char *argv[]){
    string filename;
    string line;
    ifstream in_file;
    ofstream out_file;
    command cur;
    int comp;    
    filename = argv[argc-1];
    in_file.open(filename);
    out_file.open("output_file.txt");
    min_heap heap;
    br_tree tree;
    heap.set_output(&out_file);
    tree.set_output(&out_file);
    tree.set_heap(&heap);
    //set corresponding heap and out_file for the brtree
    if (in_file.is_open()){
        //open sucessfully
        while (getline(in_file,line)){
            //run all commands
            if (line==""){break;}//avoid empty line
            parse_line(line,cur);//parse the commend
            int flag;
            while (global_timer<cur.time){
                if ((heap.num > 0)){
                    flag = heap.update_root();
                    if (flag==0){
                        //tommorrow will choose a new building
                        heap.heapify(0);
                        if (heap.act_num>heap.num){
                            //there are some inserted nodes not heapified
                            for (int i=heap.num;i<heap.act_num;i++){
                                heap.insert(heap.get(i),i);
                            }
                        }
                        heap.act_num = heap.num; 
                    }
                    if(flag==-1){
                    //current building complete
                    int id = heap.pop(tree,global_timer);
                    if (heap.act_num>heap.num){
                        //there are some inserted nodes not heapified
                        for (int i=heap.num+1;i<heap.act_num+1;i++){
                            heap.insert(heap.get(i),i-1);
                        }                                                   
                    }
                    heap.act_num = heap.num; 
                    if (heap.num ==0){
                        comp = global_timer;
                    }
                    }
                }
                
                global_timer+=1;
            }
           
            if ((heap.num>0)){                
                //run the command                                                                        
                flag = heap.update_root();                              
                if (cur.func_flag == 'P'){
                    //cout<<"print start"<<global_timer<<endl;
                    print(cur,tree);
                }
                if (flag==0){
                        //tommorrow will choose a new building
                    heap.heapify(0);
                    if (heap.act_num>heap.num){
                        //there are some inserted nodes not heapified
                        for (int i=heap.num;i<heap.act_num;i++){
                            heap.insert(heap.get(i),i);
                        }
                    }
                    heap.act_num = heap.num;                     
                }
                if(flag==-1){
                    //current building complete
                    int id = heap.pop(tree,global_timer);
                    if (heap.act_num>heap.num){
                        //there are some inserted nodes not heapified
                        for (int i=heap.num+1;i<heap.act_num+1;i++){
                            heap.insert(heap.get(i),i-1);
                        }
                        heap.act_num = heap.num;                            
                    }
                    if (heap.num ==0){
                        comp = global_timer;
                    }
                }
                if (cur.func_flag == 'I'){
                    //cout<<"insert start"<<global_timer<<endl;
                    insert(cur,heap,tree);
                } 
                                          
            }
            else{
                if (cur.func_flag == 'I'){
                    //cout<<"insert start"<<global_timer<<endl;
                    insert(cur,heap,tree);
                }
                if (cur.func_flag == 'P'){
                    //cout<<"print start"<<global_timer<<endl;
                    print(cur,tree);
                }
            }
            global_timer+=1;
        }
    }
    heap.flag=1;
    while (heap.num>0){
        //not complete
        ////cout<<global_timer<<endl;
        int flag = heap.update_root();
        if (flag==0){
            //tommorrow will choose a new building
            heap.heapify(0);
            if (heap.act_num>heap.num){
                //there are some inserted nodes not heapified
                for (int i=heap.num;i<heap.act_num;i++){
                    heap.insert(heap.get(i),i);
                }
            }
            heap.act_num = heap.num; 
        }
        if(flag==-1){
            //current building complete
            int id = heap.pop(tree,global_timer);            
            if (heap.act_num>heap.num){
                //there are some inserted nodes not heapified
                for (int i=heap.num+1;i<heap.act_num+1;i++){
                    heap.insert(heap.get(i),i-1);
                }
                heap.act_num = heap.num;                            
            }
            if (heap.num ==0){
                comp = global_timer;
            }
        }
        global_timer+=1;
    }
    in_file.close();
    out_file.close();
    return 0;
    
}