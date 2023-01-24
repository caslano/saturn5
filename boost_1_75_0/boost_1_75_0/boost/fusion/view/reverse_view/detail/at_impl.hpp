/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct at_impl;

    template <>
    struct at_impl<reverse_view_tag>
    {
        template <typename Seq, typename N>
        struct apply
        {
            typedef mpl::minus<typename Seq::size, mpl::int_<1>, N> real_n;

            typedef typename
                result_of::at<typename Seq::seq_type, real_n>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return fusion::at<real_n>(seq.seq);
            }
        };
    };
}}}

#endif

/* at_impl.hpp
EwXcsN+jpyH8OkBwpC2U3+ok9DIbg7Lpa9Pq3bjdFr76l7Q0mSTtsiTzTF/RxnehL/o80UIPBSUOFLw0ADUywyl4YS8KzVcWzJ92MmZ3KYe4G9i3jfqgaiKbjAhbiX4nhxcbF5vm/8Wum/m+eAxNWq1dJhkhxmsRD8MbJSgjlzlC9I4C5PfVHm1xDlGER5ecj/zzfyKzf6EgkbbSZgxPG30/TGOV2IqoXA+oHhfmGKv5dRdbQ5ybNLcm6PtZ6Kd/5qiLe8FXfDeGGyofnUiBZedd/rP2rpsWkaGcPhRUdlWtmAlQSadjZPYj3ECQeet95I3x4qFinWbQ8A+wBjqP/fhOxBkbUDDS6kS4VP8PN3esedAwnbZicG2VIeOzoJI5xC3v73mU+0Qx+zJT/0w6jAOrB84zigKlUBUvO2xLckhOqyldJSd/IbPXsk9xH2V+fH9F4yhfCZCWHyvjcs/9MmLScF0V3HRQ+0qUIX53r85VmlQ8vV2pcYjjLIAB0R8dzM8gjK8yXNxithsoncJypS22J1xP2ed/FJER75508+eszRLzfmzloTbFuc/lP1Kf5um9dZSOD0S3bp/+rR/N1Pv0MVZDq+oQYtkzYK7D6oxNPOURwz7BYHq58hB5LjbJak+o8DZB9byFmjj38dFyNbnEIj1XlRMGZT5ybud25JzGHTI7/3AAFxLAn17mF2BSD/npJ0LNPn53WSvb
*/