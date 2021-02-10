/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_ITERATOR_SEP_24_2009_0329PM)
#define BOOST_FUSION_NVIEW_ITERATOR_SEP_24_2009_0329PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion 
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<nview_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
              : result_of::equal_to<typename It1::first_type, typename It2::first_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
cIdK4eRPjrhxejaLSToE94YpO5/T8/x8vsY1XQfRY14SaHPoPLmThHEzhr4bu7bn/ocSFtsxbKu7sD1uXShatLbRQaCFKyFrDsvEX2AfmgNM8YRrct7UZo8WrIDGnUyDk4QroOtxE0ePAgNAanN65/q+69+hBdpozcgXHIAx7pvDmKwTWD0nyE1Udh2jhOTejlz0UdZBYiACurm7SDw7Ai/2Nv3YB1abQAieJBEd4gYeoOb6s+loEYCC+N64qBHcFTm2rxZAjlAH7YPfD0hKR+4UOYI9Iz+Q5zji+FJt4EVmpORIjrjQ6VB8ujiAcTDn+DK2fOYFwcckhBGnF5tmaS2FVjsMyzvAp+LI9tkSPCzfA5scxeV97pqykPpFWhF13KjIwmWWpCVJoU/BiCXETcrXgws7vsSgyVUrJ29agcynx/Kue4hnaFi5DjR5FBFaj88u0JOOz9D0IPS4YHx3YKK8G20rXiUMQixIBkHuox88+LjNihIOA7U5QOmqNzK0rLjUdnAt6A457hH9LaEsLunh67CTeMWTxfZiKrr8ZC23jokO6FlGlLZEN/RB2ozjx5C2N5MyrTBpPBuNivMeMCKoHcvMzLVn56aEfTAad21Hj5Yb/nr6Acb87f3p3y7yQ7wAPL1ugKIRBlGc
*/