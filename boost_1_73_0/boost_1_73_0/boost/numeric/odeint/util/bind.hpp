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
xGvDkimhHHg/8U/m5z68Hy4Ww5l/AfNjGM4uCOztZDbGrRdIVgC/zQuukLwAscpTwaOa8+ddvVarVy9Bc6UhZMqojNJGZjGYcrUMWv6yvKKiETmHU8nhHcMq/FdAXshrEaFbLAtaROWWS6yoh4P954O9ZwcOSnZbAZ2iIIOn2Af9fVhyDOEG+3l3sN/tY1zKkZIWirk9FFmYlphJm7LrJu2macVXEUeuyhzxWGQczuaeP3Vn8LR/8KzfainNtAhBif94oGF1V3AWxWUWWmHCCujkunDWH+m2eckQfOnAtRQRdHA7OVvZrY8tgPuAWmqWwtGa9XDrYPCXZfz3oL/39AN9sAjMrrAOW2hACsW1hU4OPBo+qrhlTAbbNh5kgM5RlQ1hiNgytlcVs92iIWQsR5XFhG29mohN34Z9nUqY31lGDpMPOdjEWK3wSRVChoJr7Jf69fNW+Nn5u+DEHY7dhQf7G6s3+cvdmH/r97dbshHonstjGPT7KFdLZNpUZL1R54tppf8In6BDc+awfjOVin2Cy6JXNzgeTqbuOJjMJr7RDJFEtTNFiUcMxQYKR4uGToLlwAvzfIQrmE4dtG1ENJ5XqVyyNBCZ0BbhB2+m89fDaTCcTm14sOacv7Xho1E4zgtkxB3QiIxytr9A
*/