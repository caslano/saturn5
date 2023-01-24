/* Boost interval/detail/x86gcc_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_X86GCC_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_X86GCC_ROUNDING_CONTROL_HPP

#ifndef __GNUC__
#  error This header only works with GNU CC.
#endif

#if !defined(__i386__) && !defined(__x86_64__)
#  error This header only works on x86 CPUs.
#endif

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

struct x86_rounding
{
  typedef unsigned short rounding_mode;

  static void set_rounding_mode(const rounding_mode& mode)
  { __asm__ __volatile__ ("fldcw %0" : : "m"(mode)); }

  static void get_rounding_mode(rounding_mode& mode)
  { __asm__ __volatile__ ("fnstcw %0" : "=m"(mode)); }

  template<class T>
  static T to_int(T r)
  {
    T r_;
    __asm__ ("frndint" : "=&t"(r_) : "0"(r));
    return r_;
  }
};

} // namespace detail
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_X86GCC_ROUNDING_CONTROL_HPP */

/* x86gcc_rounding_control.hpp
xYxGbofRoFo/d6w2GYXcqQR43NwjwsUZUYRh7vnEJ39I6QwDsvJwOtZNx2KoUZ+2FDwGmN9Ek2uMyBpPLCnkshM4t3d7QSnBnAviJeaJm8J4oCNpH5qhV77jfLuHxwwLPP72Bue7VPSFptRYK4jEcxdHkUB3Rfxk9fCQzy06WftCi2Al9Qzd3RsZXKGup4jX/+vmQE7qBMgoRFYBkdju3u7HI+mVa/Fsm2I/eF6CqenfB9u0WN9FaJvWbKu8eX0oYg7eJCvz1qJv2Iv7gTvMppoCK53hCSfj+tkh3CxJm+vNpmatxwqsJEWPvqznj4ATb4YPlLETqQLJ66Z2Ka620+F86E9ar1XwHK2Va5tyEqI+XMFnulFGgq/ictt25y2Fbfq+DfDHRDnUz7TeTEknHRXo924MnOdm3pNup7d1lk3SKoGlusP4e/PMCPxje4b6Dd1+0uSoqIqL1UjFXdBkHZMvg7fKbJ4VR+MmzMdVHzcaWCE66QJ6t6AQLtd+RiNSVq6PSM1n/JmKuXI2ThRiasNrJj0LV/z+k0Ezd190Jpr5clh7miHz9FteCvMGg1g2DDsbYtn3ahyxoE0zkLPizuUmoFW73XBXMS8dRRzk0PIflWdn+iixfsqpeOFzyqTVOB+VZx4AyeNSN75K6LtMoal4wnJkamiqz1QyL9sU6FYtYfayL4fqW3MdxS7Mmc+Ys9SYNN44bLkXxhQ1
*/