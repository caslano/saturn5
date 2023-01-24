/*
  [auto_generated]
  boost/numeric/odeint/external/vexcl/vexcl_abs.hpp

  [begin_description]
  abs() specialization for vexcl
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>
#include <vexcl/operations.hpp>

namespace vex {

template <typename T, size_t N>
typename std::enable_if<
    std::is_integral<T>::value,
    typename boost::proto::result_of::make_expr<
        boost::proto::tag::function,
        abs_func,
        const vex::multivector<T, N>&
    >::type const
>::type
abs(const multivector<T, N> &arg) {
    return boost::proto::make_expr<boost::proto::tag::function>(
            abs_func(),
            boost::ref(arg)
            );
}

template <typename T, size_t N>
typename std::enable_if<
    !std::is_integral<T>::value,
    typename boost::proto::result_of::make_expr<
        boost::proto::tag::function,
        fabs_func,
        const vex::multivector<T, N>&
    >::type const
>::type
abs(const multivector<T, N> &arg) {
    return boost::proto::make_expr<boost::proto::tag::function>(
            fabs_func(),
            boost::ref(arg)
            );
}

} // namespace vex

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED

/* vexcl_abs.hpp
oxPVEiJdikjQm8Wqm0JgTRwSIzXpq3S9dWaK7D3PAUCwjDY0tM/Trhi+0pBLn+1XzNHpOJPgQdGltWYBaG45np0Hz0zybGCeNPK8wAir/xzNqOKqr3nOvy1vaFTxwgpsXa3jZ8oDRjbu+JZZDQT2vVq7caJaOzRX8HkYas88otL8CuQ3pTeoNY/RsWF99Hp609j0/z9hs3OEio1WopRBbR283JO81F98uHCu0ZTRB55cmNiM4ccVds3w498u3fDjE8ae//MrsWfHlzSe933B0XG4VcOP3TZ14112qIYfshBk+HFXUUPDD2ixWeL/tf8ONdFiTw8P7L+W2H6gHEaCNmNHfyu69hverOiaHSS6SvaZ7uMGnDjdU2fWkz3dwVH1qgzbEIWVHAX7zBDlv2v/+/KbUYOHEvTH/6NsFfMvQzV7lUy5TTqfxz8xEqEsO0WE0vMQEcrrBzmh9FzKLTUml/B597mhKsEUjyS6mAlSB0lPaSWBghwPrP8vF5S2fNi8pcZjoftwmi1EZfkO5jmhrrlVa6huimy+CHVhjMogn385Sde01H9UoNUgKcvuLtY3T0efJj0GacxyWRoUFXzjBd2oeRRz473yvmdZniiW+aTlTawqmdGPHLqhrMNauqrk8r8lwKDn7HBm0FMgb96sSal7WpGklCPrUurr1YyfVHMyubSIk8nNmzmZzLKoZFIkMjLRDXpIaIrZ3KRB
*/