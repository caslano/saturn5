/*=============================================================================
    Copyright (c) 2012-2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CONVERT_IMPL_10172012_0940)
#define BOOST_FUSION_CONVERT_IMPL_10172012_0940

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/detail/build_std_tuple.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef detail::build_std_tuple<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type
                > gen;

                typedef typename gen::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return gen::call(begin(seq), end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
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
*/