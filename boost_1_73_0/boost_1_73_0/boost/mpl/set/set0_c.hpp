
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
yYt0jxtkDUZZbJMT+chzFt6CuM7cgSaNN5++1AK8p9B3ndADxzAsCH5+BiORFSlXPMbkZ+Q0ZorZZFyKbAAZf5Ai47sNL3mLhGIAa/bOH3JxRFpkJeJ9FTWtRQD2YltKkEke4XKKC1Q/0FH96KM26KYJz9XRYFRPGoc2STJWNJpsAjRnGT9UGF1v1QasjgFfzgrwFRjCyJJETCUih12Cu5I8UQlLoeSyELnkyKQfqICi+YzlaPeqyjbQ9fYkWIb+fNCu0syDRajfdW/0bzPHn/pPj97voXkF2ha2qAo0TVT5LG3FWYnzbPznvjO6XWvdjvnj7wy1N/T4ebRXG//Fy2S9h6omwNYKz6JsqO4VbJiEFec5XMiNUBeEftR7kaIohRKRSLHxhmFC1ewRqgpfWqRu7KeunlUF2qte9zW/ZsNK9XXbMDdCqqFp9TsGPiYChSjVsLGMQOVrOPqvLVzF9w0523XiG1h6U88NAQtVA10Ye6E7ARNGwePL61sN3sI0+B48h9VVOBmheuNOP/1V/wBQSwMECgAAAAgALWdKUvwT2lUuAgAA1AMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4NDRVVAUAAbZIJGC1U21vmzAQ/m4p/+GUKuqmlfCiLGk7
*/