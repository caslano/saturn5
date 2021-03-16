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
ZMAakLgBqz7ey6FXQVpg9Y9+p/QmaTJqSv1pKuAcxxjU+DddAmo3/OV1YQOY+xgNZJjmsIMr+kYNZeW9mHsXzt/rzPu1YoT98l6My6CsZvRh49mZZxb+IHucN5QrrwENex6LDWjUtDMzw8osVnI/FPVdmG1Fs8f+EycXWPsnOvw8m73ni23eN6UEcCjgfJvD7WG8oXB76L0p3H6RzVF4SwDHAYIeS3skLUXbFGCFzTa2SkCcwoZs3qVuuc1h+NA=
*/