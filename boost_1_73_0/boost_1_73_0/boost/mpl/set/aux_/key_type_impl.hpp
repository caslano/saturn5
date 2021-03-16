
#ifndef BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct key_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
U6KQsgH3oGi2wPlrl4yBsCrPZaCb05ncXGY6X8ikjaWG7GXRuTiBPqasYWAF4hslIx6HJsbgQktSDMQgr1eJ8saclCrlug2DisnnViMlNNiCEdxO8fF1Pr4YO5YIRONJqshPwcuEUxaMn+nyRoIEsctC1lovQnl3v85HR8DWdFSPo6NL2J5Gx+uVR4cy0/wbZjHxGGUx6AkdVTxBWT/8ogU7sp+nTsizqSKPHLMYlo5ZF5SWtHNllegiaonhOwI=
*/