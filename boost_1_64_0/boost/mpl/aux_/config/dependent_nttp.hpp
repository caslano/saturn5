
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
f0BzpVIQQ2LpUdfAmcFvFrF7UPzQQmxyLu2jUR0VWZfdT/UXm8/S8n3eI+w9kwKJuUW6nls0DUuw74DyVesxr2aJ5LGIKZc8T8JZT/t6+JRGZPqY06c8k7fQfpzF0Sh44Zs467BzoR18h1xfRuA+SHpNkHvWEC8aXBeFSwUwPTXEf34iwQHPULqaW6LJ2cJVqziintBVkCetva/kjmsgyW5HD88QYcbW3ke92YEl0Tq8DJHc6PWihODwGAxG46uk5x2sXK8jxT09u6RQfwmsb2tWE8u/H1Zxfy9pjvqVLePORdSq6CgX6N0irqbgAAlIUhKw2l/bq6pmt/q3l2kfYLVZsUck4OCU+SJIup6TezKf3LcP+TDG1jnWXVX3wu5GCAqDNZ8MxdZIn0Saq7usQX/n3n+ZjNsemVzCEJ6NubRjKTEozC+5sAWjXjwJz/7JO0Uej64VqabY0DdBIpu9/zPluoeW3k9RBkcn81srh5HbUKQDyJEub7ueDzrToL97J28Vy+OONHUe6TuxCfppar5BdcdZX2UKKbcql1e8XnL+pyMHlFSvRz9YWg==
*/