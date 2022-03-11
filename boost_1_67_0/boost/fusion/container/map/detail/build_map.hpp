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