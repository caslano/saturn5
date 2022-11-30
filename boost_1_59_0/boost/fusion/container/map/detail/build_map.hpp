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
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
*/