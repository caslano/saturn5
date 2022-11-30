//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_WEIBULL_HPP
#define BOOST_STATS_WEIBULL_HPP

// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3668.htm
// http://mathworld.wolfram.com/WeibullDistribution.html

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>

#include <utility>

namespace boost{ namespace math
{
namespace detail{

template <class RealType, class Policy>
inline bool check_weibull_shape(
      const char* function,
      RealType shape,
      RealType* result, const Policy& pol)
{
   if((shape <= 0) || !(boost::math::isfinite)(shape))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Shape parameter is %1%, but must be > 0 !", shape, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_weibull_x(
      const char* function,
      RealType const& x,
      RealType* result, const Policy& pol)
{
   if((x < 0) || !(boost::math::isfinite)(x))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Random variate is %1% but must be >= 0 !", x, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_weibull(
      const char* function,
      RealType scale,
      RealType shape,
      RealType* result, const Policy& pol)
{
   return check_scale(function, scale, result, pol) && check_weibull_shape(function, shape, result, pol);
}

} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class weibull_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   weibull_distribution(RealType l_shape, RealType l_scale = 1)
      : m_shape(l_shape), m_scale(l_scale)
   {
      RealType result;
      detail::check_weibull("boost::math::weibull_distribution<%1%>::weibull_distribution", l_scale, l_shape, &result, Policy());
   }

   RealType shape()const
   {
      return m_shape;
   }

   RealType scale()const
   {
      return m_scale;
   }
private:
   //
   // Data members:
   //
   RealType m_shape;     // distribution shape
   RealType m_scale;     // distribution scale
};

typedef weibull_distribution<double> weibull;

#ifdef __cpp_deduction_guides
template <class RealType>
weibull_distribution(RealType)->weibull_distribution<typename boost::math::tools::promote_args<RealType>::type>;
template <class RealType>
weibull_distribution(RealType,RealType)->weibull_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const weibull_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const weibull_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   using boost::math::tools::min_value;
   return std::pair<RealType, RealType>(min_value<RealType>(),  max_value<RealType>());
   // A discontinuity at x == 0, so only support down to min_value.
}

template <class RealType, class Policy>
inline RealType pdf(const weibull_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::pdf(const weibull_distribution<%1%>, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_weibull_x(function, x, &result, Policy()))
      return result;

   if(x == 0)
   {
      if(shape == 1)
      {
         return 1 / scale;
      }
      if(shape > 1)
      {
         return 0;
      }
      return policies::raise_overflow_error<RealType>(function, 0, Policy());
   }
   result = exp(-pow(x / scale, shape));
   result *= pow(x / scale, shape - 1) * shape / scale;

   return result;
}

template <class RealType, class Policy>
inline RealType cdf(const weibull_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::cdf(const weibull_distribution<%1%>, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_weibull_x(function, x, &result, Policy()))
      return result;

   result = -boost::math::expm1(-pow(x / scale, shape), Policy());

   return result;
}

template <class RealType, class Policy>
inline RealType quantile(const weibull_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const weibull_distribution<%1%>, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, p, &result, Policy()))
      return result;

   if(p == 1)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = scale * pow(-boost::math::log1p(-p, Policy()), 1 / shape);

   return result;
}

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<weibull_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::cdf(const weibull_distribution<%1%>, %1%)";

   RealType shape = c.dist.shape();
   RealType scale = c.dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_weibull_x(function, c.param, &result, Policy()))
      return result;

   result = exp(-pow(c.param / scale, shape));

   return result;
}

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<weibull_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const weibull_distribution<%1%>, %1%)";

   RealType shape = c.dist.shape();
   RealType scale = c.dist.scale();
   RealType q = c.param;

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, q, &result, Policy()))
      return result;

   if(q == 0)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = scale * pow(-log(q), 1 / shape);

   return result;
}

template <class RealType, class Policy>
inline RealType mean(const weibull_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::mean(const weibull_distribution<%1%>)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;

   result = scale * boost::math::tgamma(1 + 1 / shape, Policy());
   return result;
}

template <class RealType, class Policy>
inline RealType variance(const weibull_distribution<RealType, Policy>& dist)
{
   RealType shape = dist.shape();
   RealType scale = dist.scale();

   static const char* function = "boost::math::variance(const weibull_distribution<%1%>)";

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
   {
      return result;
   }
   result = boost::math::tgamma(1 + 1 / shape, Policy());
   result *= -result;
   result += boost::math::tgamma(1 + 2 / shape, Policy());
   result *= scale * scale;
   return result;
}

template <class RealType, class Policy>
inline RealType mode(const weibull_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std function pow.

   static const char* function = "boost::math::mode(const weibull_distribution<%1%>)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
   {
      return result;
   }
   if(shape <= 1)
      return 0;
   result = scale * pow((shape - 1) / shape, 1 / shape);
   return result;
}

template <class RealType, class Policy>
inline RealType median(const weibull_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std function pow.

   static const char* function = "boost::math::median(const weibull_distribution<%1%>)";

   RealType shape = dist.shape(); // Wikipedia k
   RealType scale = dist.scale(); // Wikipedia lambda

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
   {
      return result;
   }
   using boost::math::constants::ln_two;
   result = scale * pow(ln_two<RealType>(), 1 / shape);
   return result;
}

template <class RealType, class Policy>
inline RealType skewness(const weibull_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::skewness(const weibull_distribution<%1%>)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
   {
      return result;
   }
   RealType g1, g2, g3, d;

   g1 = boost::math::tgamma(1 + 1 / shape, Policy());
   g2 = boost::math::tgamma(1 + 2 / shape, Policy());
   g3 = boost::math::tgamma(1 + 3 / shape, Policy());
   d = pow(g2 - g1 * g1, RealType(1.5));

   result = (2 * g1 * g1 * g1 - 3 * g1 * g2 + g3) / d;
   return result;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const weibull_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::kurtosis_excess(const weibull_distribution<%1%>)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;

   RealType g1, g2, g3, g4, d, g1_2, g1_4;

   g1 = boost::math::tgamma(1 + 1 / shape, Policy());
   g2 = boost::math::tgamma(1 + 2 / shape, Policy());
   g3 = boost::math::tgamma(1 + 3 / shape, Policy());
   g4 = boost::math::tgamma(1 + 4 / shape, Policy());
   g1_2 = g1 * g1;
   g1_4 = g1_2 * g1_2;
   d = g2 - g1_2;
   d *= d;

   result = -6 * g1_4 + 12 * g1_2 * g2 - 3 * g2 * g2 - 4 * g1 * g3 + g4;
   result /= d;
   return result;
}

template <class RealType, class Policy>
inline RealType kurtosis(const weibull_distribution<RealType, Policy>& dist)
{
   return kurtosis_excess(dist) + 3;
}

template <class RealType, class Policy>
inline RealType entropy(const weibull_distribution<RealType, Policy>& dist)
{
   using std::log;
   RealType k = dist.shape();
   RealType lambda = dist.scale();
   return constants::euler<RealType>()*(1-1/k) + log(lambda/k) + 1;
}

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_WEIBULL_HPP



/* weibull.hpp
qYG96uTOUEvhF3wQs8WfLqsDaVGO3F7GWTqHwmINRamzDvTt/Y+1mtSNfzVHf1L+FYd8ik3ip3bUHHteF+ypKMw6qavqm77FSzsbtuf8YhRFoNdesEDT6BWvFTKz6txRdwfyauMiySz4bLy5jFDSYkHBBDU3Rtmqx6fMjdw8K+vlGuKQ+70ibEAfmTEQ/EPIWjlHjIlqE860lf6a3qe+i9XBii+tU62LqZLorpHahAL7yRqv+WalmBSSRq+PFcZSAWimj2CptBljb1Y9Eg4RGWhRXP8DWwdYM4KU7aoqcuEbD3bYVA8/+HQKTer9PKOjJjgW1PaDfF6rHuHHVWq7EqhKuae4qR9yRtCHbgcvd2fsIs57dVfAF1L3+QaOW1Tv0hLJ+mubz1icu0VfOBhPb44ygPN/7gkPfqSz74b5LhKFgmlGMP/FQeD/xuE38hl8xUjPbgaebNijo5Q3iJTQhtsJhu/3ZfCnTAmuzCkEQghYaHiID0ybQQVV3dDfT+fYMJ5ji8U39HF8syqd4/g4adwLgXq+YOsskcLNjpccqG1wjVb/Pugvp2FhV9CJrfRjYaKUrHemXc0+Soz2x0rEFk0B4QqCZI1HaCtCLk/9/xyC+wCvOeDJGCH/b348gpfp5T+8076Vjcgvvsm/YrnVJyh0UhDqZ4OlNIvO0f5N6Ihxph2RMTK01cMOwiVg2OkeDc2N0LJ7E6xm5UpJiq36hsAqvLZtXQjj4nsOt7vXJItGxfbKGuXL3XhtVe4UD+U8OBYld8uX57B9ttGD5W9Ar4KFx5MBGDgDMHPZ1zQ9zp1+TZ8Rn2acacQGwQCANSYAMOAd81xq9OhdmBqNgaPTT2+uryFVGT9PaemU4+KduFzWsOMITd/CeEzsA7Tbbwt8N8+SiRT7EX2sgrkCLsmQ6QKrz6zPuj6PdTu6gu+YZ8NgxHraq2ChF5WEhMt6cHnqCb/dEk5Y97KtY5r8M+L5gRtKA9WPwnld2o5I0bnHvRTLptUUDQDaJXXRaQ4dz4coM0HZHJuKaJ1x9okRgdb9d3mRu2U+O5MIQrU7ecj4c2eiGxM2FG1d232+gVYBDg+MW3gAI/WdgQD504WL4Gfzpi6Owd7bje4B4bAfR04mJ6wFR2rt6wKj9u9poA36/LDE8gQGOelDYXPB/ComnqQTHrtrcv2ranWXTzWtwfHCWsqGXPbbLe9Kgwj2ej3lRxsI79uRMZMH3AHwqnSULDnRo3fCaHiYI8jSw806BRV7sbaz4cOom3eWVJRzz3FphRwcsDvkx0VXclEusa/afG0dWgBYu+HdzX7mwvTP+C0bRXDWaI1F7Nm9enY7IQ50STokjPjcitYV7WFvyfB7uV/q+Cfb0HWG97rTh5N5Zxfxmu9dy+ROzuYUndJ7HiPr5D4Sr4vTcBdFWJJhS1uIB04MSCLLuoo4WsmxM7F0rF55DaalerTdClx+8Dxx3BXVXt06hUjEKrzWjuZREQGzFlfcFo+Wm8sZeHiSqmhj9Xdm6k0Twxe+zKeixDqlyupAGYmJi7f6Spg1v7v38OJTn9023rqTVpstOTFljdatOisZ5Sh+d+CGqTKORdg05PdT2lmXn9nLJfkvy+OkDWSvKgwrMj+YtrHsWARa2nmff+XlWYeu1oFY51NWnJeGeVrJ1kFlFOOjGfH9OpW35Zv4OqTsLV0LTR8ieVI4/HXHJnDTgRiuSEnetZmv7wHXw8OGzychG2Hl78zAMPBKuStbG6CV3jG9pASY792q3jjGi7sUofqRkx9cLL9kkSlk/8DJtn1HWH91xk1G4ulal+v00d9Qw5mqv2e3iVmMcLyGDez+Qk5EHvmXxlYLxuJewT5OmEy4hU2RO5e9CpPNCTPLhMsDlp7FaQdxEq0AcpP/4Acd+Uwfhg4e9DmjvqEflGe/9taPAcQj08//XSugsqV10V1lOdGPbqYnRrM6qAns3oX+LJgVMROxNQ54/S1BEifvMlFj4z0yNldMNU1NY2VafHqxYh8RsHgi0LxtYX3V0pnTjNca/kX4lh5px5WOZKcTVzUxUzqMZ+5uyTNDKEa0SliLxYe7kNw9F7U2UGDD3eCaDuVbhSTbQ2e3E/vb2CGVMt7dnOlaofpohHba7U7f13D7Sz1kWy1Mmzla0Dj69K9n8U++LBNZWXVQq4v3rjepYez7c6vq+O3bkpfmaCe7o8iA7MMLYy2Y29XyNifyph42wmtPmXQj2zwINfW2kQb8i1dPKrcAJOfX1QQwSZaOo6q6ValFcGDFe314Ser5w3NBjiBeG/eniuBhw/obF/pc/7r2lnXXdNM6tmuH6pOqprcqLEBf8OsnrH+7fshkqOAtwyZ/U5lHTSlTy6MYHIryX40CS+c7amEOOK6LKhk0SAdJrYKxHfY2T85xac6qwDtK9tqIIOaNlM1C4uS00lBemQSi0QOVFnR9Jr/Tr7P/VjDLrncrXKTLonnVxon38UTWlwyZOOLy4ly/50bWaRKZ2WFPhawa9JdnnGYG4J9rpkne1o/Ql7Q4SvgPUkbxK29AjDDRz82Wpr1Txx8RB4uRP2W6sUX+p2c7THZJQJIkAqd/NQvWEyf0EeOFzuxK9BpKBk7OVLiy/DL2XynO/J4oQ5T81GuLemnGq0O6VeqiCLhuPjwFlIxGvOxSoTcC3oWGl3XejdCP2TwTa549FOLnzmMjptxzPBrNvLYlVQ6n5niPZj/vxVgrNR6RWvXc3SjFuXxb7b5KLY1esA/f2zuJ6t/endrTxDCMOhPaONxX9WDmwsjkn1ckl3CK7tXmgAyQLrlsy4xMV+6uRTE9/Wt2yrRUyH3vLvHR7lRcB4MsLrdu8Bqx5WH6m2cuCOo+iD4o/AVwZ6b+7LIuV6ImNzyK4QaD7KerjdiVOCNxAsuVhydYu12WDIdFhQiaoW+P8SYP4G8X5Vnh+BB6W0MVC09to178xlYwU3JfhrZR0VrSysIgzVxUKFGwfal8EvE5q63xRF0Py7IsPs9ooTaONjPcimv0WWUSwaI12wgYd2yMum89+8VNH6x0qaznNXA+3H9IQgMBTOg7PpCGGzvbjNjG046JG9llhNtJCTlfkm/WVt1NJ9jcZXjYTlqY0/k6arg6KorUYVxD3Zff6I53+ZyfxxH6hnkwhH2j5KwY8905WID2ojSqY52Ebm0fGqCcrzRji4Dl+9QRMrEVhN9415+Lo93Xi+OM3s7GuBPoD384Au4D9QBH4IA0fu0/IbL1FAYYhjywgoCDetj/mrUJM1itXZRPFvLCZu2kbjuj16sH3pK7OKj5cmnAFUSyrDhyhhgoTOYKuLWQYaGQyRWddXG9cz8Ppo6jjYDfGv7f275GjBWU3kKkftxXeijNWKzf18Rm1WNFlqeDvGuPjyTgVMFFYvHh9S6t1hKOlIw6uGKAFHYmqM0D64hiH4ulknaP5WGzug168KqRy/GXXJtxanmkhGI08ArCLg9wXuQ1LL7QDh7XP1Exqjk+48/R8y75r6NRLP3eBnjQZhRX5Wik63v/4kUxX7j83aMvDj6/lJFzjzrx1yO2/iukPNpR8M+JF4HqEa4aYcSIuqoDTeEO4qbLprePN07Snq0VglIiN423Usrvf9/tZWFzt6DTz/9c1ehbHmtIzycunjmjPsj/ifoLZLu6yDZLeCEaUs37r3nEjaf4LN5v1lrxrgW3OL36N6Geqre6whV/WTo/L6OlpqgQodccgr2UqDx9BtYLObpJCVuQtXYkTuRAuKV2ua8tgHcCSpyuyDb/6kMIYVNvsm+GBVXmiUzKFYqdkeRycvwf3w8g6M1egzW+eA/AHmDzPwYjIALAu38QdxN3tIq9E39DRwBNAGlFVx2EybjfjwLEf88mjVFB3uV/sMTMsXhevJgZy3EP8ECHuWUCtr0bU8FayNQH+jEcm5G52IludUi2Ky3plLPIgAdrYFPRgeMwDrNVdVkZfYyw/PtYtY394syHRMnfz0zKnhMh20/G2/CKQNWf+/2oohin6JbAXukc33ueZ+IyOI2umnK4XBD9B4ZDpDuX79wKE6vh+9cUwxZ8po9DpxjDoT97sjByOOrnwWGl5MErEFGm9nMpRJcUOcL+yLFoGxNLQQGbz6oSicRYNPfUTsKj5sXlR/7Durby3ezeOVZ/0Tknmzo6nkTRSNKs1ubFN8HT8l615IzOHdOWsmSUD3Z416BH/3Rj2xsMcTQzc6RefZbPlHU7znwwPsN33YMYaOdCKXpOmSGjgNzdyhTjFHSnNOdSBC2toCExnufz6xncRNbjz5hncV6bikK4alMnttzvFJZ2smlfWk8dp3cMZsPD3+cXRtXB05YAJ7pKMRNxNDE9qqiGW0ZfsrSqBNbhqqUP/qOGPZXhgNsZWLb/dz938Ih3aUVDF9FDapm1cgkWLWW480/XTEi8S17ASoL+Ku4s24y7pKW7mO27yJ7ubgT+xjmlHya0Oo9KMj/SdEEwYmPG+O+ENuyBmhmpU8ry87qTaRt8VZeinkMChKcBADADFO+xbZA682R8tlMAQ0YOvh/w7vA/pYoZA9SNfJ3+BF3ln8lZH+rzO2zZGc0qpt8gpbdCvtoEVYR/8X4dCsLwTcyvqVo24vawudmgKvHxVLkRYUxWzlKukaG0U4PBZmOzdoicBc2t21e3eBF65KSOJMMcjv3GkN0hd/9x+/b86CLh2jo2UMxNaFBRPwm1mN/aO/Jfu5YnCaa0JTEbYZaZwz6nCaBMTzu3IH7Fbme8hzoNDOP4+6KZTAlerzggZzgrU/sv9vW1k00x3TZKVgg7yD4ABUf0OSfnw7Pp44ymQIvHb4/awA8AeDgt3olR/aJ+hR1sGtAwGBj47yUDYEYA3dD0s7zeIXoKdQtgPHeouZOxYUbDzoOxi8abDyRLFXWe5aNKtZ+68qTn19vVUsm2AxJSxn6Yk4f0RtgbpRDLlvXYHh7szDsNXicxSjQBtZbymL8kcPzYND7P3IP+xnMvZFEdkiN9rdOBbTA922S2UoMyeNXDbLGEs9PfjMB4yuyVuOrH0vxQnsT7nx/qeTEta6Ah4q4N8s2MUJO+jsghRTzXGUOzUr3t/ut3qll2EqefRSPWAvtJhL/frYfcBiQuuAtsxlUFbIi0jkP9/0J8wVM4xi+NFUtB+WuSgVHJEhE+Rlu24doQ0fqPeb+G1AUIDKOb1Hk1FN5D7L8ePF/aBrovean5Lx935DXEIm9A6uanB4Qx95VLmYVjs3/uTks9lAuSXX7HRgqAxMnKtw0vVMuras1x60RwrfJfxlGQbFK/sekckDKp//j6r5hty8ZU5o9D9zzVhZcBetrNXWnaVRMzvG2PVDzUC9+P2Pai8c5OpvCtUXFFLhIPVwjYfFby7hCE7vVLWlCNTQK9e8zhBm8qK9OV0KLj/NpIf1xMZ0w9/qa6GYqHvdcg+hRZ7Cdmurr34uaRLsOplITo3sRALi6DSTXplSLTXA8qCgM9B34DjgMBWd80/P1fwOBcV/wO1cR06+Au/BHqYc//muXG4QLX3XvdCL7g+uECDzy73QxE5OfhAi4d4OO5WX1BK0fAH8AJfMV9U3bwPD7eh9g+DIpeoIA9c8Twb+Fl+v0OJ+Hv+oVJu7lkrQqBe6Jshu+Nb6hgsCF5qTvwTGUGvmSX2ZAwLPKgVCj5YAQZ0hbsop41SFnEcHia+wcNQWXwGZUOk9NZwQVllJ4bpEVvx9a0zz7i0LdaW7mHcr5SR5xjffeIju5sTPFDHzHLPx/nVs3fTo3BGzVOtca49svmvA1qWNEclDpxQs1RKvzE+OQx/PI5mfAzK/6gkpfdhPqA45HNEysIKL1oFNJqCdMcZCiJkBXCer0MUrg9GvCgXRBmCPt9nyuJ+NpbIPpeMd+6JfGLnIl1t+0VZd0YhCp9lqOVQzaCzOkT/RJHBHxM60Ka2FKTZL7vVLcFpcTMjNk5nEbgMJTQIfsxyQYR4pUKYp+q58cNUy2aWo3mgXSoTH7upNoeF84O08KTL/7CHEXXiQ6NkahGoCmJghrFZYBMNXdkjkefw6JPcL2LJhwnIQbd90gertw5S4Ej1SfKbetOiORWpJca037MjbL/qP2FUpHxPYRHi5gDjfVFH7PgijvRXNAXIvWIrEsnIx7A3gpuqqFDVdYNcUF8jOYgVV+VXXBGCG1U+Xfb9Hy0vlg88+jSyLj9jds24wURp1LoEOC+1wL8d/6WOMH/xDsug/79VTO6YYUOfjKYOlHJbQjPhu6f8ioQtz/A2acE6LTODXmgLF6Hdo0OaffLxRqILUy06HRU6a9UER1kx0UMSKCIxcVCc1ymTXrv4HoJXfT9jDVs/pp36jDHRSVfH2U12bp//nr5KZsuctdvG77tY5Lba59hTp5rITBbKs35p32gnmjkLcWrK+Dy/z/NH8KojST9J5YYiejRkpPICtvJcYZTcSmIYBXD1tZ6Qr2VxJq+/PcX6AMQgElEjQQI4GU4oluZlTxpYpB1SlxPk4Tkmw0lDUqcuiJD32QTVi49YsGjBUYBTrHoONZ7BVEmeEv7y+3SDn5MWliBkS3HGBAj1KIQHFV1JqX/BBCci8jMeMK0lWDOcLFlAhAAA0SIDdQAILuvt97u3uzsTO6aJ74pGV21tpJTHY46NGpQOtcE4uWM7VmawwIEicmB/2hIkEKJAfkBe6SOeAB6iHv0e4sIAJgeKaIxwh5H4L9IVP/io6kozhCMwAQu2DExBYTkUBP4axMatAJHLKF8AaxoQXU2eArjbzArUS1nSKRJ3VsPpWQhnJKmhOliq8wyExUi/FIR/guUOPP+auokeaJhFCu9oQbC2HWjLoXGYyyrsVfUI2MKo1HQysxoaEoWKdYxLFA/Q+mmYR+z600r6HXSr0Sj32LT7tkp0gitR2qE3NiDmPN8yooQftldJ6x3PGaGZbFoxY0AUSJnXOsIdk45SEqgcaGkoCy/W31MV+uSQh23Iu9gLbQWAcMdrlj/n/GTzH4lOmjRoq/JcU2Qe+kA8Qg3aaXMOMt/HZoNtVJcqOXGJXLUGiLANVBBShjNiUx4dMQFzm3jBdmQhYV99MBtkkLXpgP/Nu8t4TtbWIV24UX2pUi5KsAmAnRl3/zmkfbntdXAEP9NLGpRCjY8XsW4s1PwmLWOj07LopppgQ0FcjMnXhRToENCpu+zgdOlnBA2h3blDSMqGzmIz0/KCd+8J1MUSEJhxjqOp1VFyeeapsg/U8kin0AUuKFMv9zLCQgp1k6yTNlX2l2wcbJTPxWlc4sFG/3F642uz1uuoSNsk5nlH4kluKp83FevdDkIDkiC8kEplLaZb8/MyCqlS9BRRuMQZv5MGawkGWX0edTtp0UzMfAsNnyfZPXg9ir9sqgvd2oqErSmQk6FhdzhA6ZNUMKGQ+W0XOEunz08k7JpHxgd/a4rNkXBCz0pLoSkEeldsDSS9fCCoZkYcBi3xKadiZLknPJJOR8nQQ5yNcmt8DniP70eNibTp8ppias20T78l1wajpf/KqdasYF8mUBZbqvmQbaABO/Fs5RZ3eRKGNcm+NCo+qenMnbkICGzgMnKN9Ya/aSWbbZJguUwEyFV9Et655R5IahwXQ9cpr2kHJIGh42Z4ps4HyNvKLchzLhrFwNzr0j17tMG
*/