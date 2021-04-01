
#ifndef BOOST_MPL_AUX_NA_HPP_INCLUDED
#define BOOST_MPL_AUX_NA_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na_fwd.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

template< typename T >
struct is_na
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_na<na>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template< typename T >
struct is_not_na
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template<>
struct is_not_na<na>
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< typename T, typename U > struct if_na
{
    typedef T type;
};

template< typename U > struct if_na<na,U>
{
    typedef U type;
};
#else
template< typename T > struct if_na_impl
{
    template< typename U > struct apply
    {
        typedef T type;
    };
};

template<> struct if_na_impl<na>
{
    template< typename U > struct apply
    {
        typedef U type;
    };
};

template< typename T, typename U > struct if_na
    : if_na_impl<T>::template apply<U>
{
};
#endif

}}

#endif // BOOST_MPL_AUX_NA_HPP_INCLUDED

/* na.hpp
w0959J3gL7O+yXmRSmPeMhlyASaR/rI0Is6/trPZYZNDT45Vf/6CmhdQbdwMM6xmJVgJWJfZYRp+lFT+SrXOqqUsOnKkqiyYjRxa7mJFlxtWmVN8NuTkm+4vqpkvd+8DtgzF8Ae3HdRlz73fvvUMs7vZzYSU77Ov32sLi4LRkL3RgegYS2OeMZlnXiYww8fMhQfGNVTLKHp4wXNXJALT2/PqI22uawgd+mFq5z2hoMaBAMSTd4I6AVnYbjAVGQ80ncozGPlar1qyEwDV9y32cd2aIPqmac/q2l3wOWTvJgrIBUXoJBTH/5FVmAD9pSHPvedhlAxBB2n75VqsvD6Pi8mrPwmnOj6dYLImL5sbQ2OL6uYqGffL6CSB6cjJNy/nztvXSjKvc+ICs3SHFoqeIh+9SDbttuBaJriQNrIWKrB1f7XMuBBtU/zON2lhqkd9vlDiN5Otz/KB+aZroLPsA1+O8Me2kohRNarONDVdQzh8QBxNHbyrok8NrY68KaeupcD5WoQW27UJg1RZA87UsPTAo5Ld9dDXNA2VZN2LM6myFk7t9Qfh+ZXsAA==
*/