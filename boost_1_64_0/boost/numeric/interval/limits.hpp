/* Boost interval/limits.hpp template implementation file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002-2003 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_LIMITS_HPP
#define BOOST_NUMERIC_INTERVAL_LIMITS_HPP


#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/numeric/interval/detail/interval_prototype.hpp>

namespace std {

template<class T, class Policies>
class numeric_limits<boost::numeric::interval<T, Policies> >
  : public numeric_limits<T>
{
private:
  typedef boost::numeric::interval<T, Policies> I;
  typedef numeric_limits<T> bl;
public:
  static I min BOOST_PREVENT_MACRO_SUBSTITUTION () BOOST_NOEXCEPT_OR_NOTHROW { return I((bl::min)(), (bl::min)()); }
  static I max BOOST_PREVENT_MACRO_SUBSTITUTION () BOOST_NOEXCEPT_OR_NOTHROW { return I((bl::max)(), (bl::max)()); }
  static I epsilon() BOOST_NOEXCEPT_OR_NOTHROW { return I(bl::epsilon(), bl::epsilon()); }

  BOOST_STATIC_CONSTANT(float_round_style, round_style = round_indeterminate);
  BOOST_STATIC_CONSTANT(bool, is_iec559 = false);

  static I infinity () BOOST_NOEXCEPT_OR_NOTHROW { return I::whole(); }
  static I quiet_NaN() BOOST_NOEXCEPT_OR_NOTHROW { return I::empty(); }
  static I signaling_NaN() BOOST_NOEXCEPT_OR_NOTHROW
  { return I(bl::signaling_NaN(), bl::signaling_Nan()); }
  static I denorm_min() BOOST_NOEXCEPT_OR_NOTHROW
  { return I(bl::denorm_min(), bl::denorm_min()); }
private:
  static I round_error();    // hide this on purpose, not yet implemented
};

} // namespace std


#endif // BOOST_NUMERIC_INTERVAL_LIMITS_HPP

/* limits.hpp
G7jPZ82CyZx/EnflGccHsxdm6tI9muMrradTXliU3pSDjDvMSI7d4pWGdRfmLmxzjIY1chBMzotetl4cxwDzk3E3jeR5IkN534fhm7vyvgmTubu42MILjC1MX5jXrPMcX25p5b45asd+1muYzInmZc9W4byU0Z6zszdNGSNPmMwXt7guOtyrYIbCHtUZcZxnN5h8381f+eMZd5jMly0birjx76IwW2HeR3eG84wCk+N7Nvm3J8/QMGdZQ1LrsCbvgMkYZb0Oc+Vcw+yEddiwcgb3d5iNsOujDfI5n8r4GkRYNOR8lkXdlbb1wy/WZJiVfF+fmWFcRzAZ9+2W3VdyrmHmwi6ObTOP+QmzFKZTf6cf91S1XWL3e8xdmIyt2SODwm/+MBdhS46HX2GdV/p53fWlNc/CSl+OFKt7jLmr/Oa4kD5bebeAyfnsWMI+hHW+nHa+HLOr1Zt1Hibj/jvnNM911WAytvo79+QxB2FOwgY//nGSZw2YnLNkk6qlWcthsp9+TUyasJbDHIQZz1k5kzkIk3O9skxoJms5zFLY+P6ph7mmYXKue23osIFzpoxhzCH/0ZyX8tpjX/Hm1wLWZJjMz+CjpzSsgzDZz84P3y/h/geTubu+Vx095hLMVs5ZE992/O4GsxC286nZOd6rYK7CzAc4J3FtwtyFRZh2aMOzKcxQmGHpo1Y8M8AMhD20yazBdQszFuaRVol3NZ0K2nk2Y3QW64slTP5mtLVJPc41zEjY9w+3i3JNK795ZUDDaMYBJse30M8glt+aYZayn+UMGvGsAZNj8P4Ua8rzGUzm7gLvPnsZB5iMX8cNb/wYB5iM+8xYc67pfTB7YVcvtz3LsxvMWZh7fPA9zjXMU9j9zQu4j7lW1M7PQX4fH3DdwmS+HJw9rBdrHUzmWe0rAaW5d8Dk+6aXv2fMeqa0O3yoxDbeH2Byzlw+HLPjPg2zFtaz02hLrluYh7A+tXqc49hhMu71TV4wr/Uqacfhx6pTmcylSkr9rPzGgfcOmJOcl6/1GnFeYHJ8QS+z23JeYCbCGr+eFM91q7S7VfZSIPMFJsc+u7hTzP8tESZz/suEUVx/KcpvBh584sL9QRlfwIgNnLMcmKuwV8Vv88z3A+YgLOdyKQvOWWXtM1G5gy6MkSdM5oTXg9Pc30NgMu7XZlxcyPUH0wjbE92D67Y3zFBYgc/JW5xP5TeneKQU3v+UdlMvry7LuVbe9yjf4AW/TyjtwrxG/MM4wGyENR3UK4LrVmm3s1mghrVV6WeL3615972stOuReessY6T0s5Tl1xM8eyvtTN6/5JkoX3mfY+9yR1h3q2i3u1e0yGTu/TD5vnHTVzRl3GEy7qMr7fdn3GFyXo7NiWSeVVPaJb43HML9r4pyXrr86jHvxTBjYbOOffvEvVHpZ3JQQ3vWa8WaDW/0nmda5X3LG83rz5qlzEvDBZGnedZQfvNHkvdy1jOl3avUJhZcm8q8aB7UzeLaVH7T+ErtXNZ5mKlsdztwF/dipd2sppVrsQ7Cisr5LCjLWvBVabd48/p6jHtV7ZrVVtOb9wdbmGxnX2vrWu63MPm+bphp/q1AaWc703U+cwJmJOxN5MiSvMso7ZbaODTjORImcyIzKvI/PHvDbIV1bfG5B/dpmJ6w9ebDnZkTSrtRmlerGXeYlbCEbzdb8Dut0i63yERDrveqyr14W+Iw3nOUdmvbD97G+ME8hC2sWPitxLWadk22O1fnDucTJvOlzq6O9Vl3Yfpyzkz+seUaU9qtCWuyn/OptOuVHc449FbaNfhn30HONcxA2LSjs/mbcTATWc+sPZpw/VVT7rDlApmDqxRrs63Keq4x5Td3NTk=
*/