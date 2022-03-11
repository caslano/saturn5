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
#include <typeinfo>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/property_tree/detail/xml_parser_utils.hpp>
#include <boost/throw_exception.hpp>
#include <exception>
#include <sstream>

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
    virtual ~parse_error() throw() {}
    virtual const char* what() const throw() { return statement.c_str(); }
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

    bool is_directed() const
    {
        return is_convertible<
            typename graph_traits< MutableGraph >::directed_category,
            directed_tag >::value;
    }

    virtual any do_add_vertex() { return any(add_vertex(m_g)); }

    virtual std::pair< any, bool > do_add_edge(any source, any target)
    {
        std::pair< edge_descriptor, bool > retval
            = add_edge(any_cast< vertex_descriptor >(source),
                any_cast< vertex_descriptor >(target), m_g);
        return std::make_pair(any(retval.first), retval.second);
    }

    virtual void set_graph_property(const std::string& name,
        const std::string& value, const std::string& value_type)
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

    virtual void set_vertex_property(const std::string& name, any vertex,
        const std::string& value, const std::string& value_type)
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

    virtual void set_edge_property(const std::string& name, any edge,
        const std::string& value, const std::string& value_type)
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