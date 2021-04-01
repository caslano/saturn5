
#ifndef BOOST_MPL_REPLACE_IF_HPP_INCLUDED
#define BOOST_MPL_REPLACE_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/transform.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate, typename T >
struct replace_if_op
{
    template< typename U > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >
    {
#else
    {
        typedef typename if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >::type type;
#endif
    };
};


template<
      typename Sequence
    , typename Predicate
    , typename T
    , typename Inserter
    >
struct replace_if_impl
    : transform1_impl<
          Sequence
        , protect< aux::replace_if_op<Predicate,T> >
        , Inserter
        >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename T
    , typename Inserter
    >
struct reverse_replace_if_impl
    : reverse_transform1_impl<
          Sequence
        , protect< aux::replace_if_op<Predicate,T> >
        , Inserter
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, replace_if)

}}

#endif // BOOST_MPL_REPLACE_IF_HPP_INCLUDED

/* replace_if.hpp
bcNl2TZ3RrDh8Egw9sDlMqvSUcfNlb2cJR5e9J0OLbEy76YSQ9o6eu8lLcwb6L37DWTLe16h5Y4P6z9acR98+xRr4PgiAWViadpWGum0IvGMB9O3mCLAkcOFXPTNc+pXV2K9127rXfGeOrpmiiEeDCqxYcv7l0QQ+2FZ+bumgsy3dRGPv8AxLtw0oH5PyBy2huAiFbmtfWOo7pEBh/ewBrHoCMvB8xigjxNc1xIBPbUi2GnaZZL5kMDIxGvCDQZSMzDl063Wi7q9tAwoVG4G6fPHT3EMXTPj8EoEl7cfKjlUElANW3tHk86x+OqExPVyUIIgt7JuODLBWAP9qy7p51qbOQbFYYEKIacfB1H8KBjbWvMWPARLjHwpsGHCob9bxDzkb23ZEXpCCdMgUEkpRI9OO+040Gknm0ePYgs0Q91R/eHmZLafjrsHe/jZBzJL3gKGbiZVT1X/nosACanCbMqpYhhxdyJNCXKkdbvF6T2qysAK4PfMmzk/cF6dl7L5Y7C37+ciKsNDF4BVo95aB1B+TTbKZvG9om4j7rslbOrwEMfCKx6bJ8onVg==
*/