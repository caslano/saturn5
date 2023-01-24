#ifndef BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mp_fold.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>

namespace boost
{
namespace mp11
{

// mp_min_element<L, P>
namespace detail
{

template<template<class...> class P> struct select_min
{
    template<class T1, class T2> using fn = mp_if<P<T1, T2>, T1, T2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_min_element = mp_fold_q<mp_rest<L>, mp_first<L>, detail::select_min<P>>;
template<class L, class Q> using mp_min_element_q = mp_min_element<L, Q::template fn>;

// mp_max_element<L, P>
namespace detail
{

template<template<class...> class P> struct select_max
{
    template<class T1, class T2> using fn = mp_if<P<T2, T1>, T1, T2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_max_element = mp_fold_q<mp_rest<L>, mp_first<L>, detail::select_max<P>>;
template<class L, class Q> using mp_max_element_q = mp_max_element<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED

/* mp_min_element.hpp
Gdz/v/1D0gobw8wjI7ithBraaoNtuRHh6iZx7JhX/JVe7m6JG85b8fGWCvmRgVuFxYEGZEvZdi+vt11dTYQoz8YddY3DUxcX3i+id1aW5m8MI0DXvY0UhtYeaBzOhDB6UN/fPiN7pBZuxF1Qf1f5UZ7ok3GZtc5hWROoplgbfpQhGTFnHdSziQ4PbH1eCZ7hwO88b7v0tGtaXJW7oWjjIxoHCjCEKnV9kssXYfHAf0BBv/F6KO0q559oRQ0sBOavBSrlrxNQ0FxywCMWXfAN3qmaDabK7IEFJQGlfLfhm4aAOFM2Dt5kjNKA3gbUMyxqwIfPQ6mD1zBGQikfscEkmjqwcO0ar+Ffn/e/hnZ/G9j166lPQZ2V1TYheVH98SpT0HzeZPhTJfbhm1Ok6rLIi08km78ucffdEsvm6HO5wmrvuvCykxli/mfB03+cc7IYUrpmZIzgy5Ud+rlF/Z3HnWxIMzRGlLi7JbrMkyPekA3vi4oDjWTuufB6kLI2DHarz+FaZLfwP+rvF/XWNze2Q6LWL6fqEn2OVTROLrorEn3y30Wtq9WRk/0kJwP/LxmJ/iP+A9kzmF9+shGZ3mqfrKa3+5vRcKbTH6X3vI3lfxV4TQlwYFY6of5aZnWcWkZ1PopNb12Vx93aD0giu1kcXXhHSZuXbD5di6zK9a87/5G6/SdIErsFYHnyZg6ovyYUkTNtJIKuY6bJdGQI
*/