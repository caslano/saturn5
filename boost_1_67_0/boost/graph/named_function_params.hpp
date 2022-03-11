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