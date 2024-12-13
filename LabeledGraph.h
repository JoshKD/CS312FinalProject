#ifndef LABELED_GRAPH_H
#define LABELED_GRAPH_H

#include <set>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#ifndef LABELED_GRAPH_H
#define LABELED_GRAPH_H

#include <set>
#include <map>
#include <vector>
#include <string>
#include <iostream>

class LabeledGraph {
public:

    // CONSTRUCTOR
    LabeledGraph()  {nedges = 0; }
    LabeledGraph(std::string a);

    // MODIFICATION MEMBER FUNCTIONS
    void add_vertex(std::string vlabel);
    void add_edge(std::string source, std::string target);
    void display_related_vertices(std::string a);

    // CONSTANT MEMBER FUNCTIONS
    int V() const { return vertices.size(); }
    int E() const { return nedges; }
    bool contains(std::string vlabel) const;
    std::set<int> neighbors(int v) const;
    std::string label(int v) const;
    int index(std::string vlabel);

    // BFS AND PATH FUNCTIONS
    std::map<int, int> BFS(int v);
    std::vector<int> pathTo(std::map<int, int>& parent_map, int target);

    // OVERLOADED OUTPUT OPERATOR
    friend std::ostream& operator<< (std::ostream &out, const LabeledGraph &g);

private:
    int nedges;
    std::vector<std::set<int>> vertices;
    std::vector<std::string> labels;
    std::map<std::string, int> indexedLabels;
};

#endif


class LabeledGraph {
public:

    // CONSTRUCTOR
    LabeledGraph()  {nedges = 0; }
    LabeledGraph(std::string a);

    // MODIFICATION MEMBER FUNCTIONS
    //adds a vertex with a specifc label
    void add_vertex(std::string vlabel);
    void display_related_vertices(std::string a);

    //adds an edge from vertex with source label to vertex with target label
    void add_edge(std::string source, std::string target);

    // CONSTANT MEMBER FUNCTIONS
    int V( ) const { return vertices.size(); } //number of vertices
    int E( ) const { return nedges; }       //number of edges
    bool contains(std::string vlabel) const;     //does graph contain vertex with label vlabel?
    std::set<int> neighbors(int v) const;  //returns the vertices adjacent to vertex v
    std::string label(int v) const;     //returns the label of vertex v
    int index(std::string vlabel);           //returns the index of the vertex with label vlabel

    // OVERLOADED OUTPUT OPERATOR
    friend std::ostream& operator<< (std::ostream &out, const LabeledGraph &g);

private:
  int nedges;
  std::vector<std::set<int> > vertices;
  std::vector<std::string> labels;
  std::map<std::string, int> indexedLabels;
};

#endif
