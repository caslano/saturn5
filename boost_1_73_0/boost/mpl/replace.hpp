
#ifndef BOOST_MPL_REPLACE_HPP_INCLUDED
#define BOOST_MPL_REPLACE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
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

#include <boost/mpl/replace_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename OldType
    , typename NewType
    , typename Inserter 
    >
struct replace_impl
    : replace_if_impl< Sequence, same_as<OldType>, NewType, Inserter >
{
};

template<
      typename Sequence
    , typename OldType
    , typename NewType
    , typename Inserter 
    >
struct reverse_replace_impl
    : reverse_replace_if_impl< Sequence, same_as<OldType>, NewType, Inserter >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, replace)

}}

#endif // BOOST_MPL_REPLACE_HPP_INCLUDED

/* replace.hpp
cpWEVWG57mH+HqzLnmzM3mzNPuzAvuzBfuzPARzBgRzP07iIQ3gLh3I5z+AqjuA6nslNHMlnOIqbOZrbOY4fcCI/ZOoB9DdwRub94og7Ttt3d2qzxwpfPK1C+Z6XJP/33y/+v/U38JodsMs9ZPFJ0f0N/OveG4j1PxB7HyA2xIbYEBtiQ2yIDbHh1w5FhVG/1f3/+PiEf+a9f8dwLz2MtYLfVHZ9d0ruvXT3Uzt1iUuekJwe
*/