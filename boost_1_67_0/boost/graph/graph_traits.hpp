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