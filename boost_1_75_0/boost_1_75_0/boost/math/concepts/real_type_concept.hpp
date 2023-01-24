//  Copyright John Maddock 2007-8.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_REAL_TYPE_CONCEPT_HPP
#define BOOST_MATH_REAL_TYPE_CONCEPT_HPP

#include <boost/config.hpp>
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4510)
#pragma warning(disable: 4610)
#endif
#include <boost/concept_check.hpp>
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/precision.hpp>


namespace boost{ namespace math{ namespace concepts{

template <class RealType>
struct RealTypeConcept
{
   template <class Other>
   void check_binary_ops(Other o)
   {
      RealType r(o);
      r = o;
      r -= o;
      r += o;
      r *= o;
      r /= o;
      r = r - o;
      r = o - r;
      r = r + o;
      r = o + r;
      r = o * r;
      r = r * o;
      r = r / o;
      r = o / r;
      bool b;
      b = r == o;
      suppress_unused_variable_warning(b);
      b = o == r;
      suppress_unused_variable_warning(b);
      b = r != o;
      suppress_unused_variable_warning(b);
      b = o != r;
      suppress_unused_variable_warning(b);
      b = r <= o;
      suppress_unused_variable_warning(b);
      b = o <= r;
      suppress_unused_variable_warning(b);
      b = r >= o;
      suppress_unused_variable_warning(b);
      b = o >= r;
      suppress_unused_variable_warning(b);
      b = r < o;
      suppress_unused_variable_warning(b);
      b = o < r;
      suppress_unused_variable_warning(b);
      b = r > o;
      suppress_unused_variable_warning(b);
      b = o > r;
      suppress_unused_variable_warning(b);
   }

   void constraints()
   {
      BOOST_MATH_STD_USING

      RealType r;
      check_binary_ops(r);
      check_binary_ops(0.5f);
      check_binary_ops(0.5);
      //check_binary_ops(0.5L);
      check_binary_ops(1);
      //check_binary_ops(1u);
      check_binary_ops(1L);
      //check_binary_ops(1uL);
#ifndef BOOST_HAS_LONG_LONG
      check_binary_ops(1LL);
#endif
      RealType r2 = +r;
      r2 = -r;

      r2 = fabs(r);
      r2 = abs(r);
      r2 = ceil(r);
      r2 = floor(r);
      r2 = exp(r);
      r2 = pow(r, r2);
      r2 = sqrt(r);
      r2 = log(r);
      r2 = cos(r);
      r2 = sin(r);
      r2 = tan(r);
      r2 = asin(r);
      r2 = acos(r);
      r2 = atan(r);
      int i;
      r2 = ldexp(r, i);
      r2 = frexp(r, &i);
      i = boost::math::tools::digits<RealType>();
      r2 = boost::math::tools::max_value<RealType>();
      r2 = boost::math::tools::min_value<RealType>();
      r2 = boost::math::tools::log_max_value<RealType>();
      r2 = boost::math::tools::log_min_value<RealType>();
      r2 = boost::math::tools::epsilon<RealType>();
   }
}; // struct DistributionConcept


}}} // namespaces

#endif


/* real_type_concept.hpp
u/DpKF6XrsF4kPnP5CfTvnifF+XKoH8RW7CVBdMFXj1ydvvJDIrkkScjH3Iowc/BlIM2C7MQ/ZZxsVpyxTm1F89+bvkqFRULxAO1L+KCDsvSqHputhovNJqatTuUTArWq6pmhe0dB22M+ShfYgjtZ8mG8C2Htb+cLjwpoHSOWRnIKeVvYs4EBGhfOcyff0hrxF9hyOR2e3xsZDjJqK/aVUk7wFxBzaN85aIRLU958HUG53He+QS2O5+PC/iwBurZooUMHSSKOB43aP2288zqXP/8/t0qHRKzjgzuxxchOiX9rtqZahaw7sHcOtZTYZsGJRrPbX9CgbNRoLq89+scgggwZg2uNP1dV1dHYM3ktvS7JxQtZBUYNJ7azejrhodI7fK2SAZVz4yh8v4g5VgOe5eHer7HM+VzLQ3gyp5EgRh+bqGgHPcwFKpGdFb6D09fhmcB249G5ya/WvbuegqAxhiIq7YBpGUzPGNKUQ8J+Av2WbeAGOn/E/v/sfEmIPrvvXXBf+mtm4K9chuAOt/lJbnHmj8CVIVZjfhO3ZWj/p5bN19Q+W6jnJ+2Q9F26c7XFWDwfLfVaEX7iIr5VR0d+3UqEQk2+mHoZiP2Qz9PzM9/5NaJ5gBNtAMca61ujYiJ8bVdVgVeRrtpnHM6oHiNoMdEtqigx9kEIrwHcBXNGOSLYrfSf8sxOpAjG1vqmZIYRnCNQccJKvnA8XYw
*/