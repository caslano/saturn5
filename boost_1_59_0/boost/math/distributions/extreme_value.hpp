//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_EXTREME_VALUE_HPP
#define BOOST_STATS_EXTREME_VALUE_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>

//
// This is the maximum extreme value distribution, see
// http://www.itl.nist.gov/div898/handbook/eda/section3/eda366g.htm
// and http://mathworld.wolfram.com/ExtremeValueDistribution.html
// Also known as a Fisher-Tippett distribution, a log-Weibull
// distribution or a Gumbel distribution.

#include <utility>
#include <cmath>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4702) // unreachable code (return after domain_error throw).
#endif

namespace boost{ namespace math{

namespace detail{
//
// Error check:
//
template <class RealType, class Policy>
inline bool verify_scale_b(const char* function, RealType b, RealType* presult, const Policy& pol)
{
   if((b <= 0) || !(boost::math::isfinite)(b))
   {
      *presult = policies::raise_domain_error<RealType>(
         function,
         "The scale parameter \"b\" must be finite and > 0, but was: %1%.", b, pol);
      return false;
   }
   return true;
}

} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class extreme_value_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   extreme_value_distribution(RealType a = 0, RealType b = 1)
      : m_a(a), m_b(b)
   {
      RealType err;
      detail::verify_scale_b("boost::math::extreme_value_distribution<%1%>::extreme_value_distribution", b, &err, Policy());
      detail::check_finite("boost::math::extreme_value_distribution<%1%>::extreme_value_distribution", a, &err, Policy());
   } // extreme_value_distribution

   RealType location()const { return m_a; }
   RealType scale()const { return m_b; }

private:
   RealType m_a, m_b;
};

typedef extreme_value_distribution<double> extreme_value;

#ifdef __cpp_deduction_guides
template <class RealType>
extreme_value_distribution(RealType)->extreme_value_distribution<typename boost::math::tools::promote_args<RealType>::type>;
template <class RealType>
extreme_value_distribution(RealType,RealType)->extreme_value_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(
      std::numeric_limits<RealType>::has_infinity ? -std::numeric_limits<RealType>::infinity() : -max_value<RealType>(), 
      std::numeric_limits<RealType>::has_infinity ? std::numeric_limits<RealType>::infinity() : max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(-max_value<RealType>(),  max_value<RealType>());
}

template <class RealType, class Policy>
inline RealType pdf(const extreme_value_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::pdf(const extreme_value_distribution<%1%>&, %1%)";

   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if((boost::math::isinf)(x))
      return 0.0f;
   if(0 == detail::check_x(function, x, &result, Policy()))
      return result;
   RealType e = (a - x) / b;
   if(e < tools::log_max_value<RealType>())
      result = exp(e) * exp(-exp(e)) / b;
   // else.... result *must* be zero since exp(e) is infinite...
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const extreme_value_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::cdf(const extreme_value_distribution<%1%>&, %1%)";

   if((boost::math::isinf)(x))
      return x < 0 ? 0.0f : 1.0f;
   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_x("boost::math::cdf(const extreme_value_distribution<%1%>&, %1%)", x, &result, Policy()))
      return result;

   result = exp(-exp((a-x)/b));

   return result;
} // cdf

template <class RealType, class Policy>
RealType quantile(const extreme_value_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::quantile(const extreme_value_distribution<%1%>&, %1%)";

   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_probability(function, p, &result, Policy()))
      return result;

   if(p == 0)
      return -policies::raise_overflow_error<RealType>(function, 0, Policy());
   if(p == 1)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = a - log(-log(p)) * b;

   return result;
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<extreme_value_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::cdf(const extreme_value_distribution<%1%>&, %1%)";

   if((boost::math::isinf)(c.param))
      return c.param < 0 ? 1.0f : 0.0f;
   RealType a = c.dist.location();
   RealType b = c.dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_x(function, c.param, &result, Policy()))
      return result;

   result = -boost::math::expm1(-exp((a-c.param)/b), Policy());

   return result;
}

template <class RealType, class Policy>
RealType quantile(const complemented2_type<extreme_value_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::quantile(const extreme_value_distribution<%1%>&, %1%)";

   RealType a = c.dist.location();
   RealType b = c.dist.scale();
   RealType q = c.param;
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_probability(function, q, &result, Policy()))
      return result;

   if(q == 0)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());
   if(q == 1)
      return -policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = a - log(-boost::math::log1p(-q, Policy())) * b;

   return result;
}

template <class RealType, class Policy>
inline RealType mean(const extreme_value_distribution<RealType, Policy>& dist)
{
   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b("boost::math::mean(const extreme_value_distribution<%1%>&)", b, &result, Policy()))
      return result;
   if (0 == detail::check_finite("boost::math::mean(const extreme_value_distribution<%1%>&)", a, &result, Policy()))
      return result;
   return a + constants::euler<RealType>() * b;
}

template <class RealType, class Policy>
inline RealType standard_deviation(const extreme_value_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING // for ADL of std functions.

   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b("boost::math::standard_deviation(const extreme_value_distribution<%1%>&)", b, &result, Policy()))
      return result;
   if(0 == detail::check_finite("boost::math::standard_deviation(const extreme_value_distribution<%1%>&)", dist.location(), &result, Policy()))
      return result;
   return constants::pi<RealType>() * b / sqrt(static_cast<RealType>(6));
}

template <class RealType, class Policy>
inline RealType mode(const extreme_value_distribution<RealType, Policy>& dist)
{
   return dist.location();
}

template <class RealType, class Policy>
inline RealType median(const extreme_value_distribution<RealType, Policy>& dist)
{
  using constants::ln_ln_two;
   return dist.location() - dist.scale() * ln_ln_two<RealType>();
}

template <class RealType, class Policy>
inline RealType skewness(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{
   //
   // This is 12 * sqrt(6) * zeta(3) / pi^3:
   // See http://mathworld.wolfram.com/ExtremeValueDistribution.html
   //
   return static_cast<RealType>(1.1395470994046486574927930193898461120875997958366L);
}

template <class RealType, class Policy>
inline RealType kurtosis(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{
   // See http://mathworld.wolfram.com/ExtremeValueDistribution.html
   return RealType(27) / 5;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{
   // See http://mathworld.wolfram.com/ExtremeValueDistribution.html
   return RealType(12) / 5;
}


} // namespace math
} // namespace boost

#ifdef _MSC_VER
# pragma warning(pop)
#endif

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_EXTREME_VALUE_HPP

/* extreme_value.hpp
m8lD/Yr+4TlBjksr5ISPAs2gohb6dOuCORV6s4gkPwgS5W9r3MYs1/Xfm424j/3WA630Y+nVXhVYpoecUZCuB3YK6bo40zYzLZJnbg1FFjBf8INrKzfDe/Sx4ulLsNUPDp6ZALUK7gunlYdqaSE6E9cce3EG/b8W2dML6GBxAqtzEyZc3RE0B8MqLTY4ME9T037Y641dDyYpp60nrOHJy7M3yWesI8DzvASw/3wgR83KOVPp4HlLk263mFP+XR9+ntbln9Ytv8FTpS/i9wWhb25UpWjrPsKuNXzSS138q3ZFtf6KpIA7QB0qxG+/CulI7oXWYuExM+pj5BaHGmW2twGv67yGUZMBopdnM2u8U01aBEzVBe/+jm5kHIuUgubJWnsw8EC75PcaBO06fNPJ50c6pqfylPmXLahzvh1Ei/nBu4GEbTLvwKG6+5WqdDRUSajQMnnGfzRHucj5BB4XLH5zI/W3jbcGQdSSIhws14841g4oOqBt4AZHbY9Vn6zTB0+azivHFi71crnd7RzWZb0AZqO0ciqA/MLPGlMDWNUWynp9kM41P+pb3ngFb1PMceSJY63RSNUpIhhAGIZjMSEN0hhP8SggdexK10nOCAIy/nYsAoKrOSWka4RwBPkJh8xIXAbjNIWfS0Gr9OrW4gwZx6LBAXuDcEAuwGAkJw64uZpqXTFpJG3w4P3LjVTTcV6OtdXuZePr+enKbwb7CnuNgeCoyQZ56eyQ17MIGO+U73MMCWvPXLIbaifTXzgdYvdPrA8+4dPesa0f+R4kybc6Bfmkf2w5Cx6qkip8M3yCw19HtatQfNy0Zz/Ty1Cs1lLyVrfof7gVjqyzfLI1OFta5+dxTurky2mdXgJuLf7UQNjBt51lcOl/AY/V/+aqV/S/ImFMGFsP5T6f5J44p+/r7LO7erpyVjT2dHR86lUOx7ekBZSF+59mI620l2KgjyvsWJdDu2x6aISATh/3WYpaG7v5LhmCgLzWpMh3/OtWHuMPrGtgvChe8ImArxtcnTxP+740Zch08zLN9bac6KDZceHdDCC+iSpXRC9Cfv/MIVq8H/Sm6Pk2W9xWm0pPxEr1Tv7ZhTvsQrsNZ48Y8kEakI/WTp/ibDUnLjBxHIbl96NW3RFftwF/qCahyGkUdwzP4k25F6HAr+1L6R2PWQ2Wlam0SnhBhsIPHzzvdY2oQ3Coanm0Z5+VZLw+sFcQvLa7KP6nM5pX9JhLqM6Y8Be92h2F9yZw+w3ivF7x+Af09vzhJuIWYM7M7x/ht7LOhepPeluO0bia19WmzzeEbf8liK8m+VazxGB3r5cajaUZ/d5huImFgLGnRby4iGymGYGO/8oWCyENM5Bo83MYeJHtXMYPguMoXKGN6yJfRHJMPc6+if2geoHiDhJFAj463IfR2gf+rp5oClGQM6pqR9CEFlzBJTx+f6zmJMXfMs9vdlHxg5FsJcBNrwOWBPmtY9YjtZ0PnU1rVp87iKwwP0OWhNX2bor84BKr5/LLDNgJgiiGGBgMsa2/DFo0PvhlucxM24Z0+MPTD7fe7EZUwbeF3azWVeb+ZDO+btMnqCd9PUcIlId/3eXCEhQXBJH5+BGJnS9a6gfvqER0qIZw9wpHxBclh/66isVamepU9szwUHUTRT6r6F4HtFpQYHmsJWqkKWVnLt1IzW7ylKeIlhBQ3YFoDYMidOQlVzztfzP7Uj3aps1VB7n/gw3cwZ9/zx6OR3s9EgRqs+0QyPHa4VKyVTmLlnCFrbwugGMr1kRescywScVMy7CaaI/tFCFq8GbPSGRxqDODz/q5DnjxVse17MnkNZGDA0Fr5lSI/G4+ZNGb8TBgPC/jsmzhDg5ZEZthfM8j8PFKKD8lCVzWZBh1kp9NMG7/8syP+4YM7iWBIh25JU04Hb9LHVUfwJm6Kbd1MlmBGp3M+PT8i+kk87oebvhDH6LaxjPUOqO8pf+CdLhAdvud0yro7ZeqXtaYeuYp1865hcn6t8v378JZbIzNeODQWXlNyckTvTFjXpJz8pKDmD3+o4n6szbHcn3FPpWtmjk4dizTsCVqL4NlVRdLa3wdAmv+pcUdazmy9FInmNljLkVWGOesmE/iDzU02V7JHHs/5wLa2TMVr1RUL7VrgpFPZ8giO3TkcLlX5E3SgBW9j4/KaUWKFwzlcYdNyz/GAO8IgA0QjOP+T2dIO9kNiEOf8Py0HUEAxvfLhxUo6RsWVZarO38IuBwRlOl1DBcYMeyhJ77xgn151htZrEeNXnbOUHDC7vptUJChs/db7SOfc656VTPApLbofvbyQT7C2hERx/Mlv3CWS4lGT5W5MFKBmL2Blo2KzCGP13XlbOiymI3aPusQkpSfJFU6cLr0G0zKUHFZ1hou0I/jLC7p7A0Lw295boRArJaLPjal8ZYHiMUV/Xu07UaC3Bynk8o3btB53pGCNh3aczgVmCILeBu0JAGXU9kqwV5PqDeinXxanNMelFpMDoKVGZDntIAPj3ZFgaPUyklSk2uyjC7J4+vEDlQm977Jlgmd9EldOicbcUaC070T6YCI4lLeRGKWxzGEAV4Qf9xDgtjqBy1BUjKjDspXZYgWQvuVP+bI07+vIhaAdIiqN4+sJSuBz5pW0bFWhF5xTiNk9yG0baCn/lFQiG26RO18WYk6MeiO9IIrXDMYi7+jRmYpXask1aVPox7W9Ki4uojRv4yO3QE5hKWiewYHoIKYa4QNzLfkIiCfwH8f2pGqBKcF3W4zntmAXkbRcdxO22uy9W0/QiH/moTXrYjgZdGv+ypZV/ILxUa4JuFZvZruJoP6j7+DqeOMCi4C4RD0brFHch8ZXRfPs5nnDASnLLb5h3k73ZXM3tbCa48cttHcQP9LLpHKwCu7nFllbBU5s5zxNHFUPMYTHTnj5XjMPwgSDECaa6nibASxZMzhW+kEIgKoVX+yC0Zu07+x7hooeVRQoRBjwlwCu56sbASv/E+EXAEiHHAGQn5SB1UJ8LEk+GkFgjk1T54V42KsqDmzhGgRXceAtBCciFMXCYg3CubQjRyEqVdXasnkd2qbaTs9QTtn8CEo+gQoDy0V4zEePSZjnyKyZorC3bz5TVpreXgY5XOEFi6lH0EAoRRVoIDQgMsQGswkCLvIAc79R/2XhAIPnQlCM5aScXjNJoDxAaGCUuOLL6EY19VvCz92U7wsWQKVvDqFiQQJVqa6qCJIIER/lMiUIgWszSBMTHs0lBscpjGBVKWBOKk6X/nPkB9QGQ54WmCAQl0inILm/04lb4n0eFVO+6gnnAB6L/uA+t639qjOh1s0FCXJJPFlQL2fDn/X94JW2+MxwGFE5Dv2kwFgA8dUP1fnI4ytYILoxMggQZjUfug/rgU3weEXHiKftSQc3DzU2SHJbffFQ/HVlE1TPwQ3nxAEUJo/F8iWYBSaDFvO/FMhIqJXmbQv2x8HLNsDLcPiA2xl4ZC+/mz7Q7BR3RwzyDz1LRh7lU0yxcRH+WjFu6WQ6nxhk41yLHCDXzAiP88Xaa/6mjuxf5qkHRy4XWbiiet/Dow5Fe8vrLjl2V3okP2jUb5vbNWtO7dlrHXYjgi5U6BwNGVebgOUpodKQ2Rx1mLX6HuN9ilPyNr8RKpu3zV4K6PmHUsvTp5KRj4vd8BTjFqMSoxwpZoJU9K2fhvxMrgqME1sm6ZJlQKhlbafsv8lYe40/vQvXR4DnTTdpbr0pOMeTMgZ8QcZkvBCXCh9Ny9bGmSvD+wQFfAsYzCvJLvnH2GRNXNv/+rln8VOKfupfbc0Um1Jc3JXt5RwcsOZW+04g7KhzMw3rOYOYFutVtzTL/JNoMQZ4Hi/Q4QEPPli8bPnW3MLDq9PYz9ChIOqbur5CRBr17+Ig1+oDFUbFRwxYHy8jMDKB9jZUD8YCC8BDKYWBfbxDYhMLizPuSPb+x8W0nf88tnb03Vy1idnGW6Fde2EmKuGqZe3K8hwhOlZb9EqxO6CMT2zJHrBxn2ognw5hFqCLB15SLEst6XV8IA7S8qp0jg5VLSMstu3c0qPHq9NJ7tTHVF7ue5CEEvDqIqws0QjhYTLFaeWNYlLCQk9TnULil6jjWCEtXwImSprFu0jl1FaG0JSLvBA5Fdn2tlXZ6Z0D4XPDuZFiht4vR1z5Vbw4tiyRvL/MlscmteqsYZscPttUduPVcuWejWaWmnd/sD6YM95Ooj3SVuVIilLGazE3IbqLXRGv4KymTHRuBHazlLoOI0AVUVTOMRh2RPndDtHnuORHlWv8aVU7VsLzTpE+U21S7uaV4Ojir/48PYKKR6sJH9W18wdRNUN5sxtfjntPMRbTmmFDRrZAu/krfWVna6x5OOl5gSvDrsnIzLmU9dcsSz9S97AblAa0ZHSiRCBJXUIjPJMs7It41y5zwmi581AF+krwKy22gkX2bOHfqUDlK+Bu98w6SV4IHSk78xE8uDMs6qBQLJVD7HxW4qc19tNz6GwTwq38hyMvOes4XgQ7au4hf8Bzy5cH9OU+q+DrcUX0kdl6emnejwhlD0RBgQQkokAa9aimQxGGi8jkJ0BuAFIDJsGK5ZChbjbMJH2bsqCLF6xWWtFzdbWuuprqZUKkMYkkAZEAmCOQNWxoNdRIMgALa37h/OkN0NGY33n5+ft881nrNv9xte97yTX+ZpzZ4Om06JAGZpMiroAlF29OqbVwLQZlFoTOgxqXspiAFXq6+zUKAa/CvpDUstUVZJs75Pd8AhNgBiYCt0D7Ezs7UzDuAVRt4rmDLrIs0mjg5puiUqt5gJFvU+gslB2/BpdYgm3DuYCekiy4POOmkkOrxiDYP/Gi1bK84nn8TtSGV3NosDpVeUHakotU163UOgmp1MkVI/bVTGUY7cxOZVcbjjMmrUkA3QxQdWE0RscalyM167bgjj+/EnxoE3aNtqijOJng6F1xLMDrdgI/jojfJagYJZypf3oy65DlBehQyF96aab3woc9C/vrMViHAn1Glv5S5vFTEZRp907mf1+Z+pEeLhluvO/haZQJMJhbK0kG6XvVf6E9FFy8Lg6Z0jS2NzZYqeSewZIw2ukdDmGVuoXHDIvqM3bR5v8iiULQ2MbpVKXZCBG0a2DNLdMoNEVdrGYT2+vljlGU1nTbFmadYlbVW46Bo/OlFqiMmS3j27slalxzlqcDxToHGDuWzmxlXDK8PcgDE3792Z7b4g1vDyp0oQJZf6Vs0/WXkWrYIIrGffNzmN8dt11kjNd38ONfw8ELtOfpG7Vmm8hMPxhkCZCDdB6LFzMUaeT9RQ5mEglzMCsXMBC+1WPZ0YUbQHvWrkuNQhIdayitchSSJtMs0InHMkIVHjmqvd+tcQHHhbClJQ2w9aLaoJWDKCLTx/0bFVRB0irEz88/H7odRwjkypeOpyjORYlpzhPcbhH0jPlpG6AP4fU8m67AunMlcdtbcnf2aGuFoYm/PR1FCKDY2ReuYQW4Dj8My9jF02898AHtz7+BUnh+mA7JUvMgbn6Q9mpiikHYq33/lxwU7ATKR98o5QSZZyhud3iUUN7sX6VeI5MO3n5oNJh3OWte5FxSQ0qVUy7JzJpIfKggt8JlVeB+tVWJrRckAp4/nyBKOhtzOszDffz4SohcpMiQU3qHQXg1Io2My9hZqadh0Ewer1bQ//GE1XkLdxKlXNzCWfYx4FVN+xbC85osBaFz6OhRLOyQsfIUPbF7APSOoBGfd9QlS2SDqUuDJI2VRropCZWRCXfuMSiwiDuLx0noPMaqPs0p3LDh0sodoSfgpYWC37e8bibMxOJLr+RDNu12dZCxZJzfYgOvQqMwOE8/cEOiHg55OBLofnP0gTnX6HGxKcN07vHDoWYce3HHUsukVWfwqKmOvnkAAAs/9M+UHnxJHHBr1+f5VlaPcEapxwnn6Ukkl6co+lLoHXrJjh/gBEInAOPU8cTVvfZMi/x3iByjlyWtYYqxtAEu0pAuZz4BXrgwK7Ulq0IhS3GzOOdwZUvhSx6RdcAY9K4LRrDE1nHX+QRTyw8ZZZ6OSqjjxPLQnH69ygzcq/TTuIHb2cclKql2xwAeW4dTmDbnL9fxvdJh/E8OW+uYSwMb41rQheYC2lNjgTkX51Sv1zCiGoNQVsa2sJ5SR8WGpJU8gyLQywfJlz/HApSMDt13TNJn5ns9Ixt+/2Nwvlk9JsNEQWyFE0sEvXMLpGok6rP4toIZ3XHZWqdCFd4gr9MiQZ2gwKBiJ5nRcjFcKUwCQsWwEBDKpNcyPd7GX7/Fg7ySboh0hebg+FRIZnTbZwnwiCn8p4+sIznQBya99bh/MjxbDOPyG7cJ3iWwKaK4+1fCLVrm03p6UjOHLeGkaWGz9ZTe6xCCR2tk7K7eYnM9S0klVO4B0var/qJ1MrzJcxZHzm+FAI8lalFP4/Twx17m9uTpsW0hh0eDA+5H63m2llChUtJ4vjR4U2ySsnm6AOY8TGX5TvJK4xHvNUi2tWmn6HoncYYNpRyBFlz14rmapC6EzPyKfrrH9JTVB9s6alW2wgGxAZVcMIiLJiv4T+LzGh6IzuhIkFg4itxMytEzsKat3H/JfGpmsRHNALsFr2hZFBVn3lKo83pmk+vkWsyHAdZfoFGGQ5vcEZwSuIRI85T/y9/nKqyL1XfHUG0Q9Pzq4si+hTU0iNBfTs2TPuNBKSFIq8J+OyIiwz6iGplu2ShosZFDy4LPhXPE65GhbqgvB5mUeyCF/xpmzb9poda8wZWqfa9tu7FgIIAmvSty8+nilzFRv80zR+sygWTxdC1Vvubiyvw4/k05hQsHE0OL2FZr6wFG4zpeJjTcQwZqVqPpYEvItrmgu8yC/aQKtS7X/txI7bMC3i8vgmWe7fJWSGH9SNyXPJurIYgS8U2P/YvNbuKl0PVloF5lO6qzxEL/KdJEfCsDs8zf/+ld1pz0XMBRltAnuDh/qfGVwY3wpQl12nOivyinkaieYgpRPI69eAtYLRf0kOeQNgjN+jQNXwL7B/brdlQcQugaWU36qEiyo6dv/a5LiG1ktV/hNYDtalLE1p3wQTNsjrVty+G+VyMevgFiTdYLfaiaqGHwR2THAJZKXprZQcGtxyQomrtG6/4Qj6YZQJtplrjOck5j8TQb+lW/9VUf0UT4E9tjQH60JCb7lXC1MjcheBxXjlt1h2wYRAMnXnkZ3lnrgYV+64eZCNIwSOpo0v5i2kZX81GFqUi26KLAo6aXynw2V2UIfypvbTpsiHz79Uhm3k0VepFGhOtaPzeL86Ru2jw2aE54osQojbglyVq6QCUdXIEA6jpnMmtQZbKLHA/+6cwIbaJ2hAeKwv0gLrxz8tz/03jZtdRy9iLobYKj1+kl6yu8YzySmO1LZh+9vLYuDPzdRxZSwVaZ1ssEx8a7zahdtJVuQy7R0e722T9rPpxSgHvC6ys9AU6Xke+M4LXKfx+RE8Hc71r/lX2cWquwa4YwDKnP5gHouB2I/2SDyKCZG+hblfyOsFridVslGnxqdseMJMLtQII3UJ8Z/gJkyyBLnG+1nzRkIEHwVUiFLwYTseAsoO0embZEfAQNeW66E7FiNOkCGeYIKNBIPzUU65W3A+XPIHc4wdXSquq0m6uFZ/UHQ9T8k+qtVHLnWx/5mtt
*/