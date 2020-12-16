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
lZaPidUsNQ0xPwZWo/VDBvgMlHwCPqu27yLKtzruDzwTUb/UmpZaPOj/MP/e9lvLUmcE3Jn79S+E0woozHx6DPSZ3+tbagKN9+e7G6P8RP0aDN4GfoPXzlH6N2WplYn1g9rEUntR+gX4hWifhSLap4nJswbGXzJCvtS3tNRkhPwb3cpScbtn/vyVv62ljtV1788f2M5S6xP6owH8GFxcFnH/VNZSC9jR5YvnLLUk0f4Z4MsQeBP4kfq6v3zI5C21IjH/m8D3Ctp2nH7lH7LI9VsG+D26bv3zT+1k4ZqYf8B/UdHzo7GzpRLU+NyZnv+jO9PzP16g+UkGTzG4y+B14PMQ5WsBn42QH8ldLTU5VT7gC1P6c1d//bFQxPhtDGP8EeUbBV7E5wYR+qNWhP1J8BvASf8A8KkIvA08Rcn/EXr95gI/mFi/JUoWRFi0f6DtWmo/yr7ZDf1HyV/gM1HrJ+BTUu0P/AIi/1bZUrNT/HJoX/WXbxVL7UzgSTg/GsT6QO1uqSWo/gF+JbV+35NZvwNv4nPzMP+/8Pey1Ll29Pq7uS+zvt+XWd/vZ6nTkXihCFwdZKnDx41un9HDLTVJLDr/1tHwH+CPmSPka+N4S8VQv0SUfQnnyPZE+zWB70jZnydZCi6ayP6rnQz7mBh/iVMs9Q0xPlKnIn9q/Q58U8L+HjgN45PwH7aBLxty+5TvdOgvfR2hn8+AfUHpBwZPAZ+Okj/AVyD8wy3gCcK+GmX4A2fS5csAn5hofxd4gpJfZ9L6rXUmrX/UWZY6BB/7Rdl/Z9H3bwOfgpJvDB4/m9H/Z9P8FMN3ga9O6S/ga+u+i5h/51hqc6L9GsDnpdoH+I/B9fT9xvd5lroKieeKWr9dCPlqRcuX9sWWOoGQH/VL4F8cF/WI8r/AOX4ToV/ca+AfwcVHVn/7YuBG6A9CviRugn+p1z/z1/a9hbY/Bm6h+zfD4LVb6PHTYPgt4KsR/MStlkoT7d8AXqDG9230/B8Avjkhf5u30fZrh7n/KPCJCFzdjvUDUf448MmJ/ksCf4fyn99hqUUJ+Va/gy5/A/g2RPvE72TkC4OngLeI+Ve7G/5Fqn73YP1M9R/wpJ4fEfbDvZbalihfA/hyxPo7eT/2hyj7+gFLbUjNH+BzEvqv+QDtn+wAX4Xov+SDlnpgQqX2ivKfPAP/Mup3RIR9mnwO/gtif0s9D/8rIX9rwOe3gY3T334deMlSOVzMHOUffh32tycb4/39T+03Mf5RWW8MJPr5n9+Ffrei/YuJ9y31G/C5ouTLh+hfan0JwX0f0T71j9F+RP9mPsH4I/ZP45/Bf03tDwHflBp/n1tqN8o+Bn4jsT/b+ZLOvzaK9SOxvzwKfAPKvvgK/YuLJF79/DOJHyzl2viMGD/Jnxj75SfGv8Pwa8CnoeQDg7cYvMPg6me6fImfGf8wg2cYvMbgDaZ8LYbfYXD1C40nfqHzH2D4GeAnEv65xK+WmpG6P/CLiPiDOITL7sT9m8BnJsZnB/gIMT+bylbjUu0P/ClCPrQtm15fAKfaL27bZPkHgF9jE/EB49L5t4CT44fB1Xg2aX/Fx6PbJzG+raYk9k9rE9hqS2p/B3jTjl5/pCax1cqU/x34HNT6h+EnJrVV3Y5eH2SwebAvYT+pKWx1KGVfTUHnr6a0yf2XJINnGLzO4C3glPxvA7+P8I+0p7LV6sT+SXJq9D8lH4EvQewPdYBnCPsuM40NF2N0/MzAdLa6gShfYno7tM/67k8Bnw73nzkCVzPS/Brw1Qj7JTGzrU4CHo8q36w2Lb+Bk/Ib+M1WdP3rCVu9S7RPc3bMDyr+Yw5brw+mj+o/4IPE+M/MSY8/F/g=
*/