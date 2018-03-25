#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

template<typename T>
class node
{
public:
    node();
    node(T &d ,int &self, int& parent);
    ~node();
    node(const node<T> &other);
    node<T> & operator=(const node<T> &other);

    void setData(T data);
    void setCount(int c);
    void setRight(int r);
    void setLeft(int l );
    void setSelf(int s);
    void setParent(int p);

    int getRightIndex() const;
    int getLeftIndex()const;
    int getSelfIndex()const;
    T   getData()const;
    int getCount()const;
    int getParentIndex() const;

    void clear();
    void setposition(int&, int&);
    void increaseCount();


    template<typename U>
    friend
    ostream& operator<<(ostream &out, const node<U> &n);

    template<typename U>
    friend
    istream& operator>>(istream &in, node<U> &n);

    template<typename U>
    friend
    bool operator<(const node<U> &one, const node<U> &two);

    template<typename U>
    friend
    bool operator > (const node<U> &one, const node<U> &two);

    template<typename U>
    friend
    bool operator==(const node<U> &one, const node<U> &two);


private:
    T data;
    int selfIndex;
    int leftIndex;
    int rightIndex;
    unsigned int count;
    int parentIndex;

    void nukem();
    void copy(const node<T> &other);
    vector<int >line_num;
    vector<int >para_num;
};

template<typename T>
node<T>::node()
{
    data = T();
    parentIndex=-1;
    rightIndex = -1;
    leftIndex=-1;
    selfIndex=-1;
    count = 1;
}

template<typename T>
node<T>::node(T &d ,int &self, int& parent)
{
    data = d;
    selfIndex = self;
    parentIndex = parent;
    rightIndex = leftIndex=-1;
    count=0;
}

template<typename T>
void node<T>::setposition(int& line, int& para)
{
    line_num.push_back(line);
    para_num.push_back(para);
}

template<typename T>
node<T>::~node()
{
    selfIndex = leftIndex = rightIndex = -1;
    data = T();
    count = 0;
    parentIndex=-1;
    line_num=vector<int>();
    para_num=vector<int>();
}

template<typename T>
node<T>::node(const node<T>& other)
{
    copy(other);
}

template<typename T>
node<T> & node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
void node<T>::copy(const node<T> &other)
{
    data = other.data;
    count = other.count;
    leftIndex = other.leftIndex;
    rightIndex = other.rightIndex;
    selfIndex = other.selfIndex;
    parentIndex = other.parentIndex;

    for(int i=0;i<other.line_num.size();++i)
    {
        line_num.push_back(other.line_num[i]);
        para_num.push_back(other.para_num[i]);
    }
}

template<typename T>
void node<T>::setData(T d)
{
    data=d;
}

template<typename T>
void node<T>::increaseCount()
{
    ++count;
}
template<typename T>
void node<T>::setRight(int r)
{
    rightIndex=r;
}
template<typename T>
void node<T>::setLeft(int l )
{
    leftIndex=l;
}
template<typename T>
void node<T>::setSelf(int s)
{
    selfIndex=s;
}

template<typename T>
void node<T>::setParent(int p)
{
    parentIndex=p;
}

template<typename T>
int node<T>::getRightIndex() const
{
    return rightIndex;
}

template<typename T>
int node<T>::getLeftIndex() const
{
    return leftIndex;
}

template<typename T>
int node<T>::getSelfIndex() const
{
    return selfIndex;
}

template<typename T>
T node<T>::getData()const
{
    return data;
}

template<typename T>
int node<T>::getCount()const
{
    return count;
}

template<typename T>
int node<T>::getParentIndex() const
{
    return parentIndex;
}

template<typename T>
void node<T>::nukem()
{
    data = T();
    rightIndex=-1;
    leftIndex=-1;
    selfIndex=-1;
    count = 0;
    parentIndex=-1;
}


template<typename U>
bool operator<(const node<U> &one, const node<U> &two)
{
    return one.data < two.data;
}

template<typename U>
bool operator==(const node<U> &one, const node<U> &two)
{
    return one.data == two.data;
}

template<typename U>
bool operator > (const node<U> &one, const node<U> &two)
{
    return one.data > two.data;
}

template<typename U>
ostream& operator<<(ostream &out, const node<U> &n)
{
    out<<n.data<<" "<<n.count<<endl;
    for(int i=0;i<n.line_num.size();++i)
    {
        out<<"line position: "<<n.line_num[i]<<","<<"paragraph position: "
          <<n.para_num[i]<<endl;
    }
    return out;
}

template<typename U>
istream& operator>>(istream &in, node<U> *&n)
{
    U data;
    int count;
    char junk;
    n = NULL;
    if(in == cin)
    {
        cout<<"Data (press enter to quit): ";
        if(in.peek() != '\n')
        {
            cin>>data;
            cout<<"Count (enter = 1): ";
            if(in.peek() == '\n')
                count = 1;
            else
                cin>>count;
            n = new node<U>(data,count);
        }
    }
    else
        if(in>>data>>junk>>count>>junk)
            n = new node<U>(data,count);
    return in;
}
#endif // NODE_H
