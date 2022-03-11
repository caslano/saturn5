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