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
/cQt13G9uR/1Hnk+xnMhb56JXGP7rB+RZh5feLnW94fGl6vE3lRPG3uoa/6oq/XhDjF3zI6jVbyUVFzJbpXn8esB4qKmttG3SFi62TVZWBpJKhQgtzCn31jrzyR5fsSOYZY/mxR6whpFHyWKczBGW3fYjax37GR1y7b+ImYH49ZQ5klGWz9ZjTg3I8WtjpL4+okxYWTZqa95+37x+1BPGmO+qcguzh+fxXuPIg080abe+GG/
*/