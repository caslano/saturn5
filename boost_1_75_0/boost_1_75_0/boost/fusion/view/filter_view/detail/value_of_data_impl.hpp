/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
XFoTFM7ZAQyhV4c2mNJVANB+kTgWfHObNn5CpveAhQY0z/0RLq35VZNdFuxvQifjiTb6a8jSYS5HuQ55hb0zzuQuByQnpyHpvafHt2+vRZ4y9mTbJG5p6IfJVW69V1VafzB0g/1pm6u5qdj6ghrLOvvOZfitaE99ntLangtVUuXJcYjBfn1y72kPLVtkn2tKfa1K1xBUoALClp3cc5rEy1fOXreL9ktYZ6eUoz5KOCo9srkpZqYsosvuGrv1VK+PpiR9j9A4uZ/nCdjMtrW6wfQdUNp+38H3Zb+EqGPVejaMxclI6yzOTo9OI5uyK7e6gzuNatS+8j28/T3JyeFvADQsy9PHST60e55mqhxeE7P/zppmIV4ROVF0TqRlJ3XRSa9vomlMhk39YTJsXx+f2hfRfrHKL7rz+Ag2jksj2sjknCLW2GtFofJk8ZTxdaoGdPYMT/zFPq96Vjg0P/xM57yljsU26xBLf9D3lOVFdrfOzKeAnKYbL4/ad7cmXPbxfWLzIiVZbLt/Tgm/vzKys22SqmPNnFQdzgqX8pRwWU3JJM/Pikj6Qk54HhcZQc6ZEd1NXY0wz71NnpyPVb8F9M/46pakUPWafBa99Pqcafo7M+efuZFyrwzLkALaeLWht6+JWx+pw3htpOyTtYnVEzu+LkrerYno0yuQeQsjs+QLoLzjJk6UrovQ47lR5oax66vOuo5L4OhzKdG1
*/