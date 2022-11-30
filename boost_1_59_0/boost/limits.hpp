
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
+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
*/