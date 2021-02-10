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
2GDDAv9+EZUu4+dsQJZ3MesjioNXDhww7W9QSwMECgAAAAgALWdKUpaj+8rtIAAAf3EAABUACQBjdXJsLW1hc3Rlci9saWIvZG9oLmNVVAUAAbZIJGDtPf1z2ri2v+evULPTFhKSJmnLdJqme2kgLdMUskB2t7fNeIwRwQ3YrG2S5m77v7/zIcmyMV+9vfPenXnsNoAsHR0dHZ0vHYknOz/vtSV2xMqXQ/8ceME7tbiIwi/SS4prO843wf9Bq8/wvqqTJyJt8s0pi9VNvokSNXFUL6/ws+Os6ugz4oZ/nmDLzw5+hBJohi1Pw+l95F+PElE6LYujg8MXYg/ejg4rou4GvhyLbiKDvoyuK+LVgEr+MXK/ft2P5euKkIlwx/sKVG/kxyIOh8mdG0kBn8e+J4NYDoQbi4GMvcjvwxc/EMlIiqE/luK0ffGx2XpbEXcj3xshkPtwJuJROBsPxMi9lSKSnvRvGcbUjRIRDqE5AB/4cQIAZ4kfBvvQtxSJjCYxwsDu3XEcCvfW9cduHzpyEzFKkmn88skTbxaNAfsng9CLn3h6+PujZGJG8hGQmLj3IpwmIgnFLJYVgTUrYhIO/CG+A0GgcDrrj/14VEmxga6CwZMwErEcjxEWtPNlzGhL0VXkqWA1MQWM/QTf
*/