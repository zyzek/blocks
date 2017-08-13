class UnionFind:
    def __init__(self, items):
        # Initialise the union find
        self.indices = {v:i for i, v in enumerate(items)}
        self.items = list(items)

        # Each item belongs to its singleton equivalence class at first.
        self.parents = [i for i in range(len(items))]

        # Ranks are proxies for the height of trees.
        self.ranks = [0]*len(items)
    
    def find_index(self, i):
        if self.parents[i] != i:
            self.parents[i] = self.find_index(self.parents[i])
        return self.parents[i]

    def find(self, x):
        index = self.indices[x]
        rep_index = self.find_index(index)
        return self.items[rep_index]
    
    def union_index(self, i, j):
        i_root = self.find_index(i)
        j_root = self.find_index(j)

        if i_root == j_root:
            return False

        if self.ranks[i_root] < self.ranks[j_root]:
            self.parents[i_root] = j_root
        elif self.ranks[i_root] > self.ranks[j_root]:
            self.parents[j_root] = i_root
        else:
            self.parents[j_root] = i_root
            self.ranks[i_root] += 1
        return True

    def union(self, x, y):
        return self.union_index(self.indices[x], self.indices[y])
