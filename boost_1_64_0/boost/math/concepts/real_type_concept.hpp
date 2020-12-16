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
8pdJ/jYjvWwOTCeb8S5ki84Dbg3MJ1vo7sCJwGK6r6bPR/EkC9I3meIpBtqAJcC+RDzfHef7g+aCFoOeB60FOWC/qwUtAi33woYXtO2BFoFaHLADATuBvL1vANiC6y5QSvWQ/W8Z+LKAyhmwm4Ha8N8LKsH/IvDVgLpxrdoIPbi/ArgC91YBVwLXAJOD9kE8WwJ6HvQu7ufi3lr8Tz5z0KZoBw7gfirshzmgclDbTCDudwHduO7A/0bgClwHQN24Xg56DbQGVLQAfKBsF/yBFoJ3LnAB7j0PWRYHw8B1L3AZ7q0GJu8xaK/sAaWeBZskrkuAHlCfC/9xPQDswPUiUBWua0EZsGG2A5fiXidwJXCpzua5Gvc6gojrRcA1wIyzETf+P0X20FyQB/dKgB3ALpAH/5cCV4NnJTBpP+gY9zLOgW7w3wkqwv/+YD4Ce/CsMciD/4tBQbuqH/cCoF5cDwDtU6Bv/O8AXzeoHNd+oGp3bQfmAosWIu2gTlx7gS7cawMtxv8u4HLQKlA3nvfh3jJgP3AN7iWei/TiOgf4IzDRibSAckFVIBfuNwIz3IgPmAt0gVQ77yLgXFwvAS4C72ugflAvrr1u3AOlnof4g+EBfwQuxz1P8B6wC6jahhNLkW6gff9wG7EdzxyglfgfIHuxH36dpQj/AKQF1IL/tUAvyAf6BM+T82x4sxmyK68C9ZYCQWtAjvOH7MxV+O8FLQFl4LoXWADMwvNckBPkBgVwvwb3O0DdoBWcbXohcDFoBWglqB/3kjpRf/A/B5hUA1mB2cB2YCeoiuzZPcFr4GtA3rbtw71yYMYFiBfo+Iu9c4HTcsrj+PO879xqppqmaWYa0zRdpVLTnZpVEUIUhRClmUmt1NRMidBE1BKSKNeNDSE2trXWWobFtlg71i2LFbFZQnZzz9rv85//c97nfebMeCP28pmX02/OOf9znnO//f//c8BNuI0H52PemuD1L/oKf1fgX41ZjtmAfQ24GXROoMzAGuxFl5EW7CPBUeBkTC3uVdir+ft6zBbs67E/TbzbMdlj4TFjJmIWY9aMbeLf/sf2/xVz9sj+P5879Wfnod+f5s1fZeVTT507o2pSRWnV/Lr3/KsCZwMVlrOBLCa2LYWxvcPY0NnA/nkN7hkI9+3PBoi33n4yw7L/zi7xJvVg+nQ/WVo+Rzfhks7zCxpMJ+F3b79CXPX24GsjoT24pi3TkjZN1jemK/M7pMsvs+FRe5kV2dI18wxN2jenrWgPpO3VBtJWbEvbrOlliZZb8R5I2/wke9qG29JWWTUn0bQN/w5pM3eo6B6/WAP0wbQlbWPDadOzi5baT/UsAvuI1q3BU4S+QO2us7Aubbt9LhF3fmc5f8glbcvDaauM66PfOJYQ3pw/dHI8OglnPX9YvptlzHfjzh86Ydpq/ME+vin8vr/mbY0tbxL8m8fINbuRrzV7OF9+na1NtdfZBku+zBiRwPi/YTfytuF7ylt1mj1vNba8McYkWm81u5G3mu8pbxOb2fNWa8sbY1SieavdjbzV7uG8GT6FdrIDfBlZzD0cdmyJ5U2OslknTZ9ZVTfGnZFp9LDt65FAvo7OkrsKp84oC+QnQGPyCm0VCO3MsnK+ZLuvMBT3p22EvsrRsbYN+L747ythMwNhM0Nhde5gfQaNjtNviX97J8+JSPjsQPjsUHgi51c589Qzyk34XeKfTeioWYvN7fLN43qW1hnl6uucm3rzyq+tll+O3qmIP25aTkqbCVIenrtxyzbzmuRTx9hWdesVfexqWpR4Fdt5a4IiqXdWxsF6n0T4+nXfj3zngYdLmKOiF1FDDzGDv445zW3mrHdTnSfBDpFmTkY=
*/