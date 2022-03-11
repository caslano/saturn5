//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_LOGNORMAL_HPP
#define BOOST_STATS_LOGNORMAL_HPP

// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3669.htm
// http://mathworld.wolfram.com/LogNormalDistribution.html
// http://en.wikipedia.org/wiki/Lognormal_distribution

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>

#include <utility>

namespace boost{ namespace math
{
namespace detail
{

  template <class RealType, class Policy>
  inline bool check_lognormal_x(
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

} // namespace detail


template <class RealType = double, class Policy = policies::policy<> >
class lognormal_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   lognormal_distribution(RealType l_location = 0, RealType l_scale = 1)
      : m_location(l_location), m_scale(l_scale)
   {
      RealType result;
      detail::check_scale("boost::math::lognormal_distribution<%1%>::lognormal_distribution", l_scale, &result, Policy());
      detail::check_location("boost::math::lognormal_distribution<%1%>::lognormal_distribution", l_location, &result, Policy());
   }

   RealType location()const
   {
      return m_location;
   }

   RealType scale()const
   {
      return m_scale;
   }
private:
   //
   // Data members:
   //
   RealType m_location;  // distribution location.
   RealType m_scale;     // distribution scale.
};

typedef lognormal_distribution<double> lognormal;

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const lognormal_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x is >0 to +infinity.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const lognormal_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0),  max_value<RealType>());
}

template <class RealType, class Policy>
RealType pdf(const lognormal_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType mu = dist.location();
   RealType sigma = dist.scale();

   static const char* function = "boost::math::pdf(const lognormal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(0 == detail::check_scale(function, sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location(function, mu, &result, Policy()))
      return result;
   if(0 == detail::check_lognormal_x(function, x, &result, Policy()))
      return result;

   if(x == 0)
      return 0;

   RealType exponent = log(x) - mu;
   exponent *= -exponent;
   exponent /= 2 * sigma * sigma;

   result = exp(exponent);
   result /= sigma * sqrt(2 * constants::pi<RealType>()) * x;

   return result;
}

template <class RealType, class Policy>
inline RealType cdf(const lognormal_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::cdf(const lognormal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(0 == detail::check_scale(function, dist.scale(), &result, Policy()))
      return result;
   if(0 == detail::check_location(function, dist.location(), &result, Policy()))
      return result;
   if(0 == detail::check_lognormal_x(function, x, &result, Policy()))
      return result;

   if(x == 0)
      return 0;

   normal_distribution<RealType, Policy> norm(dist.location(), dist.scale());
   return cdf(norm, log(x));
}

template <class RealType, class Policy>
inline RealType quantile(const lognormal_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const lognormal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(0 == detail::check_scale(function, dist.scale(), &result, Policy()))
      return result;
   if(0 == detail::check_location(function, dist.location(), &result, Policy()))
      return result;
   if(0 == detail::check_probability(function, p, &result, Policy()))
      return result;

   if(p == 0)
      return 0;
   if(p == 1)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   normal_distribution<RealType, Policy> norm(dist.location(), dist.scale());
   return exp(quantile(norm, p));
}

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<lognormal_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::cdf(const lognormal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(0 == detail::check_scale(function, c.dist.scale(), &result, Policy()))
      return result;
   if(0 == detail::check_location(function, c.dist.location(), &result, Policy()))
      return result;
   if(0 == detail::check_lognormal_x(function, c.param, &result, Policy()))
      return result;

   if(c.param == 0)
      return 1;

   normal_distribution<RealType, Policy> norm(c.dist.location(), c.dist.scale());
   return cdf(complement(norm, log(c.param)));
}

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<lognormal_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const lognormal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(0 == detail::check_scale(function, c.dist.scale(), &result, Policy()))
      return result;
   if(0 == detail::check_location(function, c.dist.location(), &result, Policy()))
      return result;
   if(0 == detail::check_probability(function, c.param, &result, Policy()))
      return result;

   if(c.param == 1)
      return 0;
   if(c.param == 0)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   normal_distribution<RealType, Policy> norm(c.dist.location(), c.dist.scale());
   return exp(quantile(complement(norm, c.param)));
}

template <class RealType, class Policy>
inline RealType mean(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType mu = dist.location();
   RealType sigma = dist.scale();

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::mean(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::mean(const lognormal_distribution<%1%>&)", mu, &result, Policy()))
      return result;

   return exp(mu + sigma * sigma / 2);
}

template <class RealType, class Policy>
inline RealType variance(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType mu = dist.location();
   RealType sigma = dist.scale();

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::variance(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::variance(const lognormal_distribution<%1%>&)", mu, &result, Policy()))
      return result;

   return boost::math::expm1(sigma * sigma, Policy()) * exp(2 * mu + sigma * sigma);
}

template <class RealType, class Policy>
inline RealType mode(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType mu = dist.location();
   RealType sigma = dist.scale();

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::mode(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::mode(const lognormal_distribution<%1%>&)", mu, &result, Policy()))
      return result;

   return exp(mu - sigma * sigma);
}

template <class RealType, class Policy>
inline RealType median(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions
   RealType mu = dist.location();
   return exp(mu); // e^mu
}

template <class RealType, class Policy>
inline RealType skewness(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   //RealType mu = dist.location();
   RealType sigma = dist.scale();

   RealType ss = sigma * sigma;
   RealType ess = exp(ss);

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::skewness(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::skewness(const lognormal_distribution<%1%>&)", dist.location(), &result, Policy()))
      return result;

   return (ess + 2) * sqrt(boost::math::expm1(ss, Policy()));
}

template <class RealType, class Policy>
inline RealType kurtosis(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   //RealType mu = dist.location();
   RealType sigma = dist.scale();
   RealType ss = sigma * sigma;

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::kurtosis(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::kurtosis(const lognormal_distribution<%1%>&)", dist.location(), &result, Policy()))
      return result;

   return exp(4 * ss) + 2 * exp(3 * ss) + 3 * exp(2 * ss) - 3;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   // RealType mu = dist.location();
   RealType sigma = dist.scale();
   RealType ss = sigma * sigma;

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::kurtosis_excess(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::kurtosis_excess(const lognormal_distribution<%1%>&)", dist.location(), &result, Policy()))
      return result;

   return exp(4 * ss) + 2 * exp(3 * ss) + 3 * exp(2 * ss) - 6;
}

template <class RealType, class Policy>
inline RealType entropy(const lognormal_distribution<RealType, Policy>& dist)
{
   using std::log;
   RealType mu = dist.location();
   RealType sigma = dist.scale();
   return mu + log(constants::two_pi<RealType>()*constants::e<RealType>()*sigma*sigma)/2;
}

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_STUDENTS_T_HPP



/* lognormal.hpp
/6j947GB3pIGVh9Wmf/C50XgrTRVHlj0L33ecT9Ne78ae0mUDnHHn6/BH5BEnRM+ucAa8dz5u0oy77piUCCcj1b+TOWNI0S4bqzUwHyX+gWjFGUD3u/EQ0ilJDm9fMGK1PBDMiby65KbHLUcxHatGbc3326kUdudXKnfzlG63Cldy2QcqC6HvW4y1VBkHFFX6SUdUYeFODpM+T6LDYQp55oF5ZDO0JwEPnmUKQHX3H4c5ZgdwD1o70AQtMzNfBHl9PsdUTWHmoQR3iOZ0IKE1WD82q9vxzIvF5X9X4QVLvzKXUL1nVmK4i/l/mDIIrBPxjnoxCCDCTXLk91yxk2CxOfUzeTa8dOfkcWIsAw/6vjwoo72h+x+Oe36VRxLJD+hrGIWMaL8Yh8YXFk5LjODJft3Rw1tPS40NqjAas4cDMOA4ERejoL5ToHxr/5vF3tR/WB/DuDqhGAF6fDFdiFT9LGSkKirpoDeZTD3L12tHsHBOdVwEgb799YLFy+ewD7GceLIVv7zlElMETdnVAXhxKpwbk0y2LQHVRnn3mRDyZA6+bAhseefCiVn7Tt5aYfcvROlBz6LQJQqJjYHMUWT3ljUR1tswra4owzmmacFpW9Eyl6hC7W5NuKu5DcpQ2M+3gpIGqahNCTCiR4DliPgFa5Yca9LRp2PGbKTCzSNbfJ+Svn2KQu9h7u/SiWcd49StSOaXzqPTD4xs5S1kMoYy+GmiEN9H2ycmR7NqPZtOD0P1Jyy46a9JkjSmK/6GcztlFkhTfVFzp+uacDFIsAJ8PLUp/SkielVZ5P9TJvhBAXikgwO2XZjrDusmDVutlDpDoj8TM6nJeuz6VePz0xkHge6fd6mALJ62C5ckJ58U8ZILskYGU/SIYu4qnfGcbF5dL27ZbyCR/ybYETHItCv31AoIuEshwXY34VV5qszM5EHIx0zO5mDUIGHq2rPxvZOroSew0PJB47Oj4i3umPxe9R2swkt/wdDDWWhGN5WuiNUgANGTOjFSwEc58mV+ZzLeVeD367HxhMO8wYfQvOvsaMh7OCQlkjv+3xlFrBh3lTYWuod5dEvRmyj9LE1SlWo8c5MmbIa4aqGCgPbSF+BKDHVrs6R18Wl6k2VXdB4UP+9DGDlxAhFsH/WCM4bgyhmFGa3NTRNqYuhEWRv50rDceNn1bVJ3vianTk5GVju6Kv3F5ZyjWfVrYA7W+BgwHPuYSRvxGRgHOzB1pLYmHbfaft+gCzxKm+goO7K0hxnyD5YpSwYqivvt4vqwpDVkJOJYidsMcg3Y0seYmVOEnqe4he+cVh0P7FRzn2RGGPYjC+tBuBn/K/H2MGQg7QNlK9zYhzQ7vF+NgYuwwsGOe3w/2B78skId7MRICJ0m9MjmpGqaQr5newCppyjB/LFdJwJprM4Lb6pDqdacTv3GSNGf0xDQB+fmiC3YPo+rgYLfDJvSG07pPWxCcr2CdJlu/9SLyqv/1ilX3fB3aNJ2ReV/E0a6gpYImhtpyF52dSwYbziqIW37bsuBD4hjKuXpgU81fyw4zX5ibvKiVEMQ31RYAKGcK4wsiKV19HYyh69y0I2ZrS/dqKh7xK8SIarTHGhUvDqHJQEe+maRs2S1WU8W8vHel4/pG/0JWAIwvdxbNdYpcHeU2GOrvwOkZpDpusgBrZaAUOzHSwzBuVQjeplrPS2mSYElyY+uqVpB9uzm2Rb2hykaJXtfI/ABM2ogA9Cy3zAvHf1lWoCfXDdz7mQNw3UznRBHWX6Ui7LFZc8giAs39h7ZkhyKhpEAO5cu8YUXYnYGk6sVL2VDubdRNs62arKo0pJvUPi//4PqAFTGNhS4MJ4toBcXCp53/QPeSbOrI0ik9JH7JUypDTJ8YzKP9R6T4SsqnNLS8tXcz7QlKAUNZff7Zxzha1RPyuPCsx8q4vJjWXRUItskQM0cs+YnD5OrYc5UhPl7w0Z/2ppWss6yXj9N83CyB31e99AxJIZ3BmYlTBNGhByNr0jhjuExUYiNMT2AdbbLHRNtf7Og8kJB2DcV0knGiHUmE2Z7XBVFVKFUiYRn4LvljNOXC5LhskGoFu0Av0LhjSXioDZd8BHOCZHMgsGGp8PqXUUW/2YfzYevEeZnHAcU15xUe49mqCUl9605gdKqSqU3cZ3/Q+QBdLybhPJkkal/jvzHZcU1SBU2h1BB2LZE5lraFIW3Js29/FLXXvRaruQHpJX9ailfs/po0Fg+J1KDUXwlVvHppcSNU0pCL1uPs5lwt/UYxyhicdsNGrnFULza/kyBHOcOw3bHf4plCXh8HRMxU2wEkqyFk3SWairvgSZzkeg8wF5ICBP1xnjRTf2a6cfHNbq4lFVQENxs1hL735OaL9kHL86ilAAn9oshmEJEPEP+6XywRFf55EraasnBVBYjZGYIBULO2jcBLn7D8uXGQfKa3hsQXnOoi+p3DLB8P4AAwrNamK/eiQvTqu6JR6TKnT5iyJM8EE3g1SMTDufrNu+JG+za1ozdpgg2jJ82TF3NLmcGoBFlKntSs0h3i/TMUdVMkg0Lmwx7S0yF2N8anKUPte6WR6EeBePRtOpsVWBjElvoFA6CsL4HxR5B5EwA6gBd+bDCHwkwbdgkshokRGx43LNMT7JmRmgpyN6CE+9o64TqEcagotpj09BKOmQpMeakaQ8ifa1WJX2Vx331P7oF4S80Uy7+O4+iyZFFYPQsv1YjLKRS+vuW05KxxS/FmNfum8r5ymsikdJKdt3Wqus/QiL922t4v+1Cgwee8XNslmInvk4UW8tDYiNz/Mwx8vCbom+ZFRNePvtFD56IHweG4QtOP76fTnjmSxmeJIwhluInSb40QDqadM0zlGIFjiseH0nPV6Yx5DbUSjz0TiopB9WMY84IfGC6K2ML3txXsX40rGViM1SgIcmGDCe+Y48oMzpOctYjadqrjl8pPVia9tD+hLmQ73sXG/a26MZGOr/H0Ht1X/ueB8eE1oeEcKv34Z4opsAj/676c6ZsfL14MVNgSJKud1XZhwwqDCpRuV8aZSR4iBNR+EUkY1M1866jzrmQAD0QTxTk7Xwd8FV6s+fNt30WBMYFMqpghwfM0GUxMuq4uGZxY5filWpIMnDGus7VW/ZixKSYhdUbY298zYkNTXjm+Egl/yLjBM+eBVmClCRJuuilZ+81pCjmsl2LW+FRbgegrIGLgYn30DS32AugK7qKSQt8arhUAWBFb2HdLA5rEFE5B2sn8Z4q45ci+UOlNFoRJvm+QsHCBgXk9GTTVGA8Ao8QyLwT32QZjpTChNVnfXTkEeKpbZWpM3Y/+UdbqQbZnHHi/KpagqhinNXoaCB4P2jROq8YFOxOUJA8lc9WGaLkQgjUcyQheBPXk4WvcVWo85UUh5oTIZFw9pJ8t7elpsIJXJOz3uRpY3m2EFFB1nHtxIxc70yo7yRvO3w2g2bKwTnCBEcFwHH2CymZMcuYQEXXGlZBeVDrx8TPYArLuoWhrO9N2nWawFfPc1hDDWjoBTduiUyZzAmjWTEQzNHV/fdngIEyjx42LWPiTDFXoG+kdnhGoaX0KARVosClYZ5Cc4AkJe9oL6MLFQDuSHoodf1zs8MUgJIZg2HCuvJTFnwUjaDIO+s8uBEpwBLCxk/4LmS2IMRSgFaHky7ranJYH6V4kjYxTzMJbw4ZTQkb+MEpAEcz840G4wSN1+hm0jQC1GpiVhsc/t3z5p3FzHZqIF+BmMbHW3nnV35t41vZPPvzYSMz1dzCDCHFqMvRz47+NGWcmN023rY+vsZse7xvQ+Wg9uLmcQADbVBIsKJjRCNJlONnZ0TkocHIpNhCDt6FKRUAA+sL32h245BFyzKi0KJ1Fyr2wxWbS1jX5xGomUj8FCgKMHg/HM0gFrKA0Z+ziWkbtRe4pLMtO3DuxB3aUX1EPanrOTK7F7SmEIOicOgtBPdDr5V38OFtX/sQiIklXKWt+NAUMNEYpW0mh23YLdwey753Y2s1hv9evtVR5/0rr+Qjt3xboZE5u5QWJ0hZ2xht0y7Jl0cLXUXrbCiDaHlKays8pK9DmiApVECD18g+fOTTXqyw885hoDZ2c+zO1g/7rYOII87jkCMuVTukl8eQvxLqziYxjSi+TtgNEVmtLzWwpr+OR6A/0Aa+ljevOEc/0jpaDNr5CH+wLi75yCOJYW8DCl3Q2UXoaO5Y9JS3g55HhihJK7AlU3G54ToOJ/+LRgmsoRNRkiQIzbGWYKD+jwMDIWnneGkL9dv+Pazyq0NMa5nN7kvw2Zk5HCiKN2WkfBnnUC9xQxVN06NrKfwL2+opLzTFRDm5VEdCuT0bA5GIOYgtBPVzK2mYAJX8a/Qq+Ze92Qj6DAdz/E3h2XGOzOPRtgFDhRjB4J99gUR6OO9zgEkMwQS880DIUReSOmKBnqJgP8aPpiADOwsz5Q5F20KJpkIuUVHCRUZICJ7zad72qjakYrmLs1tfYFxe23eTYk25uJMl/P2q4dSzurF/v4L1jwwFFOgm/gIs7E3nKTu2Kb+hDZRuKQ67IkWeZMxUnDEltyTdl8d/BpXs+A/zrclAe7CWsQubzp2hnaUeRfQGVyWdF22lrtCTWTayRu5x1toh5gEAsPUmHf7bLX4BQF1ipW5O8E1JqgC4ecFQBQvy4WOItzCoR+9ZI6VpkGscz63AVrMZ5r4xI+CI6pTQqlahyaIZWg1GOcisSHdkenuW0pTV2RhAloxcjMdsFzRaF9inc+OmnBe+HM+wfRab7/qBiwPAAos9dO3RHP7hk9rj6GOLibWEvoml7VIw65gYPaA+tMs/hyJWPfTTpA9qhE+56lWdcxYf4aUbieQagloROTIxcUm69n38oVvB85BPao/92w80XhLajwkB7kb6yPuhfp7TAkYvgF+E0/POzWg+sQGvcljRZTtBMexe7jucyWSzj3+bnLUttOcaIi/y6vS5uUbv7UhP1OVkGlD1YxAkv0FCxuUk/7Myp91bMm8DTV7IYPseohzKhmW6IOymKZzyT/0uWw0QbolvbL1qxMYwn/hihFqqqKYIThLAH59UxRN2xHsMi85DW2Vv7pnYreizyXz+E7HFkc6DnH67VWqlIJRNME7B/TzffpY6aIEQ6nEB1hzy/d1plydEtc8hcVI238GmrlYNUWoJ/SwFsH/vFWOXO+/oRQT6Z1afdCc7GBPbe1ILhf9zMQy4EQYwBnCWM4qEBSS0Fr7KpsSy1Ji0zgVUODv7TkAq12Qv+wdy6OLsErtKgBICDB5LZavpJ0vBl5vgWNgYc8q+E4nepvbejwEPQpYd4njeie1j//l3v95TQWCCQVouysjzAZc4nzELL0nHpxCYwYkY6/ShWw4DS9n+Js9fCCVjRKiKHmDjl894tTwhnhny11suLimQlBTd+uIjCDrSumrek6KF/DGndIS2NabGhBUpFSjacVTtAr9DNfTYigIEAPQWtv21rZt27Zt27Zt27Zt27Ztc/twPmEySZBoDCO7RZO9YVyVwVrMwMICINN9mY885fSZyqwjqG5LOzoSC3CZwBH+AsIZ69xeXeUhpDzFsRg5Fu8HyM4eMN6ke1ALmPSiFTlvCnMaRZwjwJ2/l8B7z7WAXzY707uROa5DngXBjVGVualbTV2UTms9xn53P7w9m6TQEg/vkMDANwVx4p7zHd2/Ui89iAmh2TJiUzoDTfOaewWlHM04M4VCQjKM3Zjsg48wYFTsfwKYiiRFO6iBzqizI+uoBeR3F55I61P2Jm8g6fHRifkkAK8Le8v+C+iHP3sKER6DXZ18Ov2DGCyz4tnJTOlWXj55g5KhP+AvhjgH3fVGY/MaidhF5gbku7eLv/6cawo8phO5O+hWu8+lhxxNBM2v+g0Mv+gDhgfxEs6G6D3HVJfU6Pji6lSzGYD9nxajmlggTZvDbcCdNIPUAxQs0curSYPhFoYpDhX3Afp5QZ9zVwPTtxQgXlr9OIeuCSBcCF3eLE4c4Yw00G68QOmD/hhZ0bsynGRMnLg5VJC3UDSnx+IMxuCnlKdV0Vbs8sGeRO+obiLRohztzLYmQtIUIn4q1pTKeEm99fskyeQCGggRqTo7XSipENNbU2lv9IwbVDt3CfSx74rfZbbA61lY58zQshMh1LgLvNf62C0WXVmsfsIT794rsurzFy7hJrS+iNjPnZkuIWg8TSdIWblQKp/wUUg++AtrXTwS/rL6+jFG6dcqiYNCmCICAoYpu42RWHwo4keHobm+2DMFQmyUrJHOt2LhG+TlQCDHitVtfZrCPkS5BWnXr2kvZ6yDvl8wHq9yytrMoADMm16mb1CpjvuQg843LjqJuibaH57myXbOcYM1oZP3pwd5/eNT3SLcdbr4ArGjeJNTGeMysoqrvTxW6aHvA+KIXQav/XlkPB9RmCvS1ezZRoEtlr+qWwyWsFpKDyX3gSLDB+2ywz4w5b/PXXOQOBSmMYBv1xG1mquFVOjknS3HcLEysLnXlFXVnBT3PubJWjeB9Pu86TTMm0dBIoMc9lBnsWmrbO45QXQUbgdkLSpfP79BgqpsoiwaHprxFa/pT8MLOti/c4oZCfgmt8Qfu7do05SOgopI8HE0grz0gS2L+Pha7O2nFfmsXbLjTyZJ0fFFfDwlKHdEYOrsrkczCpEk5Izk5Z2lGKS529gy1ezFPSplhcm9TqYOJ0wiQEKe7njADl1JwzZlvCWTPfSGtz1jAd0G1mZ57gQQdoGq47FXpGUFUMdw3aiSYFPblzHKNMIGNFE0oIRC2bxk+1sFtgHB5YTizDfBF2c1hJRiYCyGwuu5w3ns8cblX+EoIXm4H/Ud+wl5oGeEfAsXnDTCFaTpUlrfTgj367nLH/ZyOUbuuGoap7Jh/ZnjztpO75lpI/odz+39MwRkXj4AYPM3MWhTlV174zjKjnzHned72+//jEAIl8T5x6uedQ6gJRA4HZ7rHH7x6ObNk9LUXCZaeMBMjX62rry/go203HtOygHUGAA3MQMYTS7d/3MKgCbjtX3WE7TpgBKivKLrun0BwcXUqu6LN1Sui9iDNGuXfwrUPs0cu/JyAn/pwvpmtRb/dS+4rqSSI7paRIpllT5F4wIpnQN8c4GDCRu7WFxTBJYqYDXC2P7tZnGHEWceirl7jRhLLlRWDKsciZObh1FoAaEH9d4D+bFX4r/cy0tnnSaDuHp7d0Pgal2B6khI+pYwXrZrfTJoaedcyp6ctcEGvF8bpah5exKIlZZu+6zq0iMZfsCF+2kXyZDvmaFCXpZufIVjIJhJzO0NvcwNHQLYBVaq35vd26ywnApzb/picpq9FiBYuExC2I5+sW6ofCR5KSe9HI1Fp6J2/XDcTVT+XLM9DsJ/0DPo1Lq7ouZ3Bs8ACswyQsD17YqaA3XQ0iKaZocgUkmIM1rxmctfxBwn1pYTKAQmaPeCcQRJnZj+z5cs+sUH66fgFVvwkeobYZ+bCdmQ9hsv9xTgDuroLqDEFPabz4BNpO2gfnrNcSvOHJy701ZKJXJBP3Z3GIASx7gVixKe0RNFIgM4ITxyP2Shz49ipMwbICKhh5va4+dE/yvxNPU8k3ov8O38mYYrLK3sEEJTHVvXxW+bntHFrt0c6B5ECGa9uPwFZ1gT/wKWkumVTzYTifvqegsC3LkbgkljDdQe0J284r+EEhTH/jB1dSDUGZ2bHJByvtE9Md5auaYodjs7ErnL7si7SYfIjt/U9sNaQaJBYQu8/QizqDiqBywi/ksl0WWLK/asM1GHQgb/1oAaelTGmZIg2MRb7LqV7AoKfSVBqtOJdbJi/VQV7PQgxKLxdsMIHwU60IxeYTrBbqgn5NaLtylECWe0ZjdIUSxYV5KVAl9SPgeMIEqxUxks/5iY7GisGZmvGyoTVGdJwtJEMl+PGKMKKOHhp+ZvSGt7jsix066PnrVTMP0cIHbrFVqKobzdztyg1+MQwh0RSx+gyDiMsWx2MskzgKJ2nM2N1taEmTJsxpcGkZnpKU1Y4g81FHeQoDsDIfp5+PKlQNXEIQB/fJ69hPkn4UZXm12lCXdVtm7xs+Yx9S67kwMKM/7/2tDD8KzbbwHmWlbE32Hx4alRF35PwuHqnirsj64nG+LsEx0soAtS7epzp31JjmyJsRY+WOXXDVilPize326kEFsehGekD2MgeSZ0jcQDDGssnD1BaBdUBU7DkyuKXYKofhgDJXVYfwMYx9Ks2ohQGWRjHcaaq8O7gG+ExxDhyuRC2FGRw0oQ10zqSw76icls58gInROR4/GJhZYS2SIs86gHQBKks6elMJnbiIjKD6MO/SRYqvG7W2zlih795xuEvCSMfirzV844ae3J/0NyleODDyRjXcqxyBk+Rtq5wk8Tzqk9Z8nEGE+n8TycZYZO23iMv8vkZPPaLyawbol7pgaXGyij5i+IzY8GLbyysISakJzS0pM8J9chdzYXzsEtkcAsrAutGBxkT9jEeZHH89OBTiX9SEJk56a+p7QuT999TfhPD503a41vNzFixH/9H5Z1o0IdlbETx0f4yi2HKoqVtNQi1ButWVed5O3+Mzb2yufoTcF4uYl8+xEwE88TBsT569MtwHCsY1pGB7zm6I+z4CuOrr0+fIzpJTBzohU02sxxAoiGM1fk+yhZAZr6QPvLOfPr7X1gb9qtGf0oUFcfLoYd3PclWqJs9YS/O7K9A2yNQle7A3xP/8IhwgLX7UZXRJqT/xnYAv18dOmHN5w9ffYXbCIWWmQQAxmroWHPmTzXAMse4cVinzLAgP0U1abS0PsPIcRbZLOfGFPj9FCiMzWCRRsg/zNKwiXxnjnjKUG4zfmIS7bGfDODMFiC4pdNzIBqkV9BeXWBvHupevkDeA+XDYs0p2u2XNTs+H7J7CQ2Vbt83Rc/YUjz9YWWeNlVFTFjuWHRrNVSTf2TWyqe9Dr/MQJI4yeVGjizWHZ5CfaeoVQEXUUTHaSF24AQrh2Qw3GhbIPhxHVJ2kLo8OMaQ30xczO+o8RzDQeZ/Wx5YqnvhvXHK9PgGPgjHEv/pv5a3LLNfa2L7uF0TlWHacJV4EpXdy7daenuambU6eRFYOqiWwvdETDbaCWLwcmh/lHF5q2cJ3Jpb1T14SVC+bhl7wLgMBAVXhddmRdJUSSmF3ZzSURlX5sHpwZeNFqkFILP/nUMYJ2IOYGPQq0=
*/