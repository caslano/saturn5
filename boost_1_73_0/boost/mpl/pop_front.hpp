
#ifndef BOOST_MPL_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_POP_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/pop_front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct pop_front
    : pop_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,pop_front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, pop_front)

}}

#endif // BOOST_MPL_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
cR5n/n5jcs91aWMzRjvCQnaHsnUA5b+g66R+FfNcX4Z0HG++7HvJtJ+559orfUMqZZWFq7L3R8hP61WuEpPSwu/UUuODzHuumV4I81YOZa5RRev1W5l50xPyc0/OPajxUI+VUTRzvsz1bbZMP+tb49/PGJu7vvdD/VPalPjUOD+sUb91Od/ZfB6+s2lRKNRThvNOd6FI+Dvsh1lFWZXVeHh2u7iFQ11jqHusynbCllDudxXW
*/