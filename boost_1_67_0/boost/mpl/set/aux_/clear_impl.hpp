
#ifndef BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef set0<> type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
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
*/