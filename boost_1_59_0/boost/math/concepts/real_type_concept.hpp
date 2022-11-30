//  Copyright John Maddock 2007-8.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_REAL_TYPE_CONCEPT_HPP
#define BOOST_MATH_REAL_TYPE_CONCEPT_HPP

#include <cmath>
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4510)
#pragma warning(disable: 4610)
#endif
#ifdef _MSC_VER
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
      check_binary_ops(1LL);
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