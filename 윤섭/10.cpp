#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int T, N;
int ans;
int M;
vector<int> cost;
vector<vector<int>> preTask;

void calculateTime() {
    vector<int> pre(N + 1, 0);    
    vector<int> finish(N + 1, 0);  
    queue<int> q;

    for (int i = 1; i <= N; i++)
        pre[i] = preTask[i].size();

    for (int i = 1; i <= N; i++)
        if (pre[i] == 0) {
            finish[i] = cost[i];
            q.push(i);
        }

    int cnt = 0;
    int localAns = 0;

    while (!q.empty()) {
        int now = q.front(); q.pop();
        cnt++;
        localAns = max(localAns, finish[now]);

        for (int nxt = 1; nxt <= N; nxt++) {
            for (int j = 0; j < preTask[nxt].size(); j++) {
                if (preTask[nxt][j] == now) {
                    pre[nxt]--;
                    finish[nxt] = max(finish[nxt], finish[now] + cost[nxt]);
                    if (pre[nxt] == 0) q.push(nxt);
                }
            }
        }
    }

    if (cnt != N) ans = -1;
    else if (ans != -1) ans = min(ans, localAns);
}

int main() {
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        ans = 21e8;
        cin >> N;
        cost.assign(N + 1, 0);
        preTask.assign(N + 1, {});

        for (int i = 1; i <= N; i++) {
            cin >> cost[i] >> M;
            for (int j = 0; j < M; j++) {
                int from;
                cin >> from;
                preTask[i].push_back(from);
            }
        }

        for (int i = 1; i <= N; i++) {
            int temp = cost[i];
            cost[i] /= 2;     
            calculateTime();
            cost[i] = temp;   
        }

        cout << "#" << tc << " " << ans << "\n";
    }
}
