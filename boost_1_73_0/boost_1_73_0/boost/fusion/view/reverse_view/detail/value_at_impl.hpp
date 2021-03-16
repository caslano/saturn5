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
pH+FJzqQDsuD3wKf00djF+o6D0udh6l+HxNsu2Cnc2DNFf/L2ZnAVVWtbfwFEZBzgAMcOCDgBIgjIqKo5YBjJgkiTqkBAioJgoCKWl2za+aQU5pDDumnN9PqWlmmNljXbHCs7GY2qN/1lpXezLTBvPXttfba73rXXnbA7/y6P/d9eP7Ps/fa6+y9zz5wjg8dFfZitIOXL6wplqNSy78tuqi8kp/IzW8gL7RdZ9BvJ7f/FoP8/pr7Gtf3D9LNLyM=
*/