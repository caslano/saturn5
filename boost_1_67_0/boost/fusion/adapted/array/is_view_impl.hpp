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
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
*/