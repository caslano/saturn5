/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1340)
#define FUSION_CONVERT_IMPL_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/as_map.hpp>
#include <boost/fusion/container/map/detail/cpp03/map.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<map_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::as_map<
                        result_of::size<Sequence>::value
                      , is_base_of<
                            associative_tag
                          , typename traits::category_of<Sequence>::type>::value
                    >
                gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
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
*/