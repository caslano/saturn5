/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
Function-templates for discrete Datatypes like int, unsigned or
    any class that provides a ++ operator c.f. iterators
-----------------------------------------------------------------------------*/

#ifndef BOOST_ICL_TO_STRING_HPP_JOFA_000712
#define BOOST_ICL_TO_STRING_HPP_JOFA_000712

#include <stdio.h>
#include <string>
#include <sstream>

namespace boost{ namespace icl
{    

/// Static class template for the string representation of values
template <class Type>
struct to_string
{
    /** Converts all values of types to std::string that implement an operator << */
    static std::string apply(const Type& value)
    {
        std::stringstream repr;
        repr << value;
        return repr.str();
    }
};

}} // namespace boost icl

#endif



/* to_string.hpp
iuzpdGFsCcAYmueOQd01SO9D+iQAx/Um42lxAE9LAryjJTCfLw3M58sC8znN8e1e29c6cXzaC877PMZaDsJYgtQLaQDSCKRzkN6DdAXS55CuQ/rhYLg/Y2OL+XOIt5lyMvO2a85YQxxfDvA2czyx3P2lw3di7UdegnJkJ8wlGyH1Q/ryxXi7UmNyL1epxjrX+Q3woB8MPhSid9HgmHTbNwVteAfSZUifBtqDe/JjtlnUK7/L9FB/r7JrTzDn5l5h2luOSXuLmx+USdE3xPlNG8tUZmedhTwo8/vlm3aVqcy+egn14pdDNiLTfjKc2VVNG9GIZTP5RNpMlqn+YZgbsWkMWDYW7auPND/1si/ryBhIL+tyLr3McJo2mc+kTWZZohwTb1jmFy9re8g3L+s9HFz+Osu2Y+7lKWYTuHaYiHsdpAFIlZdJ/0cdfxi+fwzph5epRKQ91OVRbkP+8K0gu6A8i20RrUcyvziXmbfTevpFIx/r6SZvYD3dvEfyzFKPh4gIv2A99IchrVu2qTaF+MXNGOuXoJKPIV2DdH3Ih+VDkfYZQznn62WGz7aI7y0f2JazLrfNjYeSWJfbZu/T2g1IfqyF4rRgQh7++RGATSWh2oEiP9LGtUXu3iTgB/s1XU8ts9dNzH21KHd+1sJrPYtsG+v+RdnYA2K3yrDfW2zbWvcv1mO/xT9HgN9LnT9wzoHZXac2Y2N9vtSu
*/