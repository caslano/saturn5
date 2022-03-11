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
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
*/