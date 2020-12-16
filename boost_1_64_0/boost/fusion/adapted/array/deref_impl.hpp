/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_DEREF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<po_array_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                add_reference<
                    typename remove_extent<typename It::seq_type>::type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return (*it.seq)[It::index::value];
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
LcmWY77aWIbpSEGJmMvgKRI+WwC/5BmR+WjQaGAab2A+5wnlmDgEknJj2IpOOIo3Xxbz4FIKsgnikHweg+4XDWDk7iFuYxW245UCuphLB6RpP0JdAUDSZwDCOFBQgMCf4blko4XZu1Nq8IXHgmFNW68GQhApJrUBBgwSlsDQAqGvbhMqKcc9ArohQhYGHWNYOGUzNSsKw8QyugOpUA9XAtgN1lgnGjibqjNamlvAXWPYBVmuIX+PRi0JmF+Y11MWH0EeHgCh7HfHcB4RFkAJDuzX3tNHelj1RQB8xoYDmjf9CPAlAY16IuXJrt4zIAa6l4IduAhE9sheUzeHSqPjJok4I1XfMPwteHHa0WZx1s9NBDVjz6N1wquOqqhOVGS6HJjVsbo6ZqG6akyNum1Lw3pPtUkpeMNvCidTkaqEiuU6NOfRWL6XtGliSzbbFHVjE5+iCEm4nHMDCInW1y2G8hv41sUUJhcuBplwvZSNhuaE3C6hP+Rgaw8XhvY+gW1MDxmOsB4uEe+ik/K7bJapvxJkSXUcRtuCW4K3d0BjyTFS60OLLjpy8yrcV0hjwPUgmLZDBxYMBDWy2yQEwqwDEuaGruVgMD+XxLu4ARmV3R/BihwamgxIjFVIhnftPRzfivcj9vwajLpRFAyuI69sfHadmhV20MF3gHwaLeLQXbi/kqYXfJ06ogdMoSd49Gi4vpsAELqfrOLtq/LBC1GFeohEV3YIKHzC3NxYMxdhhnTRADgwP1Vcz6tzIxK5EYHcJkD5Ed14bjS87O5nCcDNFKSb7dxBfRXBWEM+NfYjFtHfsQvIMgad+bHUPHqjJcz+NUj9bvp45m8LJMiW6sN+WZiw4j0cLyo6Gw5LYKBYqzeOGwD9AlMpTfTK9SYofZ3Y4fKluqKAAsfI39AnqUBZ4RDQFygQUX6TwEFWppf0yTS8Su3BtaVDe/BY0MPC1N7Nyz4eZwo0yjO9bW345YUEPrk7IGtLy/OHa8i10IdlRkWlJMIBuCq4OJfno7FOiob2qdr0oSMBgh2sAMF6nRBYgkf4TQYg0WxAq5oOrLj5CE/kVNmM4HlNGXJSZVxgkyJO2KyAwqYFtHXzIkKy+Kp6VNViuVKLZAYxJ63fwByAJEwCaMIsgHqmQT7LuBAYBVHWIjzoVIz5lSPcyu+DYQaxZRAjlTHgKN8qg6AIZA1E7w5pKq6aM36gQNyU/RA3ljNZwnJag2QbIRwrtmhXIq1JhBDsIYRgDAkIGj3HgWE6PmXv58H3swMOrChGklFTJgY4aWbAq0wtcEcxI5VZpdlFHiliJcu5YBO0TimFRfoh75TCqqTb2lq38ngUI129SlVVi0JSDAd1bAVhUocZkBepyvYD3xizKlo76AexeyQ47g+RgyTY7xf6aiPkubp/ZXpvsc9dYnum95mtcAIiPiaWJT0+HWO3wUMQ6ULITYuJLVaKTZfEfnb7BF4aKLGxeEaCADL7MtjS2Y2ZYCXzeEPtTjOLLaM0Cz+dNEdnaI7ihKlJB4SZ17rwElQlQyU4FdUCh+oUc1R9vZXODRPfWLLya5VJRqwC8xmLDd0nY1YMx63mNj+avoZNqgV0yxpWag7sSQUaim1jv6pzumviVvKwnqvmYcHnMmFrDqm/+A0MtSC0UKlPk4qNTRjKHtpSlLFnETDrGo5RWhLtEtCFOYQ0Al0H8+pkcKyFSNNuqLVppcKTBw/HY5DSjD28jzVWUUu0dMlAhQrpofkQgsIDyNMz6oeVVwu7mbYUWIAT7NdVqU5ddH2EywNRvI/2z8AKsx5AEN9HsVVuiTX0Yrdy2L1wtQ1y1HcAVCRZPPBYAIBJEcz+NmVbO7hv72QR3Ol5u50=
*/