#include <iostream>
#include "MinMaxHeap.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>

using namespace std;

Heap l, r;
int median;

void update(int val)
{
    if (val > median) r.Insert(val);
    else l.Insert(val);
    if (l.GetSize() > r.GetSize() + 1) {
        r.Insert(median);
        median = l.GetMax();
        l.DelMax();
    } else if (l.GetSize() < r.GetSize()) {
        l.Insert(median);
        median = r.GetMin();
        r.DelMin();
    }
}

int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; i++)
    {
        char C; cin >> C;
        if (C == '!') {
            int val; cin >> val;
            if (!i) median = val;
			else update(val);
        } else if (C == '?'){
            cout << median << endl;
        }
    }
    return 0;
}
