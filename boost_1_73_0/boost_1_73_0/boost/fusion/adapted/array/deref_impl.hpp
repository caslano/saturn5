/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_DEREF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<po_array_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                add_reference<
                    typename remove_extent<typename It::seq_type>::type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return (*it.seq)[It::index::value];
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
AC9owCKWVNow9cKb4SSEqTseu344g2EfXH9W4916/jVqg2JUAeSuFERiFgLoqiwoSQ+Cf9dOt5zwBrqT8WA4CqOwH44ifxjh3Bv6AZxD4+wc+mRh5N2ARkEX+vzhg/P+wjnBBf0UkVjuIkmUPmn8o6gk4gY34LtfetZb4PN3cM2BcYWnjGeot/feqNy/10Qq6RiYYOYPR4EXWD9QlhTrlMCVjltJMf9kmRAJx/WX6TT1DrRzFEmBWnkjFRsKzpZ4bDzLWh9NyOte0B17ZtsKsGXnmWe259lIy+Z0oO/krsomLorD9FOSUVZ17LjfPTt//8GuJxeW1ms1v4RMoEoFiVOj4q2gijyWDs3x+DfZmeKt5ViWEVyFr0Uh+AabgTKUKy9hi7pBNa4IFGQZJztkVGywGVDE2LlpxXKc/MX4tiDpklioLITAfil2RmJkRZg6qMGBaU5Y9brYh5W6iVMLuTgg8vPgNvD+6DXPW5odtKJLxoURrWGy704GoXVinkbjYTjsDgeBpV3NUu9398to0LMcllmS/kMiVTERJcjrArNuJnksoF0qYUNtoIfHB7Yiq4UNG05TaGdly/rXAqRRYZ9DZqCaj7723rrZ9wY9aLfQ/qP1UEkI2kbcPz+TEWVUNdGCZk292AKNXblm
*/