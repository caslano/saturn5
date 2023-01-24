/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_31122005_1237)
#define BOOST_FUSION_END_IMPL_31122005_1237

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/mpl/end.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename mpl::end<
                    typename remove_const<Sequence>::type
                >::type iterator;
                typedef mpl_iterator<iterator> type;
                
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
7/CMHO6OZD/DCbVwlTqN7WabewoZwLgqH7iKVYmXCDZYLJec161GBwJjOn1zuztgGme9+NYbGClYs4tm6/qq1ZKyM9M3KgJyZvuQs/sBS1CKKvcE2Cda2Z470yfbYaNuh65WJq+CPYvt7H6YqJ9RXrbyqShrJCureUi2shlMYWrVfx/WtOZEwBL3RRW0aNq6eLHbXPZKO4rXXSy47sRKq8WxAQ4jWDGyXyJRTMNKaLX7h/HIGueuCHzshoeLrdNx1E4dQvVniZsHBc2nHPNxRzu8H9I6w1wlMepnrzSRCggeEPik0eL4fv/reP5D/RSt2da/atVt5vR5pJ3RM+fK7qw/nzKkfQVX8XBX8NUQleJYC8csWYy31sWKlvoCiEj7EEZWUQxYJ0Y4lD8dypeEYbGHxYLJDWvtBuAajo7+5a00a9RbAs3wAB1d//7Z14FL8PvlvHYbkDbN1viKlQ8GPjlptu0UtMpvJdxR/aSSOwAOXa9j0w3slfa0i6tISp9VS1L6jFp6T+DvXeGdkk6BpOoiFxn5tNRQQrUmTve5DL5zZOVXfg50fIAQoC24e2e75EdqhVRD+GPPLFXH4kZQ1TWrQVZ5ZjVgiPIYF2IN6q0fUUSjf0SjGvcxSrcZDUzCNQroVS7dVL4e3swSN18J3NGHxIlqiJP3Ie4sPG8mC4doiq+jQ0lcdmK4UyUQUW+X06Lr13Nbr1n1FqMf
*/