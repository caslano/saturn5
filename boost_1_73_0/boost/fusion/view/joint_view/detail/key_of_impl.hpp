/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::first_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
QMAYtynI7OC0yRDm7QYjbjkR5XsV5XtTkBuv40+YfPFIEyr/u6iMOmyFaO+mfMxkHdt5T0tjYba8f3mdyZ+4icrIfr2ht9cpUbrva2UbRzvR3t/SjKOf0vxA17+lmVv6ByW9FWBkf8jQ9dESVp63mPzyHR5W/4Z3ZBAJ1f/YaByaD/Kh67/FUAie4X+HoXWC9Jj9fILyIqIyuI19o+AY2POIvu1TQo6OIGFt59OGbo6tGdpn
*/