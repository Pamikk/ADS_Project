/*define datasturtures*/
#include <fstream>
using namespace std;
struct br_node{
    //struct for red-black tree
    //1 for red and 0 for black
    int numid = 0;
    int executed_time = 0;
    int total_time = 0;
    br_node * l=nullptr;//left child
    br_node * r=nullptr;//right child
    br_node *p=nullptr;//parent
    int col = 0;
    int heapid;    
};
struct heap_node{
    //structure for heap nodes.
    int numid = 0;
    int executed_time = 0;
    int total_time = 0;
    br_node *pointer;//pointer to node in black-red tree
};
struct command{
    //struct for input command
    int time;
    int param1;
    int param2;//rewrite Print(param1) as Print(param1,param2),param1 = param2
    char func_flag;// I for insert and P for Print
};
class br_tree;
class min_heap{
    heap_node list[2000];//start from 0
    ofstream *file;
    public:        
        int num= 0;//current buildings in heap.
        int flag= 0;//1 if all command has been run,otherwise 0
        int act_num= 0;//current buildings in heap including not heapified part
        int building =0;//time for which has woked on current building
        void set_output(ofstream*);
        void insert(heap_node,int);// return heap_id
        void heapify(int id);// keep the properties of min-heap
        int pop(br_tree &,int);//remove the node with min val,pop the id
        int update_root();/*return 1 or 0, -1 means building has finished.
        1:still need to work on this building;0:have worked on the building for 5 days;
        -1: the building is completed*/
        void update_pointer(int ,br_node*);
        void write(int, int);//print output
        heap_node get(int);//get corresponding node
};
class br_tree{
    br_node * root=0;
    ofstream *file;
    br_node *list[2000];
    min_heap *heap;
    int next=-1;
    public:
        void set_output(ofstream*);
        void set_heap(min_heap*);
        void swap_node(br_node*,br_node*);//swap heapid and info triplet of two nodes;
        br_node* lookup(br_node* ,int);
        bool insert(br_node*);// if success return ture otherwise false;
        void del(br_node*);//delete building from ds
        bool print(int,int); //lb<=ub print node id s.t. lb<=id<=ub,true for has node in the range,otherwise false
        bool print_at(int,int,br_node*);//start at node,true for no node in the range
        void queue(br_node*);
        void write();//print output
        void raise_error(command );//raise repeat num id error
        void check_bottom_up(br_node*);//check if there are two consequent red nodes
        void deal_deficient(br_node*);//deal deficient
        void change_parent(br_node*py,br_node*v);//change v's parent to py's parent
        //cases of dealing deficiency
        void deal_Lrn(br_node *py,br_node*v,br_node*y);
        void deal_Rrn(br_node *py,br_node*v,br_node*y);
        void deal_Lbn(br_node *py,br_node*v,br_node*y);
        void deal_Rbn(br_node *py,br_node*v,br_node*y);
        //v is black
        void del_Xb0_case(br_node*py,br_node*v,br_node*y);
        void del_Rb1_case1(br_node*py,br_node*v,br_node*y);
        void del_Lb1_case1(br_node*py,br_node*v,br_node*y);
        void del_Rb1_case2(br_node*py,br_node*v,br_node*y);
        void del_Lb1_case2(br_node*py,br_node*v,br_node*y);
        //v is red
        void del_Rr0_case(br_node *py,br_node*v,br_node*y);
        void del_Lr0_case(br_node*py,br_node*v,br_node*y);
        void del_Rr1_case1(br_node*py,br_node*v,br_node*y,br_node*w);
        void del_Lr1_case1(br_node*py,br_node*v,br_node*y,br_node*w);
        void del_Rr1_case2(br_node*py,br_node*v,br_node*y,br_node*w);
        void del_Lr1_case2(br_node*py,br_node*v,br_node*y,br_node*w);
};



