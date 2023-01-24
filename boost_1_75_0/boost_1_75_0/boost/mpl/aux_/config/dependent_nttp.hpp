
#ifndef BOOST_MPL_AUX_CONFIG_DEPENDENT_NTTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_DEPENDENT_NTTP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// GCC and EDG-based compilers incorrectly reject the following code:
//   template< typename T, T n > struct a;
//   template< typename T > struct b;
//   template< typename T, T n > struct b< a<T,n> > {};

#if    !defined(BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__EDG_VERSION__, BOOST_TESTED_AT(300)) \
        || BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302)) \
        )

#   define BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC

#endif

#endif // BOOST_MPL_AUX_CONFIG_DEPENDENT_NTTP_HPP_INCLUDED

/* dependent_nttp.hpp
G5c93PnkQbxrJugOP9LeQyQDukQXZhrjAgCfnw0nLk3IybCMsHLfguMAn+FIsHOWDTDYUQT/Xm8yYkf/NqDq2I3GEEEfY0fRqzU+zBrFKXPYxZQWyo+kg+hIJbgPQYAgQRDdTJG/Cn9FvrDcYO2R2ZDZssu0rj+yewM1CFLusdzgM31Tg3+gwxNGxKY+eOm+1YU5bWxKWENKhIAa9HE+3FHfY9z25YWXnENmQnLw8mfrOvE32Yl4C6nsXsnvnNwHUtsg9+Hom/aFdCtBdw/RAFRyn56tjJAqbss2462up/NG1I78bzaYWF5rOfv6Q9s5xADzHJi3Ul9Uu+X62lngof6taU8dJr/T4rfB6aeDdLPMJgjkFGtQNgFH6mHLD/nBfth5wh/shOfn8eN7SDj/K5xPkO8Kn5/mdNYROaLTpzlvstO4daqhm2hTRZ7Dtwkf6iTa+h5WP45F/Wh1F04lvXam/HgdihO3JxoSvuYok/LDK8gsQpkfddKD+NZ0lYjnvO4P4x5BRsxPyrTdd2FzPlPuq78SDhpRgdOOw5Ex0jGhRAwHi8e0BZZx045XwcbH7ykZhvCLEMeiyF07nMZc0VSImyyOUsmvo39Oi9rvtqzQV/S22H0dYxC53OYEX2117FBYdQw5yWLmf/AMewtWY4r6DCAjjdeO4j1/ixLcvgxougOuL0GhEILlpWkIzsHSNKGt40qjmaysh6JH
*/