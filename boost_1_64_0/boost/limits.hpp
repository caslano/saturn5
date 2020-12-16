
//  (C) Copyright John maddock 1999. 
//  (C) David Abrahams 2002.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// use this header as a workaround for missing <limits>

//  See http://www.boost.org/libs/compatibility/index.html for documentation.

#ifndef BOOST_LIMITS
#define BOOST_LIMITS

#include <boost/config.hpp>

#ifdef BOOST_NO_LIMITS
#  error "There is no std::numeric_limits suppport available."
#else
# include <limits>
#endif

#if (defined(BOOST_HAS_LONG_LONG) && defined(BOOST_NO_LONG_LONG_NUMERIC_LIMITS)) \
      || (defined(BOOST_HAS_MS_INT64) && defined(BOOST_NO_MS_INT64_NUMERIC_LIMITS))
// Add missing specializations for numeric_limits:
#ifdef BOOST_HAS_MS_INT64
#  define BOOST_LLT __int64
#  define BOOST_ULLT unsigned __int64
#else
#  define BOOST_LLT  ::boost::long_long_type
#  define BOOST_ULLT  ::boost::ulong_long_type
#endif

#include <climits>  // for CHAR_BIT

namespace std
{
  template<>
  class numeric_limits<BOOST_LLT> 
  {
   public:

      BOOST_STATIC_CONSTANT(bool, is_specialized = true);
#ifdef BOOST_HAS_MS_INT64
      static BOOST_LLT min BOOST_PREVENT_MACRO_SUBSTITUTION (){ return 0x8000000000000000i64; }
      static BOOST_LLT max BOOST_PREVENT_MACRO_SUBSTITUTION (){ return 0x7FFFFFFFFFFFFFFFi64; }
#elif defined(LLONG_MAX)
      static BOOST_LLT min BOOST_PREVENT_MACRO_SUBSTITUTION (){ return LLONG_MIN; }
      static BOOST_LLT max BOOST_PREVENT_MACRO_SUBSTITUTION (){ return LLONG_MAX; }
#elif defined(LONGLONG_MAX)
      static BOOST_LLT min BOOST_PREVENT_MACRO_SUBSTITUTION (){ return LONGLONG_MIN; }
      static BOOST_LLT max BOOST_PREVENT_MACRO_SUBSTITUTION (){ return LONGLONG_MAX; }
#else
      static BOOST_LLT min BOOST_PREVENT_MACRO_SUBSTITUTION (){ return 1LL << (sizeof(BOOST_LLT) * CHAR_BIT - 1); }
      static BOOST_LLT max BOOST_PREVENT_MACRO_SUBSTITUTION (){ return ~(min)(); }
#endif
      BOOST_STATIC_CONSTANT(int, digits = sizeof(BOOST_LLT) * CHAR_BIT -1);
      BOOST_STATIC_CONSTANT(int, digits10 = (CHAR_BIT * sizeof (BOOST_LLT) - 1) * 301L / 1000);
      BOOST_STATIC_CONSTANT(bool, is_signed = true);
      BOOST_STATIC_CONSTANT(bool, is_integer = true);
      BOOST_STATIC_CONSTANT(bool, is_exact = true);
      BOOST_STATIC_CONSTANT(int, radix = 2);
      static BOOST_LLT epsilon() throw() { return 0; };
      static BOOST_LLT round_error() throw() { return 0; };

      BOOST_STATIC_CONSTANT(int, min_exponent = 0);
      BOOST_STATIC_CONSTANT(int, min_exponent10 = 0);
      BOOST_STATIC_CONSTANT(int, max_exponent = 0);
      BOOST_STATIC_CONSTANT(int, max_exponent10 = 0);

      BOOST_STATIC_CONSTANT(bool, has_infinity = false);
      BOOST_STATIC_CONSTANT(bool, has_quiet_NaN = false);
      BOOST_STATIC_CONSTANT(bool, has_signaling_NaN = false);
      BOOST_STATIC_CONSTANT(bool, has_denorm = false);
      BOOST_STATIC_CONSTANT(bool, has_denorm_loss = false);
      static BOOST_LLT infinity() throw() { return 0; };
      static BOOST_LLT quiet_NaN() throw() { return 0; };
      static BOOST_LLT signaling_NaN() throw() { return 0; };
      static BOOST_LLT denorm_min() throw() { return 0; };

      BOOST_STATIC_CONSTANT(bool, is_iec559 = false);
      BOOST_STATIC_CONSTANT(bool, is_bounded = true);
      BOOST_STATIC_CONSTANT(bool, is_modulo = true);

      BOOST_STATIC_CONSTANT(bool, traps = false);
      BOOST_STATIC_CONSTANT(bool, tinyness_before = false);
      BOOST_STATIC_CONSTANT(float_round_style, round_style = round_toward_zero);
      
  };

  template<>
  class numeric_limits<BOOST_ULLT> 
  {
   public:

      BOOST_STATIC_CONSTANT(bool, is_specialized = true);
#ifdef BOOST_HAS_MS_INT64
      static BOOST_ULLT min BOOST_PREVENT_MACRO_SUBSTITUTION (){ return 0ui64; }
      static BOOST_ULLT max BOOST_PREVENT_MACRO_SUBSTITUTION (){ return 0xFFFFFFFFFFFFFFFFui64; }
#elif defined(ULLONG_MAX) && defined(ULLONG_MIN)
      static BOOST_ULLT min BOOST_PREVENT_MACRO_SUBSTITUTION (){ return ULLONG_MIN; }
      static BOOST_ULLT max BOOST_PREVENT_MACRO_SUBSTITUTION (){ return ULLONG_MAX; }
#elif defined(ULONGLONG_MAX) && defined(ULONGLONG_MIN)
      static BOOST_ULLT min BOOST_PREVENT_MACRO_SUBSTITUTION (){ return ULONGLONG_MIN; }
      static BOOST_ULLT max BOOST_PREVENT_MACRO_SUBSTITUTION (){ return ULONGLONG_MAX; }
#else
      static BOOST_ULLT min BOOST_PREVENT_MACRO_SUBSTITUTION (){ return 0uLL; }
      static BOOST_ULLT max BOOST_PREVENT_MACRO_SUBSTITUTION (){ return ~0uLL; }
#endif
      BOOST_STATIC_CONSTANT(int, digits = sizeof(BOOST_LLT) * CHAR_BIT);
      BOOST_STATIC_CONSTANT(int, digits10 = (CHAR_BIT * sizeof (BOOST_LLT)) * 301L / 1000);
      BOOST_STATIC_CONSTANT(bool, is_signed = false);
      BOOST_STATIC_CONSTANT(bool, is_integer = true);
      BOOST_STATIC_CONSTANT(bool, is_exact = true);
      BOOST_STATIC_CONSTANT(int, radix = 2);
      static BOOST_ULLT epsilon() throw() { return 0; };
      static BOOST_ULLT round_error() throw() { return 0; };

      BOOST_STATIC_CONSTANT(int, min_exponent = 0);
      BOOST_STATIC_CONSTANT(int, min_exponent10 = 0);
      BOOST_STATIC_CONSTANT(int, max_exponent = 0);
      BOOST_STATIC_CONSTANT(int, max_exponent10 = 0);

      BOOST_STATIC_CONSTANT(bool, has_infinity = false);
      BOOST_STATIC_CONSTANT(bool, has_quiet_NaN = false);
      BOOST_STATIC_CONSTANT(bool, has_signaling_NaN = false);
      BOOST_STATIC_CONSTANT(bool, has_denorm = false);
      BOOST_STATIC_CONSTANT(bool, has_denorm_loss = false);
      static BOOST_ULLT infinity() throw() { return 0; };
      static BOOST_ULLT quiet_NaN() throw() { return 0; };
      static BOOST_ULLT signaling_NaN() throw() { return 0; };
      static BOOST_ULLT denorm_min() throw() { return 0; };

      BOOST_STATIC_CONSTANT(bool, is_iec559 = false);
      BOOST_STATIC_CONSTANT(bool, is_bounded = true);
      BOOST_STATIC_CONSTANT(bool, is_modulo = true);

      BOOST_STATIC_CONSTANT(bool, traps = false);
      BOOST_STATIC_CONSTANT(bool, tinyness_before = false);
      BOOST_STATIC_CONSTANT(float_round_style, round_style = round_toward_zero);
      
  };
}
#endif 

#endif


/* limits.hpp
87QpIJK2IGkAjwTpIZR+/IdMAQZKEfIhSig8ZnCaL3XFzi7k0fBLh2j+S+7JMy4RZynSKTERzp2LWQSdpzrvh78vdt/PuNHDmdhPwNXlMJ3k6GYuBlu8z7jJt3qv7U7bFDNm0J3W1vBi1h85flwc7pu/7OdZxRN04w/KD3eRF0+QpSW70BU7PArFOKWmIo5z/kONqzesGB5YPxhKo/VzMlTQhY587gajHtp6uQcG9iTPsCoXGNT80fvauVLIdkQytydGMbJj6TBtLhxog1EBYnPIM7Gq6N3IS8r+eAixWI6fUvaXac7lrrbTtWp4xUYbsyngd9n+ygugDbgcCXlNXp9f6kj2Xdp+o34H1WSON5Lxz1ckxWXI9RsyHmPVsVViEPCywwrJ+OI7x+USjrx8Otc+in/CuRYyLtERcil2rXuGLXmK1zHYgYKHEZOmbosd+fGpDr0Bd2DHDdFxDysvGIJpXIlm53CPdLo9Gpqd7mn7JOTOeplQ5H6svu2OyJ2+tvm8ZRRR2jfx0A1G7V+jbqNz+mOKCOhgglDkkoDbM9g90oF/H0JmGoq6vLTtAr53LhMXwUhmStBuG41wkDY3Xm0bJnNvywNRNpHks4BT1wGscOY7mnDtw3URSn4xLj+uSlwVuA7h/rvxv8UpftO+G44Pl/QPHjL83/BxDU39/V90bqDUD9fqcmS8TbT6IlRe2vp3+RxbzosEHegMUp4Xpj6/1Wk/Lzd7oCNa4vzZDaLfuWq97HdmiH7nQ1a/s3s87QupzIXzffW2ZeeIXrCQ46UuPaHRwqE3tm2ZuwftYMQ6dN/XXSqifNh9D09Z9qeVim3q0cpmeeSDyFIXbxl6EtyhIon4VdNEp9cwWSy0GZjeRa5PfgH9e9LvH7/Q3/7e1Befm9rd0YjScLlZmsK3CVN4rr2EgesPp9MezhM9M7RsQ8DlYGafmsk+raqEqgCW5BNgEkuf+OS8m7g2gK4o3H8Y96k4R+KmZUCzdUor3SbfZ41p+j+nWPtVVV0vSnB1Yrsq6O8JIbHpmaIb013ilFT/1qpzwwbnHz8Lu148BBJgCjuRikvAqK4wlnBJCXnN0xOyiHLoYj+ePsUUOs/RAbzpG6jnaof22MyR9uqEs6Hm7p4tjvVHgplIQHSegXdup+G4HU7ZrucVB9bcKQ5J0X4VK2BWEZajkS9eiPLE9l7Lelgo6yEfWTKnSLc5sdT8lQC5qB7CXIvMLhXJG6bKk4qmFvGfuQtl7gZshg9cb2nnGfNn8m+6dc+AiXIa/YeJ9l6HljDRagk9vx9vqj42fMlY0SsWrug4HsccwVdc+V3mCGpwj9cXrP/JV9ozXt0WJvm8Zuyrz733M5zXzPb+1Wg/23vq+dcV1vglYFjzy1c+7GWgoIwxlnPM43HLmmPm+tdhifWv49Imls+b2peJ5R7nvyfb54fY88uzOEH6EyNpka6cY37QSI1/HmozOWFc2sTyqikDPLGcuv/95L7Zy5nnl7vIZ09ATizUderGUSGl3dXHbnE/+DPbtnv2H9K2G10gbLu3h5u2HZt7DRedDMFODpFFY82j8gXIuxx9/klumg5tz03TOVGKv13SNMbTbxkVY9NvgZCgkFn0j/wenG7FdTeuG3E9iKsVl8M5KC9v0In7KPkvnrCPWptwREUC9tEZXc//Ks8qHugrZ+YYD9S1/V+ePJ/3jedp/4zPej7v6Uk5eiygvyaAhp2i+ujyFWNrAl9FUO+SYWudeSsd7u/V3Y1QxnyGMg7POZTRjH+/LDl+8TLMS3xaxi+CWHVtGrHzSOwsEBuIOMY+6WOzKtyXmXV+PzfFFbFK0+ZgZ5Dpcv3nMelQ05RGRCZh7LU=
*/