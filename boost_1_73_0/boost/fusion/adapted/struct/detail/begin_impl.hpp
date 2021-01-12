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
wsvFbi0XLREbuSR4d7OEaf7EnFzOmpF74TMz8uc6UZhVWOadzWKvqXtdwrPwe7pbuZzt4vud98MvqlBs+AK1VBf5KpX4+af4HwuF+dzZzwCF9CywSj1fsaVjHt9Ucj23Rdz7XXfxR/jXnNGSrrYf1vh+CDmCf8cX+9c5oIWhdYGl/THti4biN0vMrXMfz6gf40wezjb1dK48G0s+GYW9yPNazn3GTjBc+EnzV8Rd1nrpxW1I
*/