/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_DEREF_IMPL_SEP_24_2009_0818AM)
#define BOOST_FUSION_NVIEW_DEREF_IMPL_SEP_24_2009_0818AM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<nview_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef typename result_of::value_of<first_type>::type index;
                typedef typename result_of::at<
                    typename sequence_type::sequence_type, index>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return at<index>(i.seq.seq);
                }
            };
        };

    }

}}

#endif


/* deref_impl.hpp
VjLSojJ63hpv/qx+zd63j+EejHCFGAOrYw/WTyuchKvxzzxefPN7iuoaNK7OnPPTXXldHZZMJnk0qotAHuG373EvLYS+j92zh/GsKgRf+Q8JdGrDtkoZJWHnAkHd2Yl2WXptYciztFsJef8/u6WziIIdm7xMT/sC3oxwH+wg+2wLbv/9qlejor8knvyokTe03e4fJ36M1i7hunky09xK0t8yV+9ZlI/J/gRqa53m1UjHaHI6UuuKVN141QNs+L6qLGLWs+Id5eH6c6YrVHf4sKX/+kJur17+UG2b5/AMra1XB2tqs4zH/UuUm2hWfG/Te+mY53x4uPo1zXc9rx7B5ExwMRAEd/2Q9VvEN2a3f9QDdKcO0habiII5Ln0UQujKTTUueShxW7cccxfWulwEuWZrVaP2qrj3vnY28CXfBPWSBIATIwobf+WSDlbjjRhkqN/l3yLMK4M26HckVk7HXv4JlgTaHmsvK0189FLSbP8Klwkvsnk3aSueCOE+F3xTq/dTDJe2i62K/F0o85VKJ3GkAY8cvxFt90uzvo7H/iYgxBeLBH7/8LhXmhQju/V99zvHIZ8f52bUcOzlpcK7nDeJNtVBZQkqxdJtqutSutX9ItEyGYRfE2kPtEbRYWdW/9ZAg3v5W/08yQUogsJyh6bDu0hzTZWyxp28rKktUjALNjNQuMh9kUkLKzhJrKWvfz/rRifwz4vnYBTl
*/