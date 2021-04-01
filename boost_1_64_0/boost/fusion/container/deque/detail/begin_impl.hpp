/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_BEGIN_IMPL_09122006_2034)
#define BOOST_FUSION_DEQUE_BEGIN_IMPL_09122006_2034

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque_iterator.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template<>
        struct begin_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    deque_iterator<Sequence, (Sequence::next_down::value + 1)>
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

/* begin_impl.hpp
nfeR1pslBDCrppvl9tN7FBFgCMahYEgGF/C+gxP7oQm6+wn46x0QlNumM+XF8528oKIqtFJkP6SuLovv0ATbFDmngC0iRg3Rkljvi7b02KCDDGhFxftsgJHhEihnnzgnqB1Rfv98VsXKh0vsNJCQG1L9NBz3q/s3juaBeSkWZCYHJdASqG/nC+njBpsURN/flsA/zaGUjTzTLwWgK5rcWSURJPTxlRO4+KkfcSmlTJ1RE33Ed5S+LWhutQpwdZVVlz2C7OKbpDqucUvJ1iotly2gRyKR0oZjO79ddhVbZZQf9vCeq/Y8eTX4QNKgYwPAgvwvYpSEpqeUSOeGu43t/VPvSgcOXySNt0WQZDc3zEAYYPzZFAjKSqgVyPliJE8s9idY2ZseK9/6KEtpYezs8UvDqDZaxqsXEYeTtwbCULDEkVtdVRwSJ+xDOYNN51Dn5CeBeDYF4THTJUtQ7GGw/pFeqxu2pNPH+BogSS9Re6Z01sAqDQrAAVdds8JVBsxxUjy9j7J1zQ0cJBhjSqFzKi5c2siLciRVC1C1sM5lyshuRd1asGI/itD9Ag==
*/