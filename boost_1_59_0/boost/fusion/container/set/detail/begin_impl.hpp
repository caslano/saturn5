/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct begin_impl;

    template <>
    struct begin_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
                  , typename Seq::category
                  , Seq
                  , 0
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

/* begin_impl.hpp
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
*/