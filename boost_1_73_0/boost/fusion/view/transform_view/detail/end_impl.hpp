/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07162005_1028)
#define FUSION_END_IMPL_07162005_1028

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view_fwd.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        // Unary Version
        template <>
        struct end_impl<transform_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator<last_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last(), s.f);
                }
            };
        };

        // Binary Version
        template <>
        struct end_impl<transform_view2_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last1_type last1_type;
                typedef typename Sequence::last2_type last2_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator2<last1_type, last2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last1(), s.last2(), s.f);
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
b3OOL5sVYB2bZ/PAdzneU+CYS9Y3a2u4I9617bKYbrm3/dwY42Wf24Yvx5bKbM3R3czYBmFq66GTeP8c49lzbId4lOQDksTTSMzSzLafu775rA4Z0h3jfA+O8S3SpIu/BSad09+T4y1tr6+wO01zj6BzWxuyy/1kcx+V+UcwKrIsU5d7DODt6CnnUwVJFcNDaerhlAe6w/10RPcMSadjHZskLCQdXZUgW4/THW/LGgZJAvoz
*/