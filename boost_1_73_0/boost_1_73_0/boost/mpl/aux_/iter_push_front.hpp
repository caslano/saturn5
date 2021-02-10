
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
MAkW3ldksDkmOUpfk8dJwKns6piI3Q0knN2uyFCYVBbw+9Vlk/8hSO+xrDz8ptUz/FUT7ZSynBfY3ANbw8U38iPWjpLUlKXU2YacUJuOqX1V+0P6Ujot6gyp+J1OuQnJjkZC7N3cT0VhHgTXlvnuljvErdcJkbBG+MoallYRTk3M5sZi0x2wAWJr7YiMDdpx+J8xCFLy4bksgLhzDfCo2wsBdWoypR/GYe3zzmn4gdS2obeqR6xKxtqNQ64CZbNcLre+0XaNfRAh0804mHf4HlFmlrowMmNUMBEZPgldFwUbkTKFUrlKJXPaSCBZSLcAT508Dt1CxseDcJKeZL2jDOc47KUyHvaHcdw7QjmMo+xkMOxHuRyeDvq9ND+an/T7eSyjQTqcH5/2B8co56dxItjpOqL4V8hk050OSvmcbqeLko7CFlRtixYT8xBCZTGnNtcpSYa9cNKys/fl+m52cTPa466/ub6dCU47EWTeRt/GargSTBbTJ1r+ErEhl7/XtwnNrm82zCSokIDs3d2eTS9uRaHmXG9Bs4fPynnXrQpgzhuu+WMz4vB9Jcj5C6/Uh+3QNeP4jRlaQbPbZO7R0qS3zUc8UjNSR1JtjA+DdQF5EzLW6EXdnc9oPjhWuEklatXi12pobaMGpclI
*/