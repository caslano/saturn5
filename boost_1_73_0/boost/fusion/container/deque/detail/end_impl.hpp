/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_END_IMPL_09122006_2034)
#define BOOST_FUSION_DEQUE_END_IMPL_09122006_2034

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque_iterator.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template<>
        struct end_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    deque_iterator<Sequence, Sequence::next_up::value>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
5edqrKeNx1X7k1KvONep6vsES6jW27yJF1EuUYKZGVooUU71Y8/ThxYrl9Eubz8z9RcROfPrx4WzHBdOqPwDSWG9GPNk34+Pqu8/NdvKijS17azTZmmuRlt5bBHp6fEDntVqI8vXivXV8mjn6ss2MdGayThIJyXvST29otSLZO9fVq3WUJZHuuo/xNWL/uO0PKrFuY206WmhhqI6pjWamZaYQs1VeT7jE55jo0VhS2Xetaip
*/