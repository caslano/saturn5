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
Y2Mabo0LsxZvk+7B6+wTE4T3Qr7VQ2M8FhcFJWUS7/I99ozo+7TclAsBsXuE172rP3b891/MOG59OX+jX8wc3d0WM63PO7nPNpzvzfXOk7U2sW/gl3DcJ8O9t5pQpJ8eT0iH8F7c/AZejpSqzpGtyM9IWPw8NMFPkd/i5hiuM/EQx4yjzwNxp89Dea00GKXjr2U+4gPOhnNySJO2rjSoqdz8ok7TVPPgRrFb4Csm1tciLanX
*/