/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_09172005_1120)
#define FUSION_EQUAL_TO_IMPL_09172005_1120

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<cons_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply
                : is_same<
                    typename I1::identity
                  , typename I2::identity
                >
            {
            };
        };
    }
}}

#endif


/* equal_to_impl.hpp
ayx79OyJhVXn3rT5q/bdYtC7xRf03eJUfbc40LRtaZOyL4T2Qh19Z+NxHMyEu8N4uqJm0vXWdH00XV+n7Y/JX5V+YhF9wtm2X2jFihUrVqxYsWLlXyLJaNnq7P+Xhutaa+z/k1g5QvvTadqf3h1NQndDf87mG+Bhjf1pDl1Yx/z/mtLSQgasVsZmOWacD/3qWbFwnY7Npo8p6UYE9as1T1fn0ps1AcwYtA9k/85B46FM2o6a
*/