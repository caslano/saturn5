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