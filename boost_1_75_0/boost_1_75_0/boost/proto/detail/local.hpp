///////////////////////////////////////////////////////////////////////////////
/// \file local.hpp
/// Contains macros to ease the generation of repetitious code constructs
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_LOCAL_MACRO
# error "local iteration target macro is not defined"
#endif

#ifndef BOOST_PROTO_LOCAL_LIMITS
# define BOOST_PROTO_LOCAL_LIMITS (1, BOOST_PROTO_MAX_ARITY)
#endif

#ifndef BOOST_PROTO_LOCAL_typename_A
# define BOOST_PROTO_LOCAL_typename_A BOOST_PROTO_typename_A
#endif

#ifndef BOOST_PROTO_LOCAL_A
# define BOOST_PROTO_LOCAL_A BOOST_PROTO_A_const_ref
#endif

#ifndef BOOST_PROTO_LOCAL_A_a
# define BOOST_PROTO_LOCAL_A_a BOOST_PROTO_A_const_ref_a
#endif

#ifndef BOOST_PROTO_LOCAL_a
# define BOOST_PROTO_LOCAL_a BOOST_PROTO_ref_a
#endif

#define BOOST_PP_LOCAL_LIMITS BOOST_PROTO_LOCAL_LIMITS

#define BOOST_PP_LOCAL_MACRO(N)       \
  BOOST_PROTO_LOCAL_MACRO(            \
      N                               \
    , BOOST_PROTO_LOCAL_typename_A    \
    , BOOST_PROTO_LOCAL_A             \
    , BOOST_PROTO_LOCAL_A_a           \
    , BOOST_PROTO_LOCAL_a             \
  )                                   \
  /**/

#include BOOST_PP_LOCAL_ITERATE()

#undef BOOST_PROTO_LOCAL_MACRO
#undef BOOST_PROTO_LOCAL_LIMITS
#undef BOOST_PROTO_LOCAL_typename_A
#undef BOOST_PROTO_LOCAL_A
#undef BOOST_PROTO_LOCAL_A_a
#undef BOOST_PROTO_LOCAL_a

/* local.hpp
ebjHvONJD0mXSM7bRHTHYWmDyD2LucezolzzH9/13CZvrq4vVi0TfNVNpbHG9HThhs9uH6Y48MoCAreLgHKzDDJE9XhiUUnTw4SMuGnhQ1HDWwokzI1mVAJhvVXp0W4SWx76pU5mtbTt+klmwZbDIAVHWxY1X3Z3tIMDSnOvtgpuZ9pO8ye1cvj3bS+dZzwyPvLYkAsrP6ZGp/fA0hC49wSDJOL7tiOU5clmqU+biB5s/OzR2viFHemTZ5OQ1SsdpCnWEXQqCJ5p6vrCqtHv261x7eKYd70Wse7DzY48rH4WW+oz6yuSpS/XDoZjYO3fwDPw0LtTbzzapu9y4jxEXv1E0ZN1RA7XICt6eQOX/JcClxLW8W0HnQAjdeD3Z2h2qHZv7FDs0LdQqzHsaIAtEa7+fw9vusnXX9m+hqrZwK7e+rsFZPR29LJuA7Y1LvXUq+PxiApdJhOmiKpyUG+q+f7Sjf9Cd0ll38Lk93qK4lK34QRkt1MLtCRbUByItrViIOYUK6ZoCI2LjSPW1WDhJ8EjjhBdI3P6xrzJP+zXUfkYP0IDaOY2XZ58BNi1rZE5SuWH8gvtOgvE2mTLCEjtljoMRnxqT2qMCaC5jzfIuNrJJV46v/IF/JI4LTDSWA8XRMu6t3ckeK88/B3Ity8lXmzzVuAXAHhJZ9Qp7SaVG2ikzVF24u9Jyvc2QJmGp3hTF3DzdEIMDKH7E1dJ
*/