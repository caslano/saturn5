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
gm3W5SUtBUAR3EWgb6OsRAVPD2UKjhB7CDxRrsj+Xj4VHopKc3y7C6z+YUs/P5lHgk1aW3RtZT/gjhYVu2+werpAUuZiLeV1Q7XZI4D5obulvrWOIJcn9ST8SEeoCCax9WII7C9s0tgR57k2DVgS7aZVWULRHszwSUt+mLuijApvqCIWsfQm0dd0skz3IgEChnjsUCFUhE5IMsh1jI1rhbjeVFUTI0u1yK0KLBPg6A46drtmxNunvPO9ElAEgIht0sQltREYkILsJC1c4RSrKAHZ4ZXD1+dfziKunREqudotkgS/1hB6kyi/JxFWwql7gNEzvZanCZFSvkEWfDmj2U6T3vsB4VaYJ41CyzEGkX9z6ObxGmmsnmZ5wMu2FpL8mxoLaA9yvX4HWXYEnAjDk9QEY5kVz8knMbF3IV3qaAdmlTtf7swCksYODJQQKdSdxEtiUbRdV2ovE3F6Ac5RTZawlYO9s6PNd4yf7Dv1KwqxLkJfyQcxQcxFENmxDxulU2+cx3jpTJhO8Gkg9tbFPz4cO9R9BNKbKIdwQ/VMBeProe8EaojU6tQ58w==
*/