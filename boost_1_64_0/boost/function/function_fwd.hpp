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
619E2HEh3SsRpeP4Gi5Ekxt5DxnGMeT8ByELd79PXxXmJvJgE7A5LHCwkhZ6SSwbJjlg5i/8vkWG9pb1t6Km1IcZ4yqTIkHt5au2lVTa4IQhV5wYTSHQtHN1Fs8OgH60LnLU4Dv8H0YJ/79c95q8ih9X5sWIBnWuy8T/Qmyu1WXr4hWxe5CHhWVlCZpu9dSjVO3PYmLH7VuFYonJu6wUdzkS9gF03dtWIuZ5T8fmB1vQbfFDV6Iext4WzyPf7ovxLyP+DFDtPQMLwEc0xQ8pUBzDsto9+Wb/tX7dOykMfRsRbKc+u4rjswSrPpEz5Rh6W4pbZKF0v1y2D4mXIJ46pA9EPUNVt072GbWnVLS2AnnT7dukErJ8POBoYcc38FZpqg8cc92W464jjF/uKgHw4GCdLKQgN5tDH+vndJLkMogF+Ik5PFVoQazKWJLg/cHim9HC66gkJ6BE0Vq0fM+bAlthiQ4n+tDcsgKemOg60IKxnRNFY4TotgDSlDidVKl+l+pgMMiL1IYmByHrgVglyrFa6Dl+ka622dRSUhJMTreVxtIH1BF3TrCWkA==
*/