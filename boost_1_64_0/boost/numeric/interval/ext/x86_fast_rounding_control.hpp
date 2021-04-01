/* Boost interval/detail/x86gcc_rounding_control.hpp file
 *
 * This header provides a rounding control policy
 * that avoids flushing results to memory. In
 * order for this optimization to be reliable, it
 * should be used only when no underflow or
 * overflow would happen without it. Indeed, only
 * values in range are correctly rounded.
 *
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_EXT_X86_FAST_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_EXT_X86_FAST_ROUNDING_CONTROL_HPP

namespace boost {
namespace numeric {
namespace interval_lib {

namespace detail {

// exceptions masked, expected precision (the mask is 0x0300)
static const fpu_rounding_modes rnd_mode_f = { 0x107f, 0x147f, 0x187f, 0x1c7f };
static const fpu_rounding_modes rnd_mode_d = { 0x127f, 0x167f, 0x1a7f, 0x1e7f };
static const fpu_rounding_modes rnd_mode_l = { 0x137f, 0x177f, 0x1b7f, 0x1f7f };

} // namespace detail

template<class T>
struct x86_fast_rounding_control;

template<>
struct x86_fast_rounding_control<float>: detail::x86_rounding
{
  static void to_nearest()  { set_rounding_mode(detail::rnd_mode_f.to_nearest);  }
  static void downward()    { set_rounding_mode(detail::rnd_mode_f.downward);    }
  static void upward()      { set_rounding_mode(detail::rnd_mode_f.upward);      }
  static void toward_zero() { set_rounding_mode(detail::rnd_mode_f.toward_zero); }
  static const float& force_rounding(const float& r) { return r; }
};

template<>
struct x86_fast_rounding_control<double>: detail::x86_rounding
{
  static void to_nearest()  { set_rounding_mode(detail::rnd_mode_d.to_nearest);  }
  static void downward()    { set_rounding_mode(detail::rnd_mode_d.downward);    }
  static void upward()      { set_rounding_mode(detail::rnd_mode_d.upward);      }
  static void toward_zero() { set_rounding_mode(detail::rnd_mode_d.toward_zero); }
  static const double& force_rounding(const double& r) { return r; }
};

template<>
struct x86_fast_rounding_control<long double>: detail::x86_rounding
{
  static void to_nearest()  { set_rounding_mode(detail::rnd_mode_l.to_nearest);  }
  static void downward()    { set_rounding_mode(detail::rnd_mode_l.downward);    }
  static void upward()      { set_rounding_mode(detail::rnd_mode_l.upward);      }
  static void toward_zero() { set_rounding_mode(detail::rnd_mode_l.toward_zero); }
  static const long double& force_rounding(const long double& r) { return r; }
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_EXT_X86_FAST_ROUNDING_CONTROL_HPP

/* x86_fast_rounding_control.hpp
uOfDpdtWvXxVvIT0qDHI02l0CSnJCAQTgWdBKULXM3RVORAKTUuXyAEvQ6XjkR/r7gV/mxbvC7b4HgiT51bQosSwElOvRtUslljlzv03e3gqJj0cKyMANmhGsiEfYLJTH4nV408YF6MqpbF8JUXf6PQ5cof1GRYPJl2gRy2sErduKZuDCnG1MLtg74oXQ3RHHlhKXgy9Ahg8/eRKsc96E7xy/ODczBSlNsACMRx3TBwUQKNjm4no7XCICwxGAkPJS3rXYsrXmjcO7yO4lQyG47qQb9b7c5HJJ96P4iqqyh1anK+Wp/ghxTLFn6qQfdMe0DMRH/JWiYZjD2sNBBzUhIjP1FkU6yXW5uAEz3OETyrXR6s9ISXpYzFmP76c9yVthufYj7g1fG7dxCtAGZ5XY1i+uEA3CsnYK9kLLCPBje6R07oHZoKA/QHAtJx7FDqXEclThurInA59pTyy+yCwbqd4cQPkoVU4syiJqVSLBiw8hk8H1MfMRsThoMzhmHQsMLY9aMbTstpdIPJNyd5jllaA9QdLYBWeyaJDF+GVWkjqlFpTQdLWDwndhA==
*/