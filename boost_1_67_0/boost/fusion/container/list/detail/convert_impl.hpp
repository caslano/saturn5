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