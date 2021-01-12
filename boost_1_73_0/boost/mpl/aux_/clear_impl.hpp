
#ifndef BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct clear_impl
{
    template< typename Sequence > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, clear_impl)

}}

#endif // BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
IJT9gL8RQglzCcmEa4THhKI8lOhO8CaYCXGEZMI1Qj4eVKxF8CGEEiYSXvwcSgbPoPwvPn9S+9/zDMru2lnPoWQNWUPWkDVkDVlD1pA1ZA1ZQ9aQNWQN/39DLsLA/1D/f/y3vvvf/r7DvlgOO6OzM20M/XNkc3xPvV+g7d3/Lpnod5jRexp176OUPm43S2jfvHts6K9LH7c/fJ/gYyyJq7A0eTS/p+UxwmwKV9+jn4nvE5Ri
*/