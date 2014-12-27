#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H

#include<vector>


using namespace std;

enum MINMAX {
    MIN,
    MAX
};


class node{
public:
    int val, id;
    bool exists;

    node(int _val, int _id, bool _exists);
    node(); //default

    friend bool operator < (const node & a, const node & b);
};
bool operator < (const node & a, const node & b);


class Heap {
private:
    vector<int> heap;
    vector<int> lvl;
    int HeapSize;
    void increase_size();
    node get_nxt(MINMAX t, int cur, int depth = 0);
    void TrickleDownMin(int pos);
    void TrickleDownMax(int pos);
    void BubbleUpMin(int pos);
    void BubbleUpMax(int pos);

public:
    Heap();
    void TrickleDown(int pos);
    void BubbleUp(int pos);
    void Insert(int val);
    void Erase(int pos);
    int GetMin();
    int GetMax();
    size_t GetSize();
    void DelMin();
    void DelMax();
};

#endif // MINMAXHEAP_H
