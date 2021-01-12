/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
                  , typename Seq::category
                  , Seq
                  , Seq::size::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
Xxv1307rX3sN1xszUsMd5aFf7FgN1wkmwc4wJHYt37b2iWof8CbYFtNX7zfvFFION8IkeBdsBe+DPeH9cDD063NwG/ap8GE4DT4Cr9Xzt8E3sd8Od8Ct8Dn4AnwZ7oKvwDfhq/Bd+GvotAu/gSnQCX8U/Bi2hX+BHeEncAD8KxwK98Iz4N/gGPgpPA9+DvPhb+FNcB+8DX4Dd8I/wR7I4QPYCzr2gdA5vwL+Ha6HP8F7oOU8
*/