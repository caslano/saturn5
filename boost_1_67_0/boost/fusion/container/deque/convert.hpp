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