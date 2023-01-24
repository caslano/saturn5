/* Boost interval/policies.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_POLICIES_HPP
#define BOOST_NUMERIC_INTERVAL_POLICIES_HPP

#include <boost/numeric/interval/interval.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * policies class
 */

template<class Rounding, class Checking>
struct policies
{
  typedef Rounding rounding;
  typedef Checking checking;
};

/*
 * policies switching classes
 */

template<class OldInterval, class NewRounding>
class change_rounding
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::checking checking;
public:
  typedef interval<T, policies<NewRounding, checking> > type;
};

template<class OldInterval, class NewChecking>
class change_checking
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::rounding rounding;
public:
  typedef interval<T, policies<rounding, NewChecking> > type;
};

/*
 * Protect / unprotect: control whether the rounding mode is set/reset
 * at each operation, rather than once and for all.
 */

template<class OldInterval>
class unprotect
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::rounding r;
  typedef typename r::unprotected_rounding newRounding;
public:
  typedef typename change_rounding<OldInterval, newRounding>::type type;
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_POLICIES_HPP

/* policies.hpp
Vaj5gUvYIPYLbKiYrAEmly6RIG7tVcaKn1DMezdYzQ09eS9N1MuGV7EX6+TrCPLqD90pagjXYBU8WYE9UnD6pgTq/30q34HQIyEpsD0Op9haSZ8z+sfjuKlEp2whOwD+biM2KVGyrWSZJMRx7MKduVva3U5YhYKebe+DBeqoYSA7P8D7i/Pfge+zLA+JVEEFfx/j/cFlBj4qtkimPdiZqUN/84ZJwZVcyBvUi5I07lb/3dtA4x+EjULx6r+Hkk8zr4YT+JAmmCiJeXqpJk4CY+OP9cDj/MUU7rTsmw7x8++A/K0W9KZ0ErjrEzmqRQq6YO6HJKFDJPer90VKAWnW7xexzpfTy+aX7uPYx+1BRAzgdwNLubCCP27ij3FXEmKwx0H+uJk/pgQw8Ftlj5/gj4/xx7Q34HcbeyzzxwKfB+4S/M3mZV7OH1tidhSgAnus8Mdp1OmH6Rns9pP8NrnvA2rlsNtP8dt23hkDE6CEkYoUl4iLWd4ook9kUHWmF8nT0mcCef4VKKP6Yg+8CbL/SlZsJtCeOMcqKX2mM59Zhh/qyuR2TUfvTogdszXPd0+qt8azH820fDe8bIgiC7fCL1fVUcwqGOFokv9O4YZ69KH57zHRh60v83xtZbzs2Xd4A8ue3QOTjSrwE658RjomZKeQLzthZCwyMl5MxTDXHqNeUI/3addWqCH4X/0e//sa/mNGj4TlmqbuXUl1
*/