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
a4TQe/zR+1lMPLH6COmD0gCRMlU8R8cY9b4Hxb7QSuD/FNxjnktaj6H464qPptG+WXHrbx1LLrVvNTJuCg/dJ9DUXS/d+fs/3Xv3D4k27l/vGnfBrN+cWT176Ihe+7LOevKI7i237q3tFofWo92wsY/6pDq2SjBr9PdFmGv0982Ybfp7P+Z+/Z1GRm7X39swV+vvKtzX6u91/L6Pay20MaTtbnV/Jo6x34h/ft+hv38X4FtX
*/