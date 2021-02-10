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
EvnO05vBQekd04o8Axtq12DCdth0m5P8x9waSQZqR5Xn5ExDvcXEG2R99KmauYtwrW5KLr+xJiRMSkXmVdqSgCOp3lAGmdzWZ5wiZzu5bUXhfBwMQqi712/1Z2WMaTNZqL/65zp0qrva/tcIhHlqxKnmzrfBbDIJpsNaddpRknkYjePwr3CwWgYfxuGp7gYHk+BLGA9WURROl/FitooGYTwcRaf+s/LVz0meC/HaTpfs9+fmVshhOA+nwwVc3OkH/wyjD8FyNIHVIlzEyzCajKbBmKbaNZTpk7nIaM/95R3e/bvkWP271LsMuqbevgFi+eVo9yCW30RtSnLWFVVAVxOuAT/RqnZHOsiYO3oyOh65bRLU7HhBZ6eAyu6loZZVh7XH7/BIZkpvEEklK8iFqGK4KYq2mS3Jb2esvQnCvXPQk3Ik0HdQSwMECgAAAAgALWdKUmeZlqfcHgAAsVYAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9GSUxFRk9STUFULm1kVVQFAAG2SCRg7Vxbc9tGln7Hr+hhyiXZS0q27GRqXLGrZEmOVdGFK1Jxsh5vABItEiMQYNCAKGb//J7vnO5Gg5JlJTNTtQ/rB4sA+3L63G/Nb9S0qXJVa1Mr02S1VldZTv+V1SKpo2g8
*/