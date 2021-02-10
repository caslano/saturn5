
#ifndef BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED
#define BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    ||  ( BOOST_WORKAROUND(__EDG_VERSION__, <= 245) \
        && !(defined(__STD_STRICT_ANSI) \
            || defined(__STD_STRICT_ANSI_ERRORS)) )

#   define BOOST_MPL_AUX_PTR_TO_REF(X) \
    *BOOST_MPL_AUX_STATIC_CAST(X*, 0) \
/**/

#else

#   define BOOST_MPL_AUX_PTR_TO_REF(X) \
    aux::ptr_to_ref(BOOST_MPL_AUX_STATIC_CAST(X*, 0)) \
/**/

#endif


namespace boost { namespace mpl { namespace aux {

template< typename T > static T const& ptr_to_ref(T*);

}}}

#endif // BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED

/* ptr_to_ref.hpp
ISgbRIWkgSzcn9ioP3E9i1v2uj5t9vI8BIDp58/hImQtJp8Zex4S5t/cL6SaZDQCUuJIpnn+lJlVaaZPWZSajZbOiylJQD71RtEJwrkYoo4D/JRY0xnOVaCFPyq/7ADDnjIMbnZx4A5miIGBjAFlkZtHjG2H+hj76EPoEPqBUx+ivpEyQonJMgnBQ5FZKQGmwHw+wMwApWn0zIMEp60m+/m0zLJpliWVZ/Pv6YBpp5kmHoPwL/wXBv2uLYiWg5Km3cF6wI47LWtrvYUB2eli4ShHN8BSW8NrZjoEPKnb3wumrvzqdLLlqfI1NZKL//T0Uv3R/tbE5Zty32hO69Mc5ekP069g/Tan1zRbENvN/Kz+ozaQWp4ptQRT7M7upO6sX3IeTOn2dxEQ3zwHu7FgdzmofOWL46tKoaXdXsiN0Ko3+9mxfUEuc91ptd2Q87Q4q5h/lzu1790h7VUmV2IoXl6Jje7YEm8e7/1X50B68xzsxoJjngfym+dgNxYccw6UN8/Bbiw4vrWIvevn72eVX7y0+eU/PvwLUEsDBAoAAAAIAC1nSlJbna64zAMAAJMJAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjAzMlVUBQABtkgkYMVWbW/iOBD+bon/MO2q
*/