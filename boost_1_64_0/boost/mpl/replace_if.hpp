
#ifndef BOOST_MPL_REPLACE_IF_HPP_INCLUDED
#define BOOST_MPL_REPLACE_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/transform.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate, typename T >
struct replace_if_op
{
    template< typename U > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >
    {
#else
    {
        typedef typename if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >::type type;
#endif
    };
};


template<
      typename Sequence
    , typename Predicate
    , typename T
    , typename Inserter
    >
struct replace_if_impl
    : transform1_impl<
          Sequence
        , protect< aux::replace_if_op<Predicate,T> >
        , Inserter
        >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename T
    , typename Inserter
    >
struct reverse_replace_if_impl
    : reverse_transform1_impl<
          Sequence
        , protect< aux::replace_if_op<Predicate,T> >
        , Inserter
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, replace_if)

}}

#endif // BOOST_MPL_REPLACE_IF_HPP_INCLUDED

/* replace_if.hpp
yFWje8jvTihyl4/jMvvIAneNu7oTNxTJujWzlzj1t680rahx3lnc1X8SBkA3Igdy5VTq9/RGYMVvJW1sihll89jbt3KYeC53kvPOiQXuin5ye6b2+nYsH1I8vbXneFrF930+VnhXu37GSLyP/zQK77cnJYL3sjNBQoRY9Gq4WHuf7ErONjsx23RitmkPDYXWaWCUL8Dla67dS/TLCTpDmcD7vGeDX8jiiZC/zK4iyjeS5e6r2PddPKXKo9czxmBND+LKiPCDf4iViX6yAP3TjFwQ6aY/Kj/U8ZotemVBBnFw+wSO9KB/fucHZBIwqGTCVPcP5wk172wxgFLivlG+2Ly9ktE7+SZKY3u3j4Ni6UO4a4QboND1Hbw8MJ8ZWC4WIvmFKGEO77Kpi/EMD4ERm2Ars9F/4IHtgXxGaDKyRhZ5jF6lOLQmZ4kyG0/N9Dudht1IV+ThG0Pci0wC+m1qSg1WjtDVFLI/9Wl9Cj9qCk0xovrndVr3LZsrDWTJJyYDwWpy2XWizKPNFWXGO+VCifhcOGayGY9YTmLDZ5T3L6tAY7jP34sZZ4JgZ7wmaTs+lbO1ePIlU0QfSoYiI+dPapb/JYG82/h3f+nRxALpzfDp0Esc/7WRT8MIy5jRjR8bqvxY1aQ7AXbDrRWLsSj0HGzvlqcTWXLU189cxrvFr22Nb26oH3dUGKg8PeGU4KxcPfEmycWXn9a60YBvYgEhD7np8nSsdwHFcpEmenyI0x8nmPojsywJWml/VnVEt/JN1Lf4VJyBJSFaBjxFMFVc5kTXym1EXf3nvs2m6BHm1tMFQsCb8o8fPKvrOiH9ug39Opf0IL89dJouvT2UD4Y5NuJHC1f71CJ1mY49CTz3dP6rTccn5rar5SYo2vM4QcFVzZWEy5tor8yVDqqTwhyaGVcks71eGXqJzelSuPfVcO9OlldY2RSeWaOdZ1aZE+iUI1wNL8xXPccNcqW/RRu3CMNHTnNuCtsTMvwe7IH6taMlnzeBG5eMgWo8/B7cA/xyaNGbNUNq39W/lZ6EYsvz25Abq75GJXDxCI+7oliMiYfBRJcGjhZqWzbBN4ndJdzE33t8H+dE/5N8ZTnUDov9W8mbRyz2n+ZLckJUeshuobrjyk5AAywV9f374WyzoecLvncRSSlirPdXlUHonzhiFE6wyxHpIsxUeUm5sT3r0b4SNdnkK/llg53RL2p+iQps5U3sc8fbI3b6J7yaL9fb4CK6+rf3hCElX7MhXy/lp+fR49qzNtkcBfC8dlUvdn+uoi4RpSK9+FxruvE8pCP6XyP9En0XLiZz2SqgPhFfhE6nHEdFX7Flj7679TxMOnQCZSdX5GBY/ip9FFCcoejVrX38/KsmW/mptaYxarXiztPjgoZ3V+XaVi5DrU9bY5XXoe0zn0XHAAb9ctT5kxar/WWK/i9i0h+Ptt/ulv44XJB2aUz6uVyGWmfFot+gWfWhaXjexwfk82KuBxW9K8dbOsS3Ubjg8IDyYWLP35xpeR7fYv61AhMb7a/w0jkU277BGfw/O9z3w6/rpxOp6Ueq6Y9NTe+QTTHbFm8h+V7O0nZaMxb2yq5eu3cDuDh3B9UqP8kXjsnHuZJY6HKgLQfT9TAtElCTg6pJtalJumpyMg0RvL+0qINeUfO+ML5ds4MMtYY2hVIYeOY/4aISgOVh/8n+XtzJfXTNu7H628dlqPXlt2KVF6Jt9v7u8JSDOqkx6Yc/k/TffTNWeTOV847anvF6/zvd4/XHseg3rJ8UC6/nJ/C8s3t43oCYzxsU0z7+vq+753Uc4DpbWmPqh8tQ63ctscob0PbGfT3Lc01r9/J8ORb9Bt95seRxxHwe/B8=
*/