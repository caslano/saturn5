// Copyright (C) 2006  Tiago de Paula Peixoto <tiago@forked.de>
// Copyright (C) 2004  The Trustees of Indiana University.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  Authors: Douglas Gregor
//           Andrew Lumsdaine
//           Tiago de Paula Peixoto

#ifndef BOOST_GRAPH_GRAPHML_HPP
#define BOOST_GRAPH_GRAPHML_HPP

#include <boost/config.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/graph/dll_import_export.hpp>
#include <boost/graph/graphviz.hpp> // for exceptions
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/property_tree/detail/xml_parser_utils.hpp>
#include <boost/throw_exception.hpp>
#include <exception>
#include <sstream>
#include <typeinfo>

namespace boost
{

/////////////////////////////////////////////////////////////////////////////
// Graph reader exceptions
/////////////////////////////////////////////////////////////////////////////
struct BOOST_SYMBOL_VISIBLE parse_error : public graph_exception
{
    parse_error(const std::string& err)
    {
        error = err;
        statement = "parse error: " + error;
    }
    ~parse_error() throw() BOOST_OVERRIDE {}
    const char* what() const throw() BOOST_OVERRIDE { return statement.c_str(); }
    std::string statement;
    std::string error;
};

class mutate_graph
{
public:
    virtual ~mutate_graph() {}
    virtual bool is_directed() const = 0;

    virtual boost::any do_add_vertex() = 0;
    virtual std::pair< boost::any, bool > do_add_edge(
        boost::any source, boost::any target)
        = 0;

    virtual void set_graph_property(const std::string& name,
        const std::string& value, const std::string& value_type)
        = 0;

    virtual void set_vertex_property(const std::string& name, boost::any vertex,
        const std::string& value, const std::string& value_type)
        = 0;

    virtual void set_edge_property(const std::string& name, boost::any edge,
        const std::string& value, const std::string& value_type)
        = 0;
};

template < typename MutableGraph > class mutate_graph_impl : public mutate_graph
{
    typedef typename graph_traits< MutableGraph >::vertex_descriptor
        vertex_descriptor;
    typedef
        typename graph_traits< MutableGraph >::edge_descriptor edge_descriptor;

public:
    mutate_graph_impl(MutableGraph& g, dynamic_properties& dp)
    : m_g(g), m_dp(dp)
    {
    }

    bool is_directed() const BOOST_OVERRIDE
    {
        return is_convertible<
            typename graph_traits< MutableGraph >::directed_category,
            directed_tag >::value;
    }

    any do_add_vertex() BOOST_OVERRIDE { return any(add_vertex(m_g)); }

    std::pair< any, bool > do_add_edge(any source, any target) BOOST_OVERRIDE
    {
        std::pair< edge_descriptor, bool > retval
            = add_edge(any_cast< vertex_descriptor >(source),
                any_cast< vertex_descriptor >(target), m_g);
        return std::make_pair(any(retval.first), retval.second);
    }

    void set_graph_property(const std::string& name,
        const std::string& value, const std::string& value_type) BOOST_OVERRIDE
    {
        bool type_found = false;
        try
        {
            mpl::for_each< value_types >(
                put_property< MutableGraph*, value_types >(name, m_dp, &m_g,
                    value, value_type, m_type_names, type_found));
        }
        catch (const bad_lexical_cast&)
        {
            BOOST_THROW_EXCEPTION(parse_error("invalid value \"" + value
                + "\" for key " + name + " of type " + value_type));
        }
        if (!type_found)
        {
            BOOST_THROW_EXCEPTION(parse_error(
                "unrecognized type \"" + value_type + "\" for key " + name));
        }
    }

    void set_vertex_property(const std::string& name, any vertex,
        const std::string& value, const std::string& value_type) BOOST_OVERRIDE
    {
        bool type_found = false;
        try
        {
            mpl::for_each< value_types >(
                put_property< vertex_descriptor, value_types >(name, m_dp,
                    any_cast< vertex_descriptor >(vertex), value, value_type,
                    m_type_names, type_found));
        }
        catch (const bad_lexical_cast&)
        {
            BOOST_THROW_EXCEPTION(parse_error("invalid value \"" + value
                + "\" for key " + name + " of type " + value_type));
        }
        if (!type_found)
        {
            BOOST_THROW_EXCEPTION(parse_error(
                "unrecognized type \"" + value_type + "\" for key " + name));
        }
    }

    void set_edge_property(const std::string& name, any edge,
        const std::string& value, const std::string& value_type) BOOST_OVERRIDE
    {
        bool type_found = false;
        try
        {
            mpl::for_each< value_types >(
                put_property< edge_descriptor, value_types >(name, m_dp,
                    any_cast< edge_descriptor >(edge), value, value_type,
                    m_type_names, type_found));
        }
        catch (const bad_lexical_cast&)
        {
            BOOST_THROW_EXCEPTION(parse_error("invalid value \"" + value
                + "\" for key " + name + " of type " + value_type));
        }
        if (!type_found)
        {
            BOOST_THROW_EXCEPTION(parse_error(
                "unrecognized type \"" + value_type + "\" for key " + name));
        }
    }

    template < typename Key, typename ValueVector > class put_property
    {
    public:
        put_property(const std::string& name, dynamic_properties& dp,
            const Key& key, const std::string& value,
            const std::string& value_type, const char** type_names,
            bool& type_found)
        : m_name(name)
        , m_dp(dp)
        , m_key(key)
        , m_value(value)
        , m_value_type(value_type)
        , m_type_names(type_names)
        , m_type_found(type_found)
        {
        }
        template < class Value > void operator()(Value)
        {
            if (m_value_type
                == m_type_names[mpl::find< ValueVector,
                    Value >::type::pos::value])
            {
                put(m_name, m_dp, m_key, lexical_cast< Value >(m_value));
                m_type_found = true;
            }
        }

    private:
        const std::string& m_name;
        dynamic_properties& m_dp;
        const Key& m_key;
        const std::string& m_value;
        const std::string& m_value_type;
        const char** m_type_names;
        bool& m_type_found;
    };

protected:
    MutableGraph& m_g;
    dynamic_properties& m_dp;
    typedef mpl::vector< bool, int, long, float, double, std::string >
        value_types;
    static const char* m_type_names[];
};

template < typename MutableGraph >
const char* mutate_graph_impl< MutableGraph >::m_type_names[]
    = { "boolean", "int", "long", "float", "double", "string" };

void BOOST_GRAPH_DECL read_graphml(
    std::istream& in, mutate_graph& g, size_t desired_idx);

template < typename MutableGraph >
void read_graphml(std::istream& in, MutableGraph& g, dynamic_properties& dp,
    size_t desired_idx = 0)
{
    mutate_graph_impl< MutableGraph > mg(g, dp);
    read_graphml(in, mg, desired_idx);
}

template < typename Types > class get_type_name
{
public:
    get_type_name(const std::type_info& type, const char** type_names,
        std::string& type_name)
    : m_type(type), m_type_names(type_names), m_type_name(type_name)
    {
    }
    template < typename Type > void operator()(Type)
    {
        if (typeid(Type) == m_type)
            m_type_name
                = m_type_names[mpl::find< Types, Type >::type::pos::value];
    }

private:
    const std::type_info& m_type;
    const char** m_type_names;
    std::string& m_type_name;
};

template < typename Graph, typename VertexIndexMap >
void write_graphml(std::ostream& out, const Graph& g,
    VertexIndexMap vertex_index, const dynamic_properties& dp,
    bool ordered_vertices = false)
{
    typedef typename graph_traits< Graph >::directed_category directed_category;
    typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor;
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;

    using boost::property_tree::xml_parser::encode_char_entities;

    BOOST_STATIC_CONSTANT(bool,
        graph_is_directed
        = (is_convertible< directed_category*, directed_tag* >::value));

    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" "
           "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
           "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns "
           "http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";

    typedef mpl::vector< bool, short, unsigned short, int, unsigned int, long,
        unsigned long, long long, unsigned long long, float, double,
        long double, std::string >
        value_types;
    const char* type_names[] = { "boolean", "int", "int", "int", "int", "long",
        "long", "long", "long", "float", "double", "double", "string" };
    std::map< std::string, std::string > graph_key_ids;
    std::map< std::string, std::string > vertex_key_ids;
    std::map< std::string, std::string > edge_key_ids;
    int key_count = 0;

    // Output keys
    for (dynamic_properties::const_iterator i = dp.begin(); i != dp.end(); ++i)
    {
        std::string key_id = "key" + lexical_cast< std::string >(key_count++);
        if (i->second->key() == typeid(Graph*))
            graph_key_ids[i->first] = key_id;
        else if (i->second->key() == typeid(vertex_descriptor))
            vertex_key_ids[i->first] = key_id;
        else if (i->second->key() == typeid(edge_descriptor))
            edge_key_ids[i->first] = key_id;
        else
            continue;
        std::string type_name = "string";
        mpl::for_each< value_types >(get_type_name< value_types >(
            i->second->value(), type_names, type_name));
        out << "  <key id=\"" << encode_char_entities(key_id) << "\" for=\""
            << (i->second->key() == typeid(Graph*)
                       ? "graph"
                       : (i->second->key() == typeid(vertex_descriptor)
                               ? "node"
                               : "edge"))
            << "\""
            << " attr.name=\"" << i->first << "\""
            << " attr.type=\"" << type_name << "\""
            << " />\n";
    }

    out << "  <graph id=\"G\" edgedefault=\""
        << (graph_is_directed ? "directed" : "undirected") << "\""
        << " parse.nodeids=\"" << (ordered_vertices ? "canonical" : "free")
        << "\""
        << " parse.edgeids=\"canonical\" parse.order=\"nodesfirst\">\n";

    // Output graph data
    for (dynamic_properties::const_iterator i = dp.begin(); i != dp.end(); ++i)
    {
        if (i->second->key() == typeid(Graph*))
        {
            // The const_cast here is just to get typeid correct for property
            // map key; the graph should not be mutated using it.
            out << "   <data key=\"" << graph_key_ids[i->first] << "\">"
                << encode_char_entities(
                       i->second->get_string(const_cast< Graph* >(&g)))
                << "</data>\n";
        }
    }

    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator;
    vertex_iterator v, v_end;
    for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v)
    {
        out << "    <node id=\"n" << get(vertex_index, *v) << "\">\n";
        // Output data
        for (dynamic_properties::const_iterator i = dp.begin(); i != dp.end();
             ++i)
        {
            if (i->second->key() == typeid(vertex_descriptor))
            {
                out << "      <data key=\"" << vertex_key_ids[i->first] << "\">"
                    << encode_char_entities(i->second->get_string(*v))
                    << "</data>\n";
            }
        }
        out << "    </node>\n";
    }

    typedef typename graph_traits< Graph >::edge_iterator edge_iterator;
    edge_iterator e, e_end;
    typename graph_traits< Graph >::edges_size_type edge_count = 0;
    for (boost::tie(e, e_end) = edges(g); e != e_end; ++e)
    {
        out << "    <edge id=\"e" << edge_count++ << "\" source=\"n"
            << get(vertex_index, source(*e, g)) << "\" target=\"n"
            << get(vertex_index, target(*e, g)) << "\">\n";

        // Output data
        for (dynamic_properties::const_iterator i = dp.begin(); i != dp.end();
             ++i)
        {
            if (i->second->key() == typeid(edge_descriptor))
            {
                out << "      <data key=\"" << edge_key_ids[i->first] << "\">"
                    << encode_char_entities(i->second->get_string(*e))
                    << "</data>\n";
            }
        }
        out << "    </edge>\n";
    }

    out << "  </graph>\n"
        << "</graphml>\n";
}

template < typename Graph >
void write_graphml(std::ostream& out, const Graph& g,
    const dynamic_properties& dp, bool ordered_vertices = false)
{
    write_graphml(out, g, get(vertex_index, g), dp, ordered_vertices);
}

} // boost namespace

#endif // BOOST_GRAPH_GRAPHML_HPP

/* graphml.hpp
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
*/