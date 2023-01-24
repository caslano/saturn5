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
VtPoX22M/l8i9dGfw1tKKhkQ2X70X7q6h58P+zJRaJlpfsLBDyKnzKHsQCf2P0aQ6OKtUI6tgHW9J5KGMR+3i+NoGPNRfRd7pVsJZyP7voWN02nn4zhtgLA2HIrzsN1nQIJKGoqVxlDkVahiQ7GS0f/VXTgU69U/z9GHYlX7oVjPh2LSMWMoVgUZipWF7YbiWsRYnayyoagGHYoqi20RMS3tYoAFWjhzLMWcqFQYilUGs1WKoVipb6YbsbfuptLbRP5t5vwbKf82A9Dr/Ag0Zi+HIZnBh2QqDckG1fZR8CGphQcfkodxAzB5kbx4I19SlKuTn6NDEAs3i5xlbKqy20RYmxHWIsJajDBVDEdVDMcOhnY5H9pFrTi0yy1+o3q1yGZ10FG90hjVK9vJvPGyLvOaR2WX/lR0JSC4kmq8Vp7IJ6MIDlyLpzIsvJ6HL8Y1NS1qdh7RtHLIoTvlsE1DH+yH4N1pwRFhDdgJGJec6K+DN4sP17xs7X7Zx7R2X43XetNY993NpOo8s+46LuDD+7KuSNmp2WYctVrWgud29Y8+HKfiDB41So9q6MODhutBn4mg/nrQ+yKoqx70As/zsTPoqfCn5wy+/ufvd/PnbP68iT+n8ec1PP04/hzNw0f2wc0SsT+XOEzEqEP6ULp+PF1P/l13/h7BnycS6fkHfzbz54HewfOt6035bOLpNvD3NYl8/wNPuhxps1KS
*/