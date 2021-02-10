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
211fZw160a6vdGR2zZyuD/x7NnuBuhs2kr/avPlmxj/xxO50+ztZvi7UbVzSUadBJ6enP9Mren188tanc5EqmdCklOlcFrc+fYjMk//E4v6+peWvPsmSRNLaEziNlSadLcqVKCThd6JCmWoZkdAUSR0Wao4blVIZS1qoRFJnOLruDf7r0ypWYezkrLOKdJxVSUSxuJNUyFCqOysmF0VJ2QISID9SuoTMqlRZ2oJ6SaUsltqJYSNEojMSd0IlYg51oqS4LHP9rt0OqyKBJ+0oC3U7rEPRisvlA6+uYc1SrCnLSyozqrT0idf7tMwiteArQoSHeTVPlI79rVlQmEbtrCAtk8SJw1YltXVB0sRFy+eVlMN6VfJFZ6lmbas4W+4tRFidoEVVpFCHsGBdlCHwPlVpJAuz3gSi1uKibEL+nZRtbY8oS2EVHQQT6k0OaC600j597k0/Dq+m9DkYj4PB9JqGFxQMrp28y97gHNhQ0FqQvM8LqWFFQWqZJ0pGe8r/0Ur3WtOP1Lka94ej6Wwy7FzienE16Ex7wwG9oYOTn+i3KmV4//uADhI15/zT29abt61jPOC7mRR6PdOy5EzjD6DSkDv5SIPg9673LeE3r5DekkKRJHMRfqGFyXdZqvQWkQ2/yI0wI2tyPRiO
*/