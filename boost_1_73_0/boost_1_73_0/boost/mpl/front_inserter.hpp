
#ifndef BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED
#define BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/inserter.hpp>

namespace boost { namespace mpl {

template<
      typename Sequence
    >
struct front_inserter
    : inserter< Sequence,push_front<> >
{
};

}}

#endif // BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED

/* front_inserter.hpp
6ZvtE7Zw0awfVv/FExYyzDCO+Npvvaz9LgCJcS+UJyaVTkwqnZhUOjEizIHfYYc+ws9EIx7sH/Ty3AoNL+YUHq/TxmFt8oRVV4P4gogviKgQBMYhiVSDOE3EaSJmCKKrw7pK4jKD+JKIL4mY02IcXxHxFRH1LRJfE/E1EdEWU/UNEd8QcX2LcXxLxLdExATRxWFdJNHfIM4QcYaIm1uM4ywRZ4lY12I+mEcRQkPi9hYJhwiHiI0tEh4iPET8usU=
*/