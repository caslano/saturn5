/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<reverse_view_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : result_of::value_at<
                typename Seq::seq_type
              , mpl::minus<typename Seq::size, mpl::int_<1>, N>
            >
        {};
    };
}}}

#endif

/* value_at_impl.hpp
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
*/