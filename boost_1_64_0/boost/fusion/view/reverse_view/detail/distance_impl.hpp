/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_14122005_2104)
#define FUSION_DISTANCE_IMPL_14122005_2104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion {

    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<reverse_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
            {
                typedef typename First::first_type first_type;
                typedef typename Last::first_type last_type;
                typedef typename result_of::distance<last_type, first_type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(last.first, first.first);
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
e/MzotDCuOQv06JO0rq1YpZItgmT5i6NrWRXn2v+39lF6//MR356+5y6zrAOnODBklSlOBfWlc01HfNk0ytWZbW6fzonuWxfa59Ad4WJxUvT04LGjc8kAnOJfuOnmwHhwEftdzrx/QoYPXN3di1tl3Gtn/8sZxKmGoFmJuG3CKqFEtZywAFCyBhRgtuU+M2583ajoKCxqYH7h7QY5FbKl/xn/MF6QhcGaG+uAMNiYRgvq1xIXUaewA8uGGwLQG1W+iE7I9Iu6SlsAkijhAyPx17ThfIBKFdUiZ8soP5QxrMZYwsFPoXgHKIs2O5rWR5i4Ps7fdneUYbJjpe2gTqSXpWnnWQ12bP7B5D89NsmcFqVnwvbJKaiLpwxwV3iqI68m9VDZKotz6wDy7G8qzs88dvzeudjaYweoVN1qF9juscqoOwcTZ9IQyDAd10v5uLwbwD4Y3XmSoTjiQEX0SBTxghogNk/Qy8d0zBF/sJAnfMOrvHTB/V0X1mYx9Gdp1H+YxmtfBaYn+uIYPhoEXGljcWPZ8hqfj7I7lw3hgU/ckhJuvT90Qw8jGzP6Q==
*/