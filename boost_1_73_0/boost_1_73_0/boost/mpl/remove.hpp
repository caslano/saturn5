
#ifndef BOOST_MPL_REMOVE_HPP_INCLUDED
#define BOOST_MPL_REMOVE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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

#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct remove_impl
    : remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct reverse_remove_impl
    : reverse_remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, remove)

}}

#endif // BOOST_MPL_REMOVE_HPP_INCLUDED

/* remove.hpp
ZOdS28ic2O9oyM5K5AQwxhsVGRDZy9U1VJggJGM8olxuaK+KZvJs9/hAFF9x2KuwbZaVq3VDOlw6inpb+2K/mxrMoODKZmXHpWSm+BN/ULg2/uhdSsRSR7U3s4U+W/dz/euBJQk7rZl0jYnzaAPxRDbii3RFWKjcz3TYDlQI5Qrsu2EYvXsr+eIwhu0rJj2kgdyx4RfW2XuC4h3LZvBE9nLyfZNptAFCz4OPdIzebd7MEMsptv2FzKDcom2v+EM=
*/