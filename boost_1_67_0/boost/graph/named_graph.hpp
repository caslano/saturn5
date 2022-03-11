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