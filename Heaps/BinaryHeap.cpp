#include <iostream>
#include <cassert>
#include <cstdio>

using namespace std;

const int MAXN = int(1e6);

int Heap[MAXN];
int HeapSize = 0;

void SiftDown(int id)
{
    if (id * 2 > HeapSize) return;
    int left = id * 2,
        right = id * 2 + 1;

    if (left == HeapSize){
        if (Heap[id] > Heap[left]) swap(Heap[id], Heap[left]);
    } else {
        int nxt = (Heap[left] < Heap[right] ? left : right);
        if (Heap[id] > Heap[nxt]) {
            swap(Heap[id], Heap[nxt]);
            SiftDown(nxt);
        };
    }
}

void SiftUp(int id)
{
    if (id == 1) return;

    int par = id / 2;
    if (Heap[par] > Heap[id]) {
        swap(Heap[par], Heap[id]);
        SiftUp(par);
    }
}

void DeleteMin()
{
    Heap[1] = Heap[HeapSize];
    HeapSize -= 1;
    SiftDown(1);
    return;
}

void Insert(int val)
{
    HeapSize += 1;
    Heap[HeapSize] = val;
    SiftUp(HeapSize);
}

int GetMin()
{
    return Heap[1];
}

int main()
{
    int n; assert(scanf("%d", &n) == 1);
    for (int i = 1; i <= n; i++)
    {
        int item;
        assert(scanf("%d", &item) == 1);
        Insert(item);
    }


    for (int i = 0; i < n; i++)
    {
        printf("%d ", GetMin());
        DeleteMin();
    }

    return 0;
}
