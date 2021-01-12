
#ifndef BOOST_MPL_BACK_INSERTER_HPP_INCLUDED
#define BOOST_MPL_BACK_INSERTER_HPP_INCLUDED

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

#include <boost/mpl/push_back.hpp>
#include <boost/mpl/inserter.hpp>

namespace boost {
namespace mpl {

template<
      typename Sequence
    >
struct back_inserter
    : inserter< Sequence,push_back<> >
{
};

}}

#endif // BOOST_MPL_BACK_INSERTER_HPP_INCLUDED

/* back_inserter.hpp
q9mfbPFJyWmJ2d7kzd1HIFfXR8CV5hjRNdd1jGinPrvPcR4g5wy85zBle+FWJW1LtGU4cu64p26c3FM3zU/6n0p/VP3zTJbexHN1cBnejsuxKa7Au3AVRuNajMN1aMICtOPTOAkLcTluxI24CXfjZtyLW1CemyZ9QSmLwXPTOjJfFbwXa2IkBmNnvBOjJF9dsA1GYxfsjvdjD4zBnhiPvTEJ+8j6K5WTvp/SJzQYGxKXZP07
*/