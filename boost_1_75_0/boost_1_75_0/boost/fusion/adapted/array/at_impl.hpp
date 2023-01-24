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
XU/8QX2LhU0bdcg+1s9kvEmm6LpppmCZGgPf1DDVP8javGACtMNwkep7YgwTAAplW0u5LgAefE7rpfsiMPKLoNQFAfA8ILCeZljTxvlGsD5NkwMS9+BNcUFgLYlcQfDpNA3KLgLWc5H49kEfutZyChjm8kU+JPBkXa9n+O4myqvi3KUt4RQvmR2DhQORLL9DOqrobwubknq4M7ZhxYS5IZZAIMOXtgxydWSBjZunCKKzpaLUD2NXkvHb42iON0FUFWStZ2QgVkZwOIKC9bSITMGsNfD4NoOp3ngBIekdl8ChI1bPO38z0gY/BWDYJE6hxXEOGEJ6ZMDZqaC2VOsifh8BHP1zZ8Fuxv8CenYEKnPOwklah0+IL3Oq0fQFzghB3m0pJA3LJm9Ji9Uo1UYbyz2TifqWv0PUeT3/XvYOeIK5r64JbCCWMPwtIs9fTaaKn05GOdkG7f3J5B4yiZ9e8eR4qqhrJJ2B7T9/KhY4T+bqO0OXAwSyb58XKFTdpYnLXvypGKbr9mry0ZM82IMeErceKRJMWLqvi4dFrmWgo9pjL+5ltcicaKPKCtp4fMuIKw3kX2UwEJLhK6SF0OuJnioHS1I9CsTaBhAOPM1fT3TV7Zme+DzqLOCKI3qL49ILeQ4YeKWPFRQuo2WPiyx7kPn5XVWgTPO5aDlttOnJb6XseZYBN/ORup1MlomDEb9GqVwUSZqvqCYgfXZf
*/