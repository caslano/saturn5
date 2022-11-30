/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_20061213_2207)
#define FUSION_CONVERT_20061213_2207

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/detail/convert_impl.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
///////////////////////////////////////////////////////////////////////////////
// C++03 (non-variadic) implementation
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/deque/detail/cpp03/build_deque.hpp>

#else
///////////////////////////////////////////////////////////////////////////////
// C++11 variadic implementation
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/deque/detail/build_deque.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_deque :
            detail::build_deque<
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
            >
        {
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef result_of::as_deque<Sequence> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef result_of::as_deque<Sequence const> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }
}}

#endif
#endif

/* convert.hpp
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
*/