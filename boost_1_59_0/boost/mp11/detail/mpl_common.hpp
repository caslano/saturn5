#ifndef BOOST_MP11_DETAIL_MPL_COMMON_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MPL_COMMON_HPP_INCLUDED

// Copyright 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/list.hpp>
#include <boost/mp11/algorithm.hpp>

namespace boost
{
namespace mpl
{

struct forward_iterator_tag;

namespace aux
{

struct mp11_tag {};

template<class L> struct mp11_iterator
{
    using category = forward_iterator_tag;

    using type = mp11::mp_first<L>;
    using next = mp11_iterator<mp11::mp_rest<L>>;
};

} // namespace aux

// at

template< typename Tag > struct at_impl;

template<> struct at_impl<aux::mp11_tag>
{
    template<class L, class I> struct apply
    {
        using type = mp11::mp_at<L, I>;
    };
};

// back

template< typename Tag > struct back_impl;

template<> struct back_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using N = mp11::mp_size<L>;
        using type = mp11::mp_at_c<L, N::value - 1>;
    };
};

// begin

template< typename Tag > struct begin_impl;

template<> struct begin_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = aux::mp11_iterator<L>;
    };
};

// clear

template< typename Tag > struct clear_impl;

template<> struct clear_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = mp11::mp_clear<L>;
    };
};

// end

template< typename Tag > struct end_impl;

template<> struct end_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = aux::mp11_iterator<mp11::mp_clear<L>>;
    };
};

// front

template< typename Tag > struct front_impl;

template<> struct front_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = mp11::mp_front<L>;
    };
};

// pop_front

template< typename Tag > struct pop_front_impl;

template<> struct pop_front_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = mp11::mp_pop_front<L>;
    };
};

// push_back

template< typename Tag > struct push_back_impl;

template<> struct push_back_impl<aux::mp11_tag>
{
    template<class L, class T> struct apply
    {
        using type = mp11::mp_push_back<L, T>;
    };
};

// push_front

template< typename Tag > struct push_front_impl;

template<> struct push_front_impl<aux::mp11_tag>
{
    template<class L, class T> struct apply
    {
        using type = mp11::mp_push_front<L, T>;
    };
};

// size

template< typename Tag > struct size_impl;

template<> struct size_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = mp11::mp_size<L>;
    };
};

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MPL_COMMON_HPP_INCLUDED

/* mpl_common.hpp
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
*/