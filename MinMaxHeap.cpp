/*
  ---------------------------------------------------------------------
  INCLUDE, CONSTS, DATA
  ---------------------------------------------------------------------
*/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <cstdlib>

using namespace std;

const int MAXN = int(1e6);

static int Heap[MAXN], lvl[MAXN];
static int HeapSize= 0;



/*
  ---------------------------------------------------------------------
  STRUCT, ENUM
  ---------------------------------------------------------------------
*/

enum MINMAX {
    MIN,
    MAX
};

struct node{
    int val, id;
    bool exists;
    node(int _val, int _id, bool _exists) :
        val(_val), id(_id), exists(_exists) { }
    node() : exists(false) { } //default
};
bool operator < (const node & a, const node & b)
{
    if (!a.exists) return 0;
	if (!b.exists) return 1;
    return a.val < b.val;
}
void TrickleDown(int pos);
node get_nxt(MINMAX t, int cur, int depth = 0);
void TrickleDownMin(int pos);
void TrickleDownMax(int pos);
void BubbleUp(int pos);
void BubbleUpMin(int pos);
void BubbleUpMax(int pos);




/*
  ---------------------------------------------------------------------
  BASE FUNCTIONS
  ---------------------------------------------------------------------
*/


void TrickleDown(int pos)
{
    if (lvl[pos] % 2) TrickleDownMin(pos);
    else TrickleDownMax(pos);
}

node get_nxt(MINMAX t, int cur, int depth)
{
    if (depth > 2 || cur > HeapSize) return node();
    int mult = 1;
    if (t == MAX) mult = -1;
    node res = min(get_nxt(t, cur * 2, depth + 1), get_nxt(t, cur * 2 + 1, depth + 1));
    if (depth != 0) res = min(res, node(Heap[cur] * mult, cur, true));

    return res;
}

void TrickleDownMin(int pos)
{
    node nxt = get_nxt(MIN, pos);
    if (!nxt.exists) return;

    if (lvl[nxt.id] - lvl[pos] == 2) { // is grandchild
        if (Heap[nxt.id] < Heap[pos]) {
            swap(Heap[nxt.id], Heap[pos]);
            if (Heap[nxt.id] > Heap[nxt.id / 2])
                swap(Heap[nxt.id], Heap[nxt.id / 2]);
            TrickleDownMin(nxt.id);
        }
    } else {
        if (Heap[nxt.id] < Heap[pos])
            swap(Heap[pos], Heap[nxt.id]);
    }
}

void TrickleDownMax(int pos)
{
    node nxt = get_nxt(MAX, pos);
    if (!nxt.exists) return;

    if (lvl[nxt.id] - lvl[pos] == 2) {
        if (Heap[nxt.id] > Heap[pos]) {
            swap(Heap[nxt.id], Heap[pos]);
            if (Heap[nxt.id] < Heap[nxt.id / 2])
                swap(Heap[nxt.id], Heap[nxt.id / 2]);
            TrickleDownMin(nxt.id);
        }
    } else {
        if (Heap[nxt.id] > Heap[pos])
            swap(Heap[pos], Heap[nxt.id]);
    }
}

void BubbleUp(int pos)
{
    if (pos == 1) return;
    int par = pos / 2;

    if (lvl[pos] % 2) {              // min level
        if (Heap[pos] > Heap[par]) {
            swap(Heap[pos], Heap[par]);
            BubbleUpMax(par);
        } else {
            BubbleUpMin(pos);
        }
    } else {                         // max level
        if (Heap[pos] < Heap[par]) {
            swap(Heap[pos], Heap[par]);
            BubbleUpMin(par);
        } else {
            BubbleUpMax(pos);
        }
    }
}

void BubbleUpMin(int pos)
{
    if (lvl[pos] < 3) return; // no grandparent
    int par = (pos / 2) / 2; // par -> grandpar
    if (Heap[par] > Heap[pos]) {
        swap(Heap[par], Heap[pos]);
        BubbleUpMin(par);
    }
}

void BubbleUpMax(int pos)
{
    if (lvl[pos] < 3) return; // no grandparent
    int par = (pos / 2) / 2; // par -> grandpar
    if (Heap[par] < Heap[pos]) {
        swap(Heap[par], Heap[pos]);
        BubbleUpMax(par);
    }
}





/*
  ---------------------------------------------------------------------
  EXTRA FUNCTIONS
  ---------------------------------------------------------------------
*/

static void insert(int val)
{
    ++HeapSize;
    Heap[HeapSize] = val;

    if (HeapSize == 1) lvl[HeapSize] = 1;
    else if (lvl[HeapSize - 1] == lvl[HeapSize / 2]) lvl[HeapSize] = lvl[HeapSize - 1] + 1;
    else lvl[HeapSize] = lvl[HeapSize - 1];

    BubbleUp(HeapSize);
}

int get_min()
{
    assert(HeapSize >= 1);
    return Heap[1];
}

static int get_max()
{
    assert(HeapSize >= 1);
    int res = Heap[1];
    if (HeapSize >= 2) res = max(res, Heap[2]);
    if (HeapSize >= 3) res = max(res, Heap[3]);
    return res;
}

static void remove(int pos)
{
    swap(Heap[pos], Heap[HeapSize]);
    --HeapSize;
    TrickleDown(pos);
}

static void remove_min()
{
    assert(HeapSize >= 1);
    remove(1);
}

static void remove_max()
{
    assert(HeapSize >= 1);
    if (HeapSize == 1) {
        remove(1);
    } else {
        if (HeapSize == 2 || Heap[2] > Heap[3]) remove(2);
        else remove(3);
    }
}


/*
  ---------------------------------------------------------------------
  MAIN
  ---------------------------------------------------------------------
*/


int main()
{
//    assert(freopen("input.in", "r", stdin) != NULL);
//    assert(freopen("myout.txt", "w", stdout) );

    int n; assert(scanf("%d", &n) == 1);
    for (int i = 0; i < n; i++)
    {
        int x; assert(scanf("%d", &x) == 1);
        insert(x);
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", get_min());
        remove_min();
    }

    return 0;
}

