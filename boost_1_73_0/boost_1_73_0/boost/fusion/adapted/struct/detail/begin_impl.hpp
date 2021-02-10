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
dXKKWvGd5up5hyy7h+GDjmtcXxDKhgev++wQXuR1Dwe9VzbGOtfPWfaCcGtNUv/Y2nmd6UfcGTxH/7lo9i27qRQczA/h5P37d/Aa3hyfnJlwSWpGOSSK1hva3phwXvQ7/1Xk7s6S9IMJVAHh1iPAtGISpCjVLWkp4DNnOa0lLYBIKKjMW7bBF1aDqiiUjFOYh9HKCz6acFuxvBpx9qIDWYmOF1CRHYWW5pTtBpiGtApEiQiIXzCpELNTTNQWhqegaLuVI4wmQbgUQHaEcbLBcERBpVQj/7HtvGs5ZmIXIpd2PpXCqtT2SVYrZLMlexCNAiWgk9QEbW/CVhSs1CuWCDebbsOZrMwHWhiwLmzRgqScj3DoyqgcUqCQjNUytSU0yJ4pvUhRSx3tthLbR4ZY1hGo7Noaw2FZ0K4QWHgTurqgbW/fF2KKMla5L/kfWvbAvQBRIyuYOQl4yQw2RDJpwlcvvQqXKXx14tgJ0hWEC3CC1Yj32QsuURsMo7ZA75qWSmTRAts2nNHiUfC/OumGlV7BfBn7YZRm3xZu7AWL8NJJHTiF2ckZfOpqre23M5hxttHNhzPr9Mw6xg39llEi95mkSrcZb1SURNDkCgLni2s8i7x+DXknFXaoEazGiqM6pRwaosvetOKmL0BO
*/