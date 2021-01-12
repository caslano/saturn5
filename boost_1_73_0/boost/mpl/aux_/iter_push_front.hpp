
#ifndef BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/deref.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename Sequence
    , typename Iterator
    >
struct iter_push_front
{
    typedef typename push_front<
          Sequence
        , typename deref<Iterator>::type
        >::type type;
};

}}}

#endif // BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED

/* iter_push_front.hpp
MTbBJ/gWPsXe+Awn42+4EHMp78rGPHgR88pxvXU2eT4QTVKeuQnUQQb2s2yUBy7FmrgMe+By7Isr8B7GEq7JfEbK+a4wwUKwfzOqIHZEZ+yEzfBtHIjeOBU74xbsguewK/6OPvJNp27oje/ge9gdh6CvXDcwrTznpz3/V4KwmsBg/RaHC/4Nq+NKbIir0A9X40xcgzmZSQLWxvX4Fv4du+AG7IWJOBA3YihuxmG4Fd/HT3AN
*/