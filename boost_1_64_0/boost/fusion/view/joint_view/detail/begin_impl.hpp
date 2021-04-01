/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07162005_0115)
#define FUSION_BEGIN_IMPL_07162005_0115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<joint_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::concat_type concat_type;
                typedef typename Sequence::category category;
                typedef result_of::equal_to<first_type, last_type> equal_to;

                typedef typename
                    mpl::if_<
                        equal_to
                      , concat_type
                      , joint_view_iterator<category, first_type, last_type, concat_type>
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s, mpl::true_)
                {
                    return s.concat();
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s, mpl::false_)
                {
                    return type(s.first(), s.concat());
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return call(s, equal_to());
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
NYtp4cQnhdgYicRiFHL8zuhIvc7uI+EHzNntjGEmDBhtVmvp9mj5RcbIbDy3PpP6vMfN/dUK5VZEYpuRXHrq6AZ9lhSS8/bppccQeZT5fN5c8dcgfqAOdMB6nTKyBqwSlFDOayYD8BXsfY0PVMbNgE7BNKC38GX/4xvK9K6N7ip5xqiHHg6qgrXKNPOavTjuTDYE94NsAqiOQqgXiRaNHHP9UKN3jpv41HhnFpGMGW90Gtr7w03owqAMDOkAi/M4A9DvusyyWhTzimAazyMs/z5DxZs2GZfIYzW/oxTDaN2ai9RRTY8PVUv/mXZqpY1qDGCF6+SAmWxx8aa+I6YWVWXIStB8Pdh2nHP4VERuRGBN+u+oUJ7e5Su1CkTOyYEbgEoOiJ/MDTvX8ifE/LHeBJH/7ttlbfvpXQwXk6E45pG3pWDEoZrGZWpiAme8eYi/nqdPFv1GRbDBliY6/XoWhcD8qns0k0Kg6GUzUBnYuNN1xbrYpUyW/a4D5QU04eByrJQqsGTh+GfeLKTsDToIYdiUsJ5DHv+1iCTsRl7/+yRnDTmtGeiD8pZS0g==
*/