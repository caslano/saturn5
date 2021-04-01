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
ZxYD++B7lTJNjmkeQWVS25lQpNZGPCHJM2jDc8tUK1uUo4HYPe6XM2ainw1uoPRxgOk0pvRQfZj4AW0VSZT35KVz+auiwqthHuMdDy2nnE4S1zQz7ypFjie2B/f2hE4I0XuYrBI03Kl3rPr55Iu4oI3QTrgRd1hBZXf7sZwtTcFhcE6mpWopjMS7wToLWMNFH3SLpX2d6R1Cr4IuitLCi4hjFtcaIQK51gG5j0ZEtDR6caw3grF1RL4ywPv//jlpjxILfW3bWeB82BiucJrzrTWzOk9F3SbB+NkQaelpv3RuvQcpzSQERSfEBFBxmwUMIfrprbj6OkiWWTSul2J3jd+1UkW4GPEsD5fqnMkatDNvNop+WDR6EC5LCEaPdM5mJGcdMIfURTD6DCoU0DTP2HxsRaK6tKY7wEvI4fRaSlZN3puA8XNrUTZ9WzbhZ2RKNLtdczjvMEgYgRYfiSajlYv9bDgq9TI9iOtrh9Y6/JSXSiay4KcALZQTvdWTYFefx//YD6iGVQJe/8fJTVoFS5kczX276J3CRw4bdSm2Rx1wgm0r7xVNrl/QpQ==
*/