/*=============================================================================
    Copyright (c) 2012-2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CONVERT_IMPL_10172012_0120)
#define BOOST_FUSION_CONVERT_IMPL_10172012_0120

#include <boost/tuple/tuple.hpp>
#include <boost/fusion/adapted/boost_tuple/detail/build_cons.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::build_tuple_cons<
                        typename result_of::begin<Sequence>::type
                      , typename result_of::end<Sequence>::type
                    >
                build_tuple_cons;

                typedef typename build_tuple_cons::type type;

                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return build_tuple_cons::call(fusion::begin(seq), fusion::end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
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
*/