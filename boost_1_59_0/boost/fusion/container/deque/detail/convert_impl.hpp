/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_20061213_2207)
#define FUSION_CONVERT_IMPL_20061213_2207

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/convert.hpp>
#include <boost/fusion/container/deque/deque.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct as_deque;
    }

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<deque_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef result_of::as_deque<Sequence> gen;
                typedef typename gen::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq)
#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
                        , fusion::end(seq)
#endif
                    );
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
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
*/