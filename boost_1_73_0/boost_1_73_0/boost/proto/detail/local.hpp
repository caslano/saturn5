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
/Lq3A3WMsWgq+XI/9fMIMantcQvbaA9zGVufIp4m9DRxS3/iDmNai37xvWEWPifNr1wHPEH7u4V2k84YtA9xPOM56ghjrwWMP4P0m491sJBI7Ns62cLrtItX7qMdc7576fP/fJrxXR/yjzq7cAFw5UXs63HaA/35Yvazur+FgfQ1z7DtjEomNtP/1+Z4v19joEp/g7pP3HiLejyJ/mGIhRuTuZ5hrLmE9labPLyU64Wn6KOOE99epD+o2Za4/j0=
*/