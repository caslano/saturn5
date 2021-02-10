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
rtPZIqYhABY7exK2GP3yms54AD1l9Lr/zQH4ZDofXUyicYs/OYCfXU4vLl/P52+Wk+FiNJ0E/zknzyQ4jxZRAJPl+FBCk2nr0sZ43Dblccfpxl0ZW9wXk3sUpwqFrsqX7BAO+Ho1aVWg5juyWaNb/c8KdYr0J+m3JcIyqm8SeMDdQFvuZqnpcLv4aK9QdLxb/gVQSwMECgAAAAgALWdKUuRyfwPOAwAApQgAACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjE1NTYuY1VUBQABtkgkYK1V72/bNhD97r/i5iGDZKh22k9r3ARTbKf16tqB7awIEICgJcriQIsCSeXHmvzvu6Pk2GkzeB+qIKJ0vHfv8fEo9zo/72pBBw5ezP8zvHD0iEuj/xaJez2bsUeo/xB1g+Mhkh7sII8shMOQRwg8hDUsH+iZsUNEN6SNbj1C3jB6xAjCCDnQ5YOR69xBMAjh7fv3v8MbeHf87jiCIS+kULBwolgJs47gQ+ojf+T8/r5rxVkEwgFX3abUMpcWrM7cHTcC8FnJRBRWpMAtpMImRq7wRRbgcgGZVAIGs8vr8fRjBHe5THIq8qArsLmuVAo5vxVgRCLkbV2j5MaBzhCOxVNpHRasnNRFF7kFOGE2lmoQ
*/