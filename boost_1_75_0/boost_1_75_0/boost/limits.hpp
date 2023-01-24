
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
maqbDu5d0F+z4HexWv8swv4bTaJIuvpflD9msfofIWnw3wQo/Rn4XQD/Yd7Z0KIxJAf6jZCSUat1llnKPcikgMVYxLnRFhd8MS3ZuXlrW2Ay3m3tjtuWKc6WFbtPsnY3WLthaiqi1eeyts16B/PVSelts8TB6M0vKiqcLv1UkOXfpJn4S8RjVAhZNk9HlHE0pAxPA1mISbUg4yjjtrHYKRBbELRzsDg7T7o/AiJzlW/5JYuILURZuEj5VlqObAf3DDIx/g80/g8YXx2ILw2d5iqMFK2mqt/71k0zW2xmPoHYwpQ4gLOa+N+3g9LH11nSAMJ+WHrhLchZ5VkPv1nKt0XTQRwrqON/301sh5QF3TRLazOuSyGEuAepe1c3gt+o+l8N8gPHd5tU/wtB/lVB/tVB/heD/C8F+f8Y5P9EH/BvCPLjLlFdqamk5DSxyHf1oGZh5n06zjlpvo6ginG9RU94nx70IhAAmHQqj2w3kXzBbZ9UsglWtVKdvEsPQ5fPpNHxkCFXBTQgIN2T+qfeCCJkrnyQQirDJ8GoiKF8hlGRFwM5xLkT5Q6Qoet61P28/aqrhfe2GdnenhlwS7cDKdgtqkD6gEL1nIJaMyk1y14oJR9btPoMtKgAdTSkBc65BUrhl0TDwne30Qi+0eC7h/rGgS+e+iaCb3uxDnyJ4IujcZPAdx/1pYEvAXxVSx5P+5lYOGEiBEoHy1lY
*/