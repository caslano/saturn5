
#ifndef BOOST_MPL_SAME_AS_HPP_INCLUDED
#define BOOST_MPL_SAME_AS_HPP_INCLUDED

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

#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template< typename T1 >
struct same_as
{
    template< typename T2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : is_same<T1,T2>
    {
#else
    {
        typedef typename is_same<T1,T2>::type type;
#endif
    };
};

template< typename T1 >
struct not_same_as
{
    template< typename T2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : not_< is_same<T1,T2> >
    {
#else
    {
        typedef typename not_< is_same<T1,T2> >::type type;
#endif
    };
};

}}

#endif // BOOST_MPL_SAME_AS_HPP_INCLUDED

/* same_as.hpp
EEXR4jGa8Z4b53bEB/Li7vBfjPX3DfeDbp8vZH3ELGmmFTAV2mmnrfhFThTjxxeeik7raCAyL2KEHIJPzGllLoLbaJFopGm/QRG5O7rTUmheMfQY7tPFZr9/bQwmK3Kc0f7Q/Zs3zKmmmtkzGb/QamPlSJMq/jqteZ1BGySjQYc7tKWbT1oPiOMzjFYnoj6p5k2sFFqx6+jP51vMaFfkob4TL1DjqqvUq46tQykfS51JMDl+KOQ1XD1Q+Y0qcIk2Km0ysLvbZBvkZ1F8Kx16a0INU4SxIgS0lzsaNb4VDG+zLuTwKvv7bHTPL59Gv0YndaPug7rSwYt/qBchu92n7vmtI8ggA1Bs78rxSYGOVVz4yijW+5lrMxd5A7rcEUXeQd2tNuHn2Z7IHWx6KdvC0ao7rQ1/dTngIj8wNizy2wXvwoOKB88NmPVO6pUAKTE/EcJrF0+H1gvpjNYIiKOl+jfP06gPkzGJ3ZOvZz0iSMKMtx20jJV6obAAsd85Bie/ee87OoKXPFsALQChTSroC+5ElPp6btq83GEu7uMN47Pjy7SPyLXh+w003x1PXJNI5goCmGweazf0AWy02RCoZWTrWVdh3EAmIsJRpeH/myed0vFjdVUfc/NpgmbLkJIS0+Q3wbdujD+rAHKFbeEc/58KwM73t3UaCtZm5g6u/2DpO2kse0OnU0Kw9yhqe354639n6lmyDRWtDxVd
*/