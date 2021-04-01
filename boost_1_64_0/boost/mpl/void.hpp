
#ifndef BOOST_MPL_VOID_HPP_INCLUDED
#define BOOST_MPL_VOID_HPP_INCLUDED

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

#include <boost/mpl/void_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

//  [JDG Feb-4-2003] made void_ a complete type to allow it to be
//  instantiated so that it can be passed in as an object that can be
//  used to select an overloaded function. Possible use includes signaling
//  a zero arity functor evaluation call.
struct void_ { typedef void_ type; };

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

namespace boost { namespace mpl {

template< typename T >
struct is_void_
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_void_<void_>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template< typename T >
struct is_not_void_
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template<>
struct is_not_void_<void_>
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

BOOST_MPL_AUX_NA_SPEC(1, is_void_)
BOOST_MPL_AUX_NA_SPEC(1, is_not_void_)

}}

#endif // BOOST_MPL_VOID_HPP_INCLUDED

/* void.hpp
EkeQcWhPRhz3HvLQrFiYBBfCUpHc5mmJOAj+4jQgzwUKsBTgmY7t46LZbHDVPNOZTFU0N6MUzLiS3gX87f5tknfGTSY24UEnWzjY3tVAhlJEL28Rbzl6ap+IJDHWHCr/6gWHBTswPkwHhFaHWrpJ/Hip3kG/JKo5PR5DKqf1msSNHKqDTA5pEtA2zCgiIM9yxBcCziLtEQblqnVuoKaL1vo5NUkT6ciq9xK1wEZY9jZqM1PG+JxSLVcS6bovb2Lg8U1tNP+ar8WDDAToOkwdyXbpoo1tMZbiDUIhRc0lH5M518vZW54S1MbnrXkwulzGTXFOUxYYsGs/j7fEjKeXLO6MG1cDoMqDpT+kzaAY9a0ScvywaAOivNicHNmjPFIgddakeibXAZiNByhcB/OYl4y2Y0+EDsFhdcIkU7EydRXkaB+GKZTMJIuDpYLXvTtFt6T7Bdwhfjd6nLEdVGZ+4d4MEDvrkMAGaTFBSvDiu+ql4KgMBCu7Cn3UwnXMkchAEXwUwRAOccZEpXw7dfEWDHyaRZ61+ovmegE28JijvN+/LtN0P2CQe8H36w==
*/