/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TRANSFORM_VIEW_ITERATOR_20070127_0957)
#define BOOST_FUSION_TRANSFORM_VIEW_ITERATOR_20070127_0957

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion {

    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<transform_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : result_of::equal_to<typename It1::first_type, typename It2::first_type>
            {};
        };

        template<>
        struct equal_to_impl<transform_view_iterator2_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : result_of::equal_to<typename It1::first1_type, typename It2::first1_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
reFZTPDukX9x9pxZ4Pj1nL7tsp5nlfaKt5bsedcjvvTb3YJMZR3MjgIP3V3km8LVCupHJz/NGO5PqaRZ4c7mqWA+InrM14PRvZPGJII/8Rb2x6kuwT4O5pD3Tib3XG+MXZn9VW+oDeezB1nJWfHGOakJDwnsxxJXPuRFWS2kAuHi+XRzGA88h6uvZl9Fa1d399eTPzrFH5Pu/C3MwnXT09JP5/PHxIheeu7M/5k/y1gmdKT7z121PGdYgujalC+hay4/L/SSdPKa6GKyPbfXMoarD6Xsw6i8ZBVkEM/1mHQ4pdM0yIKZv/2sJ7fy5uowtr1RRr245IdaZa7ggBqkX85Keqcof1MOb0h2kpobvUHMmM+fF65t2OKdxTa3/ywbYPZqsAycEUcO02U94h1YTZtwrOZ4i0k0k94b/Qvs8KgsRnPnPy/RyYogC4i5c96n+dLacH6yUo6jSDf3Oh+Rqq9n8JlBz/wCpc74FJ7ZRGXBmTIQhc3FP2D6IFN9HjU6vLmb7JF7JCb5k4VOwiZd1QbYu3M9PBv4xdFI7bEzJwa3DvLZzIqhw7qS7Z4v8u3yA9BB+Cpn/1Yl/eIZKKXiN2pLk7TgqV+o/Y/B/JlJb8j4jVrx4BjMOXd+HBw1dRXYhPP1ujDbKtiy8zyD1/eUIvbX07bBKbSydOd66Afy/fh6xqrBbNwe9pfqYaMotdL92CPnu+mUD6U3HTyh
*/