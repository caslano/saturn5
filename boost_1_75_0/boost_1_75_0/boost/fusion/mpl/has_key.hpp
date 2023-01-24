/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HAS_KEY_10022005_1617)
#define FUSION_HAS_KEY_10022005_1617

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct has_key_impl;

    template <>
    struct has_key_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Key>
        struct apply : fusion::result_of::has_key<Sequence, Key> {};
    };
}}

#endif


/* has_key.hpp
QnMVauhZ5gpNHBVMQr8Zrx5C9js45GJwVEEIM4egE9YiN9OcEk8tFrkM9NBBEtT3wXYlejbDzNRaFLgCE72jL0xfncvrZcaQfq8t0J2k9ck7hV2SThG8tEbDNZe2o+V4R+dNqMTYhIjk/z4lTJPGAt+7gem2KX6sbjxFa1wkq2Db574d5tjU4HzIbPnJ3Ciya4i9yRBw0uNEJgp66m5IZBsRH2tldokLLTiP0UJELjBwA+1EBzrtRLBvtH8Oa9sFX858Ltb+l7z2vxRrX3weELd38O23vuyIyxtn6CDQxWzfhFgiLxdqwvcIzxM7gayDgCChY+7H9WYBo17E9g0QEnAkgT3YLnZPNSGsGEt2qaReifYgKHXKYpFqYOTniJ041GEOdoWZbpfZlEWpv/qGWY9QGufLq+xVvwOuZ2BBzsjCEyMKxD0Qkljbrj5ehmYEdABvKMrCc9guq4n9m9nmsMevNMJk2FJkxsNj6w4MH2vvQDD3dg3/7sipV/vdr2rvsPLm+Ecdcfhfa7+qpcWU/Mx4g3uitOJHif4D1yaniVU35awzOXQA5+H4vUusbM/2Kof4xp2HMIaUN1BqCSnnojtYgYjtKaL2jGYzOD1zASrjzYJUiUCgb9aZyCONFEZrd2DTdJ1TNjZbnfZTVdNxw/f4F9ZuuZk6fbG+q05f9VOj0198qOtpYj3+y7hOPT7oXdgkK99f1ukP92On
*/