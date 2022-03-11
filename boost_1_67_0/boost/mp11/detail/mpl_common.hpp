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