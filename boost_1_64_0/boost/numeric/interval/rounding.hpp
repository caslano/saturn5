/* Boost interval/rounding.hpp template implementation file
 *
 * Copyright 2002-2003 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_ROUNDING_HPP
#define BOOST_NUMERIC_INTERVAL_ROUNDING_HPP

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * Default rounding_control class (does nothing)
 */

template<class T>
struct rounding_control
{
  typedef int rounding_mode;
  static void get_rounding_mode(rounding_mode&) {}
  static void set_rounding_mode(rounding_mode)  {}
  static void upward()     {}
  static void downward()   {}
  static void to_nearest() {}
  static const T& to_int(const T& x)         { return x; }
  static const T& force_rounding(const T& x) { return x; }
};

/*
 * A few rounding control classes (exact/std/opp: see documentation)
 *   rounded_arith_* control the rounding of the arithmetic operators
 *   rounded_transc_* control the rounding of the transcendental functions
 */

template<class T, class Rounding = rounding_control<T> >
struct rounded_arith_exact;

template<class T, class Rounding = rounding_control<T> >
struct rounded_arith_std;

template<class T, class Rounding = rounding_control<T> >
struct rounded_arith_opp;

template<class T, class Rounding>
struct rounded_transc_dummy;

template<class T, class Rounding = rounded_arith_exact<T> > 
struct rounded_transc_exact;

template<class T, class Rounding = rounded_arith_std<T> > 
struct rounded_transc_std;

template<class T, class Rounding = rounded_arith_opp<T> > 
struct rounded_transc_opp;

/*
 * State-saving classes: allow to set and reset rounding control
 */

namespace detail {

template<class Rounding>
struct save_state_unprotected: Rounding
{
  typedef save_state_unprotected<Rounding> unprotected_rounding;
};

} // namespace detail

template<class Rounding>
struct save_state: Rounding
{
  typename Rounding::rounding_mode mode;
  save_state() {
    this->get_rounding_mode(mode);
    this->init();
  }
  ~save_state() { this->set_rounding_mode(mode); }
  typedef detail::save_state_unprotected<Rounding> unprotected_rounding;
};
  
template<class Rounding>
struct save_state_nothing: Rounding
{
  typedef save_state_nothing<Rounding> unprotected_rounding;
};
  
template<class T>
struct rounded_math: save_state_nothing<rounded_arith_exact<T> >
{};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_ROUNDING_HPP

/* rounding.hpp
jxM2sUiN2TwvweRctzxe+iTXEUzmWb0Eg7acF5idsMS4EdWYE0o7s8C05ryTwBzkGNac+c2cgHkIixlWtfAsBQv4a0fxHLD2qgvvXP30dFr9a/hPZh7B86P9Lc5L736sL38s4UTNwjsCTF+YU3zjplzTMANhE/a76zJGMGNhA/8zfBXXe7/Cfh7G89bIsrY8T8D0hQXuzCnPvQpWVNjdSbV5t/gKMxC25HDTjsz5/vheLmxWo+Ak7nEwFNo/591DeAY1nXuaY+jPdfvH/jnaufB+BLMSFh/4y51xgJkL6zNuynquTZixsB4+z9py7DCNsAW16hjwLAUzE+ZY69t25u4AzJmwPQOambDWwYyETQ0Iac2/2cDk+7bP/U8d5jzMXI4vXu8V72Mw2Zd+G71W85wFsxHmH2RdjXkGk/MZsqR1Pa4HmJ2wibYL9rAWwCyFWS4Pqsv1oPRzid/vKswzmK3sy6QKfoyRYgev3JnMfQXmIKyY73KOQW8gaoiwDe0Oh3A+YfI3X24s/NtnNZiJsN/Ogcu5ryjt9DSJHENHmJOw1kN2leY3HaUvnyODWAuWKTbZ7TVjmwFzFnax3tMCniNhMn5eM9+OZn7CZIzKLPfi+IwG6emUEFbz9+VNHDtMjm94RocGzBeY7Ev7qEk3uXfAXIT5zg7kXTsBJvupadn4O3NCsX3v9cbzrg2zEja0bP++HLvSz+rOWQM5dpjMiRT3KcYc+2A9neLCig7wcub3a5jsi9+90pyzUMV2vNE9wvMEzEW+71QwxzAFJvtpUH+gI+v14MLamolnVmpeGea8sIN49nQvtYt5PQR1sMj/9ocD+NfHXd5u5Le8oawTf2zmgNkBnBfFNpY0aMGaBTMT1nCc3WDWrFjsOcJe1B1RWF9g8jf187KKMl9g+sJSUxexXXuYnrCyUcX1uY5iC+ds/5//nk8aa2sszFHYtxnmzZhnMGNhwQN9PnKuYQbC1m1+F869EaYRNiB2w3yuP5ilsEa3OwfyXAezEBbVxq8H4wAzFdZ/3PCujIPym4Hz/jOD+98w7d9cdTyA9cUWZi7MxmM623kr7VoebPmJa1ppd6pOHeZ1CEzOdd9KF9bxHgcz+mv78Ow0s+8DfpODaYQ9W3TyHGud0u7Cu9fXeIaGWQn7PXjFHMZIscxRL1jrdsAchT2eVJlrOhvmIKxIxrks7g8wQ2Hfw57X5hkTZipsxfJsxkhnOOZT2MGkJg8ZB5hsZ9/9pj7jADMXdrXO0bOsLzA5Z4+21TrPfUVpl1XalHkdDpPzebHCkiOMkfKbHuf3Ft61lXbrdm//yhgp7zvpWD6fZ1qYtTDDgsabuVaUeRlz9mUS93CYjbBvfc9w7JdhVnI+Nbk8K+YpfUm/kMDzxEeYjPv6tl94TrYcgfUurPmyBhp+84CZCRt5ZSzvxQEwe2HmNuU2cD3A5PuCDjXPYZ1XLPjJz0P8BgiTc7b/2Ywr3N9htsJs01LvMq9hcux7XHILvzXDTISFPR93lTmvtJtQoa0xaw/MTpjfr/wgnr1hMkbeUeFWnM+RWEfSujsP5ZzB5NitG4/uyzmDybF76PRfzfyEyTjs/c/z5cxPxUaNXHyZ8wmT+fKl81RvnjGV932f/nkf7wEwOb5yvWbn8puO0u6Ww7B4zhlM5nVc2bphrBMwN2HNtvncYi0Yhb1f2IiyF7ZzvcOc5XxWWOPGNQ2TObHjSPxU1lblN18HbHfm2oTJMQR3rRzBtQmTYyhb8tEBrk2YnOs15Y3Y7gxM5tKGoFNVeUdXbEv5MvqsrYoV39PZlnmmjN3VZfpwfgcbrR2jmbqbnHiXgcnfTLY5eJFnDZixsCd3f/bk+Qw=
*/