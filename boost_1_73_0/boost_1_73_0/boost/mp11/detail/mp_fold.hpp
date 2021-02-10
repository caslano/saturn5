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
EYkUSDpb99dnKGptJ9tumwIpWsCQJYrz3ps3w7Ezw7ShRLO5l3FRSPz6yA73UuV67r3ebFbtBV7dbNzN7ebtOyB7U3pUCsGo4VKAYsFeMy8LT6FZ6NB+gDVTn5gKNM9xh2JNdcC3ul2kdT4/wwlqKbiRCoPP3ntZTgxxYsL4RQyDKIYrVMCE4ZS0ApqKYQoXPe9aCoPrwVsmdqZMoR/1vLu7u+BsP0vhJd9h1iibVPXMryTSMv85CCkom/lJPIiHo+G07/9R7E9Ec9rzet6q5Wy9gHuOl9o64LQ6zcn/STSKxWJtSq4BP3rfNFKzHIyELUNSs1cCH+8RFBAZXIFgx4zunrGOOSJYYqn4722OqeuXigsGDdEIGHABhZJ1G0QrjhqdWXEURWd+9aPIihE7DUQxKCwChna0FRF5z3OdlcI7TpXUsjDBYrEOhy+ix5YObPK1lF2yjuxInHxFvHxzAr8SEqUqkILh+z+D3p5Df2mlTbTgqi0dNj+QwiCcXVUs58q1/oOUOH5CyhN5bg4Nltmw30xYmrr6EWhJlGZmxrUMJpPhNIgfK09a6Q86Mc9OFamwWDsGjNvML46JWXFOKC0Z/fjf6+5/qXu67PGpG2dY7eu2lbsp5/r6OObmXmlMc5xquF4wggeK4Zy8
*/