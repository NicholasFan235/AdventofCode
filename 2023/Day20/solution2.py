#%%
import networkx
import pandas as pd
import numpy as np
import matplotlib
import matplotlib.colors
import matplotlib.pyplot as plt
import re
import graphviz

# %%
class Module:
    def __init__(self, name:str):
        self.name = name
        self.connection_names = []
        self.connections = []

class Broadcaster(Module):
    def type(self): return "Broadcaster"
    def __repr__(self): return "Broadcaster"
    
class FlipFlop(Module):
    def type(self): return "%"
    def __repr__(self): return "FlipFlop"

class Conjunction(Module):
    def type(self): return "&"
    def __repr__(self): return "Conjunction"

broadcaster = None
class ModuleFactory:
    def loads(data:str):
        data = data.strip().split(' -> ')
        data[1] = data[1].strip().split(', ')
        
        match data[0][0]:
            case '%':
                c = FlipFlop
                data[0] = data[0][1:]
            case '&':
                c = Conjunction
                data[0] = data[0][1:]
            case _:
                c = Broadcaster

        m = c(data[0])
        m.connection_names = data[1]
        return m


# %%
with open('input.txt', 'r') as f:
    modules = {v.name:v for v in (ModuleFactory.loads(s) for s in f.readlines())}

# %%
modules
# %%

G = networkx.DiGraph()
G.add_nodes_from(modules.keys())
G.add_edges_from([[o,c] for o in modules for c in modules[o].connection_names])

#%%
pos = networkx.nx_agraph.graphviz_layout(G)
networkx.draw_networkx_nodes(G, pos)
networkx.draw_networkx_labels(G, pos)
networkx.draw_networkx_edges(G, pos)
_ = ""
# %%
