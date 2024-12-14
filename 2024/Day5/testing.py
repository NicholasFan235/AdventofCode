import numpy as np
import networkx
import pandas as pd

rules = []
updates = []

with open('input.txt', 'r') as f:
    for l in f:
        l = l.strip()
        if len(l) == 0: break
        l = l.split('|')
        l = [int(i) for i in l]
        rules.append(l)

    for l in f:
        l = l.strip()
        if len(l)==0: break
        updates.append([int(i) for i in l.split(',')])

rules = np.array(rules)

all_pages = list(set(rules.reshape(-1).tolist()))

network = {p:{q:int(q!=p) for q in all_pages} for p in all_pages}
for rule in rules:
    network[rule[1]][rule[0]] = 0

# print(pd.DataFrame.from_dict(network, orient='index'))
edges = [[i,j] for i in network for j in network[i] if network[i][j]==1]

G = networkx.DiGraph()
G.add_nodes_from(all_pages)
G.add_edges_from(edges)
print(G)

print(networkx.find_cycle(G))
