/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07162005_1031)
#define FUSION_BEGIN_IMPL_07162005_1031

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
        struct begin_impl;

        // Unary Version
        template <>
        struct begin_impl<transform_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator<first_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first(), s.f);
                }
            };
        };

        // Binary Version
        template <>
        struct begin_impl<transform_view2_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first1_type first1_type;
                typedef typename Sequence::first2_type first2_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator2<first1_type, first2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first1(), s.first2(), s.f);
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
ofQ5b82S4Mk5ay9AZeQl6Dlc/RSN92kw6hzc1hKUtAmWqCHqGjKnh1tKqR4xlWkhHuo4fmXbGTgfign1c1zsSeNpCny47fYSQ8LT/s9zQoc3sL1iKWdOXgDUtVXiv8EVHl2lBz5yuhkzK4LG29FaSDkOW0rDNOa6MJPh2c9yGMtIfXtKzNCLIl+otflFZSm0642coYgA4XtUJInXdKiqvRg78ncqc6H9AH8CWyCB2FhDYUCLQZTmFNxfMG6k101ExednLqEv/K6PnCWYmoNRZrfiouokBmIBVrODS0UIFNv0Uk7TUNp3jU+tYExne3LeabKXJBlC9SsO1uB2lcJLNWCKkciuP1BgnfCBUIh7i6DFqejOQYtTY9hx7qvZBkOF4Bc07mQk3oK1BdUB2tO7+6M0xm3KLMJbubdqJIdhyFXGMmIV7ke+us9Dgyrq699cvypJo1jeYOgImNu6n/+2g5Cu9oDFgqDCeiKyd08IVBv8prOZY146VpicIh2o3CJmmyF4oC0UxbGSTBV1NZx+rN6WvptcqkmX9064t0FcIBzgvTYBBsF2ep5k1Q==
*/