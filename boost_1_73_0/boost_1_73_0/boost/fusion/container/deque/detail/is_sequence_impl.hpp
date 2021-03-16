/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
cL0D11e7jysdc621cSIDroXg6tAtuIFr7YkTGXC9C64zJ47Mc63jcSIDrkXgGjNozzbXuhwnMuB673+4yseLDLgWg+ursb9Oc61a8SIDrvfVmr/Grdh4kQHXEnBN2VOU71pN40UGXB8oVw2+23SOFxlwlSqXa/WPFxlwfahcidwaEy8y4PoIXG9c7FDJtabGiwy4loJr8MnZg4/zbLwdLzLgWgau2qHeQa61Ll5kwLUc1sbEPz8951qH4kUGXCs=
*/