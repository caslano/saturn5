/*
 *     [begin_description]
 *     Boost bind pull the placeholders, _1, _2, ... into global
 *     namespace. This can conflict with the C++03 TR1 and C++11 
 *     std::placeholders. This header provides a workaround for 
 *     this problem.
 *     [end_description]
 *        
 *     Copyright 2012 Christoph Koke
 *     Copyright 2012 Karsten Ahnert
 *           
 *     Distributed under the Boost Software License, Version 1.0.
 *     (See accompanying file LICENSE_1_0.txt or
 *     copy at http://www.boost.org/LICENSE_1_0.txt)
 * */

#ifndef BOOST_NUMERIC_ODEINT_UTIL_BIND_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_BIND_HPP_INCLUDED


#include <boost/numeric/odeint/config.hpp>


#if BOOST_NUMERIC_ODEINT_CXX11 
    #include <functional>
#else
#define BOOST_BIND_NO_PLACEHOLDERS
#include <boost/bind.hpp>
#endif

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

#if BOOST_NUMERIC_ODEINT_CXX11 

using ::std::bind;
using namespace ::std::placeholders;


#else

// unnamed namespace to avoid multiple declarations (#138)
namespace {
using ::boost::bind;
boost::arg<1> _1;
boost::arg<2> _2;
}
// using ::boost::bind;
// using ::_1;
// using ::_2;

#endif

}
}
}
}





/*

// the following is the suggested way. Unfortunately it does not work with all compilers.

#ifdef BOOST_NO_CXX11_HDR_FUNCTIONAL
#include <boost/bind.hpp>
#else
#include <functional>
#endif


namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

    
#ifdef BOOST_NO_CXX11_HDR_FUNCTIONAL

using ::boost::bind;
using ::_1;
using ::_2;

#else

using ::std::bind;
using namespace ::std::placeholders;

#endif


}
}
}
}*/

#endif // BOOST_NUMERIC_ODEINT_UTIL_BIND_HPP_INCLUDED

/* bind.hpp
69ITsAJ3/n05vIwMTn3C4GaeCWO92BBRUWTgWYuUa275C1wOsfP5qK68GDmhgnlPfO2G5F97PeLlAdENt28uwAjMhdijQNekT6Fpi1i87h4nkK9JxABRsOLKkQUCw5PPB3OMesIS8bra5n6JASdFr4L7hTMzQmUkR/GoXO4yJ8q7dLovbzNsTGWRBzb4J+JkNABeUuyB9byJmMbuOBK1rqz8m2lWBGi2b3wtIeM7P6Pd+wqTrsjRIX6wL/pFjpI=
*/