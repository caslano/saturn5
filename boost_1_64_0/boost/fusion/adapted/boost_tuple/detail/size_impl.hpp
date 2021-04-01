/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_09272006_0724)
#define BOOST_FUSION_SIZE_IMPL_09272006_0724

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template <>
        struct size_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply : mpl::int_<tuples::length<Sequence>::value> {};
        };
    }
}}

#endif

/* size_impl.hpp
hGPppVJ3C48nYT30ayLvPXkxsA/5rxhvbBBJSBuNuN/t65zxLHzeMpF9LNa0s8/zNXHDSFjP/6ddZ+E1XBlN/uN143/Tcrwj09zWGhDnIFZC+59UMsJzA7EC/40PWsQ3lCz2WUxhq6SNnCQ1OJhu8OosaD5zlJjzVGcwnKiUExnRHEAxe1LJGrq/AvuMBAYPgrj/3krz0QbqsJ3rSPAuLP3ywiKjBk8+Ql4RFQ6UHvGM/GEWv5M4jrfPrWo4WwWQxc1QmMU1OVINvoV2NwpTmBrZc0KkFrND53tm9Aal3D06sw5HvUWQL+QcQnbOGblG2pJC/G0bBZWeCr7KP2TkBdfRtH7vGzsWaq3DqVAlpsNanqAmmRJwu4nrOcLeI3023VXLJm8DCECEGKI99yRC3ml2HNBLubj0ZNbHIV6FYsORCG9YRLkYecYaMpadze6/xM2YKp6gLzH1XfzRJh36LvksPQIQskkroqYFvn+i9DdAizb0tAHIbhc0hOfWPLtM4LHFeyDUSR76x/l72/IJesDFzuHU6Ju/K1QFvMqGDQZPK52LBya0pqcn8w==
*/