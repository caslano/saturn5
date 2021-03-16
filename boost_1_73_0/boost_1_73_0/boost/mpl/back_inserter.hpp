
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
bRmH0vj9pvH7fXYMoXgthnfYhvG6SwxXiwOXFZyG0ZZeDP/L2rmAV1VdeXzfc28eBDSIAQMEvMjFLxRE1FQJjxow2osyEosPdNQkJMFE8riSe/miE5iDCWPC9ZHPR0srasaqwzjqoFiLj/ELA5b4GIeW6mjns1IdW9Pb1rZfWxlrYf5rrb33OfcRUaeXL/zOWWefvfd57cfaa68d64h9kfaE/Tgm6o/jORbYBc5y36LP+kAC9gMJ8Mew3coGrew=
*/