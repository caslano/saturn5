
#ifndef BOOST_MPL_REVERSE_HPP_INCLUDED
#define BOOST_MPL_REVERSE_HPP_INCLUDED

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

#include <boost/mpl/copy.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Inserter)
    >
struct reverse
    : reverse_copy<
          Sequence
        , Inserter
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, reverse)

}}

#endif // BOOST_MPL_REVERSE_HPP_INCLUDED

/* reverse.hpp
xEPh28Q7hWLi2KJHVBxHJ0+ITyn0i21r/Fwc7dvcOpWw/6PLTiSuE3rk31+LeuTP7wdy/z1fu5SLQmQyQjttY4RDIvmdJy2RYzD5ANoI/LVlu5HxULZDHVjuPsltI9J8YZoZM6fVCPmiZYjUjPTc7/1z8y+00ePYO9SyS0pHxiOpiIs0F5YzfWnu9ImmZ9Y/vRLqnyQ+nBOcIwp4b+E4t4a12J7HsCO7sTNPZReexpM5gqcw
*/