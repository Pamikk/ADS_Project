/*implement class functions of datastructure
funtion of class functions are descripted in ds.h*/
#include"ds.h"
#include <math.h> 
#include<iostream>
using namespace std;
//helper funcs
bool cmp_heap(heap_node a,heap_node b){
    //bool if a is defined as greater than b
    //a with greater executed_time and greater numid when executed_time equals
    if (a.executed_time>b.executed_time){
        return true;
    }else if ((a.executed_time == b.executed_time) and (a.numid > b.numid)){
        return true;
    }
    else return false;
}
void br_tree::change_parent(br_node*py,br_node*v){
    br_node *gp = py->p;
    if (gp == 0){
        //py is root
        root = v;
        v->p = 0;
    }else{
        cout<<"change_parent:"<<gp->numid<<','<<v->numid<<endl;
        if (py==gp->l){
            gp->l = v;
            v->p = gp;
        }else{
            if (py==gp->r){
                gp->r = v;
                v->p = gp;
            }else{
                cout<<"gp:"<<gp->numid<<endl;
                cout<<"gp is not p of py,wtf?"<<endl;
            }
        }
    }
}
void br_tree::del_Xb0_case(br_node*py,br_node*v,br_node*y){
    //Lb0 or Rb0
    cout<<"Xb0"<<endl;
    if (py->col == 0){
        //py is black
        v->col = 1;
        deal_deficient(py);//need to continue
    }else
    {
        py->col =0;
        v->col = 1;
    }   
}
void br_tree::del_Rb1_case1(br_node*py,br_node*v,br_node*y){
    cout<<"Rb1_case1"<<endl;
    br_node* a = v->l;
    br_node* b = v->r;
    change_parent(py,v);
    cout<<v->numid<<endl;
    v->r = py;
    py->p = v;
    py->l =b;
    if (b!=0){b->p = py;}
    //rotation
    cout<<"after rotation"<<endl;
    if (a==0){cout<<"why Rb1"<<endl;}
    a->col = 0;
    v->col = py->col;
    py->col = 0;
    //coloring
}
void br_tree::del_Lb1_case1(br_node*py,br_node*v,br_node*y){
    cout<<"Lb1_case1"<<endl;
    br_node* a = v->r;
    br_node* b = v->l;
    change_parent(py,v);
    v->l = py;
    py->p = v;
    py->r = b;
    if (b!=0){b->p = py;}
    //rotation
    a->col = 0;
    v->col = py->col;
    py->col = 0;
    //coloring
}
void br_tree::del_Rb1_case2(br_node*py,br_node*v,br_node*y){
    cout<<"Rb1_case2 or Rb2"<<endl;
    br_node* w = v->r;
    br_node* a = v->l;
    br_node* b = w->l;//as w is red, not empty
    br_node* c = w->r;
    change_parent(py,w);
    w->r = py;
    py->p = w;
    w->l = v;
    v->p = w;
    py->l = c;
    if (c!=0){c->p = py;}
    v->r = b;
    if (b!=0){b->p = v;}
    //rotation
    w->col = py->col;
    py->col = 0;
}

void br_tree::del_Lb1_case2(br_node*py,br_node*v,br_node*y){
    cout<<"Lb1_case2 or Lb2"<<endl;
    br_node* w = v->l;
    br_node* a = v->r;
    br_node* b = w->r;//as w is red, not empty
    br_node* c = w->l;
    change_parent(py,w);
    w->l = py;
    py->p = w;
    w->r = v;
    v->p = w;
    py->r = c;
    if (c!=0){c->p = py;}
    v->l = b;
    if (b!=0){b->p = v;cout<<v->numid<<endl;}
    //rotation
    w->col = py->col;
    py->col = 0;
}

void br_tree::deal_Lbn(br_node*py,br_node*v,br_node*y){
    cout<<"deal Lbn"<<endl;
    if (v->l==nullptr){
        if (v->r==nullptr){
            //no child Lb0
            del_Xb0_case(py,v,y);
        }else{
            //Lb1
            if (v->r->col==1){
                del_Lb1_case1(py,v,y);
            }
            else{
                cout<<"left null right not red?"<<endl;
                del_Xb0_case(py,v,y);
            }
        }
    }else{
        if (v->l->col ==1){
            //Lb2 or Lb1_case2
            del_Lb1_case2(py,v,y);
        }else{
            if (v->r==nullptr){
                cout<<"left black right null?"<<endl;
            }else{
                if (v->r->col==0){
                    del_Xb0_case(py,v,y);
                }else{
                    del_Lb1_case1(py,v,y);
                }
            }
        }
    }
}
void br_tree::deal_Rbn(br_node*py,br_node*v,br_node*y){
    cout<<"deal Rbn"<<endl;
    if (v->r==nullptr){
        if (v->l==nullptr){
            //no child Lb0
            del_Xb0_case(py,v,y);
        }else{
            //Rb1
            if (v->l->col==1){
                del_Rb1_case1(py,v,y);
            }
            else{
                cout<<"right null left not red?"<<endl;
                del_Xb0_case(py,v,y);
            }
        }
    }else{
        if (v->r->col ==1){
            //Rb2 or Rb1_case2
            del_Rb1_case2(py,v,y);
        }else{
            if (v->l==nullptr){
                cout<<"right black left null?"<<endl;
            }else{
                if (v->l->col==0){
                    del_Xb0_case(py,v,y);
                }else{
                    del_Rb1_case1(py,v,y);
                }
            }
        }
    }
}
void br_tree::del_Rr0_case(br_node *py,br_node*v,br_node*y){
    cout<<"Rr0"<<endl;
    br_node * a = v->l;
    br_node * b = v->r;
    change_parent(py,v);
    v->r = py;
    py->p = v;
    py->l = b;
    b->p = py;
    //rotation
    v->col = 0;
    b->col = 1;
}
void br_tree::del_Lr0_case(br_node *py,br_node*v,br_node*y){
    cout<<"Lr0"<<endl;
    br_node * a = v->r;
    br_node * b = v->l;
    change_parent(py,v);
    v->l = py;
    py->p = v;
    py->r = b;
    b->p = py;
    //rotation
    v->col = 0;
    b->col = 1;
}
void br_tree::del_Rr1_case1(br_node*py,br_node*v,br_node*y,br_node*w){
    cout<<"Rr1 case1"<<endl;
    br_node * b = w->l;
    br_node * c = w->r;
    change_parent(py,w);
    w->l = v;
    v->p = w;
    w->r = py;
    py->p = w;
    v->r = b;
    b->p = v;
    py->l = c;
    if (c!=0)c->p = py;
    //rotation
    b->col =0;
}
void br_tree::del_Lr1_case1(br_node*py,br_node*v,br_node*y,br_node*w){
    cout<<"Lr1 case1"<<endl;
    br_node * b = w->r;
    br_node * c = w->l;
    change_parent(py,w);
    w->r = v;
    v->p = w;
    w->l = py;
    py->p = w;
    v->l = b;
    b->p = v;
    py->r = c;
    if (c!=0)c->p = py;
    //rotation
    b->col =0;
}
void br_tree::del_Rr1_case2(br_node*py,br_node*v,br_node*y,br_node*w){
    cout<<"Rr1 case2 or Rr2"<<endl;
    br_node * x = w->r;
    br_node * c = x->l;
    br_node * d = x->r;
    change_parent(py,x);
    x->l = v;
    v->p = x;
    x->r = py;
    py->p = x;
    w->r = c;
    if (c!=0) c->p = w;
    py->l = d;
    if (d!=0)d->p = py;
    //rotation
    x->col =0;
}
void br_tree::del_Lr1_case2(br_node*py,br_node*v,br_node*y,br_node*w){
    cout<<"Lr1 case2 or Lr2"<<endl;
    br_node * x = w->l;
    br_node * c = x->r;
    br_node * d = x->l;
    change_parent(py,x);
    x->r = v;
    v->p = x;
    x->l = py;
    py->p = x;
    w->l = c;
    if (c!=0) c->p = w;
    py->r = d;
    if (d!=0)d->p = py;
    //rotation
    x->col =0;
}
void br_tree::deal_Rrn(br_node *py,br_node*v,br_node*y){
    br_node* w = v->r;
    cout<<"deal Rrn"<<endl;
    if (w==0){cout<<"not deficient?"<<endl;}
    if (w->r==nullptr){
        if (w->l==nullptr){
            //no child Lb0
            del_Rr0_case(py,v,y);
        }else{
            //Rr1
            if (w->l->col==1){
                del_Rr1_case1(py,v,y,w);
            }
            else{
                cout<<"right null left not red?"<<endl;
                del_Rr0_case(py,v,y);
            }
        }
    }else{
        if (w->r->col ==1){
            //Rb2 or Rb1_case2
            del_Rr1_case2(py,v,y,w);
        }else{
            if (w->l==nullptr){
                cout<<"right black left null?"<<endl;
            }else{
                if (w->l->col==0){
                    del_Rr0_case(py,v,y);
                }else{
                    del_Rr1_case1(py,v,y,w);
                }
            }
        }
    }
}
void br_tree::deal_Lrn(br_node *py,br_node*v,br_node*y){
    br_node* w = v->l;
    cout<<"deal Rrn"<<endl;
    if (w==0){cout<<"not deficient?"<<endl;}
    if (w->l==nullptr){
        if (w->r==nullptr){
            //no child Lb0
            del_Lr0_case(py,v,y);
        }else{
            //Lr1
            if (w->r->col==1){
                del_Lr1_case1(py,v,y,w);
            }
            else{
                cout<<"right null left not red?"<<endl;
                del_Lr0_case(py,v,y);
            }
        }
    }else{
        if (w->l->col ==1){
            //Lr2 or Lr1_case2
            del_Lr1_case2(py,v,y,w);
        }else{
            if (w->r==nullptr){
                cout<<"right black left null?"<<endl;
            }else{
                if (w->r->col==0){
                    del_Lr0_case(py,v,y);
                }else{
                    del_Lr1_case1(py,v,y,w);
                }
            }
        }
    }
}

void br_tree::set_output(ofstream *f){
    file = f;
}
void br_tree::set_heap(min_heap *h){
    heap = h;
}
void br_tree::swap_node(br_node*a,br_node*b){
    //swap value of node
    br_node tmp = *a;
    a->executed_time = b->executed_time;
    a->total_time = b->total_time;
    a->numid = b->numid;
    a->heapid = b->heapid;
    b->executed_time = tmp.executed_time;
    b->total_time = tmp.total_time;
    b->numid = tmp.numid;
    b->heapid = tmp.heapid;
    (*heap).update_pointer(a->heapid,a);
    (*heap).update_pointer(b->heapid,b);
    if(a->numid == b->numid){cout<<"error"<<endl;}
}
void br_tree::write(){
    if (next==-1){
        *file<<"(0,0,0)"<<endl;
    }else{
        br_node *node = list[0];
        *file<<'('<<node->numid<<','<<node->executed_time<<','<<node->total_time<<')';
        for (int i=1;i<=next;i++){
            node = list[i];
            *file<<','<<'('<<node->numid<<','<<node->executed_time<<','<<node->total_time<<')';
        }
        *file<<endl;
    }
    next=-1;
}

void br_tree::raise_error(command cur){
    *file<<"repeated Building numId: "<<cur.param1<<"at time: "<<cur.time<<endl;
}

br_node* br_tree::lookup(br_node* node,int id){
    cout<<"lookup"<<node->numid<<','<<node->col<<endl;
    if (id == node->numid){
        //founded
        return node;
    }else{
        if (id < node->numid){
            //smaller,move to left
            if (node->l!= nullptr){
                //has left child,iterate
                return lookup(node->l,id);
            }
            else{
                //return cur node
                return node;
            }
        }else{
            //greater,move to right
            if (node->r!=nullptr){
                //has right child
                return lookup(node->r,id);
            }
            else return node;
        }
    }
}

void br_tree::get_root(){
    cout<<root->numid<<endl;
}
bool br_tree::insert(br_node* node){
    if (root == nullptr){
        //tree is empty
        root = node;
        return true;
    }else{
        node->col = 1;//set as red node
        br_node *par = lookup(root,node->numid);//find parent
        if (par->numid == node->numid){
            //numid existed
            if (par->p!=0){
                cout<<"repeated par:"<<par->p->numid<<endl;
            }
            else{
                cout<<"root:"<<root->numid<<' '<<par->numid<<endl;
            }
            return false;//insert failure
        }else if (par->numid > node->numid){
            //insert left
            par->l = node;
        }else par->r = node;
        node->p = par;
        if (par->col==1){
            //parent is red
            check_bottom_up(node);
            //adjust to keep propety
        }
    }
    if (node->p!=0){
        cout<<node->numid<<' '<<node->p->numid<<' '<<node->col<<node->p->col<<endl;
        if (node->p->p!=0){
            cout<<"gp"<<node->p->p->numid<<endl;
        }
    }
    else{
        cout<<"root:"<<node->numid<<' '<<node->col<<endl;
    }
    return true;
}

void br_tree::check_bottom_up(br_node* node){
    cout<<node->numid<<endl;
    br_node*par = node->p;
    if (par->col == 0){
        //parent is black
        return;
    }
    br_node *gp = par->p;
    //grand parent
    if (par->numid<gp->numid){
        //parent on the left
        if (gp->r!=nullptr){
            if (gp->r->col == 1){
                //XYr,color fliping
                cout<<"XYr,L"<<endl;
                par->col = 0;
                gp->col = 1;
                gp->r->col = 0;
                if (gp->numid == root->numid){
                    //gp is root
                    gp->col = 0;
                    return;
                }else{
                    //continue rebalancing
                    check_bottom_up(gp);
                    return;
                }
            }    
        }
        if (node->numid<par->numid){
            //LLb
            cout<<"LLb"<<endl;
            if (gp->numid == root->numid){
                //gp is root
                root = par;                   
                par->p =nullptr;                 
            }else{
                br_node *gpp = gp->p;
                if (gp->numid<gpp->numid){
                    //gp on the left
                    gpp->l = par;
                }else{
                    gpp->r = par;
                }
                par->p = gpp;
            }
            gp->l = par->r;
            if (par->r!=0){par->r->p = gp;}
            par->r = gp;
            gp->p = par;            
            //rotation
            par->col = 0;
            gp->col = 1;
            //coloring
        }else{
            //LRb
            cout<<"LRb"<<endl;
            if (gp->numid == root->numid){
                //gp is root
                root = node;                   
                node->p =nullptr;                 
            }else{
                br_node *gpp = gp->p;
                if (gp->numid<gpp->numid){
                    //gp on the left
                    gpp->l = node;
                }else{
                    gpp->r = node;
                }
                node->p = gpp;
            }
            gp->l = node->r;
            if(node->r!=0){node->r->p = gp;}
            par->r = node->l;
            if(node->l!=0){node->l->p = par;}
            node->l = par;
            node->r = gp;
            gp->p = node;
            par->p = node;
            //rotation
            node->col = 0;
            gp->col = 1;
            //coloring
        }
    }else{
        //parent on the right
        if (gp->l!=0){
            if (gp->l->col == 1){
                cout<<"XYr,R"<<endl;
                //XYr,color fliping
                par->col = 0;
                gp->col = 1;
                gp->l->col = 0;
                if (gp->numid == root->numid){
                    //gp is root
                    gp->col = 0;
                    return;
                }else{
                    //continue rebalancing
                    check_bottom_up(gp);
                    return;
                }
            }    
        }
        if (node->numid>par->numid){
            //RRb
            cout<<"RRb"<<endl;
            if (gp->numid == root->numid){
                //gp is root
                root = par;                   
                par->p =nullptr;                 
            }else{
                br_node *gpp = gp->p;
                if (gp->numid<gpp->numid){
                    //gp on the left
                    gpp->l = par;
                }else{
                    gpp->r = par;
                }
                par->p = gpp;
            }
            gp->r = par->l;
            if(par->l!=0){par->l->p = gp;}
            par->l = gp;
            gp->p = par;
            //rotation
            par->col = 0;
            gp->col = 1;
            //coloring
        }else{
            //RLb
            cout<<"RLb"<<endl;
            if (gp->numid == root->numid){
                //gp is root
                root = node;                   
                node->p =nullptr;                 
            }else{
                br_node *gpp = gp->p;
                if (gp->numid<gpp->numid){
                    //gp on the left
                    gpp->l = node;
                }else{
                    gpp->r = node;
                }
                node->p = gpp;
            }
            gp->r = node->l;
            if (node->l!=0){node->l->p = gp;}
            par->l = node->r;
            if (node->r!=0){node->r->p=par;}
            gp->p = node;
            par->p = node;
            node->r = par;
            node->l = gp;
            
            //rotation
            node->col = 0;
            gp->col = 1;
            //coloring
        }
    }
    return;
}

void br_tree::del(br_node *node){
    cout<<node->numid<<endl;
    br_node* par = node->p;    
    if ((node->r!=nullptr)and(node->l!=nullptr)){
        cout<<"deg2:"<<node->numid<<' '<<node->r->numid<<' '<<node->l->numid<<endl;
        //a node with degree 2
        br_node * rep = lookup(node->r,node->numid);//replaced with leftmost node in right subtree
        cout<<"rep:"<<rep->numid<<endl;
        if (rep->r!=0){
            cout<<rep->r->numid<<endl;
        }
        //leftmost numid >= node->numid+1
        cout<<"deg2:"<<rep<<' '<<node->p<<' '<<node->l->numid<<endl;
        if (rep->p->l!=0){cout<<"sibling:"<<rep->p->l->numid<<endl;}
        if (rep->p->r!=0){cout<<"sibling1:"<<rep->p->r->numid<<endl;}   
        swap_node(rep,node);
        //copying from replaced node
        cout<<"deg2:"<<rep->p<<' '<<node<<' '<<node->l->numid<<endl;        
        del(rep);
        //delete replaced node
    }else{
        cout<<"degree<2:"<<node->numid<<' '<<node->col<<','<<par<<endl;
        br_node * child;
        if (node->r == nullptr){
            child = node->l;
        }
        else{
            child = node->r;
        }
        if (node->numid == root->numid){
            //node is root
            if (child!=0){child->col = 0;}
            root = child;
            delete(node);
        }else{
            if (node->col == 1){
                //tbd is red
                //one degree red node
                if (node==par->l){
                    //node on the left
                    par->l = child;   
                }else{
                    par->r = child; 
                }
                if (child!=nullptr){
                    child->p = par; 
                    cout<<"repchild:"<<child->numid<<endl;               
                }
                cout<<par->numid<<endl;             
            }else{
                //tbd is black
                if (child!=nullptr){
                    cout<<"repchild:"<<child->numid<<','<<par->numid<<','<<par<<endl;
                    if (child->col==0){
                        cout<<"???"<<child->numid<<endl;
                        //deal_deficient(node);
                    }
                    if (node==par->l){
                        //node on the left
                        par->l = child;  
                    }else{
                        par->r = child;
                        cout<<"rightrep:"<<child<<','<<par->r<<endl;
                    }
                    child->p = par;
                    cout<<child->p<<endl;
                    child->col = 0;                    
                }else{
                    deal_deficient(node);
                    if (node->p->l==node){
                        cout<<"left:"<<node->p->l->numid<<endl;
                        node->p->l = nullptr;
                    }else{
                        cout<<"right:"<<node->p->r->numid<<endl;
                        node->p->r = nullptr;
                    }
                    cout<<"finish"<<endl;
                }
            }
            cout<<"node:"<<node->numid<<"par:"<<node->p->numid<<endl;
            delete(node);
        }
    }
    cout<<"finish delete"<<endl;
}

void br_tree::deal_deficient(br_node *node){
    cout<<"deficient:"<<node->numid<<','<<root->numid<<','<<node->p<<endl;
    if (node->numid == root->numid){
        cout<<"deficient tree"<<endl;
        return;
    }else{
        br_node * par = node->p;
        br_node * sibling;        
        if (node == par->r){            
            //node on the right
            sibling = par->l;
            cout<<sibling<<endl;
            if (sibling ==0){cout<<"one black the other null?"<<endl;}
            cout<<"deficientR:"<<node->numid<<' '<<sibling->numid<<' '<<par->numid<<endl;
            if (sibling->col == 0){
                //Rbv 
                deal_Rbn(par,sibling,node);
            }else{
                //Rrn
                deal_Rrn(par,sibling,node);
            }
        }else{
            sibling = par->r;
            if (sibling ==0){cout<<"one black the other null?"<<endl;}
            cout<<"deficientL:"<<node->numid<<' '<<sibling->numid<<' '<<par->numid<<endl;
            if (sibling->col == 0){
                //Lbv 
                deal_Lbn(par,sibling,node);
            }else{
                //Lrn
                deal_Lrn(par,sibling,node);
            }
        }
    }
    cout<<"finish dealing"<<endl;
}
bool br_tree::print(int lb,int ub){
    if (root==0){return true;}
    int val = root->numid;
    cout<<"print:"<<val<<','<<root->col<<endl;
    if (lb<=val){
        if (ub>=val){
            print_at(lb,val,root->l);
            queue(root);
            print_at(val,ub,root->r);
            return false;
        }else
        {
            return print_at(lb,ub,root->l);
        }        
    }else{
         return print_at(lb,ub,root->r);
    }
}

bool br_tree::print_at(int lb,int ub,br_node*node){
    if (node==0){return true;}    
    int val = node->numid;
    cout<<"print:"<<val<<','<<node->col<<endl;
    if (lb<=val){
        if (ub>=val){
            print_at(lb,val,node->l);
            queue(node);
            print_at(val,ub,node->r);
            return false;
        }else
        {
            return print_at(lb,ub,node->l);
        }        
    }else{
         return print_at(lb,ub,node->r);
    }    
}

void br_tree::queue(br_node *node){
    next+=1;
    list[next] = node;
}


//min-heap functions
void min_heap::insert(heap_node node,int i){
    if ((i==0)and(num==0)){
        list[0] = node;
        list[0].pointer->heapid = 0;
        num+=1;
        return;
    }
    int p = floor((i+1)/2)-1;//parent node
    heap_node tmp;
    if (cmp_heap(list[p],node)){
        if ((p>0) or (building==0)){
            //not the root node or root node is not under construction
            list[i] = list[p];
            list[i].pointer->heapid = i;
        }
        else{
            //root node but is under construction
            node.pointer->heapid = i;
            list[i] = node;            
            num+=1;
            return;
        }
        if (p==0){
            //root node but not under construction
            node.pointer->heapid = p;
            list[p] = node;            
            num+=1;
        }
        else{
            insert(node,p);
            //insert recursively
        }
    }else{
        node.pointer->heapid = i;
        list[i] = node;
        num+=1;
        
    }
    return;
}

int min_heap::pop(br_tree & tree){
    int id = list[0].numid;
    br_node * p = list[0].pointer;
    cout<<"start del from brtree"<<p->numid<<' '<<p->heapid<<' '<<id<<' '<<num<<endl;
    tree.del(p);   
    num-=1;
    list[0] = list[num];//move the last node to the root
    if (num==0){
        return id;
    }
    heapify(0);//keep min-heap     
    return id;
}

void min_heap::heapify(int id){
    int l = (id+1)*2-1;
    int r = (id+1)*2;
    if (l>=num){
        return;//no valid child
    }
    heap_node tmp;
    if (r<num){
        //node has valid right child
        if (cmp_heap(list[id],list[l])){
            //left is smaller than
            if (cmp_heap(list[r],list[l])){
                //left is the smallest
                tmp = list[id];
                list[id] = list[l];
                list[l] = tmp;
                list[id].pointer->heapid = id;
                list[l].pointer->heapid = l;
                //update heap pointer
                heapify(l);
            }else{
                //right is the smallest
                tmp = list[id];
                list[id] = list[r];
                list[r] = tmp;
                list[id].pointer->heapid = id;
                list[r].pointer->heapid = r;
                //update heap pointer
                heapify(r);
            }
        }else{
            if (cmp_heap(list[id],list[r])){
                //right is the smallest
                tmp = list[id];
                list[id] = list[r];
                list[r] = tmp;
                list[id].pointer->heapid = id;
                list[r].pointer->heapid = r;
                //update heap pointer
                heapify(r);
            }
        }
    }else{
        if (cmp_heap(list[id],list[l])){
            //left is smaller
            tmp = list[id];
            list[id] = list[l];
            list[l] = tmp;
            list[id].pointer->heapid = id;
            list[l].pointer->heapid = l;
            //update heap pointer
        }
    }
    return;
}

int min_heap::update_root(){
    int flag=1;
    building +=1;
    list[0].executed_time+=1;
    list[0].pointer->executed_time+=1;
    if (building==5){
        building=0;
        flag = 0;
    }
    if (list[0].executed_time == list[0].total_time){
        building = 0;
        flag= -1;
    }else{
        if  (list[0].executed_time > list[0].total_time){
            building = 0;
            cout<<"why not pop earlier..."<<endl;
            cout<<list[0].numid;
            flag=-1;
        }
    }
    //cout<<list[0].numid<<' '<<list[0].executed_time<<endl;
    return flag;
}

void min_heap::update_pointer(int id,br_node*p){
    list[id].pointer = p;
}