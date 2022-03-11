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