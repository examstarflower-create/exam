import sys
sys.setrecursionlimit(50000)

def max_indep_set(n, edges, weight):
    tree = [[] for _ in range(n+1)]
    for u, v in edges:
        tree[u].append(v)
        tree[v].append(u)

    msum = [[0,0] for _ in range(n+1)]
    visited = [False] * (n+1)

    def dfs(node):
        visited[node] = True
        msum[node][1] = weight[node - 1]

        for neighbor in tree[node]:
            if not visited[neighbor]:
                dfs(neighbor)
                msum[node][0] += max(msum[neighbor][0], msum[neighbor][1])
                msum[node][1] += msum[neighbor][0]
        
    dfs(1)

    return max(msum[1][0], msum[1][1])
