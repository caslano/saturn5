
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
V8jOPDoKaTxQ2T9rmdg4yIVbOzhur10MJhs+H1ivZp+nWJcCcpsbKz1yhdsBm2LegbCNYGFYm36b5DpZx5kvMBmh5+iTs/rpm3KemJNz7xnZrMaPW2tWWAEnIwUv/jKov+4xoboMgbnYBOCllYU1jqDnOfH62k1FpBTCJjWGVXN/JwcHB5vVlZWZmYX1wIaLPYTZuzxpeuuh+oQUomZ5d7NXEi+ku7iP4VhXgqaCIgV9271KW0/FyJVAAmIHzqDyL0PhG9ueDHYf9CSU65cxzTHpMsVP5ilAxRkDJsZVjOGBJW9ccQ9lmSb25EHL/RDlwsq+jza/KaSljNeUltq63mstsszWv3BFAVZkZ5tl7GMdcpT4q1+bzzJCJ35avMcgZ0RkaruUvPbC+bNH0D/6SixH5suuS0ZqMJpuYjOroOwiNJPyXYwDZUQRb1HIQWVlXgqPQyhT7EQB3C2ca+F9vccxsJu60j5ByzuuDs9A1AbzBCA7CpIsAltNlPsm9goBfh6+Hz+kGNlkjkVGv23pNSe/AAJY2MIcdsmomWRyhhX4UUYFKHgH/ekGfgXhW9L84mdoe5Onni2802JjXBn+eGB9Sl6rVt1DhZUjB0vF60yoc1oiVizr15mb8ePsaBZKaRUaITMNGg9vgVAItVuOgvh9KQRNYxlhYxGu1qME37GxGKfxRJf59Q45zWwenPm9dVRG35qhJr1tLDJ1
*/