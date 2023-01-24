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
3lLxxLjcBf0t/tHwuH8BPhwk2bb7+oG89izzFYDvYguMFg+ZyH1/USJ3CY+qHFPbyUduGcbNkY9cOeFZo/rjKeZA0cFHLsr/UXmXHXtAsOPldk+xHU/EjcOwvGllInsUj3ddyjL85QouT5xN/n01S9TUM3SOwonY6xk9bwhc8LrVZLgDvC6JjKGuQw5kqjPQ8xygzojERfI4iCj7SZYHlVUnKYT9Syzq6A40am6tHvNM/NnfipYh6taXi/kcFiW5bScWmd2ZJ0ImEF95rsI0NfsMKt9zfOkZ/qSNqO1reZ0G3g9XUPbkpFZ8jeyb40MkP4GTdt+F2NkwSvIsxYlrp+XCNvDkSprV/zTuEVuzzylpu0IHeBekPMbEqznQ5Flo4rbV+4dhHyO76OMy3oe/H40FZ8VbgbydmxHqgV1vJiOxHHkmmRqBM5c/1azPPAXoq1n//BShdDKp5EAefcrAKuWmnRXWMtl+S3GBysPmZ2be2SEVO/6AA6SlGnOPR3RmiD9L5scBrE5SuvyJUWpcVvCu+xfA537AU3hkkf+GlXvo9EOHE7wRVzchTojxILF0geodbUyB+XiGnvRdT1FFcB7LD5A6cIgkT0rU+kryzZYNqRwBv2vDv7+iQudrKXCHRWD/yZOj6/FKyuRUzdq+0iAE7kgUOhqiOtRwfy4tKj7wNk3fdQV81/naOu66juPPQm1+xDjlACKh3GiX
*/