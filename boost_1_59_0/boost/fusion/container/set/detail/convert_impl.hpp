/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1341)
#define FUSION_CONVERT_IMPL_09232005_1341

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/as_set.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct set_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<set_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef detail::as_set<result_of::size<Sequence>::value> gen;
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