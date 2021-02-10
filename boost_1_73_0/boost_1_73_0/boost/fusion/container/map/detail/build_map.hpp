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
IgLrTabxg+CeXEnIwQJNaMFEs2twSiwnsbXYI73CtubnBjPeoP3XTnRVC5sZNTSTxTa4S62FLeh13nx+Kx7AmCY+qUlw+FFNxHesMmCdf7Ko3Q/f9f0KGBs7YOIEk+lu1j5B6bEyeO5sixfP9JP2ePMz4P+8Bpb8KeJPJLYSRJFbiLncEh5YavSl5hq4H9wndwrkDnB9aKHzOAtRzL0HBCdcDB98FLCXgzAmYOBxQCeyqhJIw1B6OqD+fccKQQB53EDXDeYe5MNG/ltxFTY6D3n9AL6g73iAzK1rqRsBGQq+oEUMjjY5DPcAwDw3jgFZXF6AuuWA5xm30vkjGkjJPyZTUnGFxZ9NKD4MbWyFM2vAD5rdlGv6zFI/El3zjez2VptQd3NTtsLPBkMLNxL7KfEHt4bqRpU8WFjokQteHhAtd50o7ekOmdm+6kd1c6NVr7XVMfDjw9xlYvGc/gaWUdpTzqR50W3+43KzVikAAfWxDsoBMHTMSsEVeKxsP9fyXfBDOoydne/3Tk+Z4fq34PKkMgSLntvu0BVBgJSLO6xvVLb7Rt83dgsAdWJ0gsQqkbghSuhKleK6jB1CSF/Mj38fNmywrm3zadxEBaC9mc6isfQ8G6yyPYcTPEeE43JmHEi8YRmDYk1URCb+
*/