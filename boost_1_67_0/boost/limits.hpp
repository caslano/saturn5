
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
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
*/