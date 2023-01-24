/* Boost interval/hw_rounding.hpp template implementation file
 *
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 * Copyright 2005 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_HW_ROUNDING_HPP
#define BOOST_NUMERIC_INTERVAL_HW_ROUNDING_HPP

#include <boost/numeric/interval/rounding.hpp>
#include <boost/numeric/interval/rounded_arith.hpp>

#define BOOST_NUMERIC_INTERVAL_NO_HARDWARE

// define appropriate specialization of rounding_control for built-in types
#if defined(__x86_64__) && (defined(__USE_ISOC99) || defined(__APPLE__))
#  include <boost/numeric/interval/detail/c99_rounding_control.hpp>
#elif defined(__i386__) || defined(_M_IX86) || defined(__BORLANDC__) || defined(_M_X64)
#  include <boost/numeric/interval/detail/x86_rounding_control.hpp>
#elif defined(__i386) && defined(__SUNPRO_CC)
#  include <boost/numeric/interval/detail/x86_rounding_control.hpp>
#elif defined(powerpc) || defined(__powerpc__) || defined(__ppc__)
#  include <boost/numeric/interval/detail/ppc_rounding_control.hpp>
#elif defined(sparc) || defined(__sparc__)
#  include <boost/numeric/interval/detail/sparc_rounding_control.hpp>
#elif defined(alpha) || defined(__alpha__)
#  include <boost/numeric/interval/detail/alpha_rounding_control.hpp>
#elif defined(ia64) || defined(__ia64) || defined(__ia64__)
#  include <boost/numeric/interval/detail/ia64_rounding_control.hpp>
#endif

#if defined(BOOST_NUMERIC_INTERVAL_NO_HARDWARE) && (defined(__USE_ISOC99) || defined(__MSL__))
#  include <boost/numeric/interval/detail/c99_rounding_control.hpp>
#endif

#if defined(BOOST_NUMERIC_INTERVAL_NO_HARDWARE)
#  undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE
#  error Boost.Numeric.Interval: Please specify rounding control mechanism.
#endif

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * Three specializations of rounded_math<T>
 */

template<>
struct rounded_math<float>
  : save_state<rounded_arith_opp<float> >
{};

template<>
struct rounded_math<double>
  : save_state<rounded_arith_opp<double> >
{};

template<>
struct rounded_math<long double>
  : save_state<rounded_arith_opp<long double> >
{};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_HW_ROUNDING_HPP

/* hw_rounding.hpp
+W506ZbI/T3RHVANWHX8K4d8Au2YWKxWfAQ3rmPdCFRKbNNcitQ9oBnER9BVQq4DFiR5fInD1uBLlmuB80p2tmClR40ePCiuBbhl1pQE2rrNK5Zr4NJh2zI3ySP7PslCj8oEj3LlkB+4f+OT75EiyVY/p9tHSPucymKNMje4KL2AW0l2qiuGG8h0lOYwfeXI1AA0NKQJI1zK5KxQf7nW1K7VAtbFOWGMDw7AAc3U8Gad7X02m4evReWHmb4AWJkgb4fmYygNRCSWc4aVu1cLQlQsZ6Qmik7vogM0mJbBbP9L+LAoQ38UJOy4aCoQQ6cyrkA9MMwgbEqCxrnvU//iePa3qtVni64emga7ji1as8AWLQMXzamM73LRsg9la7DwU5xKcVaJIzBm0QhfnFYbsmn1uBKL2Ep8QiuRjivxia1uLgjLnk9I6kqAU+fJ75D1tQDLYtofMgVqjVq97fSc90Dmd2CGoHBZuGv68MgsIRxtadc96mZSoetwXFsp7OCyNMpnEaXRLHBlH3XLxynGkjY0HYsv/Ytv6JZH+A6g4Bue99gjs4LzTvlViqihakCkoHEG4dR0BtdQM/VWRrfGy8wIb3so48GexDdlTs1Q10yijTnaI+elyvvIo51M1thFFgXDIburTif1jEN0b0G3lwKYYw6bY4f65J1jq9xofK72AfVPKQMivtFEjhQfvYPYZL0ZNeJyo61WHLef
*/