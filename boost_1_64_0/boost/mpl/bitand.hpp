
#ifndef BOOST_MPL_BITAND_HPP_INCLUDED
#define BOOST_MPL_BITAND_HPP_INCLUDED

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
// macros, see http://tinyurl.com/ycwdxco; 'defined(bitand)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'bitand' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitand)
#   pragma push_macro("bitand")
#   undef bitand
#   define bitand(x)
#endif
#endif
#endif

#define AUX778076_OP_NAME   bitand_
#define AUX778076_OP_PREFIX bitand
#define AUX778076_OP_TOKEN  &
#include <boost/mpl/aux_/arithmetic_op.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitand)
#   pragma pop_macro("bitand")
#endif
#endif
#endif

#endif // BOOST_MPL_BITAND_HPP_INCLUDED

/* bitand.hpp
3U4PztYUrcxWM/XU4zbLwkUVion80rbDzS5sRSMi4eJtHLa7S+ggIlimJVN2EvMz2pG/uKXwsPZqp59M5UPCRR1RvQc7yjm41FXCMpMNSGJ9gb2l4Cew1BgWDmU5eS1qXWkbeOBAkRQ23JVkV5DxMSfFRMT74/uvkhrEA7r4ew0hEQp5qpV5aZcTsEZrQlPPeAfgEY2BbtLrXsyc0NTShsFukxr1JZBdV8CuWxBxot5ElBbEMJmyJQJl+UYnYZi9xVfjiIj72o3hAzPTpCipokpU14Q/cKM372wVpBgNRWR1ywfdXiZxExZ8+h1CoGIWZsAz799NurfgddbEWnNFez6+M9rT42JESYaZsCRWSNqq6H2ZmkAWlZL1ax191ByJFonP4NbREGhbtzGNRH44xqvlRLl91oSCf4ngZIuJ0EruVWiIdFVsiXHQPBOcVZ3SdyFrLW4qQsKHcBD9yedI2tjX7utuzpVLJT9SjlC17+pGbuHjjyB20eDZGkgI0OaKhpdOgD6iuZVZCcdNyoi5OjfO1J+0oSmVW7cKiYJdtgI8jgONXNatGxO2gQ==
*/