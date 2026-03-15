#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct edge {
    int u, v, w;
    edge(int u, int v, int w) :u(u), v(v), w(w) {}

};

int find(int x, vector<int>& parent) {
    if (parent[x] != x) {
        parent[x] = find(parent[x], parent);
    }
    return parent[x];
}
void unite(int x, int y, vector<int>& parent, vector<int>& rank) {
    if (rank[x] > rank[y]) {
        parent[y] = x;
    }
    else {
        parent[x] = y;
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
    }
}
int main() {
    int n, m;
    while (cin >> n >> m && (n || m)) {
        vector<int> nw(n);
        for (int i = 0;i < n;++i) {
            cin >> nw[i];
        }
        vector<vector<int>> ew(n, vector<int>(n));
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < n;j++) {
                cin >> ew[i][j];
            }
        }
        vector<int> best;
        double ratio = -1;
        for (int mask = 0;mask < (1 << n);++mask) {
            int count = 0;
            for (int i = 0;i < n;++i) {
                if (mask & (1 << i)) {
                    count++;
                }
            }
            if (count != m) {
                continue;
            }
            vector<int> sub;
            int sn = 0;
            for (int i = 0;i < n;++i) {
                if (mask & (1 << i)) {
                    sub.push_back(i);
                    sn += nw[i];
                }
            }
            vector<int> parent(n);
            for (int i = 0;i < n;i++) {
                parent[i] = i;
            }
            vector<int> rank(n, 1);
            vector<edge> gra;
            for (int i = 0;i < m;i++) {
                for (int j = i + 1;j < m;j++) {
                    gra.push_back(edge(sub[i], sub[j], ew[sub[i]][sub[j]]));
                }
            }
            sort(gra.begin(), gra.end(), [](edge a, edge b) {
                return a.w < b.w;
                });
            int se = 0;
            int edgecount = 0;
            for (edge& e : gra) {
                int fu = find(e.u, parent);
                int fv = find(e.v, parent);
                if (fu != fv) {
                    edgecount++;
                    unite(fu, fv, parent, rank);
                    se += e.w;
                    if (edgecount == m - 1) {
                        break;
                    }
                }
            }
            if (ratio == -1) {
                ratio = (double)se / sn;
                best = sub;
            }
            else {
                if ((double)se / sn < ratio) {
                    ratio = (double)se / sn;
                    best = sub;
                }
                else if ((double)se / sn == ratio) {
                    for (int i = 0;i < m;i++) {
                        if (sub[i] == best[i]) {
                            continue;
                        }
                        else if (sub[i] < best[i]) {
                            best = sub;
                            break;
                        }
                        else {
                            break;
                        }
                    }
                }
            }

        }
        for (int i = 0;i < m;i++) {
            cout << best[i] + 1 << " ";
        }
        cout << endl;

    }
    return 0;
}