/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09222005_1104)
#define FUSION_CONVERT_IMPL_09222005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/as_vector.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename detail::as_vector<result_of::size<Sequence>::value> gen;
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