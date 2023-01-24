
#ifndef BOOST_MPL_SET_SET0_C_HPP_INCLUDED
#define BOOST_MPL_SET_SET0_C_HPP_INCLUDED

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

#include <boost/mpl/set/set0.hpp>
#include <boost/mpl/integral_c.hpp>

namespace boost { namespace mpl {

template< typename T > struct set0_c
    : set0<>
{
    typedef set0_c type;
    typedef T value_type;
};

}}

#endif // BOOST_MPL_SET_SET0_C_HPP_INCLUDED

/* set0_c.hpp
xM09/LrVZw8h19h+uXY5Sn6Wlf1dmy0Z4Wme47VJjm0QfU+1kUYsoVmbgdl0iUR3+9mb79idEpA/sSJXzPkXd37CMqglvaIQmvWYG8vm7QLWb3aoGjaulKx/Vw02mYthmvf7OmkGYqWLN1W8SNguqilHPxVVasEGR2cNujikZl1GcZledSXGpQENsMQsh+Z5lTDLRFWEUEaHMTuZHKDpw9XJxK6cCkjxZj9v6Uy1bpbijhZlOufNo336tVlJhXjfq+uad6Z9zXKQG9vBOlmg0UnejlpI2C2JW2KZjCRPSJNMgHjZS5955QRicL0uGq5X6V6dRsNSMhF5Ge5A6juD8iOQqyZPYtCOJ34SFhlXAGQsuA01ZZ6j5D+i4v1Wm0jGj5+xpX98pa22ItCeTbgIcWOZvJzp2m3mm9prfy0diZEdgTX5EfmN4FTGYaqowvyJo+Nqt1B7Ww/bm5XZlfnmMpYZj3ZTHfPF0zW/G0GhE1s7zIhVssNDn1RenBKJyYaOCQsHzCOrMe+xD+nZd0Ph4Q9DsVjX17FMq2KqgDf3MjsDiSOS3f3N941+hubuIRPv5M74NHOpjjwoyWFWwWaYJK+VhGYSrCo33s+7xEpJ5DjL+PV9X5NID1EXWyPJqT+EFqnO4JsJXLvlQSaOavnS3VE1Qi2riQv3xnOXt9/YlF17P2SvW0ENLI1BBNT1Y4H1wfClzZMjHiWA1Rei
*/