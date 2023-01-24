/* Boost interval/detail/interval_prototype.hpp file
 *
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP

namespace boost {
namespace numeric {

namespace interval_lib {

template<class T> struct rounded_math;
template<class T> struct checking_strict;
class comparison_error;
template<class Rounding, class Checking> struct policies;

/*
 * default policies class
 */

template<class T>
struct default_policies
{
  typedef policies<rounded_math<T>, checking_strict<T> > type;
};
    
} // namespace interval_lib

template<class T, class Policies = typename interval_lib::default_policies<T>::type >
class interval;  

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP

/* interval_prototype.hpp
nsiXqism0TsAQYX+QKQCxVYBIXScQ1S1kWDbDhoqzbcTcCiMfp0LcQUuzEX/Z716FR0gqqUVWFdWF7ywbB+MwzbNnhEFwDj8rI6GPpd3Hs9Q1vgxhTSzIzbPIcs9uc57cmcJPWM4YCh9gpMzIlfmlAyUrmbV4uujUtUXNnLPRvg20LVGAY9LzJHNo7LhNyz5EenhB3M7hvJ3cibO5cVw1uOa/afxZnHuF5Vmqt2BnBR3WhyNGATImpGJU73ptiIcHJ2n5EzgNGtMPi8ReDo9C32hEmoph9zsiGYPjse2pMWnUDQGe7sxqNWYYh/Krr6Yq8rN6nmhzE/RvMGjyNj12iI6gy5G/5XxYvRxP3E+X9lGuv9c0qk6g0ma4HFomzB1ir+swse+9LA9Eia1xdyhvXFbceqxMs227D+kzRwLHYe1gDVwKQG77YMLvFpV6T4eiADPlGGazb2ZNZScKJnViw6tvWii6jcXzmh6Gl9pxc8rbMt24+dLctxgjUALcBvz/C6polK5PinUpgW6egCCZf+g93rBO3gKKstV8p+htnVVWCG35PuhLtsHn03rXmv7YLNeJ1cKp8zAr0FL1SSbe2ekH352fsnBi+nLD7bhi/DZp8bLbKesVWOYmrPFtrQvxqg59yxI8pQ1LkrCMsB2/L4H3rN6p27GNJ4ueBmHOV1ChZlK0VA21PlZtNIJzu/gxbzIl6Q68vrGnv1k
*/