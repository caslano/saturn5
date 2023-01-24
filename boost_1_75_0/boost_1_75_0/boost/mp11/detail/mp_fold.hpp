#ifndef BOOST_MP11_DETAIL_MP_FOLD_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_FOLD_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/config.hpp>

namespace boost
{
namespace mp11
{

// mp_fold<L, V, F>
namespace detail
{

template<class L, class V, template<class...> class F> struct mp_fold_impl
{
// An error "no type named 'type'" here means that the first argument to mp_fold is not a list
};

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1800 )

template<template<class...> class L, class... T, class V, template<class...> class F> struct mp_fold_impl<L<T...>, V, F>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = V;
};

#else

template<template<class...> class L, class V, template<class...> class F> struct mp_fold_impl<L<>, V, F>
{
    using type = V;
};

#endif

template<template<class...> class L, class T1, class... T, class V, template<class...> class F> struct mp_fold_impl<L<T1, T...>, V, F>
{
    using type = typename mp_fold_impl<L<T...>, F<V, T1>, F>::type;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T, class V, template<class...> class F> struct mp_fold_impl<L<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...>, V, F>
{
    using type = typename mp_fold_impl<L<T...>, F<F<F<F<F<F<F<F<F<F<V, T1>, T2>, T3>, T4>, T5>, T6>, T7>, T8>, T9>, T10>, F>::type;
};

} // namespace detail

template<class L, class V, template<class...> class F> using mp_fold = typename detail::mp_fold_impl<L, V, F>::type;
template<class L, class V, class Q> using mp_fold_q = mp_fold<L, V, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_FOLD_HPP_INCLUDED

/* mp_fold.hpp
LygElE1+1oyZk6ZNlQnKFf4aKXdXIX+z6qQg/702aEU9W9zSueqWYcneamVXt9ncqwWuzuHm1Xjo5tX5vWSnxVNnSIVyhS+Lmf1c4t8D4MRf3MXPbLE2OBzE9LA+w1fJvUoGz9A3kltOTc0lCz0TeKaGZb8Xq4Nn6Z/8Cq9vIa2tMQXCiN1omVWtFh2uzln6BDmtFCKX1szH/PvUgJU39bG0nK225BlzVMNJeMyTatmCHgPZQVpzaU6PXi9Rl0WX6/aWUdPDTCSjZqFcKTuPDh0L+/e0zjGa+q70WtIDkkRewPp9JmlsNqYzYgHiznSXLpw/3+014vzRPG2hz7PQJ93VVAMlmWLGCR41lUiVslppP2is2JEAchVijlmOsbQ14Xbl1nhk4coohbgw6D9MFwL+vN00oRIuNOXyLpTVklEyr9wtHrRwlfA8Zp1hlwl4UK70eZNB6s7vqI1jleLuTPv5Mr1GSx4nbTPcKrh0aaP2IUSFZebiCt+88rwatRxbdzhbYRdHEHs0RWvFaGnVVqtGalW1Zu3au4MKpfaIUVWjZu2tNrFaK0ZQe7Tqq1mCKGokYiQI+fJ9f9z3/t5zznvP+/ud5z7vc8/zXH9YUMPynPQ7+sdfcg2uSwyLPqdy0V2OYGoV/psXPVUkUVgcRmcY1Nq08dClNaMJWvOYa9NMdEPO/a8AjW+Xbh0dw207qwlVriFjh+bGmax0
*/