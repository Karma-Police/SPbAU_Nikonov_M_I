#include "MinMaxHeap.h"
#include <cassert>

node::node(int _val, int _id, bool _exists) : val(_val), id(_id), exists(_exists) { }
node::node() : exists(false) { } //default
Heap::Heap()
{
    HeapSize = 0;
}

bool operator <(const node & a, const node & b)
{
    if (!a.exists) 
		return 0;
    if (!b.exists) 
		return 1;
    return a.val < b.val;
}

node Heap::get_nxt(MINMAX t, int cur, int depth)
{
    if (depth > 2 || cur > HeapSize) 
		return node();
    int mult = 1;
    if (t == MAX) 
		mult = -1;

    node res = min(get_nxt(t, cur * 2, depth + 1), get_nxt(t, cur * 2 + 1, depth + 1));
    if (depth != 0) 
		res = min(res, node(heap[cur] * mult, cur, true));

    return res;
}

void Heap::TrickleDown(int pos)
{
    if (lvl[pos] % 2) 
		TrickleDownMin(pos);
    else 
		TrickleDownMax(pos);
}

void Heap::TrickleDownMin(int pos)
{
    node nxt = get_nxt(MIN, pos);
    if (!nxt.exists) 
		return;

    if (lvl[nxt.id] - lvl[pos] == 2) { // is grandchild
        if (heap[nxt.id] < heap[pos]) {
            swap(heap[nxt.id], heap[pos]);
            if (heap[nxt.id] > heap[nxt.id / 2])
                swap(heap[nxt.id], heap[nxt.id / 2]);
            TrickleDownMin(nxt.id);
        }
    } else {
        if (heap[nxt.id] < heap[pos])
            swap(heap[pos], heap[nxt.id]);
    }
}

void Heap::TrickleDownMax(int pos)
{
    node nxt = get_nxt(MAX, pos);
    if (!nxt.exists) return;

    if (lvl[nxt.id] - lvl[pos] == 2) { // is grandchild
        if (heap[nxt.id] > heap[pos]) {
            swap(heap[nxt.id], heap[pos]);
            if (heap[nxt.id] < heap[nxt.id / 2])
                swap(heap[nxt.id], heap[nxt.id / 2]);
            TrickleDownMax(nxt.id);
        }
    } else {
        if (heap[nxt.id] > heap[pos])
            swap(heap[pos], heap[nxt.id]);
    }
}

void Heap::BubbleUp(int pos)
{
    if (pos == 1) 
		return;
    int par = pos / 2;

    if (lvl[pos] % 2) {              // min level
        if (heap[pos] > heap[par]) {
            swap(heap[pos], heap[par]);
            BubbleUpMax(par);
        } else {
            BubbleUpMin(pos);
        }
    } else {                         // max level
        if (heap[pos] < heap[par]) {
            swap(heap[pos], heap[par]);
            BubbleUpMin(par);
        } else {
            BubbleUpMax(pos);
        }
    }
}

void Heap::BubbleUpMin(int pos)
{
    if (lvl[pos] < 3) 
		return; // no grandparent
    int par = (pos / 2) / 2; // par -> grandpar
    if (heap[par] > heap[pos]) {
        swap(heap[par], heap[pos]);
        BubbleUpMin(par);
    }
}

void Heap::BubbleUpMax(int pos)
{
    if (lvl[pos] < 3) 
		return; // no grandparent
    int par = (pos / 2) / 2; // par -> grandpar
    if (heap[par] < heap[pos]) {
        swap(heap[par], heap[pos]);
        BubbleUpMax(par);
    }
}

void Heap::Insert(int val)
{
    increase_size();
    heap[HeapSize] = val;
    BubbleUp(HeapSize);
}

int Heap::GetMin()
{
    assert(HeapSize >= 1);
    return heap[1];
}

int Heap::GetMax()
{
    assert(HeapSize >= 1);
    int res = heap[1];
    if (HeapSize >= 2) 
		res = max(res, heap[2]);
    if (HeapSize >= 3) 
		res = max(res, heap[3]);
    return res;
}

void Heap::Erase(int pos)
{
    swap(heap[pos], heap[HeapSize]);
    --HeapSize;
    TrickleDown(pos);
}

void Heap::DelMin()
{
    assert(HeapSize >= 1);
    Erase(1);
}

void Heap::DelMax()
{
    assert(HeapSize >= 1);
    if (HeapSize == 1) 
        Erase(1);
    else if (HeapSize == 2 || heap[2] > heap[3]) 
		Erase(2);
    else 
		Erase(3);
}

void Heap::increase_size()
{
    ++HeapSize;
    while ((int)heap.size() <= HeapSize)
    {
        heap.push_back(0);
        lvl.push_back(0);
    }

    if (HeapSize == 1) 
		lvl[HeapSize] = 1;
    else if (lvl[HeapSize - 1] == lvl[HeapSize / 2]) 
		lvl[HeapSize] = lvl[HeapSize - 1] + 1;
    else 
		lvl[HeapSize] = lvl[HeapSize - 1];
}

size_t Heap::GetSize()
{
    return HeapSize;
}
