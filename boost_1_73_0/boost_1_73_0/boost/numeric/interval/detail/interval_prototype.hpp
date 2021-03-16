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
Vke8cd+jyO/q9MqOIL9TIt6xSegJ15oF/bGSnIr074t4x0KBq7fTaYh/uqK/6ONznRzWrfnhlU7J54ed3A89yGetD5+fIZ8/VmDrOr2wsxTYcRrsbM1/whbwo+6/c1CPczX7zzK9egv7exH/PMQXcSdkCJoeD90K9iwB6Po130A/EjJAJvhmE+KeH5Fz6I9Xe21S9fPKaiNbIsTFA/4L4W2NEI+94BsvTohcpOAALz+cbRHi2gPx7vVxkAwwuOw=
*/