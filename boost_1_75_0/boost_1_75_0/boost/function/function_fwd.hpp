// Boost.Function library
//  Copyright (C) Douglas Gregor 2008
//
//  Use, modification and distribution is subject to the Boost
//  Software License, Version 1.0.  (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org
#ifndef BOOST_FUNCTION_FWD_HPP
#define BOOST_FUNCTION_FWD_HPP
#include <boost/config.hpp>

#if defined(__sgi) && defined(_COMPILER_VERSION) && _COMPILER_VERSION <= 730 && !defined(BOOST_STRICT_CONFIG)
// Work around a compiler bug.
// boost::python::objects::function has to be seen by the compiler before the
// boost::function class template.
namespace boost { namespace python { namespace objects {
  class function;
}}}
#endif

#if defined(BOOST_BCB_PARTIAL_SPECIALIZATION_BUG)                         \
 || !(defined(BOOST_STRICT_CONFIG) || !defined(__SUNPRO_CC) || __SUNPRO_CC > 0x540)
#  define BOOST_FUNCTION_NO_FUNCTION_TYPE_SYNTAX
#endif

namespace boost {
  class bad_function_call;

#if !defined(BOOST_FUNCTION_NO_FUNCTION_TYPE_SYNTAX)
  // Preferred syntax
  template<typename Signature> class function;

  template<typename Signature>
  inline void swap(function<Signature>& f1, function<Signature>& f2)
  {
    f1.swap(f2);
  }
#endif // have partial specialization

  // Portable syntax
  template<typename R> class function0;
  template<typename R, typename T1> class function1;
  template<typename R, typename T1, typename T2> class function2;
  template<typename R, typename T1, typename T2, typename T3> class function3;
  template<typename R, typename T1, typename T2, typename T3, typename T4> 
    class function4;
  template<typename R, typename T1, typename T2, typename T3, typename T4,
           typename T5> 
    class function5;
  template<typename R, typename T1, typename T2, typename T3, typename T4,
           typename T5, typename T6> 
    class function6;
  template<typename R, typename T1, typename T2, typename T3, typename T4,
           typename T5, typename T6, typename T7> 
    class function7;
  template<typename R, typename T1, typename T2, typename T3, typename T4,
           typename T5, typename T6, typename T7, typename T8> 
    class function8;
  template<typename R, typename T1, typename T2, typename T3, typename T4,
           typename T5, typename T6, typename T7, typename T8, typename T9> 
    class function9;
  template<typename R, typename T1, typename T2, typename T3, typename T4,
           typename T5, typename T6, typename T7, typename T8, typename T9,
           typename T10> 
    class function10;
}

#endif

/* function_fwd.hpp
fNuCb/vC2+K3TbQLuZ+Umtud0Ac1J8OMdpvsnAo9fL9qo4MGOofy0vt/APphc0lXsjKtZ0Otwy3UtQHpUD3kjXZscbid9Xbpn/T+D8aZn/0VTV8mym5XU5YnQwYLEcV2TLZy/WHa5+B1A7SV7RowXYl6qh61h1meXEZTo4rYr0x3x4QsT4EF/H/wJ+jA5S6b2UpNw73RSbHl/0l6jdJKVyhYyIZl9r7ZsY2JeVWsx1qo/8heZIVqwQMkbxNGBXfWygAALP/T9dXRpnTPoKBMKSxdcrRk9K5m9auh/ug9WH9YNZr6zNpIX1TLn1bzfsFChdEfmDr2Wq00hjt6Z1Q6trXAiegZVodfNu8R/dbIh7+nVurk/Gr6q1IejX9Jz1Nq3agTjd3JGp9+BznBoECKATc5XN2ssZVOqWbFHQIFj8ikazSXrKcxCdu90X9YGfLCqqQ+FmeeWwTiGFuRGcN4QxyXVaXle7yhwkJjBXULlYoKDodHQuFfqpUvwn3jrBd2838gIqCVjecjzXTMP4tMW6F0M9sKpCN8gv3J1YWP4ltkGMqCON8prc9yO+Kz3GlxbjhhHRF3ccMytLA+SRzsI78zxhM2ElvDX3BX1GV5Zuav2IeX+WbF9vtBNkZ3iMO9SKZaK6nWim2ixjq1RhPVeIXX2CFqvKnWaKEaRbxGnagxU61BCzlPzTZ8I16YrcZ9ay7pS79a6Fc8WgPs
*/