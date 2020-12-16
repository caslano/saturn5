#ifndef BOOST_MP11_MAP_HPP_INCLUDED
#define BOOST_MP11_MAP_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mp_map_find.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/function.hpp>
#include <boost/mp11/set.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_map_contains<M, K>
template<class M, class K> using mp_map_contains = mp_not<std::is_same<mp_map_find<M, K>, void>>;

// mp_map_insert<M, T>
template<class M, class T> using mp_map_insert = mp_if< mp_map_contains<M, mp_first<T>>, M, mp_push_back<M, T> >;

// mp_map_replace<M, T>
namespace detail
{

template<class M, class T> struct mp_map_replace_impl;

template<template<class...> class M, class... U, class T> struct mp_map_replace_impl<M<U...>, T>
{
    using K = mp_first<T>;

    // mp_replace_if is inlined here using a struct _f because of msvc-14.0

    template<class V> struct _f { using type = mp_if< std::is_same<mp_first<V>, K>, T, V >; };

    using type = mp_if< mp_map_contains<M<U...>, K>, M<typename _f<U>::type...>, M<U..., T> >;
};

} // namespace detail

template<class M, class T> using mp_map_replace = typename detail::mp_map_replace_impl<M, T>::type;

// mp_map_update<M, T, F>
namespace detail
{

template<class M, class T, template<class...> class F> struct mp_map_update_impl
{
    template<class U> using _f = std::is_same<mp_first<T>, mp_first<U>>;

    // _f3<L<X, Y...>> -> L<X, F<X, Y...>>
    template<class L> using _f3 = mp_assign<L, mp_list<mp_first<L>, mp_rename<L, F> > >;

    using type = mp_if< mp_map_contains<M, mp_first<T>>, mp_transform_if<_f, _f3, M>, mp_push_back<M, T> >;
};

} // namespace detail

template<class M, class T, template<class...> class F> using mp_map_update = typename detail::mp_map_update_impl<M, T, F>::type;
template<class M, class T, class Q> using mp_map_update_q = mp_map_update<M, T, Q::template fn>;

// mp_map_erase<M, K>
namespace detail
{

template<class M, class K> struct mp_map_erase_impl
{
    template<class T> using _f = std::is_same<mp_first<T>, K>;
    using type = mp_remove_if<M, _f>;
};

} // namespace detail

template<class M, class K> using mp_map_erase = typename detail::mp_map_erase_impl<M, K>::type;

// mp_map_keys<M>
template<class M> using mp_map_keys = mp_transform<mp_first, M>;

// mp_is_map<M>
namespace detail
{

template<class L> struct mp_is_map_element: mp_false
{
};

template<template<class...> class L, class T1, class... T> struct mp_is_map_element<L<T1, T...>>: mp_true
{
};

template<class M> using mp_keys_are_set = mp_is_set<mp_map_keys<M>>;

template<class M> struct mp_is_map_impl
{
    using type = mp_false;
};

template<template<class...> class M, class... T> struct mp_is_map_impl<M<T...>>
{
    using type = mp_eval_if<mp_not<mp_all<mp_is_map_element<T>...>>, mp_false, mp_keys_are_set, M<T...>>;
};

} // namespace detail

template<class M> using mp_is_map = typename detail::mp_is_map_impl<M>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_MAP_HPP_INCLUDED

/* map.hpp
JHzXK0Qv4bx07PkpTDd61taO9JxKmVB4qwsUQULTBuCpPtAIVUx40VHwpHD1Avy98UeBfwn39+jAlrIf3czQEeBoITShU4kmHmkVLg5LYMuKqCn7/MBPOAmY7wdAeq4a46FMTVKvNxZQvbBXvBoDAOvEFc6pdZ2ZMnToov2XDrR/384sf0dplZrUz8yz6avL8IwTquGO5hpqsSdn4ZA5vRlUgUjmUvomllbjr1B1C3wunR6FT83l+634G1sh/3gNP7EtUpyqavxE1gx+NzT37StQ4R77rjs09u0pkbdTZqNWDNCyKfJV59aUhr/Kp26Ecw1VrmjFr1krFBz3X3vFq4FGRGPh6qpyr2usZ0S3cZ5R8ylosQKPQvAoBI8WeDXTh+kU+x0MeimM+d3ahJ/TV1F1P8TS6UnVdAgF6tVRw+jpxYMm5ceFjBhWjakmd186/RP4pl2U09eKOmb5j158lr8bBQGtuNiOQoTpXNX4sGqcOqrbrRh/PgXXJaJXC3JVXT8FRrjQjDTi6c2V+Gdc2hSRUoueUXUdR8ujaFMo2qi8KRRcW6+xLLNqJsWaxZmFKNbYtClasEvLLCt5ZmbSyCtGWZcRhc9h7KpxXUYV3oRR+SUs84XmZmP60LjsKYINWlAasqNMHVH4PKZEdhTONKXMNqdk0kQ9PVSmo7jwBUo5yjGu8GpMqQXnhOYSzUhtHIfS20/pj0uJJjka1c6qSiLHVcn8GJs9pdvYvCmvqBhrtbKIMMxfwcZi1h6LIUNX5RoU124z1qC4Yh4YK8SJQ5Aw2EdwSJfkWVRAIb4XLqAQ3kpJafiwHjRkMI3v+EKV8Rx1iayqOH8XxkAJy5vSDWItoFj1LlPCYL6oli5h/J4LUcQ4aSEIWGlJeEV3Lp0zccaVjoSLoCqm3MX1qBqVNqXbKChdJbKZQzUbgEMzdicOzVpBHKqkBq1VTglx4hAkDKpaAT699TJxhUgqF1AIL6q4JLxTd/kcGm6ZQ0/lJeNQ4Wr/9LmwahInhWlaRVycI3MqTpZqN+iiNINFqRJFSe9LsF0So0yilC0CNVktNGS1EESuBByF5ZkZld32ZWZoJGYnIZEFOcNcer5ozyKLpIJ8da659DQsPUnXkOQ1GaKEjc2li1IlixKPDdp7UIzsDVHKFoGarBYasloIIldcGl7XTT6Hhlvm0CndknEIReklIUq1daIntCBJNRuc7YhSbUMiScrRwpIK0stdzYTmtGVTpuiM22VTZiJB8ogskrJpaEzpHnPpTLfIyZIcpSWVIxw1E4lRjhaWVIru6CKfPcMts6dXl2TsQSl6BaWIs3JpWaVrWbmMrLpBVvNVUqQEnzz+eZWDuOt+mwe3t5FPmrrl0hQKVCWCfcSAKgrSXkSh8SIKgZzS4vB5qplWf1tOZYms2uVUViJBShdZJOVUs99cenrb0l1CcbDQ0Cb8mp60oWEsl5lGoeb4RUFJaRzrl8+h4ZY59H5OGw61HdxYUeKs0izIUs0GV7uypLQnS0pSWdouJwWnMi1xKmGnlJay1c3OTjq6cdKODP8Tfs1oV5aUhLKUUpVUsuVzaLhlDl3ti+FQakXJyvA24dfMjmtKvpSa0kdZMSpl8lbns97q9AEuZas7Jiv5AMeEd2iEy+q4puRLqSnNzZTPoeGWObRXZntj3FxDU+pQB+7rsKaUnUpTqs6IUSiTz02yrc9N8sW4LQKTviR/TOnpSTWldEtylN1hTSk7laZ0nlc+e4ZbZk9zeix7kmtKHYIBctqFAVyJYICclHrAqPQUOmWGJZ2y7dwNURyBICWdYi/xpIABXB2AASb86m8XBnAlggFyNBpdSWncziOfQ8Mtc2h2Wio=
*/