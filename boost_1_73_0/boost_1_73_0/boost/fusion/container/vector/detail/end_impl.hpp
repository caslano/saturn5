/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05042005_1142)
#define FUSION_END_IMPL_05042005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::size size;
                typedef vector_iterator<Sequence, size::value> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
PA5mcpKDLJ2Cbp2iMQLaw5vLmEwujrCWCWwpwtksuVWSP7TFrvI0jLOJTPf11NEy02GrBOzqkiwPwJPRcCB3MhHDsmDgZJkD55T6MfYE4IhAJJT0PY1XL/cUy2vYvBvZ4LWpnuiNaZjBBFMZju+xOzkLF5mxTJAszjCmxiiUgLLCpimjPeQBNWGEEHtof0J8u43yqQHb4jrNBtBFrdlsArJ3PrQvg/6gdTnod7rvz9uIejQgzHwnTm4XOzTtJN7j0whNPwlsYMYbLJEyUxnztHCyYme8BNS4VvCk18/gFGqjdBUnueCvRaiRpYHThJ5i3LNRskwzqTdHtTBwopnAx/ALtIZJJCIcjXC7N9Wk/x2F8lxm+ZE4fHHwYgNxBl8G6pkEeQFvHksnJYKBF2gTdhE+a9qT6uJBw4qrakloFgL2doAE70xUfzvPUKB1e3h72j5rXZ0PgpNet9s+GQS4g72rwRF1UZwhTFDLvAD90AUkDNwgnQY3cZ4AfQMK5Wk0QvREgiN6I47p8Fv1/hvgdLRudxlflSCIb7hTRo3F6UM9dbuq7Os5zTwD5B1Na853zGJHIUz98Mh7kaFVnCzz0iEQ1pdj/eLztS/6M6x6/8WRPk3KsPllZU91hSqPmS+JW2ubr50lnLPhcpYf
*/