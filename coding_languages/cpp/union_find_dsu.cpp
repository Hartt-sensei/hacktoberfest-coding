/*
Union-Find (Disjoint Set Union) with Path Compression and Union by Size
- Operations:
  - find(x): returns representative of the set containing x
  - unite(a, b): merges sets of a and b
  - same(a, b): checks if a and b are in the same set
  - size(x): size of the set containing x

Time Complexity (amortized): ~O(alpha(n)) per op
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> parent, sz;

    DSU(int n) : n(n), parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // path compression
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b); // union by size
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    int size(int x) {
        return sz[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example usage:
    int n = 7; // nodes 0..6
    DSU dsu(n);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(5, 6);
    dsu.unite(2, 4); // merges {0,1,2} with {3,4}

    cout << boolalpha;
    cout << "same(0, 4) = " << dsu.same(0, 4) << "\n"; // true
    cout << "same(0, 6) = " << dsu.same(0, 6) << "\n"; // false
    cout << "size(0) = " << dsu.size(0) << "\n";       // 5
    cout << "size(6) = " << dsu.size(6) << "\n";       // 2

    // Try adding an edge that connects two components
    if (dsu.unite(4, 6)) {
        cout << "Merged sets of 4 and 6\n";
    }
    cout << "same(0, 6) = " << dsu.same(0, 6) << "\n"; // true now
    cout << "size(0) = " << dsu.size(0) << "\n";       // 7

    return 0;
}
