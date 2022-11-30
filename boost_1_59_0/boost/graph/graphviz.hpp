//=======================================================================
// Copyright 2001 University of Notre Dame.
// Copyright 2003 Jeremy Siek
// Authors: Lie-Quan Lee, Jeremy Siek, and Douglas Gregor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPHVIZ_HPP
#define BOOST_GRAPHVIZ_HPP

#include <boost/config.hpp>
#include <cstdio> // for FILE
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <boost/property_map/property_map.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/subgraph.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/dll_import_export.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/detail/mpi_include.hpp>
#include <boost/spirit/include/classic_multi_pass.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/xpressive/xpressive_static.hpp>
#include <boost/foreach.hpp>

namespace boost
{

template < typename directed_category > struct graphviz_io_traits
{
    static std::string name() { return "digraph"; }
    static std::string delimiter() { return "->"; }
};

template <> struct graphviz_io_traits< undirected_tag >
{
    static std::string name() { return "graph"; }
    static std::string delimiter() { return "--"; }
};

struct default_writer
{
    void operator()(std::ostream&) const {}
    template < class VorE > void operator()(std::ostream&, const VorE&) const {}
};

template < typename T > inline std::string escape_dot_string(const T& obj)
{
    using namespace boost::xpressive;
    static sregex valid_unquoted_id = (((alpha | '_') >> *_w)
        | (!as_xpr('-') >> (('.' >> *_d) | (+_d >> !('.' >> *_d)))));
    std::string s(boost::lexical_cast< std::string >(obj));
    if (regex_match(s, valid_unquoted_id))
    {
        return s;
    }
    else
    {
        boost::algorithm::replace_all(s, "\"", "\\\"");
        return "\"" + s + "\"";
    }
}

template < class Name > class label_writer
{
public:
    label_writer(Name _name) : name(_name) {}
    template < class VertexOrEdge >
    void operator()(std::ostream& out, const VertexOrEdge& v) const
    {
        out << "[label=" << escape_dot_string(get(name, v)) << "]";
    }

private:
    Name name;
};
template < class Name > inline label_writer< Name > make_label_writer(Name n)
{
    return label_writer< Name >(n);
}

enum edge_attribute_t
{
    edge_attribute = 1111
};
enum vertex_attribute_t
{
    vertex_attribute = 2222
};
enum graph_graph_attribute_t
{
    graph_graph_attribute = 3333
};
enum graph_vertex_attribute_t
{
    graph_vertex_attribute = 4444
};
enum graph_edge_attribute_t
{
    graph_edge_attribute = 5555
};

BOOST_INSTALL_PROPERTY(edge, attribute);
BOOST_INSTALL_PROPERTY(vertex, attribute);
BOOST_INSTALL_PROPERTY(graph, graph_attribute);
BOOST_INSTALL_PROPERTY(graph, vertex_attribute);
BOOST_INSTALL_PROPERTY(graph, edge_attribute);

template < class Attribute >
inline void write_attributes(const Attribute& attr, std::ostream& out)
{
    typename Attribute::const_iterator i, iend;
    i = attr.begin();
    iend = attr.end();

    while (i != iend)
    {
        out << i->first << "=" << escape_dot_string(i->second);
        ++i;
        if (i != iend)
            out << ", ";
    }
}

template < typename Attributes >
inline void write_all_attributes(
    Attributes attributes, const std::string& name, std::ostream& out)
{
    typename Attributes::const_iterator i = attributes.begin(),
                                        end = attributes.end();
    if (i != end)
    {
        out << name << " [\n";
        write_attributes(attributes, out);
        out << "];\n";
    }
}

inline void write_all_attributes(
    detail::error_property_not_found, const std::string&, std::ostream&)
{
    // Do nothing - no attributes exist
}

template < typename GraphGraphAttributes, typename GraphNodeAttributes,
    typename GraphEdgeAttributes >
struct graph_attributes_writer
{
    graph_attributes_writer(
        GraphGraphAttributes gg, GraphNodeAttributes gn, GraphEdgeAttributes ge)
    : g_attributes(gg), n_attributes(gn), e_attributes(ge)
    {
    }

    void operator()(std::ostream& out) const
    {
        write_all_attributes(g_attributes, "graph", out);
        write_all_attributes(n_attributes, "node", out);
        write_all_attributes(e_attributes, "edge", out);
    }
    GraphGraphAttributes g_attributes;
    GraphNodeAttributes n_attributes;
    GraphEdgeAttributes e_attributes;
};

template < typename GAttrMap, typename NAttrMap, typename EAttrMap >
graph_attributes_writer< GAttrMap, NAttrMap, EAttrMap >
make_graph_attributes_writer(
    const GAttrMap& g_attr, const NAttrMap& n_attr, const EAttrMap& e_attr)
{
    return graph_attributes_writer< GAttrMap, NAttrMap, EAttrMap >(
        g_attr, n_attr, e_attr);
}

template < typename Graph >
graph_attributes_writer<
    typename graph_property< Graph, graph_graph_attribute_t >::type,
    typename graph_property< Graph, graph_vertex_attribute_t >::type,
    typename graph_property< Graph, graph_edge_attribute_t >::type >
make_graph_attributes_writer(const Graph& g)
{
    typedef typename graph_property< Graph, graph_graph_attribute_t >::type
        GAttrMap;
    typedef typename graph_property< Graph, graph_vertex_attribute_t >::type
        NAttrMap;
    typedef
        typename graph_property< Graph, graph_edge_attribute_t >::type EAttrMap;
    GAttrMap gam = get_property(g, graph_graph_attribute);
    NAttrMap nam = get_property(g, graph_vertex_attribute);
    EAttrMap eam = get_property(g, graph_edge_attribute);
    graph_attributes_writer< GAttrMap, NAttrMap, EAttrMap > writer(
        gam, nam, eam);
    return writer;
}

template < typename AttributeMap > struct attributes_writer
{
    attributes_writer(AttributeMap attr) : attributes(attr) {}

    template < class VorE >
    void operator()(std::ostream& out, const VorE& e) const
    {
        this->write_attribute(out, attributes[e]);
    }

private:
    template < typename AttributeSequence >
    void write_attribute(std::ostream& out, const AttributeSequence& seq) const
    {
        if (!seq.empty())
        {
            out << "[";
            write_attributes(seq, out);
            out << "]";
        }
    }

    void write_attribute(std::ostream&, detail::error_property_not_found) const
    {
    }
    AttributeMap attributes;
};

template < typename Graph >
attributes_writer<
    typename property_map< Graph, edge_attribute_t >::const_type >
make_edge_attributes_writer(const Graph& g)
{
    typedef typename property_map< Graph, edge_attribute_t >::const_type
        EdgeAttributeMap;
    return attributes_writer< EdgeAttributeMap >(get(edge_attribute, g));
}

template < typename Graph >
attributes_writer<
    typename property_map< Graph, vertex_attribute_t >::const_type >
make_vertex_attributes_writer(const Graph& g)
{
    typedef typename property_map< Graph, vertex_attribute_t >::const_type
        VertexAttributeMap;
    return attributes_writer< VertexAttributeMap >(get(vertex_attribute, g));
}

template < typename Graph, typename VertexPropertiesWriter,
    typename EdgePropertiesWriter, typename GraphPropertiesWriter,
    typename VertexID >
inline void write_graphviz(std::ostream& out, const Graph& g,
    VertexPropertiesWriter vpw, EdgePropertiesWriter epw,
    GraphPropertiesWriter gpw,
    VertexID vertex_id BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< Graph >));

    typedef typename graph_traits< Graph >::directed_category cat_type;
    typedef graphviz_io_traits< cat_type > Traits;
    std::string name = "G";
    out << Traits::name() << " " << escape_dot_string(name) << " {"
        << std::endl;

    gpw(out); // print graph properties

    typename graph_traits< Graph >::vertex_iterator i, end;

    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        out << escape_dot_string(get(vertex_id, *i));
        vpw(out, *i); // print vertex attributes
        out << ";" << std::endl;
    }
    typename graph_traits< Graph >::edge_iterator ei, edge_end;
    for (boost::tie(ei, edge_end) = edges(g); ei != edge_end; ++ei)
    {
        out << escape_dot_string(get(vertex_id, source(*ei, g)))
            << Traits::delimiter()
            << escape_dot_string(get(vertex_id, target(*ei, g))) << " ";
        epw(out, *ei); // print edge attributes
        out << ";" << std::endl;
    }
    out << "}" << std::endl;
}

template < typename Graph, typename VertexPropertiesWriter,
    typename EdgePropertiesWriter, typename GraphPropertiesWriter >
inline void write_graphviz(std::ostream& out, const Graph& g,
    VertexPropertiesWriter vpw, EdgePropertiesWriter epw,
    GraphPropertiesWriter gpw BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    write_graphviz(out, g, vpw, epw, gpw, get(vertex_index, g));
}

template < typename Graph >
inline void write_graphviz(std::ostream& out,
    const Graph& g BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    default_writer dw;
    default_writer gw;
    write_graphviz(out, g, dw, dw, gw);
}

template < typename Graph, typename VertexWriter >
inline void write_graphviz(std::ostream& out, const Graph& g,
    VertexWriter vw BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    default_writer dw;
    default_writer gw;
    write_graphviz(out, g, vw, dw, gw);
}

template < typename Graph, typename VertexWriter, typename EdgeWriter >
inline void write_graphviz(std::ostream& out, const Graph& g, VertexWriter vw,
    EdgeWriter ew BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    default_writer gw;
    write_graphviz(out, g, vw, ew, gw);
}

namespace detail
{

    template < class Graph_, class RandomAccessIterator, class VertexID >
    void write_graphviz_subgraph(std::ostream& out, const subgraph< Graph_ >& g,
        RandomAccessIterator vertex_marker, RandomAccessIterator edge_marker,
        VertexID vertex_id)
    {
        typedef subgraph< Graph_ > Graph;
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        typedef typename graph_traits< Graph >::directed_category cat_type;
        typedef graphviz_io_traits< cat_type > Traits;

        typedef typename graph_property< Graph, graph_name_t >::type NameType;
        const NameType& g_name = get_property(g, graph_name);

        if (g.is_root())
            out << Traits::name();
        else
            out << "subgraph";

        out << " " << escape_dot_string(g_name) << " {" << std::endl;

        typename Graph::const_children_iterator i_child, j_child;

        // print graph/node/edge attributes
        make_graph_attributes_writer(g)(out);

        // print subgraph
        for (boost::tie(i_child, j_child) = g.children(); i_child != j_child;
             ++i_child)
            write_graphviz_subgraph(
                out, *i_child, vertex_marker, edge_marker, vertex_id);

        // Print out vertices and edges not in the subgraphs.

        typename graph_traits< Graph >::vertex_iterator i, end;
        typename graph_traits< Graph >::edge_iterator ei, edge_end;

        for (boost::tie(i, end) = vertices(g); i != end; ++i)
        {
            Vertex v = g.local_to_global(*i);
            int pos = get(vertex_id, v);
            if (vertex_marker[pos])
            {
                vertex_marker[pos] = false;
                out << escape_dot_string(pos);
                make_vertex_attributes_writer(g.root())(out, v);
                out << ";" << std::endl;
            }
        }

        for (boost::tie(ei, edge_end) = edges(g); ei != edge_end; ++ei)
        {
            Vertex u = g.local_to_global(source(*ei, g)),
                   v = g.local_to_global(target(*ei, g));
            int pos = get(get(edge_index, g.root()), g.local_to_global(*ei));
            if (edge_marker[pos])
            {
                edge_marker[pos] = false;
                out << escape_dot_string(get(vertex_id, u)) << " "
                    << Traits::delimiter() << " "
                    << escape_dot_string(get(vertex_id, v));
                make_edge_attributes_writer(g)(
                    out, *ei); // print edge properties
                out << ";" << std::endl;
            }
        }
        out << "}" << std::endl;
    }
} // namespace detail

// requires graph_name graph property
template < typename Graph >
void write_graphviz(std::ostream& out, const subgraph< Graph >& g)
{
    std::vector< bool > edge_marker(num_edges(g), true);
    std::vector< bool > vertex_marker(num_vertices(g), true);

    detail::write_graphviz_subgraph(out, g, vertex_marker.begin(),
        edge_marker.begin(), get(vertex_index, g));
}

template < typename Graph >
void write_graphviz(const std::string& filename, const subgraph< Graph >& g)
{
    std::ofstream out(filename.c_str());
    std::vector< bool > edge_marker(num_edges(g), true);
    std::vector< bool > vertex_marker(num_vertices(g), true);

    detail::write_graphviz_subgraph(out, g, vertex_marker.begin(),
        edge_marker.begin(), get(vertex_index, g));
}

template < typename Graph, typename VertexID >
void write_graphviz(
    std::ostream& out, const subgraph< Graph >& g, VertexID vertex_id)
{
    std::vector< bool > edge_marker(num_edges(g), true);
    std::vector< bool > vertex_marker(num_vertices(g), true);

    detail::write_graphviz_subgraph(
        out, g, vertex_marker.begin(), edge_marker.begin(), vertex_id);
}

template < typename Graph, typename VertexID >
void write_graphviz(
    const std::string& filename, const subgraph< Graph >& g, VertexID vertex_id)
{
    std::ofstream out(filename.c_str());
    std::vector< bool > edge_marker(num_edges(g), true);
    std::vector< bool > vertex_marker(num_vertices(g), true);

    detail::write_graphviz_subgraph(
        out, g, vertex_marker.begin(), edge_marker.begin(), vertex_id);
}

#if 0
  // This interface has not worked for a long time
  typedef std::map<std::string, std::string> GraphvizAttrList;

  typedef property<vertex_attribute_t, GraphvizAttrList>
          GraphvizVertexProperty;

  typedef property<edge_attribute_t, GraphvizAttrList,
                   property<edge_index_t, int> >
          GraphvizEdgeProperty;

  typedef property<graph_graph_attribute_t, GraphvizAttrList,
                   property<graph_vertex_attribute_t, GraphvizAttrList,
                   property<graph_edge_attribute_t, GraphvizAttrList,
                   property<graph_name_t, std::string> > > >
          GraphvizGraphProperty;

  typedef subgraph<adjacency_list<vecS,
                   vecS, directedS,
                   GraphvizVertexProperty,
                   GraphvizEdgeProperty,
                   GraphvizGraphProperty> >
          GraphvizDigraph;

  typedef subgraph<adjacency_list<vecS,
                   vecS, undirectedS,
                   GraphvizVertexProperty,
                   GraphvizEdgeProperty,
                   GraphvizGraphProperty> >
          GraphvizGraph;

  // These four require linking the BGL-Graphviz library: libbgl-viz.a
  // from the /src directory.
  // Library has not existed for a while
  extern void read_graphviz(const std::string& file, GraphvizDigraph& g);
  extern void read_graphviz(FILE* file, GraphvizDigraph& g);

  extern void read_graphviz(const std::string& file, GraphvizGraph& g);
  extern void read_graphviz(FILE* file, GraphvizGraph& g);
#endif

class dynamic_properties_writer
{
public:
    dynamic_properties_writer(const dynamic_properties& dp) : dp(&dp) {}

    template < typename Descriptor >
    void operator()(std::ostream& out, Descriptor key) const
    {
        bool first = true;
        for (dynamic_properties::const_iterator i = dp->begin(); i != dp->end();
             ++i)
        {
            if (typeid(key) == i->second->key())
            {
                if (first)
                    out << " [";
                else
                    out << ", ";
                first = false;

                out << i->first << "="
                    << escape_dot_string(i->second->get_string(key));
            }
        }

        if (!first)
            out << "]";
    }

private:
    const dynamic_properties* dp;
};

class dynamic_vertex_properties_writer
{
public:
    dynamic_vertex_properties_writer(
        const dynamic_properties& dp, const std::string& node_id)
    : dp(&dp), node_id(&node_id)
    {
    }

    template < typename Descriptor >
    void operator()(std::ostream& out, Descriptor key) const
    {
        bool first = true;
        for (dynamic_properties::const_iterator i = dp->begin(); i != dp->end();
             ++i)
        {
            if (typeid(key) == i->second->key() && i->first != *node_id)
            {
                if (first)
                    out << " [";
                else
                    out << ", ";
                first = false;

                out << i->first << "="
                    << escape_dot_string(i->second->get_string(key));
            }
        }

        if (!first)
            out << "]";
    }

private:
    const dynamic_properties* dp;
    const std::string* node_id;
};

template < typename Graph > class dynamic_graph_properties_writer
{
public:
    dynamic_graph_properties_writer(
        const dynamic_properties& dp, const Graph& g)
    : g(&g), dp(&dp)
    {
    }

    void operator()(std::ostream& out) const
    {
        for (dynamic_properties::const_iterator i = dp->begin(); i != dp->end();
             ++i)
        {
            if (typeid(Graph*) == i->second->key())
            {
                // const_cast here is to match interface used in read_graphviz
                out << i->first << "="
                    << escape_dot_string(
                           i->second->get_string(const_cast< Graph* >(g)))
                    << ";\n";
            }
        }
    }

private:
    const Graph* g;
    const dynamic_properties* dp;
};

namespace graph
{
    namespace detail
    {

        template < typename Vertex > struct node_id_property_map
        {
            typedef std::string value_type;
            typedef value_type reference;
            typedef Vertex key_type;
            typedef readable_property_map_tag category;

            node_id_property_map() {}

            node_id_property_map(
                const dynamic_properties& dp, const std::string& node_id)
            : dp(&dp), node_id(&node_id)
            {
            }

            const dynamic_properties* dp;
            const std::string* node_id;
        };

        template < typename Vertex >
        inline std::string get(node_id_property_map< Vertex > pm,
            typename node_id_property_map< Vertex >::key_type v)
        {
            return get(*pm.node_id, *pm.dp, v);
        }

    }
} // end namespace graph::detail

template < typename Graph >
inline void write_graphviz_dp(std::ostream& out, const Graph& g,
    const dynamic_properties& dp,
    const std::string& node_id
    = "node_id" BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, vertex_list_graph_tag))
{
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    write_graphviz_dp(out, g, dp, node_id,
        graph::detail::node_id_property_map< Vertex >(dp, node_id));
}

template < typename Graph, typename VertexID >
void write_graphviz_dp(std::ostream& out, const Graph& g,
    const dynamic_properties& dp, const std::string& node_id,
    VertexID id BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, vertex_list_graph_tag))
{
    write_graphviz(out, g,
        /*vertex_writer=*/dynamic_vertex_properties_writer(dp, node_id),
        /*edge_writer=*/dynamic_properties_writer(dp),
        /*graph_writer=*/dynamic_graph_properties_writer< Graph >(dp, g), id);
}

/////////////////////////////////////////////////////////////////////////////
// Graph reader exceptions
/////////////////////////////////////////////////////////////////////////////
struct BOOST_SYMBOL_VISIBLE graph_exception : public std::exception
{
    ~graph_exception() throw() BOOST_OVERRIDE {}
    const char* what() const throw() BOOST_OVERRIDE = 0;
};

struct BOOST_SYMBOL_VISIBLE bad_parallel_edge : public graph_exception
{
    std::string from;
    std::string to;
    mutable std::string statement;
    bad_parallel_edge(const std::string& i, const std::string& j)
    : from(i), to(j)
    {
    }

    ~bad_parallel_edge() throw() BOOST_OVERRIDE {}
    const char* what() const throw() BOOST_OVERRIDE
    {
        if (statement.empty())
            statement = std::string("Failed to add parallel edge: (") + from
                + "," + to + ")\n";

        return statement.c_str();
    }
};

struct BOOST_SYMBOL_VISIBLE directed_graph_error : public graph_exception
{
    ~directed_graph_error() throw() BOOST_OVERRIDE {}
    const char* what() const throw() BOOST_OVERRIDE
    {
        return "read_graphviz: "
               "Tried to read a directed graph into an undirected graph.";
    }
};

struct BOOST_SYMBOL_VISIBLE undirected_graph_error : public graph_exception
{
    ~undirected_graph_error() throw() BOOST_OVERRIDE {}
    const char* what() const throw() BOOST_OVERRIDE
    {
        return "read_graphviz: "
               "Tried to read an undirected graph into a directed graph.";
    }
};

struct BOOST_SYMBOL_VISIBLE bad_graphviz_syntax : public graph_exception
{
    std::string errmsg;
    bad_graphviz_syntax(const std::string& errmsg) : errmsg(errmsg) {}
    const char* what() const throw() BOOST_OVERRIDE { return errmsg.c_str(); }
    ~bad_graphviz_syntax() throw() BOOST_OVERRIDE {}
};

namespace detail
{
    namespace graph
    {

        typedef std::string id_t;
        typedef id_t node_t;

        // edges are not uniquely determined by adjacent nodes
        class edge_t
        {
            int idx_;
            explicit edge_t(int i) : idx_(i) {}

        public:
            static edge_t new_edge()
            {
                static int idx = 0;
                return edge_t(idx++);
            }

            bool operator==(const edge_t& rhs) const
            {
                return idx_ == rhs.idx_;
            }
            bool operator<(const edge_t& rhs) const { return idx_ < rhs.idx_; }
        };

        class mutate_graph
        {
        public:
            virtual ~mutate_graph() {}
            virtual bool is_directed() const = 0;
            virtual void do_add_vertex(const node_t& node) = 0;

            virtual void do_add_edge(
                const edge_t& edge, const node_t& source, const node_t& target)
                = 0;

            virtual void set_node_property(
                const id_t& key, const node_t& node, const id_t& value)
                = 0;

            virtual void set_edge_property(
                const id_t& key, const edge_t& edge, const id_t& value)
                = 0;

            virtual void // RG: need new second parameter to support BGL
                         // subgraphs
            set_graph_property(const id_t& key, const id_t& value)
                = 0;

            virtual void finish_building_graph() = 0;
        };

        template < typename MutableGraph >
        class mutate_graph_impl : public mutate_graph
        {
            typedef typename graph_traits< MutableGraph >::vertex_descriptor
                bgl_vertex_t;
            typedef typename graph_traits< MutableGraph >::edge_descriptor
                bgl_edge_t;

        public:
            mutate_graph_impl(MutableGraph& graph, dynamic_properties& dp,
                std::string node_id_prop)
            : graph_(graph), dp_(dp), node_id_prop_(node_id_prop)
            {
            }

            ~mutate_graph_impl() BOOST_OVERRIDE {}

            bool is_directed() const BOOST_OVERRIDE
            {
                return boost::is_convertible<
                    typename boost::graph_traits<
                        MutableGraph >::directed_category,
                    boost::directed_tag >::value;
            }

            void do_add_vertex(const node_t& node) BOOST_OVERRIDE
            {
                // Add the node to the graph.
                bgl_vertex_t v = add_vertex(graph_);

                // Set up a mapping from name to BGL vertex.
                bgl_nodes.insert(std::make_pair(node, v));

                // node_id_prop_ allows the caller to see the real id names for
                // nodes.
                put(node_id_prop_, dp_, v, node);
            }

            void do_add_edge(const edge_t& edge, const node_t& source,
                const node_t& target) BOOST_OVERRIDE
            {
                std::pair< bgl_edge_t, bool > result
                    = add_edge(bgl_nodes[source], bgl_nodes[target], graph_);

                if (!result.second)
                {
                    // In the case of no parallel edges allowed
                    boost::throw_exception(bad_parallel_edge(source, target));
                }
                else
                {
                    bgl_edges.insert(std::make_pair(edge, result.first));
                }
            }

            void set_node_property(const id_t& key, const node_t& node,
                const id_t& value) BOOST_OVERRIDE
            {
                put(key, dp_, bgl_nodes[node], value);
            }

            void set_edge_property(const id_t& key, const edge_t& edge,
                const id_t& value) BOOST_OVERRIDE
            {
                put(key, dp_, bgl_edges[edge], value);
            }

            void set_graph_property(const id_t& key,
                const id_t& value) BOOST_OVERRIDE
            {
                /* RG: pointer to graph prevents copying */
                put(key, dp_, &graph_, value);
            }

            void finish_building_graph() BOOST_OVERRIDE {}

        protected:
            MutableGraph& graph_;
            dynamic_properties& dp_;
            std::string node_id_prop_;
            std::map< node_t, bgl_vertex_t > bgl_nodes;
            std::map< edge_t, bgl_edge_t > bgl_edges;
        };

        template < typename Directed, typename VertexProperty,
            typename EdgeProperty, typename GraphProperty, typename Vertex,
            typename EdgeIndex >
        class mutate_graph_impl< compressed_sparse_row_graph< Directed,
            VertexProperty, EdgeProperty, GraphProperty, Vertex, EdgeIndex > >
        : public mutate_graph
        {
            typedef compressed_sparse_row_graph< Directed, VertexProperty,
                EdgeProperty, GraphProperty, Vertex, EdgeIndex >
                CSRGraph;
            typedef typename graph_traits< CSRGraph >::vertices_size_type
                bgl_vertex_t;
            typedef
                typename graph_traits< CSRGraph >::edges_size_type bgl_edge_t;
            typedef typename graph_traits< CSRGraph >::edge_descriptor
                edge_descriptor;

        public:
            mutate_graph_impl(CSRGraph& graph, dynamic_properties& dp,
                std::string node_id_prop)
            : graph_(graph)
            , dp_(dp)
            , vertex_count(0)
            , node_id_prop_(node_id_prop)
            {
            }

            ~mutate_graph_impl() BOOST_OVERRIDE {}

            void finish_building_graph() BOOST_OVERRIDE
            {
                typedef compressed_sparse_row_graph< directedS, no_property,
                    bgl_edge_t, GraphProperty, Vertex, EdgeIndex >
                    TempCSRGraph;
                TempCSRGraph temp(edges_are_unsorted_multi_pass,
                    edges_to_add.begin(), edges_to_add.end(),
                    counting_iterator< bgl_edge_t >(0), vertex_count);
                set_property(temp, graph_all, get_property(graph_, graph_all));
                graph_.assign(temp); // Copies structure, not properties
                std::vector< edge_descriptor > edge_permutation_from_sorting(
                    num_edges(temp));
                BGL_FORALL_EDGES_T(e, temp, TempCSRGraph)
                {
                    edge_permutation_from_sorting[temp[e]] = e;
                }
                typedef boost::tuple< id_t, bgl_vertex_t, id_t > v_prop;
                BOOST_FOREACH (const v_prop& t, vertex_props)
                {
                    put(boost::get< 0 >(t), dp_, boost::get< 1 >(t),
                        boost::get< 2 >(t));
                }
                typedef boost::tuple< id_t, bgl_edge_t, id_t > e_prop;
                BOOST_FOREACH (const e_prop& t, edge_props)
                {
                    put(boost::get< 0 >(t), dp_,
                        edge_permutation_from_sorting[boost::get< 1 >(t)],
                        boost::get< 2 >(t));
                }
            }

            bool is_directed() const BOOST_OVERRIDE
            {
                return boost::is_convertible<
                    typename boost::graph_traits< CSRGraph >::directed_category,
                    boost::directed_tag >::value;
            }

            void do_add_vertex(const node_t& node) BOOST_OVERRIDE
            {
                // Add the node to the graph.
                bgl_vertex_t v = vertex_count++;

                // Set up a mapping from name to BGL vertex.
                bgl_nodes.insert(std::make_pair(node, v));

                // node_id_prop_ allows the caller to see the real id names for
                // nodes.
                vertex_props.push_back(
                    boost::make_tuple(node_id_prop_, v, node));
            }

            void do_add_edge(const edge_t& edge, const node_t& source,
                const node_t& target) BOOST_OVERRIDE
            {
                bgl_edge_t result = edges_to_add.size();
                edges_to_add.push_back(
                    std::make_pair(bgl_nodes[source], bgl_nodes[target]));
                bgl_edges.insert(std::make_pair(edge, result));
            }

            void set_node_property(const id_t& key, const node_t& node,
                const id_t& value) BOOST_OVERRIDE
            {
                vertex_props.push_back(
                    boost::make_tuple(key, bgl_nodes[node], value));
            }

            void set_edge_property(const id_t& key, const edge_t& edge,
                const id_t& value) BOOST_OVERRIDE
            {
                edge_props.push_back(
                    boost::make_tuple(key, bgl_edges[edge], value));
            }

            void set_graph_property(const id_t& key,
                const id_t& value) BOOST_OVERRIDE
            {
                /* RG: pointer to graph prevents copying */
                put(key, dp_, &graph_, value);
            }

        protected:
            CSRGraph& graph_;
            dynamic_properties& dp_;
            bgl_vertex_t vertex_count;
            std::string node_id_prop_;
            std::vector< boost::tuple< id_t, bgl_vertex_t, id_t > >
                vertex_props;
            std::vector< boost::tuple< id_t, bgl_edge_t, id_t > > edge_props;
            std::vector< std::pair< bgl_vertex_t, bgl_vertex_t > > edges_to_add;
            std::map< node_t, bgl_vertex_t > bgl_nodes;
            std::map< edge_t, bgl_edge_t > bgl_edges;
        };

    }
}
} // end namespace boost::detail::graph

#ifdef BOOST_GRAPH_USE_SPIRIT_PARSER
#ifndef BOOST_GRAPH_READ_GRAPHVIZ_ITERATORS
#define BOOST_GRAPH_READ_GRAPHVIZ_ITERATORS
#endif
#include <boost/graph/detail/read_graphviz_spirit.hpp>
#else // New default parser
#include <boost/graph/detail/read_graphviz_new.hpp>
#endif // BOOST_GRAPH_USE_SPIRIT_PARSER

namespace boost
{

// Parse the passed string as a GraphViz dot file.
template < typename MutableGraph >
bool read_graphviz(const std::string& data, MutableGraph& graph,
    dynamic_properties& dp, std::string const& node_id = "node_id")
{
#ifdef BOOST_GRAPH_USE_SPIRIT_PARSER
    return read_graphviz_spirit(data.begin(), data.end(), graph, dp, node_id);
#else // Non-Spirit parser
    return read_graphviz_new(data, graph, dp, node_id);
#endif
}

// Parse the passed iterator range as a GraphViz dot file.
template < typename InputIterator, typename MutableGraph >
bool read_graphviz(InputIterator user_first, InputIterator user_last,
    MutableGraph& graph, dynamic_properties& dp,
    std::string const& node_id = "node_id")
{
#ifdef BOOST_GRAPH_USE_SPIRIT_PARSER
    typedef InputIterator is_t;
    typedef boost::spirit::classic::multi_pass< is_t > iterator_t;

    iterator_t first(boost::spirit::classic::make_multi_pass(user_first));
    iterator_t last(boost::spirit::classic::make_multi_pass(user_last));

    return read_graphviz_spirit(first, last, graph, dp, node_id);
#else // Non-Spirit parser
    return read_graphviz_new(
        std::string(user_first, user_last), graph, dp, node_id);
#endif
}

// Parse the passed stream as a GraphViz dot file.
template < typename MutableGraph >
bool read_graphviz(std::istream& in, MutableGraph& graph,
    dynamic_properties& dp, std::string const& node_id = "node_id")
{
    typedef std::istream_iterator< char > is_t;
    in >> std::noskipws;
    return read_graphviz(is_t(in), is_t(), graph, dp, node_id);
}

} // namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/graphviz.hpp>)

#endif // BOOST_GRAPHVIZ_HPP

/* graphviz.hpp
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
*/