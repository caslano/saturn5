/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_DEQUE_02032013_1921)
#define BOOST_FUSION_BUILD_DEQUE_02032013_1921

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/container/deque/detail/cpp03/as_deque.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_deque
            : detail::as_deque<result_of::size<Sequence>::value>
        {
            typedef typename
                detail::as_deque<result_of::size<Sequence>::value>
            gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef typename result_of::as_deque<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef typename result_of::as_deque<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* build_deque.hpp
luAIGo6+PvC1wimlxbrlpK3UZ9ZOLBnXqyHQcOGHTUt6F2flWFVMB/TYzynFNVnAygj7kOnt++D0W488PIBVJFKF/5OQeVRlANJOieezzj6SR4eljc6o4JMQ75cdDXaYnv1K/RlPgfx4G/mVvq0VOx9MoNAgUa9z7WURWsD8JPsgRCtuoqSbKn15Jbx8fXPKlPLReaypgyzXiqoOimkkqqq+KUJOwkAypVOUVBKzs2KvBSwqxIRh6Qsbb7YhxYQC+0m3aMkXjMLevr0xuqQxvC1evANPqosQx9GBhUEKEasiRjuK1jq0dCI04Is2XmQr22SgWF3FhWm3rLYyvdSxfBFZEGoZCJTz1/JcuZ6OtpCh35GtUT0SorJjOJFpQUAw9ckJSbNefSHG5jOuLmjkHqmLh9bwKjleuY/T5FVnSqQ0VCxlS2hYWLb7p33+67HqbtWwiQcXJehNbZejooW1AsO6+wqhevlmXndrNRBzIBZgoZWWALSPm/N2znj0AofWC/ayvlpY5HJYAh7QYR1FnOhaezUgd/838AT5EhEQrgXeSBND0PsP1c7Ljg==
*/