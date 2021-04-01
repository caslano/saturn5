/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_09172005_0721)
#define FUSION_DISTANCE_09172005_0721

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/distance.hpp>
#include <boost/fusion/support/category_of.hpp>

#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct distance_impl
        {
            // default implementation
            template <typename First, typename Last>
            struct apply : distance_detail::linear_distance<First, Last> 
            {};
        };

        template <>
        struct distance_impl<iterator_facade_tag>
        {
            template <typename First, typename Last>
            struct apply : First::template distance<First, Last> {};
        };

        template <>
        struct distance_impl<boost_array_iterator_tag>;

        template <>
        struct distance_impl<mpl_iterator_tag>;

        template <>
        struct distance_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename First, typename Last>
        struct distance
          : extension::distance_impl<typename detail::tag_of<First>::type>::
                template apply<First, Last>
        {
            typedef typename extension::distance_impl<typename detail::tag_of<First>::type>:: 
            template apply<First, Last>::type distance_application;
            BOOST_STATIC_CONSTANT(int, value = distance_application::value);
        };
    }
        
    template <typename First, typename Last>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::distance<First, Last>::type
    distance(First const& a, Last const& b)
    {
        return result_of::distance<First, Last>::call(a,b);
    }
}}

#endif

/* distance.hpp
O7mi5TWxBgtd8aHwBOyr1cJ7fEVOPhLxtVdwPVWOxCeDm0IujrMcJKTDQJmLDAgVQ9OyHOm2fy5Iym0GbULQV+G0q70nugkauGVooYPx4BgVA5vkEQfIdY9p4G5fxqN5w5Uxt5n4DvCeLsf6iIS/b0uF6cHUu9b39Hrb/O2jGGzWwMiQbm0RcbhbNR8HfnY8P9QS/LVMQ77yE3Jfn5sNqeB4utC8ExVfx7cc7+Pv8Txj5ZapT7QdNJqkZVG3KuSFtsYZ5PB18lBxoe3ElOWR7g50J1r494vmKbrZItaSGqg/dLch7UMKZ02Ya0TcvGCN4BJKh9Ru5Gq90TRlRpGaaXgSWh4LfFhv4SRmiPIlb/VqROe16TzWkBEnZROYvA1rzaoz1lILFzx1ZEjHB9LbCwNxpwV7QoPyaBGIwLzZILXob5aStalPcp3ZWBCYiBbUrJ2rUBGy8SC4/Qj5/fSysBZ1W0Hvb01epoktGwN7oXSvoTalPN7/hEuiJnGRMHblewvQDGgwhaQjzNpeKUa2Xdt6RryUQmzlPx63MwPXSzL2vUUW3rzzkoiHTA==
*/