/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_VALUE_AT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_VALUE_AT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<iterator_range_tag>
        {
            template <typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::begin_type begin_type;
                typedef typename result_of::advance<begin_type,N>::type pos;
                typedef typename result_of::value_of<pos>::type type;
            };
        };
    }
}}

#endif


/* value_at_impl.hpp
3uj6DfUun7v/nU8jV/3+4K5REx/b+e7JZEdI1A0Ri9o++sz4tKPzN1439t2jp9+Imb/+0i/Trt3bo8fUx65s92m33jPabO2x+rKWH3wwsWbQnXteip9Yo+CN7tFP3lRrffY7k3/tHDHry5+W1fhowtbEPZecn7Pkifht2x5y/XrtXx87u7W+uW1OQtiM3dv//fbe9q81avzAdefWbknY8NKN7792w+u/rVl89b0L0uc4Vz+9/tedezvctOmzujl3JdyTsP79xme/K+0z+fqC/WMaNfk5esKTTZt8tW7smNkzr9z017E6USu++++CmlfsSbk25Is+t2ZviH1+c8lrw8Z0mZj1VVL792qG9Fo9fNWxIbW+z4hev+uDjw6Oj9h2snR3aeO9P/QrmZH453Bn/FPz5p9dO2dMnW2h7WaeOvh09PgH/vx+7JYZn874Ytu1u6570jmtT+rJ0+evvzbxqbp/De61JX7p9NPbHq/576RR9T5/aNOODgnjaj/40ke7B4xrdP1t2y57ak3U8mZX7vmsxsnwbb1Gx/3aqHb0sq+veO2a0jkLNo3ZeHZ2r32Ry5ePXnfy3OTV6+6a9VDI5i/D5s24/9uOUyOvOBPy64+b58yJ3vbfO3scO7D1xBv37W/+e9wv4S8PueK5Vy6p80q/Dg/esnxrcNSGIwPzMu8ds2rmtKBflk0ck/DI4bigLh9M2nJ/cMyChNyz
*/