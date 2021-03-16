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
NronMcZ2NDzTawoCE9zguhvaGZig25HxDD8zwYF+nvkZ6mdB+Dw/L1w/nygG9mKiYFtlRMG0Qn7e5nAM0a8MDsfyCX4OBTbRzw7mOO5sjtG+y4whabYw0dmacU0RbJpgVwq2ULBrBbtesFsEu02wZwR7XrCDgv1BMMyWMBbxWcxr1NAqcHKjxoCAu3NDE2htG8EVRRaVzs07AbW2l/OJClbjq1hXm5WgqsUczaoWz/X0ypjBY/rgtgwe3naWbdo=
*/