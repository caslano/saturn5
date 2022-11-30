
#ifndef BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/has_size.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

// default implementation - returns 'Sequence::size' if sequence has a 'size'
// member, and -1 otherwise; conrete sequences might override it by 
// specializing either the 'O1_size_impl' or the primary 'O1_size' template

#   if !BOOST_WORKAROUND(BOOST_MSVC, < 1300) \
    && !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))

namespace aux {
template< typename Sequence > struct O1_size_impl
    : Sequence::size
{
};
}

template< typename Tag >
struct O1_size_impl
{
    template< typename Sequence > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : if_<
              aux::has_size<Sequence>
            , aux::O1_size_impl<Sequence>
            , long_<-1>
            >::type
    {
#else
    {
        typedef typename if_<
              aux::has_size<Sequence>
            , aux::O1_size_impl<Sequence>
            , long_<-1>
            >::type type;

        BOOST_STATIC_CONSTANT(long, value =
              (if_<
                  aux::has_size<Sequence>
                , aux::O1_size_impl<Sequence>
                , long_<-1>
                >::type::value)
            );
#endif
    };
};

#   else // BOOST_MSVC

template< typename Tag >
struct O1_size_impl
{
    template< typename Sequence > struct apply
        : long_<-1>
        {
        };
};

#   endif

}}

#endif // BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED

/* O1_size_impl.hpp
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
*/