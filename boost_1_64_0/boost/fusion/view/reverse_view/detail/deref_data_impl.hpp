/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::deref_data<typename It::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref_data(it.first);
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
2yITfvFtGFjwXBKM6Sqbx5PC3xBKyJmQYsf8fiT18wt9A2x0OUfxufr9mAxcg6Eq0Pte/e+dw6mw7BRpXVD0WQ1tiNAqvmw9x4vIZ5JBfJtEj1fK4MOzV6Nlp0mKs3QbGT0l3B3pjqVEgyDue2PH23IxW3LiW7oFVekA+9f3dn4SCOrkB4KjNHJW2UD7mrK/PBH/LxzOw4wshAn5GMYcc0Bi+oFGbv1kAllryqhyZqSqJhO/SvUFYS/xgUSTgpFWDNMdvfJHtEC+O9Wws0Gv01sYdwEg87T5hY24f0p2rIkU6JAhC6QmvExuYyX1i0N1j2Ktc3ZrZKQ6RCdyEVFQxur45f9rl4dtXaK9PGeZbqt38hR8DhVzY01CTWR8FmzAjL13hh3M8WvNM2H0xmw93nobL3FjGr1fUVlzbY2I0+XuDvrKiD6FpHgE3u45LKZU0va2vWvBwlJU09Aat8YqZbD4BcGMMo9p5vQHt/sTK5vSUP0D+p7FNFBHV5kz293lLDLF6YWE0zxUG7NMj1kDC8ugMQ+b5tY5sqigqeVHkdFpOBv18/lOpTclWg==
*/