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
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
*/