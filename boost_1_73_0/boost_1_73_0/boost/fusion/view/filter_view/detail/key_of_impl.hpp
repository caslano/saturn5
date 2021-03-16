/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::first_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
6/aHhgVrQPCOvrrWRq3z0ujSjcfy1CkYSQUFlSiYVXaIGpFcTXubVjGaOg4frLjh+gkrblgBWHGbgDnREc70vBaiCo0N3lsRcLDAjgCr4+xoR+B1ikFVp994xz7U3tMBzFLjoID8nUBsPxl/4+/rnGuyi+FSeAyL0HC6PAhqRXqTWzKbqBWFcS03mCQ5t6kixFYZtxIRv2/JcPoWlA1ZZZr146GKvcB1J8rcPx9PsbhTSbVYIUi32F4esHigPwc=
*/