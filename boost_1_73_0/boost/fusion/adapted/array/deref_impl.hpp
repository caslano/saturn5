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
5mZCMAFe47TtOsSex8LiyugjGf9Mej1z6taOn1tg6jpt5fzfvOYDGLe5WjfkOkXTCvMLTHtH0y8AW4nd8V7PlvGnI2k4hjJnRQoR7eTrs8iiaUiILYZnRTpF2kba1QjpylzO1qRhWNP1T8gP6TXSPa2WSJpnY9cJxwTMg/F7CDIUqftd5V6LjME7nb3SDD81jZEszzjpnbayg35vN24+1G5NY78rTJXYmYr/msYyCSm/uLAU
*/