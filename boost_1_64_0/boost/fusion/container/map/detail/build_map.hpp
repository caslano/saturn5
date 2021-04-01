/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_MAP_02042013_1448)
#define BOOST_FUSION_BUILD_MAP_02042013_1448

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/container/map/map.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last, bool is_assoc
      , bool is_empty = result_of::equal_to<First, Last>::value
    >
    struct build_map;

    template <typename First, typename Last, bool is_assoc>
    struct build_map<First, Last, is_assoc, true>
    {
        typedef map<> type;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

    template <typename T, typename Rest>
    struct push_front_map;

    template <typename T, typename ...Rest>
    struct push_front_map<T, map<Rest...>>
    {
        typedef map<T, Rest...> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(T const& first, map<Rest...> const& rest)
        {
            return type(push_front(rest, first));
        }
    };

    template <typename First, typename Last, bool is_assoc>
    struct build_map<First, Last, is_assoc, false>
    {
        typedef
            build_map<typename result_of::next<First>::type, Last, is_assoc>
        next_build_map;

        typedef push_front_map<
            typename pair_from<First, is_assoc>::type
          , typename next_build_map::type>
        push_front;

        typedef typename push_front::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            return push_front::call(
                pair_from<First, is_assoc>::call(f)
              , next_build_map::call(fusion::next(f), l));
        }
    };
}}}

#endif

/* build_map.hpp
v0x86kwld4JuHjpCwvqqkDdYcNM10Ia+8vTJa4NExzHY4viP6qDHLZC6eU7VnkLBj85augLeaqaMBkh5yWP4EMjeIKcOHQvPcmSex+oWhbC0LAUCSIwkWD5H5FfsIiFDUy3S5TLxALJiuD2X+ibxzD0aW5+vxE/On9a4kNB0sGPM+BNFax20iy9JtZsq5aIqbEiRgrPwL6PvhAx7eVKMvkb7NIpPTJyd+M/0HAg2G1QjPGitkcNw+TXT6nroXvBsDfb4jK7+Khj8F7OSExkqjuz1Xtx1Pf7aOSvRGfXB+RjQNMkUcsQ9aU+MQ1b5KF31MU5Uz3qlA5d1IOPPac30JvK3K68WwAyi+mvGOx6unVBqYCdie48Amt+5W8+Vm9p0DXNL89x9SzNxma+xdD077P0QQXFc5s0zBD4hYCgeWonRLuqJEl8kQsMUeNBTU35VIgjrfMn26geY+QE/S14Ma6klVLQmtMj+46I3fzigZLttflofy4b7+5LN/8+8fOzU3SVZ929YaDevwKFD/pv8vNEBCdpSB47/9xsSVrKCJUqCYJQpvSANN91MLg==
*/