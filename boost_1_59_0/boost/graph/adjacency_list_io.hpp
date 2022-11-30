//=======================================================================
// Copyright 2001 Universite Joseph Fourier, Grenoble.
// Author: Francois Faure
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_ADJACENCY_LIST_IO_HPP
#define BOOST_GRAPH_ADJACENCY_LIST_IO_HPP

#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <cctype>

// Method read to parse an adjacency list from an input stream. Examples:
// cin >> read( G );
// cin >> read( G, NodePropertySubset(), EdgepropertySubset() );
//
// Method write to print an adjacency list to an output stream. Examples:
// cout << write( G );
// cout << write( G, NodePropertySubset(), EdgepropertySubset() );

namespace boost
{

/* outline
        - basic property input
        - get property subset
        - graph parser
        - property printer
        - graph printer
        - user methods
*/

//===========================================================================
// basic property input

template < class Tag, class Value, class Next >
std::istream& operator>>(std::istream& in, property< Tag, Value, Next >& p)
{
    in >> p.m_value >> p.m_base; // houpla !!
    return in;
}

template < class Tag, class Value >
std::istream& operator>>(
    std::istream& in, property< Tag, Value, no_property >& p)
{
    in >> p.m_value;
    return in;
}

inline std::istream& operator>>(std::istream& in, no_property&) { return in; }

// basic property input
//===========================================================================
// get property subsets

// get a single property tagged Stag
template < class Tag, class Value, class Next, class V, class Stag >
void get(property< Tag, Value, Next >& p, const V& v, Stag s)
{
    get(p.m_base, v, s);
}

template < class Value, class Next, class V, class Stag >
void get(property< Stag, Value, Next >& p, const V& v, Stag)
{
    p.m_value = v;
}

// get a subset of properties tagged Stag
template < class Tag, class Value, class Next, class Stag, class Svalue,
    class Snext >
void getSubset(
    property< Tag, Value, Next >& p, const property< Stag, Svalue, Snext >& s)
{
    get(p, s.m_value, Stag());
    getSubset(p, s.m_base);
}

template < class Tag, class Value, class Next, class Stag, class Svalue >
void getSubset(property< Tag, Value, Next >& p,
    const property< Stag, Svalue, no_property >& s)
{
    get(p, s.m_value, Stag());
}

inline void getSubset(no_property&, const no_property&) {}

#if !defined(BOOST_GRAPH_NO_BUNDLED_PROPERTIES)
template < typename T, typename U > void getSubset(T& p, const U& s) { p = s; }

template < typename T > void getSubset(T&, const no_property&) {}

#endif

//  get property subset
//===========================================================================
// graph parser
typedef enum
{
    PARSE_NUM_NODES,
    PARSE_VERTEX,
    PARSE_EDGE
} GraphParserState;

template < class Graph_t, class VertexProperty, class EdgeProperty,
    class VertexPropertySubset, class EdgePropertySubset >
struct GraphParser
{

    typedef Graph_t Graph;

    GraphParser(Graph* g) : graph(g) {}

    GraphParser& operator()(std::istream& in)
    {
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        std::vector< Vertex > nodes;

        GraphParserState state = PARSE_VERTEX;

        unsigned int numLine = 1;
        char c;
        while (in.get(c))
        {
            if (c == '#')
                skip(in);
            else if (c == 'n')
                state = PARSE_NUM_NODES;
            else if (c == 'v')
                state = PARSE_VERTEX;
            else if (c == 'e')
                state = PARSE_EDGE;
            else if (c == '\n')
                numLine++;
            else if (!std::isspace(c))
            {
                in.putback(c);
                if (state == PARSE_VERTEX)
                {
                    VertexPropertySubset readProp;
                    if (in >> readProp)
                    {
                        VertexProperty vp;
                        getSubset(vp, readProp);
                        nodes.push_back(add_vertex(vp, *graph));
                    }
                    else
                        std::cerr << "read vertex, parse error at line"
                                  << numLine << std::endl;
                }
                else if (state == PARSE_EDGE)
                {
                    int source, target;
                    EdgePropertySubset readProp;
                    in >> source >> target;
                    if (in >> readProp)
                    {
                        EdgeProperty ep;
                        getSubset(ep, readProp);
                        add_edge(nodes[source], nodes[target], ep, *graph);
                    }
                    else
                        std::cerr << "read edge, parse error at line" << numLine
                                  << std::endl;
                }
                else
                { // state == PARSE_NUM_NODES
                    int n;
                    if (in >> n)
                    {
                        for (int i = 0; i < n; ++i)
                            nodes.push_back(add_vertex(*graph));
                    }
                    else
                        std::cerr << "read num_nodes, parse error at line "
                                  << numLine << std::endl;
                }
            }
        }
        return (*this);
    }

protected:
    Graph* graph;

    void skip(std::istream& in)
    {
        char c = 0;
        while (c != '\n' && !in.eof())
            in.get(c);
        in.putback(c);
    }
};

// parser
//=======================================================================
// property printer

#if defined(BOOST_GRAPH_NO_BUNDLED_PROPERTIES)
template < class Graph, class Property > struct PropertyPrinter
{
    typedef typename Property::value_type Value;
    typedef typename Property::tag_type Tag;
    typedef typename Property::next_type Next;

    PropertyPrinter(const Graph& g) : graph(&g) {}

    template < class Val >
    PropertyPrinter& operator()(std::ostream& out, const Val& v)
    {
        typename property_map< Graph, Tag >::const_type ps = get(Tag(), *graph);
        out << ps[v] << " ";
        PropertyPrinter< Graph, Next > print(*graph);
        print(out, v);
        return (*this);
    }

private:
    const Graph* graph;
};
#else
template < class Graph, typename Property > struct PropertyPrinter
{
    PropertyPrinter(const Graph& g) : graph(&g) {}

    template < class Val >
    PropertyPrinter& operator()(std::ostream& out, const Val& v)
    {
        out << (*graph)[v] << " ";
        return (*this);
    }

private:
    const Graph* graph;
};

template < class Graph, typename Tag, typename Value, typename Next >
struct PropertyPrinter< Graph, property< Tag, Value, Next > >
{
    PropertyPrinter(const Graph& g) : graph(&g) {}

    template < class Val >
    PropertyPrinter& operator()(std::ostream& out, const Val& v)
    {
        typename property_map< Graph, Tag >::const_type ps = get(Tag(), *graph);
        out << ps[v] << " ";
        PropertyPrinter< Graph, Next > print(*graph);
        print(out, v);
        return (*this);
    }

private:
    const Graph* graph;
};
#endif

template < class Graph > struct PropertyPrinter< Graph, no_property >
{
    PropertyPrinter(const Graph&) {}

    template < class Val >
    PropertyPrinter& operator()(std::ostream&, const Val&)
    {
        return *this;
    }
};

// property printer
//=========================================================================
// graph printer

template < class Graph_t, class EdgeProperty > struct EdgePrinter
{

    typedef Graph_t Graph;
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;

    EdgePrinter(const Graph& g) : graph(g) {}

    const EdgePrinter& operator()(std::ostream& out) const
    {
        // assign indices to vertices
        std::map< Vertex, int > indices;
        int num = 0;
        BGL_FORALL_VERTICES_T(v, graph, Graph) { indices[v] = num++; }

        // write edges
        PropertyPrinter< Graph, EdgeProperty > print_Edge(graph);
        out << "e" << std::endl;
        BGL_FORALL_EDGES_T(e, graph, Graph)
        {
            out << indices[source(e, graph)] << " " << indices[target(e, graph)]
                << "  ";
            print_Edge(out, e);
            out << std::endl;
        }
        out << std::endl;
        return (*this);
    }

protected:
    const Graph& graph;
};

template < class Graph, class V, class E >
struct GraphPrinter : public EdgePrinter< Graph, E >
{
    GraphPrinter(const Graph& g) : EdgePrinter< Graph, E >(g) {}

    const GraphPrinter& operator()(std::ostream& out) const
    {
        PropertyPrinter< Graph, V > printNode(this->graph);
        out << "v" << std::endl;
        BGL_FORALL_VERTICES_T(v, this->graph, Graph)
        {
            printNode(out, v);
            out << std::endl;
        }

        EdgePrinter< Graph, E >::operator()(out);
        return (*this);
    }
};

template < class Graph, class E >
struct GraphPrinter< Graph, no_property, E > : public EdgePrinter< Graph, E >
{
    GraphPrinter(const Graph& g) : EdgePrinter< Graph, E >(g) {}

    const GraphPrinter& operator()(std::ostream& out) const
    {
        out << "n " << num_vertices(this->graph) << std::endl;
        EdgePrinter< Graph, E >::operator()(out);
        return (*this);
    }
};

// graph printer
//=========================================================================
// user methods

/// input stream for reading a graph
template < class Graph, class VP, class EP, class VPS, class EPS >
std::istream& operator>>(
    std::istream& in, GraphParser< Graph, VP, EP, VPS, EPS > gp)
{
    gp(in);
    return in;
}

/// graph parser for given subsets of internal vertex and edge properties
template < class EL, class VL, class D, class VP, class EP, class GP, class VPS,
    class EPS >
GraphParser< adjacency_list< EL, VL, D, VP, EP, GP >, VP, EP, VPS, EPS > read(
    adjacency_list< EL, VL, D, VP, EP, GP >& g, VPS vps, EPS eps)
{
    return GraphParser< adjacency_list< EL, VL, D, VP, EP, GP >, VP, EP, VPS,
        EPS >(&g);
}

/// graph parser for all internal vertex and edge properties
template < class EL, class VL, class D, class VP, class EP, class GP >
GraphParser< adjacency_list< EL, VL, D, VP, EP, GP >, VP, EP, VP, EP > read(
    adjacency_list< EL, VL, D, VP, EP, GP >& g)
{
    return GraphParser< adjacency_list< EL, VL, D, VP, EP, GP >, VP, EP, VP,
        EP >(&g);
}

/// output stream for writing a graph
template < class Graph, class VP, class EP >
std::ostream& operator<<(
    std::ostream& out, const GraphPrinter< Graph, VP, EP >& gp)
{
    gp(out);
    return out;
}

/// write the graph with given property subsets
template < class EL, class VL, class D, class VP, class EP, class GP, class VPS,
    class EPS >
GraphPrinter< adjacency_list< EL, VL, D, VP, EP, GP >, VPS, EPS > write(
    const adjacency_list< EL, VL, D, VP, EP, GP >& g, VPS, EPS)
{
    return GraphPrinter< adjacency_list< EL, VL, D, VP, EP, GP >, VPS, EPS >(g);
}

/// write the graph with all internal vertex and edge properties
template < class EL, class VL, class D, class VP, class EP, class GP >
GraphPrinter< adjacency_list< EL, VL, D, VP, EP, GP >, VP, EP > write(
    const adjacency_list< EL, VL, D, VP, EP, GP >& g)
{
    return GraphPrinter< adjacency_list< EL, VL, D, VP, EP, GP >, VP, EP >(g);
}

// user methods
//=========================================================================
} // boost
#endif

/* adjacency_list_io.hpp
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
*/