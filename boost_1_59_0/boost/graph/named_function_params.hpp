//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_NAMED_FUNCTION_PARAMS_HPP
#define BOOST_GRAPH_NAMED_FUNCTION_PARAMS_HPP

#include <functional>
#include <vector>
#include <boost/limits.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/core/ref.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/preprocessor.hpp>
#include <boost/parameter/is_argument_pack.hpp>
#include <boost/parameter/name.hpp>
#include <boost/parameter/binding.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/detail/d_ary_heap.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_map/shared_array_property_map.hpp>

namespace boost
{

struct parity_map_t
{
};
struct vertex_assignment_map_t
{
};
struct distance_compare_t
{
};
struct distance_combine_t
{
};
struct distance_inf_t
{
};
struct distance_zero_t
{
};
struct buffer_param_t
{
};
struct edge_copy_t
{
};
struct vertex_copy_t
{
};
struct vertex_isomorphism_t
{
};
struct vertex_invariant_t
{
};
struct vertex_invariant1_t
{
};
struct vertex_invariant2_t
{
};
struct edge_compare_t
{
};
struct vertex_max_invariant_t
{
};
struct orig_to_copy_t
{
};
struct root_vertex_t
{
};
struct polling_t
{
};
struct lookahead_t
{
};
struct in_parallel_t
{
};
struct attractive_force_t
{
};
struct repulsive_force_t
{
};
struct force_pairs_t
{
};
struct cooling_t
{
};
struct vertex_displacement_t
{
};
struct iterations_t
{
};
struct diameter_range_t
{
};
struct learning_constant_range_t
{
};
struct vertices_equivalent_t
{
};
struct edges_equivalent_t
{
};
struct index_in_heap_map_t
{
};
struct max_priority_queue_t
{
};

#define BOOST_BGL_DECLARE_NAMED_PARAMS                                         \
    BOOST_BGL_ONE_PARAM_CREF(weight_map, edge_weight)                          \
    BOOST_BGL_ONE_PARAM_CREF(weight_map2, edge_weight2)                        \
    BOOST_BGL_ONE_PARAM_CREF(distance_map, vertex_distance)                    \
    BOOST_BGL_ONE_PARAM_CREF(distance_map2, vertex_distance2)                  \
    BOOST_BGL_ONE_PARAM_CREF(predecessor_map, vertex_predecessor)              \
    BOOST_BGL_ONE_PARAM_CREF(rank_map, vertex_rank)                            \
    BOOST_BGL_ONE_PARAM_CREF(root_map, vertex_root)                            \
    BOOST_BGL_ONE_PARAM_CREF(root_vertex, root_vertex)                         \
    BOOST_BGL_ONE_PARAM_CREF(edge_centrality_map, edge_centrality)             \
    BOOST_BGL_ONE_PARAM_CREF(centrality_map, vertex_centrality)                \
    BOOST_BGL_ONE_PARAM_CREF(parity_map, parity_map)                           \
    BOOST_BGL_ONE_PARAM_CREF(color_map, vertex_color)                          \
    BOOST_BGL_ONE_PARAM_CREF(edge_color_map, edge_color)                       \
    BOOST_BGL_ONE_PARAM_CREF(capacity_map, edge_capacity)                      \
    BOOST_BGL_ONE_PARAM_CREF(residual_capacity_map, edge_residual_capacity)    \
    BOOST_BGL_ONE_PARAM_CREF(reverse_edge_map, edge_reverse)                   \
    BOOST_BGL_ONE_PARAM_CREF(discover_time_map, vertex_discover_time)          \
    BOOST_BGL_ONE_PARAM_CREF(lowpoint_map, vertex_lowpoint)                    \
    BOOST_BGL_ONE_PARAM_CREF(vertex_index_map, vertex_index)                   \
    BOOST_BGL_ONE_PARAM_CREF(vertex_index1_map, vertex_index1)                 \
    BOOST_BGL_ONE_PARAM_CREF(vertex_index2_map, vertex_index2)                 \
    BOOST_BGL_ONE_PARAM_CREF(vertex_assignment_map, vertex_assignment_map)     \
    BOOST_BGL_ONE_PARAM_CREF(visitor, graph_visitor)                           \
    BOOST_BGL_ONE_PARAM_CREF(distance_compare, distance_compare)               \
    BOOST_BGL_ONE_PARAM_CREF(distance_combine, distance_combine)               \
    BOOST_BGL_ONE_PARAM_CREF(distance_inf, distance_inf)                       \
    BOOST_BGL_ONE_PARAM_CREF(distance_zero, distance_zero)                     \
    BOOST_BGL_ONE_PARAM_CREF(edge_copy, edge_copy)                             \
    BOOST_BGL_ONE_PARAM_CREF(vertex_copy, vertex_copy)                         \
    BOOST_BGL_ONE_PARAM_REF(buffer, buffer_param)                              \
    BOOST_BGL_ONE_PARAM_CREF(orig_to_copy, orig_to_copy)                       \
    BOOST_BGL_ONE_PARAM_CREF(isomorphism_map, vertex_isomorphism)              \
    BOOST_BGL_ONE_PARAM_CREF(vertex_invariant, vertex_invariant)               \
    BOOST_BGL_ONE_PARAM_CREF(vertex_invariant1, vertex_invariant1)             \
    BOOST_BGL_ONE_PARAM_CREF(vertex_invariant2, vertex_invariant2)             \
    BOOST_BGL_ONE_PARAM_CREF(vertex_max_invariant, vertex_max_invariant)       \
    BOOST_BGL_ONE_PARAM_CREF(polling, polling)                                 \
    BOOST_BGL_ONE_PARAM_CREF(lookahead, lookahead)                             \
    BOOST_BGL_ONE_PARAM_CREF(in_parallel, in_parallel)                         \
    BOOST_BGL_ONE_PARAM_CREF(displacement_map, vertex_displacement)            \
    BOOST_BGL_ONE_PARAM_CREF(attractive_force, attractive_force)               \
    BOOST_BGL_ONE_PARAM_CREF(repulsive_force, repulsive_force)                 \
    BOOST_BGL_ONE_PARAM_CREF(force_pairs, force_pairs)                         \
    BOOST_BGL_ONE_PARAM_CREF(cooling, cooling)                                 \
    BOOST_BGL_ONE_PARAM_CREF(iterations, iterations)                           \
    BOOST_BGL_ONE_PARAM_CREF(diameter_range, diameter_range)                   \
    BOOST_BGL_ONE_PARAM_CREF(learning_constant_range, learning_constant_range) \
    BOOST_BGL_ONE_PARAM_CREF(vertices_equivalent, vertices_equivalent)         \
    BOOST_BGL_ONE_PARAM_CREF(edges_equivalent, edges_equivalent)               \
    BOOST_BGL_ONE_PARAM_CREF(index_in_heap_map, index_in_heap_map)             \
    BOOST_BGL_ONE_PARAM_REF(max_priority_queue, max_priority_queue)

template < typename T, typename Tag, typename Base = no_property >
struct bgl_named_params
{
    typedef bgl_named_params self;
    typedef Base next_type;
    typedef Tag tag_type;
    typedef T value_type;
    bgl_named_params(T v = T()) : m_value(v) {}
    bgl_named_params(T v, const Base& b) : m_value(v), m_base(b) {}
    T m_value;
    Base m_base;

#define BOOST_BGL_ONE_PARAM_REF(name, key)                           \
    template < typename PType >                                      \
    bgl_named_params< boost::reference_wrapper< PType >,             \
        BOOST_PP_CAT(key, _t), self >                                \
    name(PType& p) const                                             \
    {                                                                \
        typedef bgl_named_params< boost::reference_wrapper< PType >, \
            BOOST_PP_CAT(key, _t), self >                            \
            Params;                                                  \
        return Params(boost::ref(p), *this);                         \
    }

#define BOOST_BGL_ONE_PARAM_CREF(name, key)                                    \
    template < typename PType >                                                \
    bgl_named_params< PType, BOOST_PP_CAT(key, _t), self > name(               \
        const PType& p) const                                                  \
    {                                                                          \
        typedef bgl_named_params< PType, BOOST_PP_CAT(key, _t), self > Params; \
        return Params(p, *this);                                               \
    }

    BOOST_BGL_DECLARE_NAMED_PARAMS

#undef BOOST_BGL_ONE_PARAM_REF
#undef BOOST_BGL_ONE_PARAM_CREF

    // Duplicate
    template < typename PType >
    bgl_named_params< PType, vertex_color_t, self > vertex_color_map(
        const PType& p) const
    {
        return this->color_map(p);
    }
};

#define BOOST_BGL_ONE_PARAM_REF(name, key)                           \
    template < typename PType >                                      \
    bgl_named_params< boost::reference_wrapper< PType >,             \
        BOOST_PP_CAT(key, _t) >                                      \
    name(PType& p)                                                   \
    {                                                                \
        typedef bgl_named_params< boost::reference_wrapper< PType >, \
            BOOST_PP_CAT(key, _t) >                                  \
            Params;                                                  \
        return Params(boost::ref(p));                                \
    }

#define BOOST_BGL_ONE_PARAM_CREF(name, key)                               \
    template < typename PType >                                           \
    bgl_named_params< PType, BOOST_PP_CAT(key, _t) > name(const PType& p) \
    {                                                                     \
        typedef bgl_named_params< PType, BOOST_PP_CAT(key, _t) > Params;  \
        return Params(p);                                                 \
    }

BOOST_BGL_DECLARE_NAMED_PARAMS

#undef BOOST_BGL_ONE_PARAM_REF
#undef BOOST_BGL_ONE_PARAM_CREF

// Duplicate
template < typename PType >
bgl_named_params< PType, vertex_color_t > vertex_color_map(const PType& p)
{
    return color_map(p);
}

namespace detail
{
    struct unused_tag_type
    {
    };
}
typedef bgl_named_params< char, detail::unused_tag_type > no_named_parameters;

//===========================================================================
// Functions for extracting parameters from bgl_named_params

template < typename Tag, typename Args > struct lookup_named_param
{
};

template < typename T, typename Tag, typename Base >
struct lookup_named_param< Tag, bgl_named_params< T, Tag, Base > >
{
    typedef T type;
    static const T& get(const bgl_named_params< T, Tag, Base >& p)
    {
        return p.m_value;
    }
};

template < typename Tag1, typename T, typename Tag, typename Base >
struct lookup_named_param< Tag1, bgl_named_params< T, Tag, Base > >
{
    typedef typename lookup_named_param< Tag1, Base >::type type;
    static const type& get(const bgl_named_params< T, Tag, Base >& p)
    {
        return lookup_named_param< Tag1, Base >::get(p.m_base);
    }
};

template < typename Tag, typename Args, typename Def >
struct lookup_named_param_def
{
    typedef Def type;
    static const Def& get(const Args&, const Def& def) { return def; }
};

template < typename T, typename Tag, typename Base, typename Def >
struct lookup_named_param_def< Tag, bgl_named_params< T, Tag, Base >, Def >
{
    typedef T type;
    static const type& get(
        const bgl_named_params< T, Tag, Base >& p, const Def&)
    {
        return p.m_value;
    }
};

template < typename Tag1, typename T, typename Tag, typename Base,
    typename Def >
struct lookup_named_param_def< Tag1, bgl_named_params< T, Tag, Base >, Def >
{
    typedef typename lookup_named_param_def< Tag1, Base, Def >::type type;
    static const type& get(
        const bgl_named_params< T, Tag, Base >& p, const Def& def)
    {
        return lookup_named_param_def< Tag1, Base, Def >::get(p.m_base, def);
    }
};

struct param_not_found
{
};
static param_not_found g_param_not_found;

template < typename Tag, typename Args >
struct get_param_type : lookup_named_param_def< Tag, Args, param_not_found >
{
};

template < class Tag, typename Args >
inline const typename lookup_named_param_def< Tag, Args,
    param_not_found >::type&
get_param(const Args& p, Tag)
{
    return lookup_named_param_def< Tag, Args, param_not_found >::get(
        p, g_param_not_found);
}

template < class P, class Default >
const P& choose_param(const P& param, const Default&)
{
    return param;
}

template < class Default >
Default choose_param(const param_not_found&, const Default& d)
{
    return d;
}

template < typename T > inline bool is_default_param(const T&) { return false; }

inline bool is_default_param(const param_not_found&) { return true; }

namespace detail
{
    template < typename T > struct const_type_as_type
    {
        typedef typename T::const_type type;
    };
} // namespace detail

// Use this function instead of choose_param() when you want
// to avoid requiring get(tag, g) when it is not used.
namespace detail
{
    template < typename GraphIsConst, typename Graph, typename Param,
        typename Tag >
    struct choose_impl_result
    : boost::mpl::eval_if< boost::is_same< Param, param_not_found >,
          boost::mpl::eval_if< GraphIsConst,
              detail::const_type_as_type< property_map< Graph, Tag > >,
              property_map< Graph, Tag > >,
          boost::mpl::identity< Param > >
    {
    };

    // Parameters of f are (GraphIsConst, Graph, Param, Tag)
    template < bool Found > struct choose_impl_helper;

    template <> struct choose_impl_helper< false >
    {
        template < typename Param, typename Graph, typename PropertyTag >
        static
            typename property_map< typename boost::remove_const< Graph >::type,
                PropertyTag >::const_type
            f(boost::mpl::true_, const Graph& g, const Param&, PropertyTag tag)
        {
            return get(tag, g);
        }

        template < typename Param, typename Graph, typename PropertyTag >
        static
            typename property_map< typename boost::remove_const< Graph >::type,
                PropertyTag >::type
            f(boost::mpl::false_, Graph& g, const Param&, PropertyTag tag)
        {
            return get(tag, g);
        }
    };

    template <> struct choose_impl_helper< true >
    {
        template < typename GraphIsConst, typename Param, typename Graph,
            typename PropertyTag >
        static Param f(GraphIsConst, const Graph&, const Param& p, PropertyTag)
        {
            return p;
        }
    };
}

template < typename Param, typename Graph, typename PropertyTag >
typename detail::choose_impl_result< boost::mpl::true_, Graph, Param,
    PropertyTag >::type
choose_const_pmap(const Param& p, const Graph& g, PropertyTag tag)
{
    return detail::choose_impl_helper< !boost::is_same< Param,
        param_not_found >::value >::f(boost::mpl::true_(), g, p, tag);
}

template < typename Param, typename Graph, typename PropertyTag >
typename detail::choose_impl_result< boost::mpl::false_, Graph, Param,
    PropertyTag >::type
choose_pmap(const Param& p, Graph& g, PropertyTag tag)
{
    return detail::choose_impl_helper< !boost::is_same< Param,
        param_not_found >::value >::f(boost::mpl::false_(), g, p, tag);
}

namespace detail
{

    // used in the max-flow algorithms
    template < class Graph, class P, class T, class R >
    struct edge_capacity_value
    {
        typedef bgl_named_params< P, T, R > Params;
        typedef typename detail::choose_impl_result< boost::mpl::true_, Graph,
            typename get_param_type< edge_capacity_t, Params >::type,
            edge_capacity_t >::type CapacityEdgeMap;
        typedef typename property_traits< CapacityEdgeMap >::value_type type;
    };
    // used in the max-flow algorithms
    template < class Graph, class P, class T, class R > struct edge_weight_value
    {
        typedef bgl_named_params< P, T, R > Params;
        typedef typename detail::choose_impl_result< boost::mpl::true_, Graph,
            typename get_param_type< edge_weight_t, Params >::type,
            edge_weight_t >::type WeightMap;
        typedef typename property_traits< WeightMap >::value_type type;
    };

}

// Declare all new tags
namespace graph
{
    namespace keywords
    {
#define BOOST_BGL_ONE_PARAM_REF(name, key) BOOST_PARAMETER_NAME(name)
#define BOOST_BGL_ONE_PARAM_CREF(name, key) BOOST_PARAMETER_NAME(name)
        BOOST_BGL_DECLARE_NAMED_PARAMS
#undef BOOST_BGL_ONE_PARAM_REF
#undef BOOST_BGL_ONE_PARAM_CREF
    }
}

namespace detail
{
    template < typename Tag > struct convert_one_keyword
    {
    };
#define BOOST_BGL_ONE_PARAM_REF(name, key)                          \
    template <> struct convert_one_keyword< BOOST_PP_CAT(key, _t) > \
    {                                                               \
        typedef boost::graph::keywords::tag::name type;             \
    };
#define BOOST_BGL_ONE_PARAM_CREF(name, key) BOOST_BGL_ONE_PARAM_REF(name, key)
    BOOST_BGL_DECLARE_NAMED_PARAMS
#undef BOOST_BGL_ONE_PARAM_REF
#undef BOOST_BGL_ONE_PARAM_CREF

    template < typename T > struct convert_bgl_params_to_boost_parameter
    {
        typedef
            typename convert_one_keyword< typename T::tag_type >::type new_kw;
        typedef boost::parameter::aux::tagged_argument< new_kw,
            const typename T::value_type >
            tagged_arg_type;
        typedef convert_bgl_params_to_boost_parameter< typename T::next_type >
            rest_conv;
        typedef boost::parameter::aux::arg_list< tagged_arg_type,
            typename rest_conv::type >
            type;
        static type conv(const T& x)
        {
            return type(tagged_arg_type(x.m_value), rest_conv::conv(x.m_base));
        }
    };

    template < typename P, typename R >
    struct convert_bgl_params_to_boost_parameter<
        bgl_named_params< P, int, R > >
    {
        typedef convert_bgl_params_to_boost_parameter< R > rest_conv;
        typedef typename rest_conv::type type;
        static type conv(const bgl_named_params< P, int, R >& x)
        {
            return rest_conv::conv(x.m_base);
        }
    };

    template <>
    struct convert_bgl_params_to_boost_parameter< boost::no_property >
    {
        typedef boost::parameter::aux::empty_arg_list type;
        static type conv(const boost::no_property&) { return type(); }
    };

    template <>
    struct convert_bgl_params_to_boost_parameter< boost::no_named_parameters >
    {
        typedef boost::parameter::aux::empty_arg_list type;
        static type conv(const boost::no_named_parameters&) { return type(); }
    };

    struct bgl_parameter_not_found_type
    {
    };
}

#define BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(old_type, old_var)        \
    typedef typename boost::detail::convert_bgl_params_to_boost_parameter< \
        old_type >::type arg_pack_type;                                    \
    arg_pack_type arg_pack                                                 \
        = boost::detail::convert_bgl_params_to_boost_parameter<            \
            old_type >::conv(old_var);

namespace detail
{

    template < typename ArgType, typename Prop, typename Graph, bool Exists >
    struct override_const_property_t
    {
        typedef typename boost::remove_const< ArgType >::type result_type;
        result_type operator()(const Graph&, const ArgType& a) const
        {
            return a;
        }
    };

    template < typename ArgType, typename Prop, typename Graph >
    struct override_const_property_t< ArgType, Prop, Graph, false >
    {
        typedef
            typename boost::property_map< Graph, Prop >::const_type result_type;
        result_type operator()(const Graph& g, const ArgType&) const
        {
            return get(Prop(), g);
        }
    };

    template < typename ArgPack, typename Tag, typename Prop, typename Graph >
    struct override_const_property_result
    {
        typedef typename boost::mpl::has_key< ArgPack, Tag >::type
            _parameter_exists;
        typedef typename override_const_property_t<
            typename boost::parameter::value_type< ArgPack, Tag, int >::type,
            Prop, Graph, _parameter_exists::value >::result_type type;
    };

    template < typename ArgPack, typename Tag, typename Prop, typename Graph >
    typename override_const_property_result< ArgPack, Tag, Prop, Graph >::type
    override_const_property(const ArgPack& ap,
        const boost::parameter::keyword< Tag >& t, const Graph& g, Prop)
    {
        typedef typename boost::mpl::has_key< ArgPack, Tag >::type
            _parameter_exists;
        return override_const_property_t<
            typename boost::parameter::value_type< ArgPack, Tag, int >::type,
            Prop, Graph, _parameter_exists::value >()(g, ap[t | 0]);
    }

    template < typename ArgType, typename Prop, typename Graph, bool Exists >
    struct override_property_t
    {
        typedef ArgType result_type;
        result_type operator()(const Graph&,
            typename boost::add_lvalue_reference< ArgType >::type a) const
        {
            return a;
        }
    };

    template < typename ArgType, typename Prop, typename Graph >
    struct override_property_t< ArgType, Prop, Graph, false >
    {
        typedef typename boost::property_map< Graph, Prop >::type result_type;
        result_type operator()(const Graph& g, const ArgType&) const
        {
            return get(Prop(), g);
        }
    };

    template < typename ArgPack, typename Tag, typename Prop, typename Graph >
    struct override_property_result
    {
        typedef typename boost::mpl::has_key< ArgPack, Tag >::type
            _parameter_exists;
        typedef typename override_property_t<
            typename boost::parameter::value_type< ArgPack, Tag, int >::type,
            Prop, Graph, _parameter_exists::value >::result_type type;
    };

    template < typename ArgPack, typename Tag, typename Prop, typename Graph >
    typename override_property_result< ArgPack, Tag, Prop, Graph >::type
    override_property(const ArgPack& ap,
        const boost::parameter::keyword< Tag >& t, const Graph& g, Prop)
    {
        typedef typename boost::mpl::has_key< ArgPack, Tag >::type
            _parameter_exists;
        return override_property_t<
            typename boost::parameter::value_type< ArgPack, Tag, int >::type,
            Prop, Graph, _parameter_exists::value >()(g, ap[t | 0]);
    }

    template < typename F > struct make_arg_pack_type;
    template <> struct make_arg_pack_type< void() >
    {
        typedef boost::parameter::aux::empty_arg_list type;
    };
    template < typename K, typename A > struct make_arg_pack_type< void(K, A) >
    {
        typedef boost::parameter::aux::tagged_argument< K, A > type;
    };

#define BOOST_GRAPH_OPENING_PART_OF_PAIR(z, i, n)                          \
    boost::parameter::aux::arg_list                                        \
        < boost::parameter::aux::tagged_argument< BOOST_PP_CAT(Keyword,    \
                                                      BOOST_PP_SUB(n, i)), \
            BOOST_PP_CAT(Arg, BOOST_PP_SUB(n, i)) >,
#define BOOST_GRAPH_MAKE_PAIR_PARAM(z, i, _)                                \
    const boost::parameter::aux::tagged_argument< BOOST_PP_CAT(Keyword, i), \
        BOOST_PP_CAT(Arg, i) >& BOOST_PP_CAT(kw, i)

#define BOOST_GRAPH_MAKE_AP_TYPE_SPECIALIZATION(z, i, _)                  \
    template < BOOST_PP_ENUM_PARAMS(i, typename Keyword),                 \
        BOOST_PP_ENUM_PARAMS(i, typename Arg) >                           \
    struct make_arg_pack_type< void(                                      \
        BOOST_PP_ENUM_PARAMS(i, Keyword), BOOST_PP_ENUM_PARAMS(i, Arg)) > \
    {                                                                     \
        typedef BOOST_PP_REPEAT(i, BOOST_GRAPH_OPENING_PART_OF_PAIR,      \
            BOOST_PP_DEC(i)) boost::parameter::aux::empty_arg_list        \
            BOOST_PP_REPEAT(i, > BOOST_PP_TUPLE_EAT(3), ~) type;          \
    };
    BOOST_PP_REPEAT_FROM_TO(2, 11, BOOST_GRAPH_MAKE_AP_TYPE_SPECIALIZATION, ~)
#undef BOOST_GRAPH_MAKE_AP_TYPE_SPECIALIZATION

#define BOOST_GRAPH_MAKE_FORWARDING_FUNCTION(name, nfixed, nnamed_max)        \
    /* Entry point for conversion from BGL-style named parameters */          \
    template < BOOST_PP_ENUM_PARAMS(nfixed, typename Param)                   \
            BOOST_PP_COMMA_IF(nfixed) typename ArgPack >                      \
        typename boost::result_of< detail::BOOST_PP_CAT(name, _impl)          \
            < BOOST_PP_ENUM_PARAMS(nfixed, Param) >(BOOST_PP_ENUM_PARAMS(     \
            nfixed, Param) BOOST_PP_COMMA_IF(nfixed) const ArgPack&)          \
        > ::type BOOST_PP_CAT(name, _with_named_params)(                      \
            BOOST_PP_ENUM_BINARY_PARAMS(nfixed, const Param, &param)          \
                BOOST_PP_COMMA_IF(nfixed) const ArgPack& arg_pack)            \
    {                                                                         \
        return detail::BOOST_PP_CAT(                                          \
            name, _impl)< BOOST_PP_ENUM_PARAMS(nfixed, Param) >()(            \
            BOOST_PP_ENUM_PARAMS(nfixed, param) BOOST_PP_COMMA_IF(nfixed)     \
                arg_pack);                                                    \
    }                                                                         \
    /* Individual functions taking Boost.Parameter-style keyword arguments */ \
    BOOST_PP_REPEAT(BOOST_PP_INC(nnamed_max),                                 \
        BOOST_GRAPH_MAKE_FORWARDING_FUNCTION_ONE, (name)(nfixed))

#define BOOST_GRAPH_MAKE_FORWARDING_FUNCTION_ONE(z, nnamed, seq) \
    BOOST_GRAPH_MAKE_FORWARDING_FUNCTION_ONEX(                   \
        z, nnamed, BOOST_PP_SEQ_ELEM(0, seq), BOOST_PP_SEQ_ELEM(1, seq))

#define BOOST_GRAPH_MAKE_FORWARDING_FUNCTION_ONEX(z, nnamed, name, nfixed)     \
    template < BOOST_PP_ENUM_PARAMS_Z(z, nfixed, typename Param)               \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(                                   \
                z, nnamed, typename ArgumentPack) >                            \
    typename BOOST_PP_EXPR_IF(nnamed,                                          \
        boost::lazy_enable_if                                                  \
            < boost::parameter::is_argument_pack< ArgumentPack0 >)             \
        BOOST_PP_COMMA_IF(nnamed)::boost::graph::detail::BOOST_PP_CAT(         \
            name, _impl)< BOOST_PP_ENUM_PARAMS_Z(z, nfixed, Param) >           \
            BOOST_PP_EXPR_IF(nnamed, >)::type name(                            \
                BOOST_PP_ENUM_BINARY_PARAMS_Z(z, nfixed, Param, const& param)  \
                    BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(                    \
                        z, nnamed, ArgumentPack, const& tagged_arg))           \
    {                                                                          \
        return ::boost::graph::BOOST_PP_CAT(name, _with_named_params)(         \
            BOOST_PP_ENUM_PARAMS_Z(z, nfixed, param) BOOST_PP_COMMA_IF(nnamed) \
                BOOST_PP_LPAREN_IF(nnamed) BOOST_PP_ENUM_PARAMS_Z(             \
                    z, nnamed, tagged_arg) BOOST_PP_RPAREN_IF(nnamed));        \
    }

#define BOOST_GRAPH_MAKE_OLD_STYLE_PARAMETER_FUNCTION(name, nfixed)            \
    template < BOOST_PP_ENUM_PARAMS(nfixed, typename Param)                    \
                   BOOST_PP_COMMA_IF(nfixed) class P,                          \
        class T, class R >                                                     \
    typename boost::result_of< ::boost::graph::detail::BOOST_PP_CAT(           \
        name, _impl) BOOST_PP_EXPR_IF(nfixed, <) BOOST_PP_ENUM_PARAMS(nfixed,  \
        Param) BOOST_PP_EXPR_IF(nfixed, >)(BOOST_PP_ENUM_PARAMS(nfixed, Param) \
            BOOST_PP_COMMA_IF(nfixed) const typename boost::detail::           \
                convert_bgl_params_to_boost_parameter<                         \
                    boost::bgl_named_params< P, T, R > >::type&) >::type       \
    name(BOOST_PP_ENUM_BINARY_PARAMS(nfixed, const Param, &param)              \
            BOOST_PP_COMMA_IF(nfixed)                                          \
                const boost::bgl_named_params< P, T, R >& old_style_params)    \
    {                                                                          \
        typedef boost::bgl_named_params< P, T, R > old_style_params_type;      \
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(                              \
            old_style_params_type, old_style_params)                           \
        return ::boost::graph::BOOST_PP_CAT(name, _with_named_params)(         \
            BOOST_PP_ENUM_PARAMS(nfixed, param) BOOST_PP_COMMA_IF(nfixed)      \
                arg_pack);                                                     \
    }                                                                          \
    BOOST_PP_EXPR_IF(nfixed, template < )                                      \
    BOOST_PP_ENUM_PARAMS(nfixed, typename Param)                               \
    BOOST_PP_EXPR_IF(nfixed, >)                                                \
    BOOST_PP_EXPR_IF(nfixed, typename)                                         \
        boost::result_of< ::boost::graph::detail::BOOST_PP_CAT(                \
            name, _impl) BOOST_PP_EXPR_IF(nfixed,                              \
            <) BOOST_PP_ENUM_PARAMS(nfixed, Param) BOOST_PP_EXPR_IF(nfixed,    \
            >)(BOOST_PP_ENUM_PARAMS(nfixed, Param) BOOST_PP_COMMA_IF(nfixed)   \
                const boost::parameter::aux::empty_arg_list&) >::type          \
            name(BOOST_PP_ENUM_BINARY_PARAMS(nfixed, const Param, &param))     \
    {                                                                          \
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(                              \
            boost::no_named_parameters, boost::no_named_parameters())          \
        return ::boost::graph::BOOST_PP_CAT(name, _with_named_params)(         \
            BOOST_PP_ENUM_PARAMS(nfixed, param) BOOST_PP_COMMA_IF(nfixed)      \
                arg_pack);                                                     \
    }

}

namespace detail
{

    template < bool Exists, typename Graph, typename ArgPack, typename Value,
        typename PM >
    struct map_maker_helper
    {
        typedef PM map_type;
        static PM make_map(const Graph&, Value, const PM& pm, const ArgPack&)
        {
            return pm;
        }
    };

    template < typename Graph, typename ArgPack, typename Value, typename PM >
    struct map_maker_helper< false, Graph, ArgPack, Value, PM >
    {
        typedef typename boost::mpl::has_key< ArgPack,
            boost::graph::keywords::tag::vertex_index_map >::type
            _parameter_exists;
        typedef
            typename boost::remove_const< typename override_const_property_t<
                typename boost::parameter::value_type< ArgPack,
                    boost::graph::keywords::tag::vertex_index_map, int >::type,
                boost::vertex_index_t, Graph,
                _parameter_exists::value >::result_type >::type vi_map_type;
        typedef boost::shared_array_property_map< Value, vi_map_type > map_type;
        static map_type make_map(
            const Graph& g, Value v, const PM&, const ArgPack& ap)
        {
            return make_shared_array_property_map(num_vertices(g), v,
                override_const_property(ap,
                    boost::graph::keywords::_vertex_index_map, g,
                    vertex_index));
        }
    };

    template < typename Graph, typename ArgPack, typename MapTag,
        typename ValueType >
    struct map_maker
    {
        typedef typename boost::mpl::has_key< ArgPack, MapTag >::type
            _parameter_exists;
        BOOST_STATIC_CONSTANT(bool, has_map = (_parameter_exists::value));
        typedef map_maker_helper< has_map, Graph, ArgPack, ValueType,
            typename boost::remove_const< typename boost::parameter::value_type<
                ArgPack, MapTag, int >::type >::type >
            helper;
        typedef typename helper::map_type map_type;
        static map_type make_map(
            const Graph& g, const ArgPack& ap, ValueType default_value)
        {
            return helper::make_map(g, default_value,
                ap[::boost::parameter::keyword< MapTag >::instance | 0], ap);
        }
    };

    template < typename MapTag, typename ValueType = void >
    class make_property_map_from_arg_pack_gen
    {
        ValueType default_value;

    public:
        make_property_map_from_arg_pack_gen(ValueType default_value)
        : default_value(default_value)
        {
        }

        template < typename Graph, typename ArgPack >
        typename map_maker< Graph, ArgPack, MapTag, ValueType >::map_type
        operator()(const Graph& g, const ArgPack& ap) const
        {
            return map_maker< Graph, ArgPack, MapTag, ValueType >::make_map(
                g, ap, default_value);
        }
    };

    template < typename MapTag >
    class make_property_map_from_arg_pack_gen< MapTag, void >
    {
    public:
        template < typename ValueType, typename Graph, typename ArgPack >
        typename map_maker< Graph, ArgPack, MapTag, ValueType >::map_type
        operator()(
            const Graph& g, const ArgPack& ap, ValueType default_value) const
        {
            return map_maker< Graph, ArgPack, MapTag, ValueType >::make_map(
                g, ap, default_value);
        }
    };

    static const make_property_map_from_arg_pack_gen<
        boost::graph::keywords::tag::color_map, default_color_type >
        make_color_map_from_arg_pack(white_color);

    template < bool Exists, class Graph, class ArgPack, class KeyT,
        class ValueT, class KeyMapTag, class IndexInHeapMapTag, class Compare,
        class Q >
    struct priority_queue_maker_helper
    {
        typedef Q priority_queue_type;

        static priority_queue_type make_queue(
            const Graph&, const ArgPack&, KeyT, const Q& q)
        {
            return q;
        }
    };

    template < class Graph, class ArgPack, class KeyT, class ValueT,
        class KeyMapTag, class IndexInHeapMapTag, class Compare, class Q >
    struct priority_queue_maker_helper< false, Graph, ArgPack, KeyT, ValueT,
        KeyMapTag, IndexInHeapMapTag, Compare, Q >
    {
        typedef typename std::vector< ValueT >::size_type
            default_index_in_heap_type;
        typedef typename map_maker< Graph, ArgPack, IndexInHeapMapTag,
            default_index_in_heap_type >::helper::map_type index_in_heap_map;
        typedef boost::d_ary_heap_indirect< ValueT, 4, index_in_heap_map,
            typename map_maker< Graph, ArgPack, KeyMapTag,
                KeyT >::helper::map_type,
            Compare >
            priority_queue_type;

        static priority_queue_type make_queue(
            const Graph& g, const ArgPack& ap, KeyT defaultKey, const Q&)
        {
            return priority_queue_type(
                map_maker< Graph, ArgPack, KeyMapTag, KeyT >::make_map(
                    g, ap, defaultKey),
                map_maker< Graph, ArgPack, IndexInHeapMapTag,
                    default_index_in_heap_type >::make_map(g, ap,
                    typename boost::property_traits<
                        index_in_heap_map >::value_type(-1)));
        }
    };

    template < class Graph, class ArgPack, class KeyT, class ValueT,
        class PriorityQueueTag, class KeyMapTag, class IndexInHeapMapTag,
        class Compare >
    struct priority_queue_maker
    {
        typedef typename boost::mpl::has_key< ArgPack, PriorityQueueTag >::type
            _parameter_exists;
        BOOST_STATIC_CONSTANT(bool, g_hasQ = (_parameter_exists::value));
        typedef boost::reference_wrapper< int > int_refw;
        typedef typename boost::parameter::value_type< ArgPack,
            PriorityQueueTag, int_refw >::type param_value_type_wrapper;
        typedef typename param_value_type_wrapper::type param_value_type;
        typedef typename boost::remove_const< param_value_type >::type
            param_value_type_no_const;
        typedef priority_queue_maker_helper< g_hasQ, Graph, ArgPack, KeyT,
            ValueT, KeyMapTag, IndexInHeapMapTag, Compare,
            param_value_type_no_const >
            helper;
        typedef typename helper::priority_queue_type priority_queue_type;

        static priority_queue_type make_queue(
            const Graph& g, const ArgPack& ap, KeyT defaultKey)
        {
            return helper::make_queue(g, ap, defaultKey,
                ap[::boost::parameter::keyword< PriorityQueueTag >::instance
                    | 0]);
        }
    };

    template < class PriorityQueueTag, class KeyT, class ValueT,
        class Compare = std::less< KeyT >,
        class KeyMapTag = boost::graph::keywords::tag::distance_map,
        class IndexInHeapMapTag
        = boost::graph::keywords::tag::index_in_heap_map >
    struct make_priority_queue_from_arg_pack_gen
    {
        KeyT defaultKey;

        make_priority_queue_from_arg_pack_gen(KeyT defaultKey_)
        : defaultKey(defaultKey_)
        {
        }

        template < class F > struct result
        {
            typedef typename remove_const< typename remove_reference<
                typename function_traits< F >::arg1_type >::type >::type
                graph_type;
            typedef typename remove_const< typename remove_reference<
                typename function_traits< F >::arg2_type >::type >::type
                arg_pack_type;
            typedef typename priority_queue_maker< graph_type, arg_pack_type,
                KeyT, ValueT, PriorityQueueTag, KeyMapTag, IndexInHeapMapTag,
                Compare >::priority_queue_type type;
        };

        template < class Graph, class ArgPack >
        typename priority_queue_maker< Graph, ArgPack, KeyT, ValueT,
            PriorityQueueTag, KeyMapTag, IndexInHeapMapTag,
            Compare >::priority_queue_type
        operator()(const Graph& g, const ArgPack& ap) const
        {
            return priority_queue_maker< Graph, ArgPack, KeyT, ValueT,
                PriorityQueueTag, KeyMapTag, IndexInHeapMapTag,
                Compare >::make_queue(g, ap, defaultKey);
        }
    };

    template < typename G >
    typename boost::graph_traits< G >::vertex_descriptor get_null_vertex(
        const G&)
    {
        return boost::graph_traits< G >::null_vertex();
    }

    template < typename G >
    typename boost::graph_traits< G >::vertex_descriptor
    get_default_starting_vertex(const G& g)
    {
        std::pair< typename boost::graph_traits< G >::vertex_iterator,
            typename boost::graph_traits< G >::vertex_iterator >
            iters = vertices(g);
        return (iters.first == iters.second)
            ? boost::graph_traits< G >::null_vertex()
            : *iters.first;
    }

    template < typename G > struct get_default_starting_vertex_t
    {
        typedef
            typename boost::graph_traits< G >::vertex_descriptor result_type;
        const G& g;
        get_default_starting_vertex_t(const G& g) : g(g) {}
        result_type operator()() const
        {
            return get_default_starting_vertex(g);
        }
    };

    // Wrapper to avoid instantiating numeric_limits when users provide
    // distance_inf value manually
    template < typename T > struct get_max
    {
        T operator()() const { return (std::numeric_limits< T >::max)(); }
        typedef T result_type;
    };

} // namespace detail

} // namespace boost

#undef BOOST_BGL_DECLARE_NAMED_PARAMS

#endif // BOOST_GRAPH_NAMED_FUNCTION_PARAMS_HPP

/* named_function_params.hpp
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
*/