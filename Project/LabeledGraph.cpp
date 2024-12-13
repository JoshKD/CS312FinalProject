#include "LabeledGraph.h"
#include <queue>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

LabeledGraph::LabeledGraph(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find('/');
        if (pos == string::npos) continue;

        string movie = line.substr(0, pos);
        add_vertex(movie);

        string actor_str = line.substr(pos + 1);
        stringstream ss(actor_str);
        string actor;
        while (getline(ss, actor, '/')) {
            add_edge(movie, actor);
        }
    }
    file.close();
}

void LabeledGraph::add_vertex(string vlabel) {
   labels.push_back(vlabel);
   indexedLabels.insert(pair<string, int>(vlabel, V()));
   set<int> s;
   vertices.push_back(s);
}

void LabeledGraph::add_edge(string source, string target) {
    if (!contains(source)) add_vertex(source);
    if (!contains(target)) add_vertex(target);

    vertices[indexedLabels[source]].insert(indexedLabels[target]);
    vertices[indexedLabels[target]].insert(indexedLabels[source]);

    ++nedges;
}

bool LabeledGraph::contains(string vlabel) const {
    return indexedLabels.find(vlabel) != indexedLabels.end();
}

set<int> LabeledGraph::neighbors(int v) const {
    return vertices[v];
}

string LabeledGraph::label(int v) const {
    return labels[v];
}

int LabeledGraph::index(string vlabel) {
    return indexedLabels[vlabel];
}

map<int, int> LabeledGraph::BFS(int v) {
    map<int, int> parent_map;
    queue<int> to_visit;
    set<int> visited;

    to_visit.push(v);
    visited.insert(v);
    parent_map[v] = -1; // -1 signifies the root node

    while (!to_visit.empty()) {
        int current = to_visit.front();
        to_visit.pop();

        for (int neighbor : neighbors(current)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                to_visit.push(neighbor);
                parent_map[neighbor] = current;
            }
        }
    }

    return parent_map;
}

vector<int> LabeledGraph::pathTo(map<int, int>& parent_map, int target) {
    vector<int> path;
    int current = target;

    while (current != -1) { // root node marked by -1
        path.push_back(current);
        current = parent_map[current];
    }

    reverse(path.begin(), path.end());
    return path;
}

ostream& operator<<(ostream& out, const LabeledGraph& g) {
    out << "==================================================================================\n";
    out << "Graph Summary: " << g.V() << " Vertices, " << g.E() << " Edges\n";
    out << "==================================================================================\n";
    for (int x = 0; x < g.V(); x++) {
        out << g.label(x) << "\n    ";
        auto neighbors = g.neighbors(x);
        for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
            out << g.label(*it) << "\n    ";
        }
        out << "\n";
    }
    return out;
}

void LabeledGraph::display_related_vertices(string vlabel) {
    if (!contains(vlabel)) {
        cout << "Vertex with label '" << vlabel << "' not found in the graph." << endl;
        return;
    }

    int v = index(vlabel);
    cout << "These are directly related to " << vlabel << ":\n";
    for (int neighbor : neighbors(v)) {
        cout << "  " << label(neighbor) << endl;
    }
}