/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_1226)
#define FUSION_END_IMPL_05062005_1226

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::end_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.last;
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
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
*/