/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<po_array_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    po_array_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , extent<Seq,rank<Seq>::value-1>::value
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
QKu4/96+tv2cvibM60d5yyx78dB0h5RNFaYUyjpx4r8O7MMUEK2aOZuibq/M0m2IyT6MSCbZL25J0kqXb6NA2NEQPRqpneFDfCXIgCqdB35qF20FisUBMX4POiX0w5zKAaFP/QII0r5oeM1+r570k47ChkEV6PiYvHcJbUC7xYFJ1uKyP//Z3wRLMrvHgdaVlMAQDgykNsmJlWQJTZGHM3cR2DXSpodP58UgijYMpMSLThJMMwW6QtouoAuP8dQdazX4VkH6Cvoonk8UIEkVYj4uFEwSRTG+DmjLGFZcs926oKtCoX8KNn8tEE2fihfSH0wvBcjAuHQREBwfExIXPg2Tc6S9Hg1qXaLkWu86byF1s4OyCEdhhnlng+g2S6kggvYzwZwdxzI8M/CjNuDf3pLqx6nqHHqODf9mhSNiF+QdJ1IafO06fLaO5MHfPTm5P7x0i/M6370xMNkM0R+i1Nr5NZht+iPYB5AQtE7u7xqmn7Jfbi0Q7OtNkqLtD9uRRgyNEr3HfZ3hRaA8v4XVyys8/AHnlMzyFTPjXiFGe8xlbT47PWJYKu0qEA==
*/