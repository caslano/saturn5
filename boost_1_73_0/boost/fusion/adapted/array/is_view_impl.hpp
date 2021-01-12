/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::false_
        {};
    };
}}}

#endif

/* is_view_impl.hpp
RcyWk+a6Z5w6SfIbcdfP5xGn6qdt5l+O5p5GZRy8TeNxX1LO3yv+Ua/XebCPxJmfNObabcFAtiW/5nqRZsg92Nnb1XXPlfkDxw0+7rh8eYrdbUHzaHvlG/XDjn9+TL/cPjnf2Gp4CO+IWm05c93az8FWndy720fY4BvQacs16xa7l7Jy+ohqteUKUHuGH3ee5YnZD6W3nH/CF+HvEO88btq5+WK3ldXE8km9OpxNfuPEnHTS
*/