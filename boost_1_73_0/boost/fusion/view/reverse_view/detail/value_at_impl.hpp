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
fn15eh+0tbrC7PdpN+VyUpQvqQLftq05VT49RquMLK4sbKhAARQa/QWqAn8wOac7cnBetnQQmnghclR+Ci1n7g3SjrIU8foBrNw/rsqlGuIGSrMbmtEf4C4pGgU9TFnUGhTJfJFP5vKc+gFxhOxBT/GR5ZW1phdscri+Cudtf3r/oZXFE6g3putXC12n6gFYrwjbsqEsGCm6BZuvZ0GoBKajb3A5vq3iXl2vSEIrmpur0Acr
*/