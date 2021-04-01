/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct at_impl;

    template<>
    struct at_impl<po_array_tag>
    {
        template<typename Seq, typename N>
        struct apply
        {
            typedef typename
                add_reference<typename remove_extent<Seq>::type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return seq[N::value];
            }
        };
    };
}}}

#endif

/* at_impl.hpp
trer3Poco8F/Nu0VyajSiRqswcVFjcwC22IOuUYH+4/bKq1BvBgYv5g8nYAjBT3dFdX9qqtpmYPQ7R6JeR/e62Qa3jzrOvf4r3xEJHJOLlK07JJDy4r2sD4g7N3QsULt9ON7vskKuA2ZCIyzwdUAE9e1d71hbbo0JA2Cwa/CsBorJRn2L9JkOUnX9kKxujowgozZLhJy7WcHE2awD8o7+yTnfq0jIZhMM3nOHARoPB67pfO1FL+SND1aB3vGBlpmDIpxrimOqh4h3PBNsqev9nT2rktdOxXMm0jS8PUbFvE41wAliWGKpxs3TbvCH7y81LgonGqENzR1lIgZVvaBaSIk26ONaVec0mtmycyqeOYJm7TWsYG/codtqU/xsvubwiSABtEtfpq4IUydCmE6fO8LeyJo52rUCYtPnbq99HlrVMICATcq4Uzzj033vAMDYT5s2CB5q0tgW3N9Ggto++6vNF/sdehwjnOrmYF/w3sxbJB8cmc7wnCKEiWqlUp7pYkj3+dZwBHZjEXbpyG46GOBpvtdRSS2sQjczJBFAzRvXEeDiv2IAEfjmA==
*/