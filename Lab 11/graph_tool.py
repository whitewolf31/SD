import argparse
import sys

import matplotlib.pyplot as plt
import numpy as np
import networkx as nx
import pandas as pd
from networkx.drawing.nx_agraph import graphviz_layout

from collections import defaultdict

def visualize(args):
    df = pd.read_csv(args.path)

    G = nx.from_pandas_edgelist(df, source='from', target='to', edge_attr=['weight'], create_using=nx.DiGraph())

    labels = dict(((u, v), d['weight']) for u, v, d in G.edges(data=True))
    pos = graphviz_layout(G)

    plt.figure(figsize = (250, 250))

    options = {
    'node_color': 'red',
    'node_size': 500,
    'edge_color': 'blue',
    'width': 3,
    'arrowstyle': '-|>',
    'arrowsize': 20,
    'edge_attr': labels,
    }

    #nx.draw_networkx(G, pos=pos, arrows=True, **options, with_labels=True)
    nx.draw_networkx(G, pos=pos, arrows=False, **options, with_labels=True)
    nx.draw_networkx_labels(G, pos=pos)
    nx.draw_networkx_edge_labels(G, pos, labels, font_size=10)
    nx.draw_networkx_edges(G, pos,  width=5.0, edge_color='b', arrows=False)
    plt.show()

def generate(args):
    N = args.nodes
    edges = set()
    in_link_count = defaultdict(lambda:0)
    out_link_count = defaultdict(lambda:0)

    LIM_IN = max(2, int(0.02 * N))
    LIM_OUT = args.edges // args.nodes + 1
    tryouts = N * N * 2

    while(len(edges) < min(N * (N - 1) / 2,  args.edges)):
        tryouts -= 1
        if tryouts < 0:
            break

        from_id = np.random.choice(list(range(0, N)))
        to_id = np.random.choice(list(range(0, N)))
        weight = round(np.abs(np.random.normal()) * 10, 2)
        negative = np.random.choice([True, False], p=[0.15, 0.85])

        if negative:
            weight = -weight


        if from_id == to_id or out_link_count[from_id] >= LIM_OUT:
            continue

        out_link_count[from_id] += 1
        in_link_count[to_id] += 1

        edges.add((from_id, to_id, weight))



    edges = list(edges)
    df = pd.DataFrame(edges, columns=['from', 'to', 'weight'])
    df.to_csv(args.path, header=['from', 'to', 'weight'])

    # You need to manually add the number of nodes in the csv before the first
    # comma ",from,to" -> "200,from,to"


def main():
    parser = argparse.ArgumentParser(
        description='Tool to generate and visualize undirected graphs.\
        Path is used to read the graph is visualization is intended and\
        to write the graph if generation is intended.')

    parser.add_argument('--path', metavar='input', type=str,
                        default="graph.csv", help='Path to graph.csv')
    parser.add_argument("--nodes", type=int, default=10, metavar='V')
    parser.add_argument("--edges", type=int, default=25, metavar='E')
    parser.add_argument("--g", action='store_true',
                        help="Generate graph using edges and nodes arguments.")
    parser.add_argument("--v", action='store_true',
                        help="Display the graph visually.")

    args = parser.parse_args()

    if args.g:
        generate(args)

    if args.v:
        visualize(args)

if __name__ == "__main__":
    main()
