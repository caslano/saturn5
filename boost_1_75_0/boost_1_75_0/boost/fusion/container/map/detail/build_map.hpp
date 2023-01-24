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
XAMc45ArA3I9eRYH7lZT68SAdk3UW6d2W0O7DqjxSPRZfax/cIdRXx3V17fZ+hZH41l3T1y8POtuSy6ouE0edePmUkdmRVt0Wwlew0APdrZaHoPo0MAw9YJSyNKHVIrZIA7YS0WZRsUYO7b3I50e9IgGcvRlnA7/qPzS1fjLUXQOTPYx7Od3t6Muezp4+oZEqcX4NM6uNFtnJ7XFgKvVPTwGaEPp0yiqf59e/z6j/gasv8RU/76Q+mH+mtS/fqy5fj/XX6fXX2fUX4/1dzXVXxdS/85I9T8cUn9nkwtCk1Ukw4mMq9P7JuLib0lc6GbcpGUgNiaZVf4DXFVm6eJ9abT5gdvBRkERzmoIS6BZNzaQzreFGd9wGmDpxFiVOa0qNK3anFZtStMXdv2YECfpK+QnIfGiMQyAyVbGlDFmWxkhti/uHhNq+8Jk/cMzJtT6hzyQBJ3Ua4ykgMy0apPdHvlYYrdfnIREEWzKvMtLiqhhIu3y+zjcCaE6kfb1B/kIuJfDJZxpNH8P43Awh7Mnkq0KKn0lBZdyYjf67DAFg8QpREeRTuDvh9v9f9MJtJl1Apu83ek60Xs+148f3Rc46fTM8wZungfr5dAtzej0rME7zEX39zMosQfTm6jrfN0DKbHnyXcTxFzav6nGzqgBRIis7Gto7Nw6kA78u6w6JSYQQ1IheaJOaZ/Qp+65vqnSThTXmd/XUNqJ5Trb
*/