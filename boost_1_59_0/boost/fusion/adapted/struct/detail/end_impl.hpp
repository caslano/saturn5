/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , struct_size<typename remove_const<Seq>::type>::value
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
    struct end_impl<assoc_struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , assoc_struct_category
                  , Seq
                  , struct_size<typename remove_const<Seq>::type>::value
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
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
*/