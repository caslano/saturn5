//  (C) Copyright John Maddock 2006, 2015
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_RELATIVE_ERROR
#define BOOST_MATH_RELATIVE_ERROR

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/math/tools/precision.hpp>

namespace boost{
   namespace math{

      template <class T, class U>
      typename boost::math::tools::promote_args<T,U>::type relative_difference(const T& arg_a, const U& arg_b)
      {
         typedef typename boost::math::tools::promote_args<T, U>::type result_type;
         result_type a = arg_a;
         result_type b = arg_b;
         BOOST_MATH_STD_USING
#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
         //
         // If math.h has no long double support we can't rely
         // on the math functions generating exponents outside
         // the range of a double:
         //
         result_type min_val = (std::max)(
         tools::min_value<result_type>(),
         static_cast<result_type>((std::numeric_limits<double>::min)()));
         result_type max_val = (std::min)(
            tools::max_value<result_type>(),
            static_cast<result_type>((std::numeric_limits<double>::max)()));
#else
         result_type min_val = tools::min_value<result_type>();
         result_type max_val = tools::max_value<result_type>();
#endif
         // Screen out NaN's first, if either value is a NaN then the distance is "infinite":
         if((boost::math::isnan)(a) || (boost::math::isnan)(b))
            return max_val;
         // Screen out infinities:
         if(fabs(b) > max_val)
         {
            if(fabs(a) > max_val)
               return (a < 0) == (b < 0) ? 0 : max_val;  // one infinity is as good as another!
            else
               return max_val;  // one infinity and one finite value implies infinite difference
         }
         else if(fabs(a) > max_val)
            return max_val;    // one infinity and one finite value implies infinite difference

         //
         // If the values have different signs, treat as infinite difference:
         //
         if(((a < 0) != (b < 0)) && (a != 0) && (b != 0))
            return max_val;
         a = fabs(a);
         b = fabs(b);
         //
         // Now deal with zero's, if one value is zero (or denorm) then treat it the same as
         // min_val for the purposes of the calculation that follows:
         //
         if(a < min_val)
            a = min_val;
         if(b < min_val)
            b = min_val;

         return (std::max)(fabs((a - b) / a), fabs((a - b) / b));
      }

#if (defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)) && (LDBL_MAX_EXP <= DBL_MAX_EXP)
      template <>
      inline boost::math::tools::promote_args<double, double>::type relative_difference(const double& arg_a, const double& arg_b)
      {
         BOOST_MATH_STD_USING
         double a = arg_a;
         double b = arg_b;
         //
         // On Mac OS X we evaluate "double" functions at "long double" precision,
         // but "long double" actually has a very slightly narrower range than "double"!  
         // Therefore use the range of "long double" as our limits since results outside
         // that range may have been truncated to 0 or INF:
         //
         double min_val = (std::max)((double)tools::min_value<long double>(), tools::min_value<double>());
         double max_val = (std::min)((double)tools::max_value<long double>(), tools::max_value<double>());

         // Screen out NaN's first, if either value is a NaN then the distance is "infinite":
         if((boost::math::isnan)(a) || (boost::math::isnan)(b))
            return max_val;
         // Screen out infinities:
         if(fabs(b) > max_val)
         {
            if(fabs(a) > max_val)
               return 0;  // one infinity is as good as another!
            else
               return max_val;  // one infinity and one finite value implies infinite difference
         }
         else if(fabs(a) > max_val)
            return max_val;    // one infinity and one finite value implies infinite difference

         //
         // If the values have different signs, treat as infinite difference:
         //
         if(((a < 0) != (b < 0)) && (a != 0) && (b != 0))
            return max_val;
         a = fabs(a);
         b = fabs(b);
         //
         // Now deal with zero's, if one value is zero (or denorm) then treat it the same as
         // min_val for the purposes of the calculation that follows:
         //
         if(a < min_val)
            a = min_val;
         if(b < min_val)
            b = min_val;

         return (std::max)(fabs((a - b) / a), fabs((a - b) / b));
      }
#endif

      template <class T, class U>
      inline typename boost::math::tools::promote_args<T, U>::type epsilon_difference(const T& arg_a, const U& arg_b)
      {
         typedef typename boost::math::tools::promote_args<T, U>::type result_type;
         result_type r = relative_difference(arg_a, arg_b);
         if(tools::max_value<result_type>() * boost::math::tools::epsilon<result_type>() < r)
            return tools::max_value<result_type>();
         return r / boost::math::tools::epsilon<result_type>();
      }
} // namespace math
} // namespace boost

#endif

/* relative_difference.hpp
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
*/