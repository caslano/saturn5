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