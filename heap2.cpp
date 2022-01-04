#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data, degree;
    Node *child, *sibling, *parent;
};
Node* newNode(int key) { 
    Node *temp = new Node; 
    temp->data = key; 
    temp->degree = 0; 
    temp->child = temp->parent = temp->sibling = NULL; 
    return temp; 
} 
Node* mergeBinomialTrees(Node* b1,Node* b2){
    if(b1->data > b2->data){
        swap(b1,b2);
    }
    b2->parent=b1;
    b2->sibling=b1->child;
    b1->child=b2;
    b1->degree++;
    return b1;
}
list<Node*> unionBinomialHeap(list<Node*> h1, list<Node*> h2){
    list<Node*> _new;
    list<Node*>::iterator it=h1.begin();
    list<Node*>::iterator ot=h2.begin();
    while(it!=h1.end() && ot!=h2.end()){
        if((*it)->degree<=(*ot)->degree){
            _new.push_back(*it);
            it++;
        }
        else
        {
            _new.push_back(*ot);
            ot++;
        }
    }
    while(it!=h1.end()){
        _new.push_back(*it);
        it++;
    }
    while(ot!=h2.end()){
        _new.push_back(*ot);
        ot++;
    }
    return _new;
}
list<Node*> adjust(list<Node*> heap){
    if(heap.size()<=1){
        return heap;
    }
    list<Node*>::iterator it1,it2,it3;
    it1=it2=it3=heap.begin();
    if(heap.size()==2){
        it2=it1++;
        it2=it3;
    }
    else{
        it2++;
        it3=it2++;
    }
    while(it1!=heap.end()){
        if(it2 == heap.end()){
            it1++;
        }
        else if((*it1)->degree<(*it2)->degree)
        {
            it1++;
            it2++;
            if(it3!=heap.end())
                it3++;
        }
        else if(it3!=heap.end() and ((*it1)->degree==(*it2)->degree) and (*it1)->degree==(*it3)->degree){
            it1++;
            it2++;
            it3++;
        }
        else if((*it1)->degree==(*it2)->degree){
            Node* temp;
            *it1=mergeBinomialTrees(*it1,*it2);
            it2=heap.erase(it2);
            if(it3 != heap.end())
                it3++;
        }        
    }
            return heap;
}

  
list<Node*> insertaTreeInHeap(Node *tree, list<Node*> heap){
    list<Node*> temp;
    temp.push_back(tree);
    temp=unionBinomialHeap(heap,temp);
    return adjust(temp);
}

list<Node*> insert(list<Node*> heap,int key){
    Node* nod=newNode(key);
    heap=insertaTreeInHeap(nod,heap);
    return heap;
}

list<Node*> removeMinfromTreeBHeap(Node* tree){
    list<Node*> heap;
    Node* temp=tree->child;
    Node *lo;

    while(temp){
        lo=temp;
        temp=temp->sibling;
        lo->sibling=NULL;
        heap.push_front(lo);
    }
    return heap;
} 

Node* getMin(list<Node*> heap){
    Node* temp;
    list<Node*>:: iterator it=heap.begin();
    temp=*it;
    while(it!= heap.end()){
        if((*it)->data<temp->data)
            temp=*it;
        it++;
    }
    return temp;
}

list<Node*> extractMin(list<Node*> heap){
    list<Node*> new_heap,lo;
    Node *temp=getMin(heap);
    list<Node*>::iterator it=heap.begin();
    while(it!=heap.end()){
        if(*it!=temp){
            new_heap.push_back(*it);
        }
        it++;
    }
    lo=removeMinfromTreeBHeap(temp);
    new_heap=unionBinomialHeap(lo,new_heap);
    
    return adjust(new_heap);
}

void printTree(Node* h){
    while(h){
        cout<<h->data<<" ";
        printTree(h->child);
        h=h->sibling;
    }
}

void printHeap(list<Node*> heap){
    list<Node*> :: iterator it=heap.begin();
    it=heap.begin();
    while(it!=heap.end()){
        printTree(*it);
        it++;
    }
}

Node* findNodeinTree(Node* h,int val){
    if(h==NULL)
        return NULL;
    // cout<<endl<<"value"<<h->data<<endl;

    if (h->data == val){ 
        // cout<<"hi";
        return h;
    }
    
    Node *res = findNodeinTree(h->child,val);
    if(res!=NULL)
        return res;
    
    return findNodeinTree(h->sibling,val);
}
Node* findNodeinHeap(list<Node*> heap,int val){
    list<Node*>::iterator it=heap.begin();
    while(it!=heap.end()){
        Node* node=findNodeinTree(*it,val);
        // printTree(*it);
        // cout<<endl;
        if(node !=NULL)
            return node;
        it++;
    }
    return NULL;
}
void decreaseKeyBHeap(list<Node*>H,int old_val,int new_val)
{
    Node* node= findNodeinHeap(H, old_val);
    if(node==NULL)
        return;
    
    node->data=new_val;
    Node *parent = node->parent;

    while(parent!=NULL && parent->data>node->data){
        swap(node->data,parent->data);
        node=parent;
        parent=parent->parent;
    }
}

list<Node*> DeleteNodefromHeap(list<Node*> heap,int val){
    decreaseKeyBHeap(heap,val,INT_MIN);
    return extractMin(heap);
}
int main()
{
    int ch,key;
    list<Node*> heap;    
    heap=insert (heap,10);
    heap=insert (heap,20);
    heap=insert (heap,30);
    heap=insert (heap,40);
    heap=insert (heap,50);
    heap=insert (heap,60);
    cout<<"The Elements of the heap after insertion are"<<endl;
    printHeap(heap);
    Node* temp=getMin(heap);
    cout << "\nMinimum element of heap "<< temp->data << "\n"; 
    heap=extractMin(heap);
    cout << "Heap after deletion of minimum element\n";
    printHeap(heap);
    heap=DeleteNodefromHeap(heap,30);
    cout<< "\nHeap after deleting element 30:"<<endl;
    printHeap(heap);
    cout<<endl;
    return 0;

}
