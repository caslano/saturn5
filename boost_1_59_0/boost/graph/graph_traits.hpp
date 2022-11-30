//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_TRAITS_HPP
#define BOOST_GRAPH_TRAITS_HPP

#include <boost/config.hpp>
#include <iterator>
#include <utility> /* Primarily for std::pair */
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/pending/property.hpp>
#include <boost/detail/workaround.hpp>

namespace boost
{

namespace detail
{
#define BOOST_GRAPH_MEMBER_OR_VOID(name)                                                                                            \
    BOOST_MPL_HAS_XXX_TRAIT_DEF(name)                                                                                               \
    template < typename T > struct BOOST_JOIN(get_member_, name)                                                                    \
    {                                                                                                                               \
        typedef typename T::name type;                                                                                              \
    };                                                                                                                              \
    template < typename T >                                                                                                         \
    struct BOOST_JOIN(get_opt_member_, name)                                                                                        \
    : boost::mpl::eval_if_c< BOOST_JOIN(has_, name) < T >::value, BOOST_JOIN(get_member_, name)< T >, boost::mpl::identity< void > >\
    {                                                                                                                               \
    };
    BOOST_GRAPH_MEMBER_OR_VOID(adjacency_iterator)
    BOOST_GRAPH_MEMBER_OR_VOID(out_edge_iterator)
    BOOST_GRAPH_MEMBER_OR_VOID(in_edge_iterator)
    BOOST_GRAPH_MEMBER_OR_VOID(vertex_iterator)
    BOOST_GRAPH_MEMBER_OR_VOID(edge_iterator)
    BOOST_GRAPH_MEMBER_OR_VOID(vertices_size_type)
    BOOST_GRAPH_MEMBER_OR_VOID(edges_size_type)
    BOOST_GRAPH_MEMBER_OR_VOID(degree_size_type)
}

template < typename G > struct graph_traits
{
#define BOOST_GRAPH_PULL_OPT_MEMBER(name) \
    typedef typename detail::BOOST_JOIN(get_opt_member_, name)< G >::type name;

    typedef typename G::vertex_descriptor vertex_descriptor;
    typedef typename G::edge_descriptor edge_descriptor;
    BOOST_GRAPH_PULL_OPT_MEMBER(adjacency_iterator)
    BOOST_GRAPH_PULL_OPT_MEMBER(out_edge_iterator)
    BOOST_GRAPH_PULL_OPT_MEMBER(in_edge_iterator)
    BOOST_GRAPH_PULL_OPT_MEMBER(vertex_iterator)
    BOOST_GRAPH_PULL_OPT_MEMBER(edge_iterator)

    typedef typename G::directed_category directed_category;
    typedef typename G::edge_parallel_category edge_parallel_category;
    typedef typename G::traversal_category traversal_category;

    BOOST_GRAPH_PULL_OPT_MEMBER(vertices_size_type)
    BOOST_GRAPH_PULL_OPT_MEMBER(edges_size_type)
    BOOST_GRAPH_PULL_OPT_MEMBER(degree_size_type)
#undef BOOST_GRAPH_PULL_OPT_MEMBER

    static inline vertex_descriptor null_vertex();
};

template < typename G >
inline typename graph_traits< G >::vertex_descriptor
graph_traits< G >::null_vertex()
{
    return G::null_vertex();
}

// directed_category tags
struct directed_tag
{
};
struct undirected_tag
{
};
struct bidirectional_tag : public directed_tag
{
};

namespace detail
{
    inline bool is_directed(directed_tag) { return true; }
    inline bool is_directed(undirected_tag) { return false; }
}

/** Return true if the given graph is directed. */
template < typename Graph > bool is_directed(const Graph&)
{
    typedef typename graph_traits< Graph >::directed_category Cat;
    return detail::is_directed(Cat());
}

/** Return true if the given graph is undirected. */
template < typename Graph > bool is_undirected(const Graph& g)
{
    return !is_directed(g);
}

/** @name Directed/Undirected Graph Traits */
//@{
namespace graph_detail
{
    template < typename Tag >
    struct is_directed_tag
    : mpl::bool_< is_convertible< Tag, directed_tag >::value >
    {
    };
} // namespace graph_detail

template < typename Graph >
struct is_directed_graph
: graph_detail::is_directed_tag<
      typename graph_traits< Graph >::directed_category >
{
};

template < typename Graph >
struct is_undirected_graph : mpl::not_< is_directed_graph< Graph > >
{
};
//@}

// edge_parallel_category tags
struct allow_parallel_edge_tag
{
};
struct disallow_parallel_edge_tag
{
};

namespace detail
{
    inline bool allows_parallel(allow_parallel_edge_tag) { return true; }
    inline bool allows_parallel(disallow_parallel_edge_tag) { return false; }
}

template < typename Graph > bool allows_parallel_edges(const Graph&)
{
    typedef typename graph_traits< Graph >::edge_parallel_category Cat;
    return detail::allows_parallel(Cat());
}

/** @name Parallel Edges Traits */
//@{
/**
 * The is_multigraph metafunction returns true if the graph allows
 * parallel edges. Technically, a multigraph is a simple graph that
 * allows parallel edges, but since there are no traits for the allowance
 * or disallowance of loops, this is a moot point.
 */
template < typename Graph >
struct is_multigraph
: mpl::bool_< is_same< typename graph_traits< Graph >::edge_parallel_category,
      allow_parallel_edge_tag >::value >
{
};
//@}

// traversal_category tags
struct incidence_graph_tag
{
};
struct adjacency_graph_tag
{
};
struct bidirectional_graph_tag : virtual incidence_graph_tag
{
};
struct vertex_list_graph_tag
{
};
struct edge_list_graph_tag
{
};
struct adjacency_matrix_tag
{
};

// Parallel traversal_category tags
struct distributed_graph_tag
{
};
struct distributed_vertex_list_graph_tag
{
};
struct distributed_edge_list_graph_tag
{
};
#define BOOST_GRAPH_SEQUENTIAL_TRAITS_DEFINES_DISTRIBUTED_TAGS // Disable these
                                                               // from external
                                                               // versions of
                                                               // PBGL

/** @name Traversal Category Traits
 * These traits classify graph types by their supported methods of
 * vertex and edge traversal.
 */
//@{
template < typename Graph >
struct is_incidence_graph
: mpl::bool_<
      is_convertible< typename graph_traits< Graph >::traversal_category,
          incidence_graph_tag >::value >
{
};

template < typename Graph >
struct is_bidirectional_graph
: mpl::bool_<
      is_convertible< typename graph_traits< Graph >::traversal_category,
          bidirectional_graph_tag >::value >
{
};

template < typename Graph >
struct is_vertex_list_graph
: mpl::bool_<
      is_convertible< typename graph_traits< Graph >::traversal_category,
          vertex_list_graph_tag >::value >
{
};

template < typename Graph >
struct is_edge_list_graph
: mpl::bool_<
      is_convertible< typename graph_traits< Graph >::traversal_category,
          edge_list_graph_tag >::value >
{
};

template < typename Graph >
struct is_adjacency_matrix
: mpl::bool_<
      is_convertible< typename graph_traits< Graph >::traversal_category,
          adjacency_matrix_tag >::value >
{
};
//@}

/** @name Directed Graph Traits
 * These metafunctions are used to fully classify directed vs. undirected
 * graphs. Recall that an undirected graph is also bidirectional, but it
 * cannot be both undirected and directed at the same time.
 */
//@{
template < typename Graph >
struct is_directed_unidirectional_graph
: mpl::and_< is_directed_graph< Graph >,
      mpl::not_< is_bidirectional_graph< Graph > > >
{
};

template < typename Graph >
struct is_directed_bidirectional_graph
: mpl::and_< is_directed_graph< Graph >, is_bidirectional_graph< Graph > >
{
};
//@}

//?? not the right place ?? Lee
typedef boost::forward_traversal_tag multi_pass_input_iterator_tag;

namespace detail
{
    BOOST_MPL_HAS_XXX_TRAIT_DEF(graph_property_type)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(edge_property_type)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(vertex_property_type)

    template < typename G > struct get_graph_property_type
    {
        typedef typename G::graph_property_type type;
    };
    template < typename G > struct get_edge_property_type
    {
        typedef typename G::edge_property_type type;
    };
    template < typename G > struct get_vertex_property_type
    {
        typedef typename G::vertex_property_type type;
    };
}

template < typename G >
struct graph_property_type
: boost::mpl::eval_if< detail::has_graph_property_type< G >,
      detail::get_graph_property_type< G >, no_property >
{
};
template < typename G >
struct edge_property_type
: boost::mpl::eval_if< detail::has_edge_property_type< G >,
      detail::get_edge_property_type< G >, no_property >
{
};
template < typename G >
struct vertex_property_type
: boost::mpl::eval_if< detail::has_vertex_property_type< G >,
      detail::get_vertex_property_type< G >, no_property >
{
};

template < typename G > struct graph_bundle_type
{
    typedef typename G::graph_bundled type;
};

template < typename G > struct vertex_bundle_type
{
    typedef typename G::vertex_bundled type;
};

template < typename G > struct edge_bundle_type
{
    typedef typename G::edge_bundled type;
};

namespace graph
{
    namespace detail
    {
        template < typename Graph, typename Descriptor > class bundled_result
        {
            typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
            typedef typename mpl::if_c< (is_same< Descriptor, Vertex >::value),
                vertex_bundle_type< Graph >, edge_bundle_type< Graph > >::type
                bundler;

        public:
            typedef typename bundler::type type;
        };

        template < typename Graph >
        class bundled_result< Graph, graph_bundle_t >
        {
            typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
            typedef graph_bundle_type< Graph > bundler;

        public:
            typedef typename bundler::type type;
        };

    }
} // namespace graph::detail

namespace graph_detail
{
    // A helper metafunction for determining whether or not a type is
    // bundled.
    template < typename T >
    struct is_no_bundle : mpl::bool_< is_same< T, no_property >::value >
    {
    };
} // namespace graph_detail

/** @name Graph Property Traits
 * These metafunctions (along with those above), can be used to access the
 * vertex and edge properties (bundled or otherwise) of vertices and
 * edges.
 */
//@{
template < typename Graph >
struct has_graph_property
: mpl::not_< typename detail::is_no_property<
      typename graph_property_type< Graph >::type >::type >::type
{
};

template < typename Graph >
struct has_bundled_graph_property
: mpl::not_<
      graph_detail::is_no_bundle< typename graph_bundle_type< Graph >::type > >
{
};

template < typename Graph >
struct has_vertex_property
: mpl::not_< typename detail::is_no_property<
      typename vertex_property_type< Graph >::type > >::type
{
};

template < typename Graph >
struct has_bundled_vertex_property
: mpl::not_<
      graph_detail::is_no_bundle< typename vertex_bundle_type< Graph >::type > >
{
};

template < typename Graph >
struct has_edge_property
: mpl::not_< typename detail::is_no_property<
      typename edge_property_type< Graph >::type > >::type
{
};

template < typename Graph >
struct has_bundled_edge_property
: mpl::not_<
      graph_detail::is_no_bundle< typename edge_bundle_type< Graph >::type > >
{
};
//@}

} // namespace boost

// Since pair is in namespace std, Koenig lookup will find source and
// target if they are also defined in namespace std.  This is illegal,
// but the alternative is to put source and target in the global
// namespace which causes name conflicts with other libraries (like
// SUIF).
namespace std
{

/* Some helper functions for dealing with pairs as edges */
template < class T, class G > T source(pair< T, T > p, const G&)
{
    return p.first;
}

template < class T, class G > T target(pair< T, T > p, const G&)
{
    return p.second;
}

}

#if defined(__GNUC__) && defined(__SGI_STL_PORT)
// For some reason g++ with STLport does not see the above definition
// of source() and target() unless we bring them into the boost
// namespace.
namespace boost
{
using std::source;
using std::target;
}
#endif

#endif // BOOST_GRAPH_TRAITS_HPP

/* graph_traits.hpp
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
*/