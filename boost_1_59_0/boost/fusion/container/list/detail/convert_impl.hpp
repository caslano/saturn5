/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1215)
#define FUSION_CONVERT_IMPL_09232005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/list/detail/build_cons.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::build_cons<
                        typename result_of::begin<Sequence>::type
                      , typename result_of::end<Sequence>::type
                    >
                build_cons;

                typedef typename build_cons::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return build_cons::call(fusion::begin(seq), fusion::end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
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
*/