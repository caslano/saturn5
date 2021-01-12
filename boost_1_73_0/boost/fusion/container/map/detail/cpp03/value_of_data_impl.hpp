/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                value_of_impl<map_iterator_tag>::
                    template apply<It>::type::second_type
            type;
        };
    };
}}}

#endif

/* value_of_data_impl.hpp
lw/iSB/8M2wHP4ad4R7YHX4Cj4MnEt9p8DPso+EX8DL4JVwDv4Ib4Nfwdvg9/IWG+w3cj30P/BHuVfeAkwaYA22YC+NgL5gEh8AGcBJMhdNgQ1gGs+As2AjOh03gYnVfrv6qYQt4K2wFt8Js+CQ8Cj4P28Lfw3bwb+r+BcyFCc73HUyFnWA27AJ7wK5wAOwNT4U5cCxsDaepe6mGr1D7XLUvgH3gMngCvB72hXfBE/W+VVs6
*/