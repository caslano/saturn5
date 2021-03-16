
#ifndef BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED

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

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct has_push_back_impl;

template<>
struct has_push_back_impl< aux::list_tag >
{
    template< typename Seq > struct apply
        : false_
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
7qtmpSs2SlfsmUOr4vDiHiIcXodT74no7mDwRGteYyOTqMFYrjuysTR4YvortL2tLJlfPpd0GyoXF3C/8alTfDKOz0esFmoMxiLBgPgZAbA7UBmMNPgDwVhRU9RdFy1rbiTrFigO1ofCwRhbnDHYG2LfAW92kbGIlEyHg8TmumB4ebChKRKs0ymJ4bJiLtzpU1ayQ5lK0Vwm4qtevPtZNLekmk0kTL6vB5uvPZQ/Fp6sCapc0R06QNTdPGXYDSE=
*/