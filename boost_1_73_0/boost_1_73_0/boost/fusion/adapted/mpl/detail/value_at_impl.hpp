/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_31122005_1621)
#define BOOST_FUSION_VALUE_AT_IMPL_31122005_1621

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename N>
            struct apply : mpl::at<Sequence, N> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
PH7vzBBCjMyQhA+B1YjIR0EFg0XAZTMkA4MECRCQ7yEmkSAB0mSSgIK9hWCJU1pq1apFi8r2wZbuQsuyyAMKBQFFcV11l1ZAEFFQqPhRV5+6sO97zj3/uffOR25YeJ7w3vnd7/855z3vOffcc9+x5cf6aN38iqgjL9rf5xxEzrmDyXQzWYcT6SbyU6HWSh51TnC6VKukHZPm1xxbfh2kfU/zmUydt5AOnivOW6ppmrV7JscMMruL33XaPRo/71E=
*/