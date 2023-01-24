/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_DEQUE_02032013_1921)
#define BOOST_FUSION_BUILD_DEQUE_02032013_1921

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last
      , bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_deque;

    template <typename First, typename Last>
    struct build_deque<First, Last, true>
    {
        typedef deque<> type;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

    template <typename T, typename Rest>
    struct push_front_deque;

    template <typename T, typename ...Rest>
    struct push_front_deque<T, deque<Rest...>>
    {
        typedef deque<T, Rest...> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(T const& first, deque<Rest...> const& rest)
        {
            return type(front_extended_deque<deque<Rest...>, T>(rest, first));
        }
    };

    template <typename First, typename Last>
    struct build_deque<First, Last, false>
    {
        typedef
            build_deque<typename result_of::next<First>::type, Last>
        next_build_deque;

        typedef push_front_deque<
            typename result_of::value_of<First>::type
          , typename next_build_deque::type>
        push_front;

        typedef typename push_front::type type;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return push_front::call(
                v, next_build_deque::call(fusion::next(f), l));
        }
    };
}}}

#endif

/* build_deque.hpp
rzgl1FRK5WTvDyWdpfPVCAoUzZZy6slwnC0fWwwKgx1y2vxIg7j26xvkqNiL2+my5XYfR/BfZasi6DOc/IxcabJxv1eDPpnQYcwrEYa6R7DL1s+8CRjrPkMBYz8/PfoZvcR+IV5YmXhxHYoXOFAlb69UhYt8dilDcsbgkvsz+c+U7iyMAbtcL9Zm2YABkjmAx2zuCQeOUXGPqva4lortqY3optR6z6Yh4bKl6FoAj4W8JmIh/0Wr3N1GQHq1C6uk5uBqT986MD2xCmJrczKkobnkG8tDJFsYIXp7aqecwuFW1KiIN83FN937aZTGFBSYLm1zGwaVJNQorO9ECMPYnRQP3lep2Z74KaDZLSCTusdDExVuzyG9l1scJjfSL3jGc+H2UQo33vydZi7kgp4KYi4fJIli0H6+/2OdynmvaEe/UHbp2nDWBdygb+V9OnyvDMS7HGVd2CH0ew82OeI/rW7xzX+SP/HCf1bgc4jbVKjcZtAnhH9errCwyUaY73V34cc5t5pznnhvnIciL5H3rFnN1W9s1MrV/rCeWyd7Zz2jvvXAcNbnEMPxgBdjV3e8sPXkmEFkKOi4WrueWFGvmmMwlb6HX3l7BVeGmQNWa2ZwPK1OIPm6zPUf4ww+yE9brQa82Z+xYoHOlHpbM15Dmg1y9WNsG8e7rvqYGAdS6PyPdWuUtcEahZhpXugdM313EfWk7FIpzOS4F8hn
*/