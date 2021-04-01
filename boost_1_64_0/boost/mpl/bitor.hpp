
#ifndef BOOST_MPL_BITOR_HPP_INCLUDED
#define BOOST_MPL_BITOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2009
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// agurt, 23/jan/10: workaround a conflict with <iso646.h> header's 
// macros, see http://tinyurl.com/ycwdxco; 'defined(bitor)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'bitor' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitor)
#   pragma push_macro("bitor")
#   undef bitor
#   define bitor(x)
#endif
#endif
#endif

#define AUX778076_OP_NAME   bitor_
#define AUX778076_OP_PREFIX bitor
#define AUX778076_OP_TOKEN  |
#include <boost/mpl/aux_/arithmetic_op.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitor)
#   pragma pop_macro("bitor")
#endif
#endif
#endif

#endif // BOOST_MPL_BITOR_HPP_INCLUDED

/* bitor.hpp
rdNbbi2R+WjBBQ7DFxGyU3+PS8BypX8izTtO0H02NQkdGhNqIRkueSlFWRoQieO+2p5kfmmVQLnB8W53gDuBo+YgyuqvPSdNJECu1kdWyTnqRHegzymaEBh8d9Lx6Ph+ScKva7Qyv4kir4I5C09qwoyKeZ05JMw7GEXWLDGc2FGJT+LBVi3gZXs04w3H4yhQU/ToEeSsDr0eo95ESf8XLn5zLKZ8hYvub6EqDUdiAt/0/Nd8hLZrXBYbsmhLwS0IHyiwdGlx2gX1nx+VgzBQ0fI5S1SKnCCt/DNb6EgupUWD3L9VCPBfnpRwx6XhsSh17lN0T8IikcBZqp5fbs9K+LQvTMoOxNQ42i7gu1Tx8zvWzCwm1bzSrT7cXEsPQR0hqHJLMJ2pxBgzvzypstXZgFAGFwBjwu8Gt2P8hW6JJRfU5dNLptOVXKTTVNXxYNoTIqoQGtPiB5ZecC0IU3M2a8dpkiCghYDwkGD8D1UxHG0ZMfEg+gDvNnKcV+RyGC9G0ZGZfGeGhs96b2vlhnAiCwddP79iGsOBgTM5/ffVtdo3KwmVfgYGuJnRpw==
*/