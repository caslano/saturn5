
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