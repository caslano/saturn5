
#ifndef BOOST_MPL_AUX_ARITY_HPP_INCLUDED
#define BOOST_MPL_AUX_ARITY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/dtp.hpp>

#if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)

#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl { namespace aux {

// agurt, 15/mar/02: it's possible to implement the template so that it will 
// "just work" and do not require any specialization, but not on the compilers
// that require the arity workaround in the first place
template< typename F, BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct arity
{
    BOOST_STATIC_CONSTANT(int, value = N);
};

}}}

#endif // BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif // BOOST_MPL_AUX_ARITY_HPP_INCLUDED

/* arity.hpp
O0Du0vvuf2zu7/KA89JWnx2kl0u2BikirgZubtBf5gqTBDMBcOSlUFSCI1cP+8p069zW8Lu4+mYhxrDEkOHceiTXbfyM09jPqHaOQ5REiI6D4/NZZYEbKQft8dysK+vvUiIvDaXxng1zmJ+yPcimyrOt+lO8ueimCGg7PN2g6p+8Bl61JzlH/Xo54cFwtaqbSYcDwkfecJtmOtnQ8OMQnGpLN4HpLQHZIOIhZs5U/iu3+avqaHtTg15Z5r7GilCs68Gw2xKziFldxThVpWcbld5KqRDWgzua+8a4Gfo1C6Sg1wWnMK8H13j5LZ7nIudR3wdYTd/EGq0FAJs3qu1ZCuihiVuG9AuGeDlD/SMGPGBYOftmJyqSNjKzQ8Ov33EaIMpLg+WSI8ILN1e4YKAdyyEoPpAkqDGLJDON8InvdFXOyZfd74Gb2fHlOZ/S2td09H2p0eJlV+iJNc/xUG546n7Ocwf+5aC39wMxnDcGpAuIsbCk4lFcy0S8voZ+Wp4OXkLMbf1mRx8NigVovfnRp6vgk48ruR0AhwdwJ91wEsSobBfTA1nJnnYnSg==
*/