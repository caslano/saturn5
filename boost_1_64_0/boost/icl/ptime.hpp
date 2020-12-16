/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
itl_ptime provides adapter code for boost::posix_time::ptime.
It implements incrementation (++) decrementation (--) and a neutral element
w.r.t. addition (identity_element()).
------------------------------------------------------------------------------*/

#ifndef BOOST_ICL_PTIME_HPP_JOFA_080416
#define BOOST_ICL_PTIME_HPP_JOFA_080416

#include <boost/icl/detail/boost_config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4100) // boost/date_time/time.hpp(80) : warning C4100: 'as_offset' : unreferenced formal parameter
#pragma warning(disable:4127) // conditional expression is constant
#pragma warning(disable:4244) // 'argument' : conversion from 'int' to 'unsigned short', possible loss of data
#pragma warning(disable:4702) // boost\lexical_cast.hpp(1159) : warning C4702: unreachable code
#pragma warning(disable:4996) // Function call with parameters that may be unsafe - this call relies on the caller to check that the passed values are correct. To disable this warning, use -D_SCL_SECURE_NO_WARNINGS. See documentation on how to use Visual C++ 'Checked Iterators'
#endif                        

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/difference_type_of.hpp>
#include <boost/icl/type_traits/size_type_of.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>

namespace boost{namespace icl
{
    template<> struct is_discrete<boost::posix_time::ptime>
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<> 
    inline boost::posix_time::ptime identity_element<boost::posix_time::ptime>::value()
    { 
        return boost::posix_time::ptime(boost::posix_time::min_date_time); 
    }

    template<> 
    struct has_difference<boost::posix_time::ptime> 
    { 
        typedef has_difference type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };  

    template<> 
    struct difference_type_of<boost::posix_time::ptime> 
    { 
        typedef boost::posix_time::time_duration type; 
    };  

    template<> 
    struct size_type_of<boost::posix_time::ptime> 
    { 
        typedef boost::posix_time::time_duration type; 
    };  

    // ------------------------------------------------------------------------
    inline boost::posix_time::ptime operator ++(boost::posix_time::ptime& x)
    {
        return x += boost::posix_time::ptime::time_duration_type::unit();
    }

    inline boost::posix_time::ptime operator --(boost::posix_time::ptime& x)
    {
        return x -= boost::posix_time::ptime::time_duration_type::unit();
    }

    // ------------------------------------------------------------------------
    template<> struct is_discrete<boost::posix_time::time_duration>
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<> 
    struct has_difference<boost::posix_time::time_duration> 
    { 
        typedef has_difference type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };  

    template<> 
    struct size_type_of<boost::posix_time::time_duration> 
    { 
        typedef boost::posix_time::time_duration type; 
    };  

    inline boost::posix_time::time_duration operator ++(boost::posix_time::time_duration& x)
    {
        return x += boost::posix_time::ptime::time_duration_type::unit();
    }

    inline boost::posix_time::time_duration operator --(boost::posix_time::time_duration& x)
    {
        return x -= boost::posix_time::ptime::time_duration_type::unit();
    }
}} // namespace icl boost

#endif



/* ptime.hpp
l95uslAX6KyQnPY89RznIjPzp/DAH021RzM8d5/OdJNHszzq+srtVMly6d7OrF66WfEVC9bnNvG7Lmxr136EN+czOKGBp1HVAp1i9fx1D/t+2TQaOSlQWO3pKjI7d/yTQ9wzp9vnm/7v///7/3/O/ySYn/P9b55r/P/137FktBSMleWVjS0dHVz/8u/GZrZ3Te3//Ovgos2//7MLzJ1+f/fypz++uH//PvL390c///wzWl1dRRUVFYiDgwO1tLSgubk5NDs7i4KCgpCOjg4SEhJCy8vLiJCQEL18+RJJS0sjFhYWtLGxgWxsbFB8fDySl5dHVFRUKDc3FzExMaG1tTV07tw5pKqqilRUVBAdHR26e/cuiouLQ42NjSg4OBjV1tai0tJSFB0djTw9PdHKygpiYGBAHz58QFevXkV8fHzo8+fPyNjYGBkZGaH29nZ09uxZRE1NjfLy8tD09DQSFRVF7969Q0NDQ+jatWsInmyNJCQk0KdPnxAW/NZaT08PDQ8PI3V1daStrY1s4epSZWVlFBERgX7xi1+g1NRUuDGzBTo8PEQ9PT2orKwM8fDwICcnJ/TTTz8hbm5uzMOGNjc3UXl5OQoMDEQpKSlocnIS3YQn63R3d6PW1lZ06dIl5O3tjVxcXBAuLi6ys7NDNTU1qLCwEPHz86OPHz8iCgoKhIODg0ZGRhApKSnS1dVFV65cQaampmhiYgLR0NCg8+fPI1paWiQgIICIiIhQeno6Iicnh4claCBKSkr07ds3xMzMjI6Pj5GcnBzq7e1Fr169Qm1tbaiqqgq5u7uj2NhYxMrKin5z3dzi4iIqKChAJiYm6MePH8jKygqpqamhoqIi1NfXh7KyspCXlxfKzs5GYWFh6M6dOygpKQlpamoifX19RE9PjxITE9HU1BQCziJzc3PU39+PiImJ0S9/+UuMlhQVFdGzZ8/Q3t4ecnZ2RuPj4yg8PBydOnUKzc/Po7GxMURAQIAkJSXRr371K5SQkIBCQkKQgYEBCggIQNjY2Oj9+/fo+vXrKCYmBgkKCqKH8LgES0tLtLu7i7a2ttDTp0+Rj48Pam5uRl++fEG3bt1CaWlpaHR0FLGzs6POzk4kLCyMOjo6kJiYGPLz80NPnjxBDg4O6MaNG4iEhAQ1NTUhMzMzMMxFtLS0hNzc3FB+fj6KjIxEmZmZyN7eHjU0NKDHjx8jLi4utLOzg75//46qq6sRLy8vOjo6QpWVlej27dvo0aNHKDk5GeHh4SFra2u0sLCAFBQU0IMHD1B9fT0aHBxEbGxsqLi4GMnIyKDQ0FCUk5ODoqKi0MHBAXKEK9VPnz6N6urqkJaWFtrf30fr6+voxYsX6MyZM+jy5ctISUkJXbhwAd27dw+Ji4sjERER9PXrV/T8+XMkJSWFODk50cDAAPLw8ECvX79GXV1dSFZWFr158waRkZGhmZkZVFJSgra3t5Grqyt6+/Yt8vX1RRkZGfcBAD+D+SvA+C1g+lkwvA6YfRmM/hJMzgIGtwFzy4Oxc8HUa2BoVTAzHRg5DkwcDAYuBfN6gnEZwLRXwbCfwaxGYNSzYNI8MKgomHMIjGkIpvwEhtQDM6qDEW3BhBFgwFQw3yEYrwxM5wSG4wazbYLRAsFkk2CwbjDXJTCWC5jKDgxVCGb6CEbCARORgoGugHkmwDjnwTQCYJh0MIsGGOUbmOQYDNIL5mgDY7iDKVjBEItgBhMwghWYoAgMkAXizwbh3wHRa4Lg6UHsUyB0cxA5MQJ9w3oGwnYGUYeDoOdBzAQg5F+BiENAwAEg3vcg3BgQ7UMQ7C6I9SkItRlEegsEOgri7ARhdoAo/UCQDiBGEhCiGYhwCQQ=
*/