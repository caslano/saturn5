/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct begin_impl;

    template <>
    struct begin_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , random_access_traversal_tag
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

    template <>
    struct begin_impl<assoc_struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , assoc_struct_category
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