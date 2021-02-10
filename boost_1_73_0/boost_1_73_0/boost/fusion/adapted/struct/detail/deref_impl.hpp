/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
        {
           typedef typename
               access::struct_member<
                   typename remove_const<typename It::seq_type>::type
                 , It::index::value
               >::template apply<typename It::seq_type>
           impl;

           typedef typename impl::type type;

           BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
           static type
           call(It const& it)
           {
               return impl::call(*it.seq);
           }
        };
    };
}}}

#endif

/* deref_impl.hpp
tM1ADyED6MG3tWpfsf8BUEsDBAoAAAAIAC1nSlKOWDRGYQQAADIJAAA2AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9YT0FVVEgyX0JFQVJFUi4zVVQFAAG2SCRgrVVRT+NGEH73rxilL+FkHAhVKVd6qgnmSElsy3aOixTJ2thrvMXZtbxrAi39751dO+WgVPBwjuJ11jvffDPzzcRZDeDDd7ssR8PBm1dqvileuO6Mwkb8QTP1ukGaPkL3QcMVru9wNYInq8d0D95l9QhDY5X2vk71c5q+w91Kk9S3kTZepfoRdzrL3n4i6oeG3ZQKhpM9ODw5+Rn2YXwwPrDhnHBGK4gV5Wva3Nhwmpud30pyf+9I+skGqoBUzjPApGQSpCjUljQU8LliGeWS5kAk5FRmDVvjD8ZBlRQKVlGYBOFy6n+2YVuyrOxxHkQLshRtlUNJ7ig0NKPsroOpSaNAFIiA+DmTCjFbxQR30D0FRZuN7GE0CVJJAeSOsIqs0R1RUCpVy4+jUdY2FUYyykUmR9kuFU6pNi+iWiKbDXkAUStQAlpJbdDnbdiInBV6xRThZt2uKyZL+4kWOuT5SDQgaVX1cGjKqOxCoBD32bL1SaiRPVN6kYJL7W1bis2z
*/