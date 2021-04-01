
#ifndef BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED
#define BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/numeric_cast.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast1st_impl
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : apply_wrap2< 
              F
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag1,Tag2>,N1 >::type
            , N2
            >
    {
#else
    {
    typedef typename apply_wrap2< 
              F
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag1,Tag2>,N1 >::type
            , N2
            >::type type;
#endif
    };
};

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast2nd_impl
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : apply_wrap2< 
              F
            , N1
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag2,Tag1>,N2 >::type
            >
    {
#else
    {
        typedef typename apply_wrap2< 
              F
            , N1
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag2,Tag1>,N2 >::type
            >::type type;
#endif
    };
};

}}}

#endif // BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED

/* numeric_cast_utils.hpp
xf4Ccoz53jsUXyRMejG9qgWG8+EbAS6RYIvnpkZxPffM+RU1PBxSM3Ez99yju6B+TdNrtTBFwUKx9NqUfNm/tK+xAtkjzANSB0pyAWvh680K/jPGJq/boLCzNi9Q361vbNCnGapZkta8iTUlrEUTu77x3VU7mJlbcV25z0R5of46M8EyeowYUOp65RH3yuukaSJh+hEwRrFAyPVuS3QuRGBYsuLwsU8nuJEh2JI7z7anP4p9TQIfQge6mXIl7P9KxcbjBQU1RRdcUHbhHGAN1nIPbRF0LhKT00oln/Hqv2q4S12PgaFmLZlE87s56jf6H+aDVBSn+JnkrFgJNghOi87FezMSqjLhVp/jfu4qtWbr2cbgW5NbKbq5d7rBvjE+q1tdbI0sdLjJqSDjuTAPLlucUwNS1XVqd/M4djOKt4FegtFh043Gs5gGZ6SE0dyUbQfOwFlg7kGoaKsRkLG45aNBy83/BbIM6LcnPfklpFy/LztC/5BqaaZKbqPIBin1ez2qO+sNcRMpVq0cz5BUNli3aDasmGp/FFZuqVqz35PVTiK8AFmvy3IzmQ==
*/