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