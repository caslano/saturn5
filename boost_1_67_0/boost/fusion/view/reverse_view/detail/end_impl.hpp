/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07202005_0851)
#define FUSION_END_IMPL_07202005_0851

namespace boost { namespace fusion
{
    struct reverse_view_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<reverse_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef reverse_view_iterator<typename Sequence::first_type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& s)
                {
                    return type(s.first());
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
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
*/