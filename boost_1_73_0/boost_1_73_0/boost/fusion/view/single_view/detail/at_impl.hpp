/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_AT_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_AT_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion 
{
    struct single_view_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<single_view_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<N, mpl::int_<0> >));
                typedef typename Sequence::value_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type 
                call(Sequence& seq)
                {
                    return seq.val;
                }
            };
        };
    }

}}

#endif

/* at_impl.hpp
txOMdJ777PfeZ7Ox/u0+K2Jd3PsJ6b8QPvCTepyVxW8yrttbh+FHwf+DXr/Cz/sm2RC2y8cwEPd3+Si61CVUs/yA38Pwvol+xbXhPxvY89cQv8IT6IY9D4rpXZlej2vRPQjE0z/96Y+iL55tPnvaE4dRnspMXNQyv5LldU/8kNCTv4yjDx8GldzrCVmLKBuooS7HaSWqYlTfRqUU8D1LY5lXMhFRJRJZxWV6Bb+kuajHUozSTIqD07M3Ryc/9cTtOI3HOMhdMRPVuJhliRhHN1KUMpbpDY8xjcpaFCPoDoMnaVXDgLM6LfIBzC1FLctJhWPg9FFWFSK6idIsuoKJolqM63pabW9sxLMyg9VvJEVcbcR6+4NxPTE7eQOLmER3opjWoi7ErJI9gS17YlIk6Qh/AkDg4XR2laXVuGdXA1PlyUZRikpmGY4F/VJZ8bKluFDg6WEzMYUVpzX+qIq8wqlux8XEawhwxFFGszKHiQAO0CgpAMw9McsTWVJj2rmeQsGUALzwaOx6E1HksBjR2b8QRxcdcRVVadUTr48uX5y+uhSv98/P908u34jT52L/5A0O9vPRySEcfQqTlUJ+mJaygslLkU6mWSoTNee3+2ysrPwuzeNslkjRwdMLK1nPpoNxB1+MEjkSL/Z/
*/