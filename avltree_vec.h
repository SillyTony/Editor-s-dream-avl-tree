#ifndef AVLTREE_VEC_H
#define AVLTREE_VEC_H

#include"node.h"
#include <algorithm>
#include<vector>

enum printorder{in, pre, post};
template<typename T>
class avltree
{
public:
    avltree();
    ~avltree();
    avltree(const avltree<T> & other);
    avltree& operator=(const avltree<T>& other);

    void insert(T &data,int &lineNumber, int& ParagraphNumber);

    avltree<T>& operator<<(node<T>& other );

    void rightRotate(node<T>* & r);
    void leftRotate(node<T>* & r);
    int height(node<T>* & r);
    int theDepth();

    node<T>& theal(int pos);
    bool balanced();
    node<T>& theRoot();

    void printInOrder();


    bool find(T data);
    int findTheLeftMost(node<T> & n);
    int findTheRightMost(node<T> & n);
    int depth(int i);
    int totalNodes();
    void killNode(node<T>* & r);
    int totalNumItems();

    void printOut(node<T>* & n);

    void write(node<T>* &r);
    int rebalance(node<T>* &r);

    void popularWord(vector<pair<int, string> > &popularWords);

    void nukem();

    bool remove(T data);

    template<typename U>
    friend
    ostream& operator<<(ostream& out, avltree<U> avl);

    template<typename U>
    friend
    istream& operator >> (istream & in, avltree<U> avl);

private:

    vector< node<T>* > al;
    node<T>* root;
    void copy(const avltree<T> &);
    void clear();
    bool valid(node<T>* & r);


};

template<typename T>
avltree<T>::avltree()
{
    root=new node<T>();
}

template<typename T>
avltree<T>::~avltree()
{
    nukem();
}

template<typename T>
avltree<T>::avltree(const avltree<T> & other)
{
    copy(other);
}

template<typename T>
void avltree<T>::popularWord( vector<pair<int,string> >& popularWords)
{
    for(int i = 0; i < al.size(); i++)
    {
        if(popularWords.size() < 10 || (al[i]->getCount() > popularWords[popularWords.size()-1].first))
        {
            popularWords.push_back(make_pair(al[i]->getCount(),al[i]->getData()));
            for(int i = popularWords.size()-1; i > 0; i--)
                if(popularWords[i].first > popularWords[i-1].first)
                    swap(popularWords[i],popularWords[i-1]);
        }
    }

    while(popularWords.size() > 10)
        popularWords.pop_back();
}

template<typename T>
avltree<T>& avltree<T>::operator=(const avltree<T>& other)
{
    if(this!=&other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
void avltree<T>::printInOrder()
{
    if(!al.size())
        return;

    int pos=root->getSelfIndex();
    write(al[pos]);

}

template<typename T>
void avltree<T>::rightRotate(node<T>* & r)
{

    int ancestor = r->getParentIndex();
    int kid = r->getRightIndex();
    int offSpring = al[kid]->getLeftIndex();

    if(ancestor == -1)
    {
        root=al[kid];
    }
    else
    {
        if(*r < *al[ancestor])
        {
            al[ancestor]->setRight(kid);
        }
        else
        {
            al[ancestor]->setLeft(kid);

        }
    }

    al[kid]->setParent(ancestor);

    r->setRight(offSpring);
    if(offSpring!=-1)
        al[offSpring]->setParent(r->getSelfIndex());

    if(kid!=-1)
        al[kid]->setLeft(r->getSelfIndex());
    r->setParent(kid);
}
template<typename T>
void avltree<T>::leftRotate(node<T>* & r)
{
    int ancestor = r->getParentIndex();
    int kid = r->getLeftIndex();
    int offSpring = al[kid]->getRightIndex();

    if(ancestor == -1)
    {
        root=al[kid];
    }
    else
    {
        if(*r < *al[ancestor])
        {
            al[ancestor]->setRight(kid);
        }
        else
        {
            al[ancestor]->setLeft(kid);
        }
    }
    al[kid]->setParent(ancestor);

    r->setLeft(offSpring);
    if(offSpring!=-1)
        al[offSpring]->setParent(r->getSelfIndex());

    if(kid!=-1)
        al[kid]->setRight(r->getSelfIndex());
    r->setParent(kid);
}


template<typename T>
void avltree<T>::insert(T &data,int& lineNumber, int& paragraphNumber)
{

    int index=al.size();

    int current=root->getSelfIndex();
    int previous=-1;

    if(index==0)
    {
        al.push_back(new node<T>(data,index,current));
        al[index]->setposition(lineNumber,paragraphNumber);
        al[index]->increaseCount();
        root=al[index];
        return;
    }
    while(1)
    {
        if(current==-1)
        {
            al.push_back(new node<T>(data,index,previous));
            al[index]->setposition(lineNumber,paragraphNumber);
            al[index]->increaseCount();

            if(*al[previous] > *al[index])
                al[previous]->setRight(index);
            else
                al[previous]->setLeft(index);


            break;
        }
        else if(data < al[current]->getData())
        {
            previous=current;
            current=al[current]->getRightIndex();
        }
        else if(data == al[current]->getData())
        {
            al[current]->setposition(lineNumber,paragraphNumber);
            al[current]->increaseCount();
            return;
        }
        else
        {
            previous=current;
            current=al[current]->getLeftIndex();
        }
    }

    root = al[rebalance(al[index])];
}

template<typename T>
bool avltree<T>::remove(T data)
{
    if(!find(data))
    {
        cout<<"the data "<<data<<" does not exit in the tree, please reenter"<<endl;
        return false;
    }

    int bye=0,leftmost=0,rightmost=0;
    int parent = findParent(data);

    if(data<al[findParent(data)].theData())
    {
        bye=al[parent].theRightIndex();
        if(al[bye].theCount()>1)
        {
            --al[bye].theCount();
            return true;
        }
        if(al[bye].theLeftIndex()!=-1)
        {
            int offspring=al[bye].theLeftIndex();
            if(al[bye].theRightIndex()!=-1)
            {
                int temp=al[bye].theRightIndex();
                if(findTheLeftMost(al[temp])!=-1)
                {
                    leftmost=findTheLeftMost(al[temp]);
                    al[leftmost].theLeftIndex()=offspring;
                    al[offspring].theParentIndex()=leftmost;
                    al[parent].theRightIndex()=temp;
                    al[temp].theParentIndex()=parent;
                    rebalance(al[offspring]);//
                }
                else
                {
                    al[temp].theLeftIndex() = offspring;
                    al[offspring].theParentIndex() = temp;
                    al[parent].theRightIndex() = temp;
                    al[temp].theParentIndex() = parent;
                    rebalance(al[temp]);
                }
            }
            else
            {
                al[parent].theRightIndex() = offspring;
                al[offspring].theParentIndex() = parent;
                rebalance(al[offspring]);
            }
        }
        else
        {
            int temp=al[bye].theRightIndex();
            al[parent].theRightIndex()=temp;

            if(temp!=-1)
            {
                al[temp].theParentIndex()=parent;
                rebalance(al[temp]);
            }
            else
            {
                rebalance(al[parent]);
            }

        }
        killNode(al[bye]);

    }
    else
    {

        bye=al[parent].theLeftIndex();
        if(al[bye].theCount()>1)
        {
            --al[bye].theCount();
            return true;
        }
        if(al[bye].theRightIndex()!=-1)
        {
            int offspring=al[bye].theRightIndex();
            if(al[bye].theLeftIndex()!=-1)
            {
                int temp=al[bye].theLeftIndex();
                if(findTheRightMost(al[temp])!=-1)
                {
                    rightmost=findTheRightMost(al[temp]);
                    al[rightmost].theRightIndex()=offspring;
                    al[offspring].theParentIndex()=rightmost;
                    al[parent].theLeftIndex()=temp;
                    al[temp].theParentIndex()=parent;
                    rebalance(al[offspring]);
                }
                else                {
                    al[temp].theRightIndex()=offspring;
                    al[offspring].theParentIndex()=temp;
                    al[parent].theLeftIndex()=temp;
                    al[temp].theParentIndex()=parent;
                    rebalance(al[temp]);
                }
            }
            else
            {
                al[parent].theLeftIndex()=offspring;
                al[offspring].theParentIndex()=parent;
                rebalance(al[offspring]);
            }
        }
        else
        {
            if(al[bye].theLeftIndex()!=-1)
            {
                int temp=al[bye].theLeftIndex();
                al[parent].theLeftIndex()=temp;
                if(temp!=-1)
                {
                    al[temp].theParentIndex()=parent;
                    rebalance(al[temp]);
                }
                else
                {
                    rebalance(al[parent]);
                }
            }
        }
        killNode(al[bye]);
    }
}
template<typename T>
bool avltree<T>::find(T data)
{
    for(int i=0;i<al.size();++i)
    {
        if(al[i].theData()==data)
        {
            return true;
        }
    }
    return false;

}


template<typename T>
int avltree<T>::findTheLeftMost(node<T> & n)
{
    if(n.theLeftIndex()==-1)
        return -1;

    int leftmost=n.theLeftIndex();
    while(al[leftmost].theLeftIndex()!=-1)
    {
        leftmost=al[leftmost].theLeftIndex();
    }
    return leftmost;
}


template<typename T>
int avltree<T>::findTheRightMost(node<T> & n)
{
    if(n.theRightIndex()==-1)
        return -1;

    int rightmost=n.theRightIndex();
    while(al[rightmost].theRightIndex()!=-1)
    {
        rightmost=al[rightmost].theRightIndex();
    }
    return rightmost;

}
template<typename T>
void avltree<T>::nukem()
{
    al.clear();
}

template<typename T>
int avltree<T>::height(node<T>* & r)
{
    return depth(r->getRightIndex())-depth(r->getLeftIndex());
}

template <typename T>
int avltree<T>::depth(int i)
{
    if(i==-1)
        return 0;
    node<T>* r=al[i];
    return 1+max(depth(r->getRightIndex()),depth(r->getLeftIndex()));
}

template <typename T>
bool avltree<T>::valid(node<T>* & r)
{
    return r->getSelfIndex()<al.size() && r->getSelfIndex()>-1;
}

template<typename T>
int avltree<T>::totalNodes()
{
    return al.size();
}

template<typename T>
int avltree<T>::theDepth()
{
    return depth(al[0]);
}

template<typename T>
void avltree<T>::printOut(node<T>* &n)
{
    if(n->getSelfIndex()!=-1)
        cout<<*n<<endl;
}

template<typename T>
void avltree<T>::write(node<T>* &r)
{
    if(r->getRightIndex()!=-1)
    {
        write(al[r->getRightIndex()]);
    }
    this->printOut(r);
    if(r->getLeftIndex()!=-1)
    {

        write(al[r->getLeftIndex()]);
    }

}
template<typename T>
node<T>& avltree<T>::theRoot()
{
    return root;
}

template<typename T>
node<T>& avltree<T>::theal(int pos)
{
    return al[pos];
}

template<typename T>
int avltree<T>::rebalance(node<T>* &r)
{
    int current,previous;
    current=r->getSelfIndex();

    while(al[current]->getParentIndex()!=-1)
    {
        previous=current;
        current=al[current]->getParentIndex();

        if(height(al[current])>1)
        {
            if(height(al[previous])>=0)
            {
                rightRotate(al[current]);
            }
            else
            {
                leftRotate(al[previous]);
                rightRotate(al[current]);
            }
        }

        if(height(al[current])<-1)
        {
            if(height(al[previous])>0)
            {
                rightRotate(al[previous]);
                leftRotate(al[current]);
            }
            else
            {
                leftRotate(al[current]);
            }
        }
    }
    return current;
}

template<typename T>
void avltree<T>::killNode(node<T>* & r)
{
    *r->nukem();
}
template<typename T>
int avltree<T>::totalNumItems()
{
    int total = 0;
    for(int i = 0; i < al.size(); i++)
        total += al[i]->getCount();
    return total;
}

template<typename T>
void avltree<T>::copy(const avltree<T> &other)
{
    al = other.al;
}

template<typename U>
ostream& operator<<(ostream& out, avltree<U> avl)
{
    for(int i = 0; i < avl.al.size(); i++)
        out<<*avl.al[i]<<endl;
    return out;
}

#endif // AVLTREE_VEC_H
