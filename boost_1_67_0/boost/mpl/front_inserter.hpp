
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
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
*/