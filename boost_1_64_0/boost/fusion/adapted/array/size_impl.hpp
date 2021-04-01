/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_SIZE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct size_impl;

    template<>
    struct size_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : extent<Seq,rank<Seq>::value-1>
        {};
    };
}}}

#endif

/* size_impl.hpp
2EWBRZmenx90WPSRPR2d1x0U9EzrBTm8CTDl+l8W5K14HCplJ8IvvaSKnqcWH3HU4vCVx8ugoyEODV8zu9aLQhKmPVY9MbKkhB6c1cUlpJbxhY46sUnpOR92aNwrZwRPwZbkpFYYAFKUFVCQIQWU04PSiBaCquPIQiqlcf5jKPs0KcWUQABt+5rAarUIUt1AaapLBJXTWpRpc+oZvoguWKA8XQH3QAe42ecnxCnx9sjY9aexq+S3z3OROLboO0tplVDAlvyt8HTIjiW5CWWZY5SDmav5ubf37KYBIItYPFgckWZChbNSP4mlADV4RA8oqpO6xNbYfCmM/a4FonbceMvo9haECatjKgZItus/LxBDZu+hSIaS04lAOgybJlAksWMy+ZGbzjRlyAs/WyCCA1ehsE2SKs5yraY1LkDXXWpVRuwOgaUrPoeL7HQ9UlnMiDe4F9hYzcMlIYoXeQAeM8auCT5i7Mj1Bj4cDtheERCGP2s91xv09cFPNUT0V3X4Yz+2iRE4kxgnZcDm0S0Q6eLPrcLe7P2RjxdgLCuGZ0I9nPIDrBLPwCKVZw==
*/