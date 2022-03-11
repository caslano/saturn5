//  Copyright John Maddock 2006.
//  Copyright Paul A. Bristow 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// TODO deal with infinity as special better - or remove.
//

#ifndef BOOST_STATS_UNIFORM_HPP
#define BOOST_STATS_UNIFORM_HPP

// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3668.htm
// http://mathworld.wolfram.com/UniformDistribution.html
// http://documents.wolfram.com/calculationcenter/v2/Functions/ListsMatrices/Statistics/UniformDistribution.html
// http://en.wikipedia.org/wiki/Uniform_distribution_%28continuous%29

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>

#include <utility>

namespace boost{ namespace math
{
  namespace detail
  {
    template <class RealType, class Policy>
    inline bool check_uniform_lower(
      const char* function,
      RealType lower,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(lower))
      { // any finite value is OK.
        return true;
      }
      else
      { // Not finite.
        *result = policies::raise_domain_error<RealType>(
          function,
          "Lower parameter is %1%, but must be finite!", lower, pol);
        return false;
      }
    } // bool check_uniform_lower(

    template <class RealType, class Policy>
    inline bool check_uniform_upper(
      const char* function,
      RealType upper,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(upper))
      { // Any finite value is OK.
        return true;
      }
      else
      { // Not finite.
        *result = policies::raise_domain_error<RealType>(
          function,
          "Upper parameter is %1%, but must be finite!", upper, pol);
        return false;
      }
    } // bool check_uniform_upper(

    template <class RealType, class Policy>
    inline bool check_uniform_x(
      const char* function,
      RealType const& x,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(x))
      { // Any finite value is OK
        return true;
      }
      else
      { // Not finite..
        *result = policies::raise_domain_error<RealType>(
          function,
          "x parameter is %1%, but must be finite!", x, pol);
        return false;
      }
    } // bool check_uniform_x

    template <class RealType, class Policy>
    inline bool check_uniform(
      const char* function,
      RealType lower,
      RealType upper,
      RealType* result, const Policy& pol)
    {
      if((check_uniform_lower(function, lower, result, pol) == false)
        || (check_uniform_upper(function, upper, result, pol) == false))
      {
        return false;
      }
      else if (lower >= upper) // If lower == upper then 1 / (upper-lower) = 1/0 = +infinity!
      { // upper and lower have been checked before, so must be lower >= upper.
        *result = policies::raise_domain_error<RealType>(
          function,
          "lower parameter is %1%, but must be less than upper!", lower, pol);
        return false;
      }
      else
      { // All OK,
        return true;
      }
    } // bool check_uniform(

  } // namespace detail

  template <class RealType = double, class Policy = policies::policy<> >
  class uniform_distribution
  {
  public:
    typedef RealType value_type;
    typedef Policy policy_type;

    uniform_distribution(RealType l_lower = 0, RealType l_upper = 1) // Constructor.
      : m_lower(l_lower), m_upper(l_upper) // Default is standard uniform distribution.
    {
      RealType result;
      detail::check_uniform("boost::math::uniform_distribution<%1%>::uniform_distribution", l_lower, l_upper, &result, Policy());
    }
    // Accessor functions.
    RealType lower()const
    {
      return m_lower;
    }

    RealType upper()const
    {
      return m_upper;
    }
  private:
    // Data members:
    RealType m_lower;  // distribution lower aka a.
    RealType m_upper;  // distribution upper aka b.
  }; // class uniform_distribution

  typedef uniform_distribution<double> uniform;

  template <class RealType, class Policy>
  inline const std::pair<RealType, RealType> range(const uniform_distribution<RealType, Policy>& /* dist */)
  { // Range of permissible values for random variable x.
     using boost::math::tools::max_value;
     return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>()); // - to + 'infinity'.
     // Note RealType infinity is NOT permitted, only max_value.
  }

  template <class RealType, class Policy>
  inline const std::pair<RealType, RealType> support(const uniform_distribution<RealType, Policy>& dist)
  { // Range of supported values for random variable x.
     // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
     using boost::math::tools::max_value;
     return std::pair<RealType, RealType>(dist.lower(),  dist.upper());
  }

  template <class RealType, class Policy>
  inline RealType pdf(const uniform_distribution<RealType, Policy>& dist, const RealType& x)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::pdf(const uniform_distribution<%1%>&, %1%)", lower, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_uniform_x("boost::math::pdf(const uniform_distribution<%1%>&, %1%)", x, &result, Policy()))
    {
      return result;
    }

    if((x < lower) || (x > upper) )
    {
      return 0;
    }
    else
    {
      return 1 / (upper - lower);
    }
  } // RealType pdf(const uniform_distribution<RealType, Policy>& dist, const RealType& x)

  template <class RealType, class Policy>
  inline RealType cdf(const uniform_distribution<RealType, Policy>& dist, const RealType& x)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::cdf(const uniform_distribution<%1%>&, %1%)",lower, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_uniform_x("boost::math::cdf(const uniform_distribution<%1%>&, %1%)", x, &result, Policy()))
    {
      return result;
    }
    if (x < lower)
    {
      return 0;
    }
    if (x > upper)
    {
      return 1;
    }
    return (x - lower) / (upper - lower); // lower <= x <= upper
  } // RealType cdf(const uniform_distribution<RealType, Policy>& dist, const RealType& x)

  template <class RealType, class Policy>
  inline RealType quantile(const uniform_distribution<RealType, Policy>& dist, const RealType& p)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks
    if(false == detail::check_uniform("boost::math::quantile(const uniform_distribution<%1%>&, %1%)",lower, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_probability("boost::math::quantile(const uniform_distribution<%1%>&, %1%)", p, &result, Policy()))
    {
      return result;
    }
    if(p == 0)
    {
      return lower;
    }
    if(p == 1)
    {
      return upper;
    }
    return p * (upper - lower) + lower;
  } // RealType quantile(const uniform_distribution<RealType, Policy>& dist, const RealType& p)

  template <class RealType, class Policy>
  inline RealType cdf(const complemented2_type<uniform_distribution<RealType, Policy>, RealType>& c)
  {
    RealType lower = c.dist.lower();
    RealType upper = c.dist.upper();
    RealType x = c.param;
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::cdf(const uniform_distribution<%1%>&, %1%)", lower, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_uniform_x("boost::math::cdf(const uniform_distribution<%1%>&, %1%)", x, &result, Policy()))
    {
      return result;
    }
    if (x < lower)
    {
      return 1;
    }
    if (x > upper)
    {
      return 0;
    }
    return (upper - x) / (upper - lower);
  } // RealType cdf(const complemented2_type<uniform_distribution<RealType, Policy>, RealType>& c)

  template <class RealType, class Policy>
  inline RealType quantile(const complemented2_type<uniform_distribution<RealType, Policy>, RealType>& c)
  {
    RealType lower = c.dist.lower();
    RealType upper = c.dist.upper();
    RealType q = c.param;
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::quantile(const uniform_distribution<%1%>&, %1%)", lower, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_probability("boost::math::quantile(const uniform_distribution<%1%>&, %1%)", q, &result, Policy()))
    {
       return result;
    }
    if(q == 0)
    {
       return upper;
    }
    if(q == 1)
    {
       return lower;
    }
    return -q * (upper - lower) + upper;
  } // RealType quantile(const complemented2_type<uniform_distribution<RealType, Policy>, RealType>& c)

  template <class RealType, class Policy>
  inline RealType mean(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0;  // of checks.
    if(false == detail::check_uniform("boost::math::mean(const uniform_distribution<%1%>&)", lower, upper, &result, Policy()))
    {
      return result;
    }
    return (lower + upper ) / 2;
  } // RealType mean(const uniform_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType variance(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::variance(const uniform_distribution<%1%>&)", lower, upper, &result, Policy()))
    {
      return result;
    }
    return (upper - lower) * ( upper - lower) / 12;
    // for standard uniform = 0.833333333333333333333333333333333333333333;
  } // RealType variance(const uniform_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType mode(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::mode(const uniform_distribution<%1%>&)", lower, upper, &result, Policy()))
    {
      return result;
    }
    result = lower; // Any value [lower, upper] but arbitrarily choose lower.
    return result;
  }

  template <class RealType, class Policy>
  inline RealType median(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::median(const uniform_distribution<%1%>&)", lower, upper, &result, Policy()))
    {
      return result;
    }
    return (lower + upper) / 2; //
  }
  template <class RealType, class Policy>
  inline RealType skewness(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::skewness(const uniform_distribution<%1%>&)",lower, upper, &result, Policy()))
    {
      return result;
    }
    return 0;
  } // RealType skewness(const uniform_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType kurtosis_excess(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0;  // of checks.
    if(false == detail::check_uniform("boost::math::kurtosis_execess(const uniform_distribution<%1%>&)", lower, upper, &result, Policy()))
    {
      return result;
    }
    return static_cast<RealType>(-6)/5; //  -6/5 = -1.2;
  } // RealType kurtosis_excess(const uniform_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType kurtosis(const uniform_distribution<RealType, Policy>& dist)
  {
    return kurtosis_excess(dist) + 3;
  }

  template <class RealType, class Policy>
  inline RealType entropy(const uniform_distribution<RealType, Policy>& dist)
  {
    using std::log;
    return log(dist.upper() - dist.lower());
  }

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_UNIFORM_HPP




/* uniform.hpp
sxIJckkt8BVHFumQK2mkFnuShG7enswPlUTv6xK4QEgk4Yz6hZbgglyFtjzApYJ372BHnzACvm970tV3ftAOkZbMRvVuF082V8BN9HCwjeq3alrgT04IB2JbJco68WLtgy4O2761vmuYvJvkwPjkWvv26S3lfQBmpvqRoajRfmPk+Uhe5I4EKkEEQQHSfoP8x7l+u7o2My0bj98HWtcaaJYqoa9L7nBt3vqmD2fUJ501TLO7uhFwChViDb+668w+KAL8H3gfx0uLJkGphOrZnshPT7uX9E76saHKwNsLkgigxN9+J8qOCL9KQsPHjy2zfRA3J9DxypSttLf2REIDNfiz7fjbkdJ+SaT4uH+imXIx5qTaaKpvUJMKe/ahiHEq56X1uNNEfC/BN9kse8vch7VjSgeNj1bKtogk4C3Jp/IsF7pRnc3WcxZq604lvYJBS3kk6bc+9Zb79jJpGGtrNjVm3i4WW9jXS4VUwNpb81aTYKXTC8NLgdGhYsoPLAHRqSbUzJbXrLgUAlq8lenqs3E94Bd5Opio5dcagetcy4TFz9gq2pX8sWhO4jbHF/7h/xLLMBagcytv1zIQBcTgRb5LVfggtIGtOrgtgKKmU6o8/skAhDkk3ui4qACzk6izWOluyxRIKNK3bFMQ2ZwxR49cx+L+GJcfYpcGvGcEJzXjn7lMg9RDsA8Hwv+4VgwkIKMVcSr0aaiTsghn8SCkmob0fXxoqhJcscH+naisJdkTZBK4lY3KoB7imd0lpmR7V+QSzzyEn3Z7D28vP1Sr5Wsnn0u86aAM/J6BkQh5bJoMnPBtW220fK5wx//QVVw2QwZVAuoAfEbLF+rKfExXupgdjJ4aq+5gGHbFeogHzHbbqFpFzFt3AGqcx/iIKvhjAxPkY3hMT/wuXYtMotS+LGKiDb8UmFWL8haIa0pGCivbHiI6pBCCJ13w9ZnSEoTAHXe8uqYU3I5BPhWgMSNesW0sBBeMFGDC7nj9tnq3HoDQ2HsB3MYLG3aglAaMIZofQj7xiLuKB/eyodKDzL1x96neT2XdMLQmHhUh1I346YCiyDJExqBZreguMG9pgPi53CxuCH0DQM7eOLZLKy6iBbczGWQsf9QI11wOTl09mLpEZ72TsBNf+oCmYtWNzM8nXa2mY+JT59krgSsNBHxxfWBPFa2R9bcBXd5mOPcf/Nhi4rGeS1hNmbRbJR+4M4RJLGsILnqPP+dXFJmrRWngPcmn521QVzxIAyiyaXGKaXUg/BTf8jDSbETvdk5qm35RCfZa+woQ3mM0g02krqd06vJwA2IjwPKC8wlkgnWn6THgD1Q2eTAHmd1NtVVMJeX54quJWAj6oJ1lLPflKYaPp5gwu4OqUeJQ61NcGYRVrxEDjOFdlY0B8lhN+cDNRwOaGrcQ5m4vk2/XRl03eF5WG27LwbOXwXMSs7KkVIqNIDDDdQUYycDSQigTkY7YUpHi7SuVhRNUCsMYps8Npy5jcrOW4Q9RYWYWOfvIP2kmFopjxU/hquiv80QCogmPbOEDEwKKj6rq6vZMDcGOsRnFVN7mPYu7q0Zdn7gNQAK5nbiaHFfXLt4/VgSOHogDVQUp97bZAcxMfwMdhbiGyN7XJjtRIPXRIWUs5cme1q50q9C8O8g6DISwyaG48DyuQDC0j6m5HcBSynKjazaIqdTY3GgIeKhGHGccdmUFPGZV1oIcFIbcHN4EuEBHePZ5ITADOV6WmNS21rKvQ9dNWc/E8P4YUuXIIsXpkR2mld1OV5d3MefyUxFWg+UI7y1Z2JKDWgHilYpXl+tzLTGLd3ADh/BJ4ekjCr8zkchKfIwcJ6DB6+joGvzw4cBReC0Q42GEd0CJwAiAOwwseT/Z7yHPd7D+IP5t/WAwvpbR6+VLgz7jmz07uRR3eXl8DfYh/vd2ycYJX89RE0ABcCBG8CzXo653DUnUFvJyDNstTdp+ewBDq7hUGbj1qtoYdXXxNYal1+woxXibDHe1hZTJZow2qD+4YUNyeaKMKNYAjC5VIj0meChBWGorTiTob7M2yQcNCE+65AM8mTYOzwi0Bbns7d6oAGA2bfpNzDMfhCIK7B6QalDf/X0g3yQyewzbiC6yyhsfr044LZdSX/Aj4KgvBH07nj8OsWh+hUqiq0087650j4g/T5CUCHQS3TYb5kfU3q27K2e/BQBDIL2hJbuFLajT4WmZfPg4qAvRTb4+1fOOhKsPZKfSUUhcoQl4avXOKih+/LYyNwgrWGkmfYFPdPV3JztqQn/F1uHIXyTXERj8RlcHpixnb09ksurzRpNrR+u1u7X1OXsM4tnpKgJM63C8hYBha/uhXY/Gu+aETu/nMWJFGbc4qjn+o61Rl7/fVTIPeiQo2mWcHicmdbjk+NZIfU27z5TgmctLR6EzCH0GqYpSZshQAWTJdxLmlXvX1VJb7vtYlRc3303m/tRQnnbi04ZCDM9BDWlX5jLNATY4x1Pt2P+TERsE1aj35F/4CO/Pv3Hd7UH4UFJtWnhGxylbqegz0O/s3INeHbESgp44q1qZs6WXWfkez5wgaZnKERer1orYaZA695vYOM6UXJJCbyHh+9o9XlCHhenqjmhiG0+Q768lvtpBWEqfvQq6lYrLKL9yFou0CwKivhMcvKwDOx+liQM+ZX2LzS7XWArMlczJa9NsuOso3BKEaXScBAgQxDcSRIv7fybOXJdz40NO0fpNM+tECttvvKLxCAocVzUSzA80gL20KnFO/t7Yf8tKPC3Ya8cgrJbP3JraUmKyayU8OFDloor6bukNidHDi44ZbuEi60RksOsDw0qBuv8SZu+tqRcwROAZk2H9zXjAOEIzEBxstY/LjC9iyPucQJpx6ZJkPovlrY6e1JOrWufOcOcMFSLx20A3h78jW//rS1+pvXg8CRUbIYbLnZAQSYGfQECN/2/1H20KuHpzbEfFUOo6Ka+4YA5reob9RLaTOkcViqRHhvA2TtXdjeWlKkjxVzVNt3QXubPtzyS4uTKnmmaZwc1sRF1HDwScP3i9np67grL7X/4z//71s5xnAzEkQ/9RzEBz11T4UeIXavd+mJcDF7JakX39ADtwSBk3AlALELNgG7QYYMb0293KEV++J1t7bEf5IBL0XUK74tojBaZ5eZ18y+abusqno6tEWQfN4+YRY6162bvSUUXPXYfnJoTAj+4R+PBpMYnMkvyZUp4Eyxff2JjiOjSsiT5bu3bw1WxQBnKk84Prq9OjbH5e2o1O5x5ZACtRGEHCYED7vSVle+xPlU0mjrqtzwaK1ewq7CUac318tKwt3fvXhoqtpcuzlBYMG7ftzjcf7xjAmm2qYEvuL7QgMzEjaZ+oHIzu3NppAwi/hCgLPk6AD5NN2kvjIAxYodL3HDo76r5o8VCCBHPkYqnzQsHwzkD7Tym1cxRXRp7bRJYf7EpJ3yyklz9MqaqHM3bwUGHoRzvBQbXyVg8N5o1d5sG2cOOWIpxNVxGilWE88AxaAaYE0mb/KM3GcakxXgKjxFMLq6WJEgDNJwplzbK/rvE8K+Z5Ovjn1y0NBu+m5Vp0YyUlEDhHgWcJY9qA5OchjDuO907U/7idnciP7CiYNvzD3QtlTlbhe4ODp1kHsWkGRv3AMAOXrGFLejGzdsWZmkjCkBeoepZYTKZZoYeOEPTst7dIKXhuANMeEAGF/hzC+/r5+QlUBQQI+hX8K+RX6K+wX+G/In5F/or6Ff0r5lfsr7hf8b8SfiX+Svr191fyr5Rfqb/SfqX/yviV+SvrV/avnF+5v/J+5f8q+FX4q+hX8a+SX6W//v0q+1X+q+JX5a+qX9W/an7V/qr7Vf+r4Vfjr6Zfzb9afrX+avvV/qvjV+evrl/dv3p+9f7q+9X/a+DX4K+hX8O/Rn6N/hr7Nf5r4tfkr6lf079mfs3+mvs1/2vh1+KvpV/Lv1Z+rf5a+7X+a+PX5q+tX9u/dn7t/tr7tf/r4Nfhr6Nfx79Ofp3+Ovt1/uvi1+Wvq1/Xv25+3f66+3X/6+HX46+nX8+/Xn69/nr79f7r49fnr69f378A1H7n393jayFHKfkc/fj9DSqI3hflEyLMpaAD0Hk7hHjo0rTq45A0DfGrjC1y5mLTpd9+cJWGpr80FsRHdpORNmaGm5oLWRa3vGfe5BSsrN8ziItl4S84GXxS9na/a1WRotK+DOZdtE7GOHlqTWH7eFiicI9APPMie7I56IQYe+FSlT5PzXwoXYx3un9fk6Gigzmq2UTjUOo3u357X0dJezccuPYybIYwxjMXKA7iwoeb2mZt+myjV4kzuIBL7+IJU1+3EyTTcrc/1tgI7/JMHfOtgU9Wc8OlkId59BdWKVnMiBUwjuoDGJdgXhhuRSk3fRRdGJhnox2MTqL66YjikxSmwCTEK/HrRC92UA5XQ0LmzWAotkfcgFCW5qzHqReTDhh1eipZUJW1s8X0fUgq02VBuejRzzt2VFSpXsP2aBBhtXC9T8qiw+jDZ0HLr8t3DtiMxAoU8YpYtVvPW8AQsUyI16QH9WUHROGH7VMvM32SiOrJGN8AcXVVSKrupMmx0WmXDoRKosDn+yOMAOtLGkdtMgnwN9MygyHaBIe8MM2l2tgbx//Lif0sKOekd0N8rvvMTw/pmkpIsXF4SHc4K1yCMp39AabV02ckR9mgYm9F+M93Cxhb0SHCUUh8qQgn4hqxaGNSuLVGBqu0Isg8O+Vx34rJTkwpCbVOxCbWLVTKkwIj58JMboCMNwSbNXs2JKoNC5TLqsoQ4Tv4AV74OzEwVxO3zw6OIv9aFi06LZtqeITLNw4D2qWfXfsWSovveeTTHv/SDRcEDe3Tv1OBZuodJqa+6VpDwayfWDFXOw7tzcxKDve1WZfrTtgPp9jvMz4Kv32l5bnVlLh2RGCF/H960LDdyOSP5EwvpuOR7fOFa17Kh06qXFIhaDUFBnNa6Tm9UigNDIK+tQUIEo4VA7wo+Rxu6zH8eockidB4WiXRNXRbPyWI1En1T5AzpPxh4DDgYUOL/juI15q4/PXCu9K1KqjSRyJ1t22HTILMeqhfr1ksLZuCrswa5UqZOMMwXXKV6IjTbi45uyyARklasqPSiuIFKUyIReztabLdyUdQXc7gyIuafSL90Cdy6yPnSeICdNs+s9L4ciHQ7QElkNOIb/T1cMkUtdQE0lwE3e7u66WhAPGvj80h2oPqYzMmuZ8haerzUPvR2MTWNGBMPyLikfryfeMvvM7x+Ia1ePU60Z+r9f5T+EhS2HqboNp42PPCwdO1CKUSa4zAebCS1Rq8SHb4CXkU1aPj+dGCKlC1vQ4MNgSzLzHG8hxa4UwD+In3E/MTF20zPrmIla/AeKGNk50pYWhUlXbxqJjT0E6ZDwxsAS8t4C9fGwL6gioC/7p3wEnm2vLhUSZxkk7ZUSNOQxbrtfgoORs5Qxoz1ji9Ec0vn8QTifMwhNtpvTKe0ypBxXnyi2cK2eInJvkZPrFDvIp6y9UsQVPmvqoiGHUEf9ih72TJlgv2L9xX0YYpH4AVxpZ9X3KIbOEwh7ifIJ0yfmaNa5NMknVUD9A6aeORqT2q5MTqRke3hLygWxVQ+CR8Xq1ekcT+3txhxmr13vv8oWCmSv+8q48Qf33ldaVfEgDe934B2hKTrBEKgs4vpuCGQrS/jd3rG/pT0jP3Q4ovsd0wlX3jR7CPVy4smJ0/Xs5PGw2CU5wlecOkVNIGVs3I9pyd/4BPRgH9UAoyXdFFacfUKIUJToTykZDvLyKzZGVRjjloR2/vkY1YXgPniHYoV3ksUKyKrzCnGmj2E+dM3ggNbCPh1xDcUjYWn5QPFhhSNquyOB5eZFIVvY7l4/MX4dGFgtlaj5lOm0t/I/rBm1c2npoLJQmI2Nc9NOy+v+WHewHv1iGtI3Yqn4K/TZGQqG55RWQkf03+7CBozfTbVISHfCw8L1ZyXXF2xAFv3h1JUQgRoFH7vThQRRjbbcfHqa80RVDbQ/iKWggoW5TgzVesDfMA/ZCDsgAALP/T3aORIRO2DQfhBF26Gy76B7OU2z1hhS1RpFU1reBuUkx72cFsGcy/2ttRJ70S3c7v5+WTPz/aVBQMRvyBVjHXhzmJbxq/0zS9hgW3v9bcEWb/u46cZ5VgEN8M1GI8kaUBrml9v2Oqnj7aEUuR2Va9w9Ksfg6m31GgEu4urLsJYZ5r70sOhoKtbJjY0LYdeetdr0Yq5GYFzE1IDlMB8jUWyI4O7E0Cij7lwK71nEaz1Dk7voyahrjtfls5zmd5usogydGEFm2u29bC4QvE3LNhuFTq0CIB/jsOgAhZgq586mCHolzgwZSwTJ18ReOoLwSDzlcxDI/gUQXB4fUNiSl49R5ZcMsEtomhVgk0GORjkyYQ2OP0B+R6kso78YGSKMMHH51UunZhsfXPktEeC+vFTeTf/sitCePhJpHgGgJq7ekolEeBz8RcQKbcPr9wU9PdnJJykGm+AH0139UmB+cpBCG9Fkhjcr2UMt2fjB3ZB1bv+olS7J6t6YrgHHhqUdkUfZDZpKB719652FUS5IKYaoQgbLHHMbdgkWNMoEBbyPjXdqvzHKdvOF0ZZUakVCbzYGzhjiUH/HmTk1VNvibhdSNZvGP0SMLqrCU+wHgt9T+0VLJdow54EFq2/nDTAGDIZHvvlVHYQQTZ90L4TJlYR1GdiE6SpUfKn7BVFyZImO3ZB4BA/t3ryyWPdKoyASfA524y9hGFWkwiZ3omnbw/DKRurgkOrOPIotXXlRDMXH4vnK9t0SiCoc3oB969ktKSQOYjB7MpE1vq0TMvT/QsxwNrHfkqLTTTF2cJrCM2SVq4OlqDyxUEExTHK9O21mUe7Tc3sKMfROr5THpJP5kJLX/wlIAGoWfD3F3W4JGJ4mRXddAzXOckyOQgtGmdl2ZumXYKnPtPgPYJTOO2g4BF8teESE9LhAixeFNEfY5Re8y7RyJL3jvxVTv/WusoqPNSIrbfdFSF4kq4E4R8YqvzTKZoYjDHy599+oAkRjG2Lrxy3O4DghmjdUKHqsJJhjDeMccyz5fahIYUE5QPs8/Z4884Q78SFSTZuZTABPWmImfAm2Qb5b6R9xGNwVABAsBbCLamJVcxY3/e4vcKc+a6AhyIloe6IiN6uxqRBeJsKrFRREJLJ9BMKcWOCEh2DKPH91Nedw//RUESTSCyfsQMAkNd8VX5xPyYAsvQw44Jji78urMkFQUiRWYqfAvlce5Eu3Hau5LKudr7oGQjEq47dlrG3FQWegUBguIHapets1BBFMsFNw3bn+kNc4KoQCWXArLts15LD8JJFUGY+DKT8U5a0TmHv+/CQ46oZFjR1bB5D28TSgRrOqCcRCYnUGr0DxhXmDci920JHSV1MYqEc0uDiRfV25lRdu7YwbGQhAF6C30GsdL8onU623LdC0Llqad0hr17XKKXg6CKVuZcewEP+Ve3TUsHHBMovb4qzn4hqS7h+t0V8ARDilQDFZu72gkBFIFOr/4JFItODAvCBwC7799Q3EQTj+bbkxnIk3oK7uSTAPKOW0DXvMSuDMpBi4MkA/Mo5eY6QlllKky2eXTZ+ZK7Ly6qoYz14uNdCNUwgZEE4NzN17Nu6BtHV5TWizHJzgIhjvDNIcFlWZD04IQ1gcENJMopCO4WepoIYmbkjaBiJquntXl3/743pUXjmNHFAOpF9UWBAr+hXhYGim3HjGqzfKs1OCj2Ukd+eKw9XiFltoMwiD0KTjcfMsbx7ITfJfGsHG4E6kpqA6t1SRHyHQsc0DHxg/4l8pwF+7Nj6OHbtt2jcitdIxbz92/aRvVs2pbYtWBumU83zb6C0Gypx8anOO4k+CSrO7N9z62n6aPP6TgM9jfGQJBenxYqzBah921tnchPM975a3lWTgkbKMw2Q64N1BgKyy2KN4fgBZhdvUdbuS4fc3ShmAoyAmxcH++ev/xYDyCQqByeYmAfJmviurKERDwJ4iuDo2uvjgxGED4AgXg+idMwkXwWaBgrJi84DLY3Si5yXi1a3E5WwACLwGUm5T7jPwixpH/oCY5jxIZL/JbU7NfmJ2b89GJ7jcBswaiaz2g5AvX4nhL+GCw9ACr4vC8CY/8MR3H+TuUJp1NDcOYn48+aknWB2XdK3xBgF51eQOv53C49nwX7miKz7h+plN41mlAsNigyKPHRkqw4jb8gQNhKFg0Ic4JxgAXZBI3gemLrn3OaWBqgeAORc/eymGylLUYEEx/ax5scePt7SKQXlaFKMVuj3B+3yN5i6Cs+A193evniHkECjXfmD0+yltBIHmMSRZRXlyie9cHs7trkYMDVhdLRKUl05BDsLFU32VNFbJsyMrmthQkglDJYZaafZnk5jX3ZPCWt0rvh0Q/aL4Iz3w1iBZoexiO8lSv4PxLTVTEl512TnlvCNolMFiyDfvpSgRM1QYFXRAfwBSmYSxdE1YqDC7MqIluYSvavBwQDfKY67k21i1Aknpw2p8e25jiJt2bbnY9sPnUyXPfvKCibsMvif2/pdjw8q1aQQtsZy+lKa1CWmkoF2CZQW007l5WQkL6Q55zf0iUaaveGrxXSM5TCpJMZHVjdBHwUJV5VkrGlsaJC4EME3qogdU2CkgEhV+3mZIF4K8v2nBIEQPorlCydhtlRLN4AvC2VY+2n6yYLyzE9ZaF3M84ys5+ngANV/chBawh3mEnEescOZj55tsudnT3TP7vbPXRvun9cP13gHguWx9R/bBcwF12tA3JMTWHpog3NW/lSLR/KOdzDHfTc0znKUMgYssxMFpxzwknDGrXXzCYGB7lKd9+Vsg+OR2LzpeHpkhqzLhi2SzRBJAN8JTunEWBiYgQbd4LjOoEZc5Pj+MCYNHwXHPtcnH8kVDsK8+XY9KN/FnCPO7erA3DSEsGl+GK0OiNEmQ98rV/uSLSTSZZZ2wS+G7WfdeJ3jSSoQrIHQLRBW96r9gUrgwiAh+OOotMV0PkKnE2q04YW+zKDJKMQwIR7fQYS+z8A0LDSrv4DKGNfLYstwHrM8ZSHww38h3Lcgo64AXVXGP/inoy3apF7hDAV7QImJgwBv9p3YB+EcyjC7n88LVBqn1QcpiNFhdUiWRU0HhYXyDcnojz511uZPp+dDOZigKV4VuZpQ/LwIXiJbKao9PGchQSJfzc=
*/