/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05062005_0857)
#define FUSION_VALUE_OF_IMPL_05062005_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_value_traits.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<filter_view_iterator_tag>
            : detail::adapt_value_traits {};
    }
}}

#endif



/* value_of_impl.hpp
V7sN596jGcw70aiscD8Xb3cvIgsIwZPQ/I49t3gBX5S0qP/fTyIDSOQct486PPgOOEIwf2b7Nh03S0hhL9AlTSVyR4pV6qL1yj6cDgwdF1tjXuM0SO2ecGcsoYA/LTyYWrAb2MtoYmrb8vkbYCTYQm1yrY3QXsKKZljYrjoRN8lvMr83o4F1GYqcq4YbZhnhRdKYVYQQ3st3WDi2lI1tV+nFovbbwgBzSg+8amLoCq1sSnfqTwqTXYpx/vJfs4wEukd7SuWvuwAmyldXnat++1+0Ohz2AurQUZl6MNrpfjuzIAocolXDEetSLS3kVcWGhDb3sUIKu2JrwJ9uKScPk1uG0j6U5VZCweGY/4WKD2hfe2a5wZwFvO0yQ58jAqpjfS1GscH5ecdTaIWhuevJh1AIz7JApb1vdGeNLV/Wj9nyhH/R+/u0TvNUv6IQnduQJYb7rPou5B6VB5UwymG9PNojG2xIW9yc+UQiV4xdIoZUuoMxQH9vIzhO+mhVdP5EOwFe/Hz3CMI2Ea6FGFujA5biQdBVYb0osgZjpVYAZEUNnWR5Vksn1AexFA==
*/