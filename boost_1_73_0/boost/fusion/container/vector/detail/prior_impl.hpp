/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_05042005_1145)
#define FUSION_PRIOR_IMPL_05042005_1145

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;
    template <typename Vector, int N>
    struct vector_iterator;

    namespace extension
    {
        template <typename Tag>
        struct prior_impl;

        template <>
        struct prior_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef vector_iterator<vector, index::value-1> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }
            };
        };
    }
}}

#endif

/* prior_impl.hpp
5uZJ3ph6mdpS2kJru0d4TJt1ccbhe0u+4nnaJnLF7NsTt5WuJ2OCdQpnRiLp66X3WeH2bJmJp/yFkho2TwonhxtRLptQHvLik7LaJuW2kB0jnatqT9Df3pDHsWcpTVvYQuIR59bWvnQQOyNc0Zu4Z5u0dGLasK5y/0M5J7eWgrOfMhiW+v1auDA8hiCHGoU7Uo/S4uIbJOU2kf0tKnuzkapkDfMaSb+5Rf4145vF/+7MtcWr
*/