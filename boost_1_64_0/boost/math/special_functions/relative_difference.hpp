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
s8chVXrMiP5cLBIUaDAi4G8prsG9yP9KHz5rLNdrM0eb8tG/AXMi+nmGOGm6TInoe4UOBf2v0buMcxiIsyVOjjLb97tA4GzbBFF5L2+nDznzlps/x/XCSk1uvl5PGtO/MqOzzFc2r6o2RK+h3evJxf2M+xc9p99xnjMQXK+Jna7XvQ7+7VqgaMwbRP2vwbnt6prnDBy4n+tu2lxmwYAssSdcIFC1vbntNS4qH/KcdQHnXOmcfr/hWqR56t6uQwIXkq/F4Rs31gf2GDAnchPXoWOSLBlf0HEXwvF7FO3bvo8c3ec5SfyhXmuosOtng1mO6bCMmC/uyxEPqjczCmpUY3UxObq2+izVNuL6SjNkZl/cNqn2Rc74eskirI4XNC9IUKDBiCWbF1JrUpS4sXHouU6mRCJqzR45KpS9Xoy5hrwOufm5xSVPjR43P499rEif1zl0SYdcL3T+bz36GUqc5ZrfYcXGBeRBmRP2wtqnSluOUyLyuzH75PjfGu/wRdQnal4SdT3emO4l5HNJ7cfEpEvBtVanz57r7ZAKXWZE1fvMi10zZCnT5oT+Ocwxol5rbkyCAnX6hF3z12ePHDV6hIPGlSzHtCmex7wltOH1hjgZynSZEvJatkOaEm0mBF1DOyQ5osGQnhf3GXuKmKHBEQPmTG50gcD1bcOn6r43vcfcpE6fGddYf+5MsX1JfSR9Xe2we2VjeA/XXsv8Z3YB3wvDvmeWXYsE/u29AnFS7FzI92fbo8/4/kbzq66p9Xve6Po97+BSvhndQP6uwwZLUuZ7ixH3uoC6ceT6bJIce49DldmlXGs38PwVzaMrXSBwuKmv1OhcwesuIc+d4V4c02LExP+miLpvXc924fgzXhsrXrN6zIg5d4c0JcKXEf9KzieqDvu2ZUYsOGNfkiINhiy5V/QCgbPYvIp4JClQI+3+lQPbGZGzXHPciwxHnmsyZnFt190N9EWcm1/dMaQpUmdA7tpiO+bgxvp2E6/9N5WfOK1rugauZdw42zHbN3YsFTrsOjZF0v9WaJ0l3lXNc0aOPXMTz1/DNU6bE2ZXc92oVfKq2me6Xm9+SI+FXA60mafMmIC2t9gmxwkB8bdIUqFN+bq2nJC4vjoyIH4D8ajQYkDwRs4nSZ4qXcas2Lyx/ORfp8emenTcp3tHP8vaj5zRP/bJUaXHjMh1jAV7ZKjQZUpYbme4F1l2r2f/DeSi73HKpOzLyrvEgshpvjcUz/+/vTHF68nH48jp+F1PXXwdu6YtfY8THk9tg9cXx9ebp7HWa8cbbHs8tR3rY+gmjv/i+QNbbJP5gja4F/1/6A/jWxvPu5lTcTXgxt5w7efPb13T+QNH7kGW5vpd59vXKNjHBvfi5jcVnwINBv+3hvxsMpRoMlmvHz/D1u3VgyxVBqzW66TvdcoxaYrU6DJldPZ/10inOLmtefVZ7djXuqNaEl2vfz4gz9C+47PF8HXH//lq30IMlkRvaRy5F1mOaXNC4FbqytmkOKbFCSs2t9Wten4/Gwj5GaRa+V/uZ7l/7Yn/XXL9nfMFcvadTZUO8x19voV4HJCjTEftz9zGPCFJm5h+nWGXFHlqXEM/9pneztjfXoz1GvIRS6LaaDEkfEfjQnlXDe/ifGZ3tX+9/nqHA/JUCa/XWdcYsSB6d2Nq7AfGOfEic+il5w/svfj8gZj+Ha7XnvfUdUrozuISp82CiLYz2t3elgvHrzt/IGdboUNGX1KOOznt/67+k/M/fA/YYJu49hcMqXq8uV57n+aYDs1dfWZBVHvX514Eb2GszhZ7x9xm++XmLgdEtZmnQkdty+rXc86EFUv7G2f/dx37jdknw1TeN1aD0Po+BAs=
*/