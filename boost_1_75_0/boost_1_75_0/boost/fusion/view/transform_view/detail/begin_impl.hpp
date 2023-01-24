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
wAPjqNL83mi9QXoJTxU7BKc28fB2WW9SzmdQhqAM59urMMdgLx+T52EWM6x20yVepdYBU7Lvx3Dkhzz1Yw7nSzplv2HkJeLO/as66EyZZO1vwTSd6/wKVxhvyqhtsjf2OPP9bXQXPT9gl850fcbneQ8ztRJ10ve1yuO9Pu8iregJ9q4Eex6pO1zIwcMkzftegnlRuXzkIirZD6abGj85KT7fwtV/uJyoZcARt9+tRyRtvirwiic/4XLcX+ozVZARbXXziffO9VqtxwR3JkQ5X2KMITPtYW8lr8tMhEaZifoiHyeAGX/43s7/mYkXjCa3m85fZhwZ7bdk63WKT5bwhO7t8A8m6VPiLSIRcBHUEOi/HDL9zPNuigc9W8Lzt9xTM8UsG9oF9ZxOecJBbzuXD46KNUB5d+lJrF+mMKZyl77qAvYhLArs2OtlPWxfF+beXuQFoe/NabdKM5TKtdcxS2sPce0/x7smFjP/2smvQo57k02G35TocNZ+5fMDatlQ0OXuOOzD87KMKaIu6G42ziOeCbWVc70h6BCbo5G99FQcZoB30lfkeJh/iY/QSG9tl+cdpD/NXYTeODstNtlkdM4W7XHfsJmwf+b16S7gbCLfRA5nl31rw/1vlfJhTOMdAvQLOJPtsl6jW+Tzd9pLV2omefJkOpzVgMOF3Pu53iSNRQ2Ys+v+aXAztpeF3gZTOqr0zte41kOpHYFy
*/