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
AE9os6YVlIn9679lbr3f0EpKNdq3w44cV3tEZMtD2TfBuKRcEAKkt1Hw+rM0OLjS3iATz3JpAcCueignOYSSl/VhhKGOJXh30HqJPbUT1upXqSUyhQ5l7eX5X4YdZT6UpKLcMsXFE4AjBiv28hdgjnZ7AFFo3NhbdwW9N4Ebu8gd0kR3USZvzkBQCTyt1To042mEN7GzHdVs6ncOJWmU1/NORdYhgRtDOeeh1iqQ44jO68VeuvjnNGHImHeU08ynRZo4IoYozqXfZWXYMzErhzVxWu6TxMh/WBZwh8Lnrt24Qe6neKQQmIGiv5AxIEQzCenakjEgnnS0cQKcqNarxa42QZmf4LddHZL2qJq6ETacrZ7iKSiFxQJgvEyDdmDbCMm9naMiOaEXRAPYdEje2qQiL6KErVNLBr36fg2hjzw5SX3h/D7yPGpWv6ny1W0XMZxUDrhEuUyn9c10tF/DWONsBGRDgCbnoH1Xh7VcJl3YrRoEiwfOzU8sy4c4x4yxenAGJA5G5kW8AACC9V+fnnysM40tLyxmCPnBPOopgPdI0bKFru7lRU52tw==
*/