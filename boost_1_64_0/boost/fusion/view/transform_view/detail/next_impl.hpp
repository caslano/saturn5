/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07162005_1029)
#define FUSION_NEXT_IMPL_07162005_1029

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    template<typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        // Unary Version
        template <>
        struct next_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename result_of::next<first_type>::type next_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator<next_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first), i.f);
                }
            };
        };

        // Binary Version
        template <>
        struct next_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first1_type first1_type;
                typedef typename Iterator::first2_type first2_type;
                typedef typename result_of::next<first1_type>::type next1_type;
                typedef typename result_of::next<first2_type>::type next2_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator2<next1_type, next2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first1), fusion::next(i.first2), i.f);
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
58I16L13OGz+uy01jyutLPt+LxY3Goz+kbAJ2VyJAsx0XSk3r23EJpDaaqiTXLnar4bWFeQXZ0xUEGruvGeE07qYMCRi7iST0GQrhKd89P2feotwpJw2l5A6amfofa2RCJIc6D49K+v6Ipc3BSFL3RtZcnoKvtCRlsmNDu83Fn+2vyIgOnm19yxAdLVc/MHyQp9MazAr2awkY3IUffm3IxNzv5iC0IWd7H0+LrYTFBwefNQNAwc2SBF8UY4TkLXV9qQHZJzczZKajBuRXbA6JRHDyramLebugM1gl2GLnIf4S88+0WvCM0G7+QGuwNXomFvZ4yxuX+IqzQ0ZGLllMvNUT6GpcAu2NyULfufTFC2rh6B8MZjm+6v6OXWTwcmgVo1pjK4S/DwkGL3njhcp/x06ASXqcKs2KY0mqpaBPJUSpNObP+vCTdtBkkapsSKZmlw0SIbOheNZykgxl2NmsNyPGKoIj4WR6XIAtSVjJosFJ4yuRE1TOe7EGqufjlLdllWYvdrA4Figq9mtTn54oW83L+v6se98bZQYgkQUQSl5K3cy7sHF/eKY9w==
*/