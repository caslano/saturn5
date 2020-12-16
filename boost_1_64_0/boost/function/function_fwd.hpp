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
sK0Tb9Whve3ru39ihRRc6b2mr3HtaeRzs7eYm1tw4b+uQIicf1kePp9upKa6miFX1aO6cFVIUFQyftP5Mzdn3MPd89mf+KDEwr0z8N3dMYXt3utbGUcdr136v///jf7XwcE1EpyUijf2dWyK36NQfSZQP6+Orbb81T0nja+XWZ+mEm+xMh5fMrw++1Fn1YVO1J3tI6bb3ynTz106bLAmwGtu5PmgvB+/8dm/o+4Ak1u4wTfw4QA9hBN35V7H8Z80u1boxM3UuorJYbefWHR016nfvs3K7qrdMF5xe8fh89lzXtk0WmMs8v7f///D/Y/4aqdt3dtT19bE6ddev/3jEv0ZdxqTtFfwzthVvxn/GlO610/+Qae9Gd8c/sOJ5X4DO9i/Wqjmsk9sWLRZ7ZZzZ39LvvKAx5WoM1euV2l2pil79V1meVsxfH2NOo67xf70Cm637VpNQMYl+EXvnU+eWf5GbU2gIV+t77gSk/j+dfviOLMZ38qtLz/iarGDqLU34GFj2rmGRy+ZR1ettb286RyZ5lkx/uWieu/r2B+N+F8cu5wdvbZmZs+vypcXXyOvs7tbnEt9+iK/1wBT2L61ov7WiqF5x3hb6DXP+tUvnyyitP/51oLGJ6YvvrG0T3vUEeOEWoZyzl7qMnPJU6Uak0BiYuKNvq9HtKMvu+r9f/z/f/z/z47/c4oBiUU7Y5XeP7hvn7zm9FHL7m2/nvv5qqjS4gz3F8vTWQVtsER6cc2Wd14DrBWvd0Ue1FvqWBL23aL7Q8usmacSjZ43rmRmqzT1FghMesd+Ovfuqy03dXVNUQeRa7CU/oVHNJjPGqxF78KjfjOP9G76ZYNZRmbX2wLvtAPnNz5KWWaFHAjscsQYOQ2VHVh5ONqQ8sbF441Jt4X83cSS5baeuY/y9rOCasNfatXjZmTSRkpmqgcNrC082a5QvfbhHNHbl5F12i0HltnsmPGqf+O+na54960ztaI6Nu2BmbY/tTdqVCcdfoeI8dr95X2vBcmPj+01n3dvxYKvu3+hL3i0rjImfknjuq5vB9q6Jyb9Jzw/8//0f/p30h9/7w9LXDnlW79CI/Q7+gQkhADY8RH9m18keqQEUr3CJYmeAUGqb/qI/rJEj5JAqje/PH1+8+aP6K9MX48fc8asgqaK8NS5Z7awu4+kbzymNiROi3f/k+nZH+nduOI50cVj2/oEGn+27bar8aw+9Qsp+Lhv4fnLgUM+GkVv7b3CH7y9MT43QbRH57vtM7+Nq/55R2pX0/c1GfnXnf6cq8dUxBz94dQTyvn5fabag/bfqvEOJG24J1oSwr02/1LB8j0XizCjZ/c1zn/yRdAPi+/svEO7u27/N9nEkw9+LNPtj1mcqWe4ZuTKnOzMX7ZeVQsoSDYpOi7a3now9MaWA6eFcEINzY+OX4WbfeDwCsKbMF1SwY4e06OVbR2jHa9msfemfZGzePkmzROnVBEqlBcof7JwbbL3Av6ftX+L1beI1lcej3K9kTbv+y+vzVF4g86rHHQ7KIhQsh6ra29qPejTpyD3vvtngtZP8XPtHxS0xNOLxu+FvVxbmbQ9slY02sshHPFu4ZU3huU+VJEnPmfmm6Io9xN06it/NGj8rm/JuUcbH1QWbmhed5B/8duepCCLjRmWHpcdR5qjZxJu70n9lpq4v52uNKwguj1ocadBtJ5tviuIr/wQodKZufmseYhBuu2mnDiLLTVluNyfK/ffhS0/xz671Zh45uLrTusBxayRRqxu7emrFe2rvB0q/AeztW++mXNrcKDRbofSheWl89Ndog/vT1Ra9FMfTV7tO/Mty3j91O7C1a5Oe453Llg0QlN+25dEoJ3OpXo=
*/