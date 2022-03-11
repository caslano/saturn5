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