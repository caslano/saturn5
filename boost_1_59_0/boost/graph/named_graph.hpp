// Copyright (C) 2007 Douglas Gregor

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Provides support for named vertices in graphs, allowing one to more
// easily associate unique external names (URLs, city names, employee
// ID numbers, etc.) with the vertices of a graph.
#ifndef BOOST_GRAPH_NAMED_GRAPH_HPP
#define BOOST_GRAPH_NAMED_GRAPH_HPP

#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/functional/hash.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/optional.hpp>
#include <boost/pending/property.hpp> // for boost::lookup_one_property
#include <boost/pending/container_traits.hpp>
#include <boost/throw_exception.hpp>
#include <boost/tuple/tuple.hpp> // for boost::make_tuple
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <functional> // for std::equal_to
#include <stdexcept> // for std::runtime_error
#include <utility> // for std::pair

namespace boost
{
namespace graph
{

    /*******************************************************************
     * User-customized traits                                          *
     *******************************************************************/

    /**
     * @brief Trait used to extract the internal vertex name from a vertex
     * property.
     *
     * To enable the use of internal vertex names in a graph type,
     * specialize the @c internal_vertex_name trait for your graph
     * property (e.g., @c a City class, which stores information about the
     * vertices in a road map).
     */
    template < typename VertexProperty > struct internal_vertex_name
    {
        /**
         *  The @c type field provides a function object that extracts a key
         *  from the @c VertexProperty. The function object type must have a
         *  nested @c result_type that provides the type of the key. For
         *  more information, see the @c KeyExtractor concept in the
         *  Boost.MultiIndex documentation: @c type must either be @c void
         *  (if @c VertexProperty does not have an internal vertex name) or
         *  a model of @c KeyExtractor.
         */
        typedef void type;
    };

    /**
     * Extract the internal vertex name from a @c property structure by
     * looking at its base.
     */
    template < typename Tag, typename T, typename Base >
    struct internal_vertex_name< property< Tag, T, Base > >
    : internal_vertex_name< Base >
    {
    };

    /**
     * Construct an instance of @c VertexProperty directly from its
     * name. This function object should be used within the @c
     * internal_vertex_constructor trait.
     */
    template < typename VertexProperty > struct vertex_from_name
    {
    private:
        typedef typename internal_vertex_name< VertexProperty >::type
            extract_name_type;

        typedef typename remove_cv< typename remove_reference<
            typename extract_name_type::result_type >::type >::type
            vertex_name_type;

    public:
        typedef vertex_name_type argument_type;
        typedef VertexProperty result_type;

        VertexProperty operator()(const vertex_name_type& name)
        {
            return VertexProperty(name);
        }
    };

    /**
     * Throw an exception whenever one tries to construct a @c
     * VertexProperty instance from its name.
     */
    template < typename VertexProperty > struct cannot_add_vertex
    {
    private:
        typedef typename internal_vertex_name< VertexProperty >::type
            extract_name_type;

        typedef typename remove_cv< typename remove_reference<
            typename extract_name_type::result_type >::type >::type
            vertex_name_type;

    public:
        typedef vertex_name_type argument_type;
        typedef VertexProperty result_type;

        VertexProperty operator()(const vertex_name_type&)
        {
            boost::throw_exception(
                std::runtime_error("add_vertex: "
                                   "unable to create a vertex from its name"));
        }
    };

    /**
     * @brief Trait used to construct an instance of a @c VertexProperty,
     * which is a class type that stores the properties associated with a
     * vertex in a graph, from just the name of that vertex property. This
     * operation is used when an operation is required to map from a
     * vertex name to a vertex descriptor (e.g., to add an edge outgoing
     * from that vertex), but no vertex by the name exists. The function
     * object provided by this trait will be used to add new vertices
     * based only on their names. Since this cannot be done for arbitrary
     * types, the default behavior is to throw an exception when this
     * routine is called, which requires that all named vertices be added
     * before adding any edges by name.
     */
    template < typename VertexProperty > struct internal_vertex_constructor
    {
        /**
         * The @c type field provides a function object that constructs a
         * new instance of @c VertexProperty from the name of the vertex (as
         * determined by @c internal_vertex_name). The function object shall
         * accept a vertex name and return a @c VertexProperty. Predefined
         * options include:
         *
         *   @c vertex_from_name<VertexProperty>: construct an instance of
         *   @c VertexProperty directly from the name.
         *
         *   @c cannot_add_vertex<VertexProperty>: the default value, which
         *   throws an @c std::runtime_error if one attempts to add a vertex
         *   given just the name.
         */
        typedef cannot_add_vertex< VertexProperty > type;
    };

    /**
     * Extract the internal vertex constructor from a @c property structure by
     * looking at its base.
     */
    template < typename Tag, typename T, typename Base >
    struct internal_vertex_constructor< property< Tag, T, Base > >
    : internal_vertex_constructor< Base >
    {
    };

    /*******************************************************************
     * Named graph mixin                                               *
     *******************************************************************/

    /**
     * named_graph is a mixin that provides names for the vertices of a
     * graph, including a mapping from names to vertices. Graph types that
     * may or may not be have vertex names (depending on the properties
     * supplied by the user) should use maybe_named_graph.
     *
     * Template parameters:
     *
     *   Graph: the graph type that derives from named_graph
     *
     *   Vertex: the type of a vertex descriptor in Graph. Note: we cannot
     *   use graph_traits here, because the Graph is not yet defined.
     *
     *   VertexProperty: the type stored with each vertex in the Graph.
     */
    template < typename Graph, typename Vertex, typename VertexProperty >
    class named_graph
    {
    public:
        /// The type of the function object that extracts names from vertex
        /// properties.
        typedef typename internal_vertex_name< VertexProperty >::type
            extract_name_type;
        /// The type of the "bundled" property, from which the name can be
        /// extracted.
        typedef typename lookup_one_property< VertexProperty,
            vertex_bundle_t >::type bundled_vertex_property_type;

        /// The type of the function object that generates vertex properties
        /// from names, for the implicit addition of vertices.
        typedef typename internal_vertex_constructor< VertexProperty >::type
            vertex_constructor_type;

        /// The type used to name vertices in the graph
        typedef typename remove_cv< typename remove_reference<
            typename extract_name_type::result_type >::type >::type
            vertex_name_type;

        /// The type of vertex descriptors in the graph
        typedef Vertex vertex_descriptor;

    private:
        /// Key extractor for use with the multi_index_container
        struct extract_name_from_vertex
        {
            typedef vertex_name_type result_type;

            extract_name_from_vertex(
                Graph& graph, const extract_name_type& extract)
            : graph(graph), extract(extract)
            {
            }

            const result_type& operator()(Vertex vertex) const
            {
                return extract(graph[vertex]);
            }

            Graph& graph;
            extract_name_type extract;
        };

    public:
        /// The type that maps names to vertices
        typedef multi_index::multi_index_container< Vertex,
            multi_index::indexed_by<
                multi_index::hashed_unique< multi_index::tag< vertex_name_t >,
                    extract_name_from_vertex > > >
            named_vertices_type;

        /// The set of vertices, indexed by name
        typedef
            typename named_vertices_type::template index< vertex_name_t >::type
                vertices_by_name_type;

        /// Construct an instance of the named graph mixin, using the given
        /// function object to extract a name from the bundled property
        /// associated with a vertex.
        named_graph(const extract_name_type& extract = extract_name_type(),
            const vertex_constructor_type& vertex_constructor
            = vertex_constructor_type());

        /// Notify the named_graph that we have added the given vertex. The
        /// name of the vertex will be added to the mapping.
        void added_vertex(Vertex vertex);

        /// Notify the named_graph that we are removing the given
        /// vertex. The name of the vertex will be removed from the mapping.
        template < typename VertexIterStability >
        void removing_vertex(Vertex vertex, VertexIterStability);

        /// Notify the named_graph that we are clearing the graph.
        /// This will clear out all of the name->vertex mappings
        void clearing_graph();

        /// Retrieve the derived instance
        Graph& derived() { return static_cast< Graph& >(*this); }
        const Graph& derived() const
        {
            return static_cast< const Graph& >(*this);
        }

        /// Extract the name from a vertex property instance
        typename extract_name_type::result_type extract_name(
            const bundled_vertex_property_type& property);

        /// Search for a vertex that has the given property (based on its
        /// name)
        optional< vertex_descriptor > vertex_by_property(
            const bundled_vertex_property_type& property);

        /// Mapping from names to vertices
        named_vertices_type named_vertices;

        /// Constructs a vertex from the name of that vertex
        vertex_constructor_type vertex_constructor;
    };

/// Helper macro containing the template parameters of named_graph
#define BGL_NAMED_GRAPH_PARAMS \
    typename Graph, typename Vertex, typename VertexProperty
/// Helper macro containing the named_graph<...> instantiation
#define BGL_NAMED_GRAPH named_graph< Graph, Vertex, VertexProperty >

    template < BGL_NAMED_GRAPH_PARAMS >
    BGL_NAMED_GRAPH::named_graph(const extract_name_type& extract,
        const vertex_constructor_type& vertex_constructor)
    : named_vertices(typename named_vertices_type::ctor_args_list(
        boost::make_tuple(boost::make_tuple(0, // initial number of buckets
            extract_name_from_vertex(derived(), extract),
            boost::hash< vertex_name_type >(),
            std::equal_to< vertex_name_type >()))))
    , vertex_constructor(vertex_constructor)
    {
    }

    template < BGL_NAMED_GRAPH_PARAMS >
    inline void BGL_NAMED_GRAPH::added_vertex(Vertex vertex)
    {
        named_vertices.insert(vertex);
    }

    template < BGL_NAMED_GRAPH_PARAMS >
    template < typename VertexIterStability >
    inline void BGL_NAMED_GRAPH::removing_vertex(
        Vertex vertex, VertexIterStability)
    {
        BOOST_STATIC_ASSERT_MSG(
            (boost::is_base_of< boost::graph_detail::stable_tag,
                VertexIterStability >::value),
            "Named graphs cannot use vecS as vertex container and remove "
            "vertices; the lack of vertex descriptor stability (which iterator "
            "stability is a proxy for) means that the name -> vertex mapping "
            "would need to be completely rebuilt after each deletion.  See "
            "https://svn.boost.org/trac/boost/ticket/7863 for more information "
            "and a test case.");
        typedef typename BGL_NAMED_GRAPH::vertex_name_type vertex_name_type;
        const vertex_name_type& vertex_name = extract_name(derived()[vertex]);
        named_vertices.erase(vertex_name);
    }

    template < BGL_NAMED_GRAPH_PARAMS >
    inline void BGL_NAMED_GRAPH::clearing_graph()
    {
        named_vertices.clear();
    }

    template < BGL_NAMED_GRAPH_PARAMS >
    typename BGL_NAMED_GRAPH::extract_name_type::result_type
    BGL_NAMED_GRAPH::extract_name(const bundled_vertex_property_type& property)
    {
        return named_vertices.key_extractor().extract(property);
    }

    template < BGL_NAMED_GRAPH_PARAMS >
    optional< typename BGL_NAMED_GRAPH::vertex_descriptor >
    BGL_NAMED_GRAPH::vertex_by_property(
        const bundled_vertex_property_type& property)
    {
        return find_vertex(extract_name(property), *this);
    }

    /// Retrieve the vertex associated with the given name
    template < BGL_NAMED_GRAPH_PARAMS >
    optional< Vertex > find_vertex(
        typename BGL_NAMED_GRAPH::vertex_name_type const& name,
        const BGL_NAMED_GRAPH& g)
    {
        typedef typename BGL_NAMED_GRAPH::vertices_by_name_type
            vertices_by_name_type;

        // Retrieve the set of vertices indexed by name
        vertices_by_name_type const& vertices_by_name
            = g.named_vertices.template get< vertex_name_t >();

        /// Look for a vertex with the given name
        typename vertices_by_name_type::const_iterator iter
            = vertices_by_name.find(name);

        if (iter == vertices_by_name.end())
            return optional< Vertex >(); // vertex not found
        else
            return *iter;
    }

    /// Retrieve the vertex associated with the given name, or add a new
    /// vertex with that name if no such vertex is available.
    /// Note: This is enabled only when the vertex property type is different
    ///       from the vertex name to avoid ambiguous overload problems with
    ///       the add_vertex() function that takes a vertex property.
    template < BGL_NAMED_GRAPH_PARAMS >
    typename disable_if<
        is_same< typename BGL_NAMED_GRAPH::vertex_name_type, VertexProperty >,
        Vertex >::type
    add_vertex(typename BGL_NAMED_GRAPH::vertex_name_type const& name,
        BGL_NAMED_GRAPH& g)
    {
        if (optional< Vertex > vertex = find_vertex(name, g))
            /// We found the vertex, so return it
            return *vertex;
        else
            /// There is no vertex with the given name, so create one
            return add_vertex(g.vertex_constructor(name), g.derived());
    }

    /// Add an edge using vertex names to refer to the vertices
    template < BGL_NAMED_GRAPH_PARAMS >
    std::pair< typename graph_traits< Graph >::edge_descriptor, bool > add_edge(
        typename BGL_NAMED_GRAPH::vertex_name_type const& u_name,
        typename BGL_NAMED_GRAPH::vertex_name_type const& v_name,
        BGL_NAMED_GRAPH& g)
    {
        return add_edge(add_vertex(u_name, g.derived()),
            add_vertex(v_name, g.derived()), g.derived());
    }

    /// Add an edge using vertex descriptors or names to refer to the vertices
    template < BGL_NAMED_GRAPH_PARAMS >
    std::pair< typename graph_traits< Graph >::edge_descriptor, bool > add_edge(
        typename BGL_NAMED_GRAPH::vertex_descriptor const& u,
        typename BGL_NAMED_GRAPH::vertex_name_type const& v_name,
        BGL_NAMED_GRAPH& g)
    {
        return add_edge(u, add_vertex(v_name, g.derived()), g.derived());
    }

    /// Add an edge using vertex descriptors or names to refer to the vertices
    template < BGL_NAMED_GRAPH_PARAMS >
    std::pair< typename graph_traits< Graph >::edge_descriptor, bool > add_edge(
        typename BGL_NAMED_GRAPH::vertex_name_type const& u_name,
        typename BGL_NAMED_GRAPH::vertex_descriptor const& v,
        BGL_NAMED_GRAPH& g)
    {
        return add_edge(add_vertex(u_name, g.derived()), v, g.derived());
    }

    // Overloads to support EdgeMutablePropertyGraph graphs
    template < BGL_NAMED_GRAPH_PARAMS >
    std::pair< typename graph_traits< Graph >::edge_descriptor, bool > add_edge(
        typename BGL_NAMED_GRAPH::vertex_descriptor const& u,
        typename BGL_NAMED_GRAPH::vertex_name_type const& v_name,
        typename edge_property_type< Graph >::type const& p, BGL_NAMED_GRAPH& g)
    {
        return add_edge(u, add_vertex(v_name, g.derived()), p, g.derived());
    }

    template < BGL_NAMED_GRAPH_PARAMS >
    std::pair< typename graph_traits< Graph >::edge_descriptor, bool > add_edge(
        typename BGL_NAMED_GRAPH::vertex_name_type const& u_name,
        typename BGL_NAMED_GRAPH::vertex_descriptor const& v,
        typename edge_property_type< Graph >::type const& p, BGL_NAMED_GRAPH& g)
    {
        return add_edge(add_vertex(u_name, g.derived()), v, p, g.derived());
    }

    template < BGL_NAMED_GRAPH_PARAMS >
    std::pair< typename graph_traits< Graph >::edge_descriptor, bool > add_edge(
        typename BGL_NAMED_GRAPH::vertex_name_type const& u_name,
        typename BGL_NAMED_GRAPH::vertex_name_type const& v_name,
        typename edge_property_type< Graph >::type const& p, BGL_NAMED_GRAPH& g)
    {
        return add_edge(add_vertex(u_name, g.derived()),
            add_vertex(v_name, g.derived()), p, g.derived());
    }

#undef BGL_NAMED_GRAPH
#undef BGL_NAMED_GRAPH_PARAMS

    /*******************************************************************
     * Maybe named graph mixin                                         *
     *******************************************************************/

    /**
     * A graph mixin that can provide a mapping from names to vertices,
     * and use that mapping to simplify creation and manipulation of
     * graphs.
     */
    template < typename Graph, typename Vertex, typename VertexProperty,
        typename ExtractName =
            typename internal_vertex_name< VertexProperty >::type >
    struct maybe_named_graph
    : public named_graph< Graph, Vertex, VertexProperty >
    {
    };

    /**
     * A graph mixin that can provide a mapping from names to vertices,
     * and use that mapping to simplify creation and manipulation of
     * graphs. This partial specialization turns off this functionality
     * when the @c VertexProperty does not have an internal vertex name.
     */
    template < typename Graph, typename Vertex, typename VertexProperty >
    struct maybe_named_graph< Graph, Vertex, VertexProperty, void >
    {
        /// The type of the "bundled" property, from which the name can be
        /// extracted.
        typedef typename lookup_one_property< VertexProperty,
            vertex_bundle_t >::type bundled_vertex_property_type;

        /// Notify the named_graph that we have added the given vertex. This
        /// is a no-op.
        void added_vertex(Vertex) {}

        /// Notify the named_graph that we are removing the given
        /// vertex. This is a no-op.
        template < typename VertexIterStability >
        void removing_vertex(Vertex, VertexIterStability)
        {
        }

        /// Notify the named_graph that we are clearing the graph. This is a
        /// no-op.
        void clearing_graph() {}

        /// Search for a vertex that has the given property (based on its
        /// name). This always returns an empty optional<>
        optional< Vertex > vertex_by_property(
            const bundled_vertex_property_type&)
        {
            return optional< Vertex >();
        }
    };

}
} // end namespace boost::graph

#endif // BOOST_GRAPH_NAMED_GRAPH_HPP

/* named_graph.hpp
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
*/