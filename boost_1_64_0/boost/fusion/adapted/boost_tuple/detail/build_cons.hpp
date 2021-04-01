/*=============================================================================
    Copyright (c) 2012-2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_CONS_10172012_0130)
#define BOOST_FUSION_BUILD_CONS_10172012_0130

#include <boost/tuple/tuple.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <
        typename First
      , typename Last
      , bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_tuple_cons;

    template <typename First, typename Last>
    struct build_tuple_cons<First, Last, true>
    {
        typedef boost::tuples::null_type type;

        BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

    template <typename First, typename Last>
    struct build_tuple_cons<First, Last, false>
    {
        typedef
            build_tuple_cons<typename result_of::next<First>::type, Last>
        next_build_tuple_cons;

        typedef boost::tuples::cons<
            typename result_of::value_of<First>::type
          , typename next_build_tuple_cons::type>
        type;

        BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return type(v, next_build_tuple_cons::call(fusion::next(f), l));
        }
    };
}}}

#endif

/* build_cons.hpp
ssaPHP+unxiMZxRJ/r1Vj0oTTIkyfge5+9jchMKd+nJlQ6rDEGM71qE17iu+Crro68MSXTpi1lE+waaxn/Rls/q2V6QKt+KQiXTXuVbEZxlNORx4/mHxsCjrt/y2nni4CyUREOAHe0QIIKVVhdwj/t3BkchNLimyZFEqD/ZvIlMrx2XuINDEODWqS0yB/Xah5cMlIu7Qj5i/PSgTjeb/vGIVr4gebtwuBmX6ZcvrN+lrhHK6pyMR0Fmh0Ztfj8uluVGy5crmNNnKtsxRLUsjvgWZL9nNFo++ldcvLwOcU69ac3fD3EsIxJv6ofD2v+CfxjLo8l/zeKgIT3vrIGK55Yr6r2grYnITafel6T/17k6W0myzTcfpKT6TFcNHh5kdyOQSyAbAL9HdRreW0xlVCgKp5rmfPCm37b08sBeBy60WVALWotaKV+zYyN93oQuolxJtcEq5nAow2MpcsAH76SPe29FcQcH5HthMiOd4Kiw1rVdGQVpmLnM0tnfv4NK0wGmK84zuuZ2lig2H8NL37xYKj1YopqRg6x2OC9tRRupMLmdFjzKO+mti2Q==
*/