
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
CU40ekvGYpqsh1r1RcuBzOB37V8+FhLyAXrtFdAmB9jpNvHtnAuibVgtrgM+jp0+SQnq0lzOPLSlcHZS3ZBwV3t1RimZfl2HhE2UIln/xRrpBGnsL8r6uDajveatYUY4f/Zl9nNE6yIlX7W6lRNzKPW6I+lglGuLj199+LVPk7eA1ALqnceS3jZ5rx30XCEVohCM7vKTvylR0LGMkjJdWBVlhLI+EMm/PpoPeQXw9iHNiaQ+tBGu/ZeECdOmZX9T3iqLm6WPf9wwa4/VflljWOMyG0XTiM1DSx9z50N3J1hBbsep50ffyEJFfrOB7s0tZR40zroWw36uYvi4HicKMBFQVYwhEblFfu3esmTo8bu8+EBN86S0S/UDKn5O/8S6xzNywdTz/kmp5PuIMxNLOsxz2+L6ZYSBoSdrbXzXK41SMdDkZ4zca2Q6jMotbMSZazgdxnYTwNBjpLlmYOz6bJ3QcPpMQT+mFKKq4+0lqUNQbfYDdt7fU+WAI1n4mr/hJNX5xmzd4hZ1AC6CumiZUt3mdf9Hd6AcpGex3CqX8vxW5q3RlwpSZrnhnicHDPfMLVlvUEnngJWJrlVOZd6JtTTsE+12QmKjCqijrAeolhbrN4tpLaoicOLTrwchmnw+DXPLax7ozuq0t+t5Rtm5ufT2xsWBK6cubCXVBT0tawxT9VyOI0NhdztQwTvBXEkRWPO4x4z72q+qHBwl
*/