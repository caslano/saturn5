
#ifndef BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::list_tag >
{
    template< typename List > struct apply
        : not_<typename List::size>
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

/* empty.hpp
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
*/