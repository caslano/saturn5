//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_DERIVED_HPP
#define BOOST_STATS_DERIVED_HPP

// This file implements various common properties of distributions
// that can be implemented in terms of other properties:
// variance OR standard deviation (see note below),
// hazard, cumulative hazard (chf), coefficient_of_variation.
//
// Note that while both variance and standard_deviation are provided
// here, each distribution MUST SPECIALIZE AT LEAST ONE OF THESE
// otherwise these two versions will just call each other over and over
// until stack space runs out ...

// Of course there may be more efficient means of implementing these
// that are specific to a particular distribution, but these generic
// versions give these properties "for free" with most distributions.
//
// In order to make use of this header, it must be included AT THE END
// of the distribution header, AFTER the distribution and its core
// property accessors have been defined: this is so that compilers
// that implement 2-phase lookup and early-type-checking of templates
// can find the definitions referred to herein.
//

#include <cmath>
#include <boost/math/tools/assert.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4723) // potential divide by 0
// Suppressing spurious warning in coefficient_of_variation
#endif

namespace boost{ namespace math{

template <class Distribution>
typename Distribution::value_type variance(const Distribution& dist);

template <class Distribution>
inline typename Distribution::value_type standard_deviation(const Distribution& dist)
{
   BOOST_MATH_STD_USING  // ADL of sqrt.
   return sqrt(variance(dist));
}

template <class Distribution>
inline typename Distribution::value_type variance(const Distribution& dist)
{
   typename Distribution::value_type result = standard_deviation(dist);
   return result * result;
}

template <class Distribution, class RealType>
inline typename Distribution::value_type hazard(const Distribution& dist, const RealType& x)
{ // hazard function
  // http://www.itl.nist.gov/div898/handbook/eda/section3/eda362.htm#HAZ
   typedef typename Distribution::value_type value_type;
   typedef typename Distribution::policy_type policy_type;
   value_type p = cdf(complement(dist, x));
   value_type d = pdf(dist, x);
   if(d > p * tools::max_value<value_type>())
      return policies::raise_overflow_error<value_type>(
      "boost::math::hazard(const Distribution&, %1%)", 0, policy_type());
   if(d == 0)
   {
      // This protects against 0/0, but is it the right thing to do?
      return 0;
   }
   return d / p;
}

template <class Distribution, class RealType>
inline typename Distribution::value_type chf(const Distribution& dist, const RealType& x)
{ // cumulative hazard function.
  // http://www.itl.nist.gov/div898/handbook/eda/section3/eda362.htm#HAZ
   BOOST_MATH_STD_USING
   return -log(cdf(complement(dist, x)));
}

template <class Distribution>
inline typename Distribution::value_type coefficient_of_variation(const Distribution& dist)
{
   typedef typename Distribution::value_type value_type;
   typedef typename Distribution::policy_type policy_type;

   using std::abs;

   value_type m = mean(dist);
   value_type d = standard_deviation(dist);
   if((abs(m) < 1) && (d > abs(m) * tools::max_value<value_type>()))
   { // Checks too that m is not zero,
      return policies::raise_overflow_error<value_type>("boost::math::coefficient_of_variation(const Distribution&, %1%)", 0, policy_type());
   }
   return d / m; // so MSVC warning on zerodivide is spurious, and suppressed.
}
//
// Next follow overloads of some of the standard accessors with mixed
// argument types. We just use a typecast to forward on to the "real"
// implementation with all arguments of the same type:
//
template <class Distribution, class RealType>
inline typename Distribution::value_type pdf(const Distribution& dist, const RealType& x)
{
   typedef typename Distribution::value_type value_type;
   return pdf(dist, static_cast<value_type>(x));
}
template <class Distribution, class RealType>
inline typename Distribution::value_type cdf(const Distribution& dist, const RealType& x)
{
   typedef typename Distribution::value_type value_type;
   return cdf(dist, static_cast<value_type>(x));
}
template <class Distribution, class RealType>
inline typename Distribution::value_type quantile(const Distribution& dist, const RealType& x)
{
   typedef typename Distribution::value_type value_type;
   return quantile(dist, static_cast<value_type>(x));
}
/*
template <class Distribution, class RealType>
inline typename Distribution::value_type chf(const Distribution& dist, const RealType& x)
{
   typedef typename Distribution::value_type value_type;
   return chf(dist, static_cast<value_type>(x));
}
*/
template <class Distribution, class RealType>
inline typename Distribution::value_type cdf(const complemented2_type<Distribution, RealType>& c)
{
   typedef typename Distribution::value_type value_type;
   return cdf(complement(c.dist, static_cast<value_type>(c.param)));
}

template <class Distribution, class RealType>
inline typename Distribution::value_type quantile(const complemented2_type<Distribution, RealType>& c)
{
   typedef typename Distribution::value_type value_type;
   return quantile(complement(c.dist, static_cast<value_type>(c.param)));
}

template <class Dist>
inline typename Dist::value_type median(const Dist& d)
{ // median - default definition for those distributions for which a
  // simple closed form is not known,
  // and for which a domain_error and/or NaN generating function is NOT defined.
  typedef typename Dist::value_type value_type;
  return quantile(d, static_cast<value_type>(0.5f));
}

} // namespace math
} // namespace boost


#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif // BOOST_STATS_DERIVED_HPP

/* derived_accessors.hpp
t7UetWOGq6IusPkmkVphW893b5ibNfBNUvk1eLiKbe59jIjgMi9o4bX8OGHeOMpZwuJ/bHX+EeA6/w4jfJM2z95d44w7ZX9vp3UqHLkGD/BZdTmZ7k0hfoD56q3CQjD4X2YAnuQ9AEn3gIAVIHAAIBkOIHRSFP+XHAHhf8+AAABiAIAXQKJCEiLZLQchWJxMUUgkJFghL4+LWgzlCIEoUh5CIUURnSgxTCKZ8jeRhE8SpIiZSU0UoGAAkICzN0gFaeDUOOD/TgWNJP2lakIF5T9osLFlBwKrp7hFN4NP3YachAiYvs3GITnqkQeD6Po8hkvcVFWFENx4FgXFRHh+udgeOdJTBzfoeLUCounyRjeB6erRCN5+HY6mvENLBIkcBhD975AKLKwAb/jXzhq9kQvSyeMGteoIAVGJEAloRBIAUI4NMXCQQACOwF9iOGeAIHj6AQUZwhjQLCcmfzZrY7NHlyqHrrq6EYcBL3u1SFb6948m7F9L1W1Z2/BQmX8X1H1WD47gcSR9sP5ad3dqhVZND4lMr5X0HT+xv4bh3fyxciIVI9T1e1no6WdpQ2a1zfYDd2GdAz33lveb9qIYUqweuL/YPkPSa5SF2NFfX2U+vhmvSCFfqlpGd5+Z+MhqnSWqpsvKJ1reqJO7W+wfn2r/4vuqdgcHWGB/l336UObfOEllXS1NtyO0CVcP+dP3MO6M7vtA4SJjD/0dLA6asLDvf4/pvaooEepqfmg+Wa6/WPv2SXsZNZC09eQLOhMV0MIfvEWu52JVI8OGS9Kq6WNVEunU0f0TKuwwSgd+x/uQmEQQaqD07kxv//S2aHOSvI/bAb87+yFttPjUFUw8sfN0vXtO3NMd7LMbI9VP0tzu1yK/jlwq76pWn9ZcnKD0nV4SfdzXlPb9Ch7xrSmLZL4HRtb/0G2k8UofH1lUitLW4/hd95/tHin7C8STgWf89TtmB9t3D8MpTfUHX6Qd/aFlDXH1342iDvclwafJo+H/Kce7qdPH9Hm69jh7f5/keXlnfXLt/bLP14x2Rc2y/x13fiYz/ApPj8T3P9k9d0cUrZp4j/2sCxcPnDN7H2z2/7gUA5OevDKbkvkVf8ZK2shk3/Q+b6gAX/ysUFd1fPONXdf+TdG/FJw5kz81Z7J+zDD9MHkX++HM62O7vb44eZ6pe/f12x0XoDL9vhzuPpVX5HvS/Pl+oAbfsf4G4oN+h5M7Ex90TGxjvTn9MUi9T8f/jEeqyvPXMz//9DbF/8Szmel8Zz8gn5v9xmmzELrM+t5+k+U8TNK/zap5+vGnb6rErPnVAD1Vhi37xE/9hO2kRCjRtwFdwlI/KHvxL8fVmDBWNtKm/D7399xaeXuE77jQ8ynUDmZtPMX1jC5uqPTyO4afK/uJnW1LzBXbZf/yb5XXQnpI5Vs5tUye+x2A0yMvX9JLYS6d+1CB9Vdm9HXeO3xUvOzql4BsyvPGp8bU/E0zV1wZ/lsiLNoCz5aKkLzK1L+igJFazRP7i6p+5i/ymoJ9NuHii9+BT+mXzR+616ll9GE0lXhP3vya0ycEasniR0MqLIqYzMnXpDvHoVfx8VPTpuDj3GOVjk6/QmCBrsv+QOHPKoWmStndtdfWhsxTItS3+ZsA76Ew4PI8jLYRXB0ltIOR/r2c2lpTSuJ93Rv5nRmCzk9A2W0gBKnsZLGmn6qqRTZxRN2nkfuxduuLOui8O+jy43sFjvzS5+mCJDK6H3DWI03ze9oX2ewvz86avSLcV6gccRLFOocStdwUubIIr5BJMaJaW2+gTJVLV7eAV8A+MYHepRLIk6Kr8jUav2/6cMMdYIuXAd9F3aj+o19NQfQYOYGKQmr1o1/K9PHLhXz0Z75vCugwIepGU5ZTPuHwTeiUc9g3NsUHZNfezyokWW85dMoY3lls5S34K+gL+lsYvqHYuHUKSlScDnJN3dzQQJVstKSE54HsbvGcfR9J79dwC79dJx/urz8iLdQbhAgSgwqY5PRvLxAUdHKMdxIHO2J7eMtOO+8PBL5dnF8e6QB2SfSnHPu9kartZjQkJFvy6fvkHx7H/cJUE8wr8Zvy9y/+X8r22F+GeNp01LgUNP45/jjxFdE2bPLn23cdqcoXzzrP0EjD1NQn8jJyEKTrOvzUqE+TXFWNiN4FacZyZOLD9+X5n9XMlDF4fS/pvtVDQYGvjtTwZ3w6DnSKv/hZYMg22vMy8NINj8J1g38m3onOw7/TBvM/ZJ9yMDLSLIzUVb4ZkzAVlYPsfx79ez8ag5ZusTWW91BXEn8mRiXxfnS5Fqi6iDWLXPCqDMGB38F+G+YrrpKp7ymP6O/4DWykU36irl+/Q/JI/ZYUfvj3H6Uf3iS/vzuXhf7+3uMU2WOMJksUgOGxvWPbtq0d27Zt7cyObdu2bdu2bWPvd388eauTTiedqqRP0rvXu8M86j+mubo/7sm3j6n/cvhETM60vffjt53HnznfiMQ0T2g6wj4OdWfmaQ87M3bYaMDkrC5WaVlq7WbfasPVzrZX6ai+tw28PjNfnOsEwDKeHm3h+GFl7D9UTRAIvrpOTkN7pIIRlkNjpPAlddGbB17t8wXOUzbAvSf9T7XpIXteHl6D3/cjqGPz813ne8eZM/Iah+aj+BFEkH4STPrzbrcwh4Z2r14JTrYn9LEOJbQ2BbddEmfHF6ejNF0YRiZWoMoQyf8MjlHCE0C8siUx2O1SPbeAPAbyK8dzfBsqmMn37HLb29g1Kf79lS94GfhqPNZJ5EA7/OtL5cBadrfHws7ynaCuNqMrNM2cv+dgxTzT/o9jcLJZaclL4Gic4Lgwjr6EktK4fMcuTRPiuePF7/BwsjudVzAvzZPN7w5s+RCpxvD3iJfs0drH14W8Amg3pismvomhYJGSoPBNcFn4Kya6otYVpHXMrss488IcMk0CtN4hQtHeY9cq2giR8LVZBj8O5Y8JJwGB81iCj78nBO8mW9SsOb8MZ1WtdVqoYr0WtmOVCcpzJ8xHUXHKek52dk8qalOl+SRTbkOlb0m+/wwb6oNYQj9frJ2XdsZ6lBhvpGM1omTkepx4mrPdH5xU+t31FeeGzAm+Ehx+jVfv/UoQOsdsrNyF8tdnaB6lJ52W9uuRlpiphA0nYhabupBIXnjSXii/b4WlhxM5lHfFYNyyBdH5Zxsk/1C5rfJM2019RF7C73EUXNi/sOB9Ytw9LihQQHIjU7mY5RYymYoX3hA6KE+iN+aD+P05mFPbsXu29ae9Rl0VYziYsrNdXzyQUIMhWbgWh+FH6we6kLMc+qU1P2sr54hhI3DkiF+t+99Ah3jTn8/3P1GOHfjVSvObbqFf5Y/63d/m2uZ6zQsE9k9/sMPMkfhP3VKj8v3e1fTe1qsl8Dt1xIc/5Xu0ymt03m9I7ymxMnLK/pja4sn8qUkKMAjpvNZObtRaKtN2/uxClDitgmXvtcpIEDz8vux1EahWpVp9r04eu5cl42/nZ3Xz/oDju+On/foeW5GoqLXJa3HzrQd36HHHLLTJjeelW+o35lcgsHIXcCPEyqgpygkwSx2sffarHR5HirjPrbADie3rySQndYyJ/X7upk4qMzULPjbqWZZ4hLcXgrUcmCscZ8DctVFlM2Z4epfpjNLqnT87ZBum0sntWt6xe3qWtrG3+6PnzW8tZ98r0PN1noqPhgxb+y/oJZhiq4TYsCjubktOQNf3U+xx5+ZA9/Rny243698R/yjdzsPN/r+dgRiXaw/LT0TW3K4LvqLvnpLMrq2fmsiebmq+PS1vZ+Q3xd1vlZTOsdLifruXflg17ZK2SjjI4/vmLLcJ5uwvv0jMDWS3YUJ+zXGxtYfPg0N+v83MiaxXTysiPO6jJaLG2ET5bLN/K9oMjKcTH9WUuz8B3gJSjylsmGWaZd7HMiW+Cc+LfrVlqumvuJRr6fx4Fk8QEp9InxebzpPUIe4G/1TEkjy/hV89az+pzFlPHK7oP8+80TgM/H/fhEeJnwr0iHsKiBN8fXqresYqNdY7E+AePXaW75p7MYJgPTF1/BWse6EhODv4I/p2pD85jiXSy/Le7oRIcmg9lfLz3mLB88yN9eyd87ryT9VmWrF5X8CSnh21V8iuV/Dy3SLMyd0aJpoi7ZU/XOqu54sOOZTkJPflnFe/+sfwn0oCaceLykAtf8DLwdcmj2991483/K2Au99L1QHBWc+zJ7zMq2cIpQuNjiXZyWqjh0eL2y1HH1p5rU7H3/1Oq7A7moXXxdle97WxZ0s8qHult85MiJR/ihCmzd79a2pt3nxUN7O7/coPy3e+/2KpbaW72Ub1+ecFRP6JnFGKCli/ssHmTlxy2UoFMdO5Hmkfu7fHXCpndH+Z5+4KjAms/CM9Pd36No/tsJvIEVBqpL74ZjW+pJFh+7KyFNDOIasp6Ka8LS17fYR0eiR9C/0XeP6aOnF8gAz9Vth+u9mcajfteHYp8w9W0xRFJj3th3RH64vdj8rx6rLzSj2Hb+cn4FFigA2sVZz5Q/wKrDfdZ/VxduKysrd8t4K/d49796mPgTTbTtZQqqinZjL0cFZV73v0brUe+V/lF1Y0Ekl1wj/NHQxH5f6B2/Y+2zfxHTvfzda93zsm39WYEzi+SdoBf/4oTJ/D/ZhqM3rrvzqItnSHNO+G1FNE1bQqW47e9nzb9K+K7Mo/Lb6zfk+SWqv3KBKcMSR8d334TiZKhe8y+BAPHfx9faru/Kn5Yrg/6blbjc1ZsQr5J+/2bbcpPyZvt4v4GEisqgHWALGzast7UjpPQiTzp/wH48jeaRZpLfpPkcAcCdTQI+4/rF48x+2+xcwfxNJ/HPyvPu+g9zyf7sUjnBPyT4GlX/y7Avzkb3/LGi8F/UoyImG9TqKvd41/UCvIYTCfc7XPnY3lyXvNr5pirndrBSD3MCwLWfAILGdUv54MdVt3R7V/Og/kN/V7PnyFtrqZu3JFkMuANcd9EFvvHlSH9BV+d7pq5xXqty5kp9/u7v/V4vvxzui2JVumCfhRxkhKKEvJcWsJiEa37F6+8L2U2rceC1Kchoda2Lb+EFbv5khk+SFK4ROevkD1+2FyVWwm95saxzsZINrw02VDsvf7+m2i3+MlLDU1qrqBKzDo2xlvH0pJaH6B9PW2kiQHG6lf/srFkYGwV5v5ZrA/I+X+tIoUw7n2YtiBmOuEQjhIJG5w+2A+QX9IPPmn/dZo+15Adbwx4PQCOrvGybprJpwQ46P6e+LJmnzshc8Bm46+nHbOkg85tC3nKqKeuNO+3WPUM3V1Z0/ZeJHqzdn/rZJCn46Cz74LR7faHS9Y/EQOs7I+Veadbcr54KjJxssSf/ZkrtDzBT3PfFZLiWJ7NUSIkKp3Vlz0ckh++rklXeBs3/HSOUjCYfvfU1nQs4l5ELS6KfoMIx89IsamIBRqMbJTa0D7hNWOXrSl/RSVRZyA91s2WL2B++dHA0+xB8ZH3oU0twKeeULx75Fr1qMJQ3Pz8oFJtaGDivCAfXHKGh3H3ZgZTt1DVsxZ3E/UavqHzRx+cnti+j+ymDdqv++SanCvviw0ekK4udhceAZY8+2yBVzSOF2N2suVLMTWBok55khu9DhO+LgZ6d3YDloswvtASy0lWIFcwWDx4UhmR009ecYICVqzUg0y+0s9BledGuyKlKjNavRNeQQanRwXXgV/2a3o6DmT/Xq2cRro8yrnZDPjGXQWvmDLCxeEeHA6CQsn9qAg+yjThusctH/WcP2eQz2Cn2X7qVaJzFXS9QT6lXEfrF188dDSGgF3GBz5btWJElJd96hSfthjbNxJHF/SDkOWgr0DtxHJhdEU1iph7V6bt/3xWBoQNV5/wkMRCafOHh/vpWcqu0PpFUHRoOguFQkd8rWhvYK4lbXdWl+rsDvVLVqYMsJWzb4p+UntRcvDPT9L16WUhJHp8P5qXldepGwuzvGH9vMoZt4t0ZaxSTnXF+deA9E78CgaK/iKutl4i35rbUwMdFujlEVZ9cvr4DZsCjmxb5npsa5586rz/MPbYjlGOJSF3pSqp3LhOiaiMmRfg8voERnWXdt+1HVAMMzQMRY0XFFTVnUd/RAxOjchLNlpTkaql3hNz9nk6uEaLUu1j7n1W6h0xFd9npnG2UEEX6ifT3YFjSbW1Z6smGg+nvoKmEnBwl5fNxaEebWvGm/ixbEKGzsazeapIVRGzJCM1o5Dvn1w3JWaTRUqCi/80FSuc99TgvevHc/48sslStepT+ri0gsFG7alNonGyW6pznTIKvhpBprLi6zIXDssXrkr2eREnXDBqPG/AMXEo+vQClB5N+biXjUYWBr1qV9XHLYrJWkqjWOTb0dRVyBHRmISzfG+ycCPnMcXPGa3kq5/tME34sC+q3AcWmPXDxmqcKv3XbUcKYk3ZI31FUpC90Sz2vJb/rHDfU4hy02oHq2tvZ4wYwd3XjKk3Svq0ywIiv3wNerydGWdsJsaEhEZtW8OtfsG5IVA40NpHTCQjday6x8LhjaFP5MtZS0eFyQGRhHAEfBkjvN1RZ4viaubT9q42nXaeejgZhqEFhn10qGa8NnKKy13V9yV54yYRWLARrDjGhiseHKC8Zf8+FBZNd5azFLVYpuXCiWUY1sR4GSuzshsTheOPvwbQmhlOKnfvbV3Kjd8EjY+WXSKP+vNMfGSzK2z+P7WsOJroHDzUzcY3oZMpFp1SgS1apwla272TXbGYALmOJezTLFOaU+aPNHxhEMN93mFP3Na48PZUKL7i3ngzmplVt9nZOy8bA8yvGhAnhqHRFyI4Lg6bxDfglaSGoXPeM15z6q1v3P1EU1ZXdzLNxex/BF75M+rcPr7Dd0hVLzkHKXy8vvoFPr2n6t+bX+Ktivz4Lf34Jw5h0WuZeRvpn83RxZ0eX3OZNbcdOMh8AOTTCrvUWk8f07UOpJMVgs6D+SEGVC/d35ONJOOVJOcqNJc+brODs5lRJJtjA3DWwOhdn+7JTrtN4faYQZ+SYnlPPNg50saeSmBe7Vn+BCNjA08O8i9F/TA91SDTVhlN3fHs7ZXu3pfsC1zQ2dbcqREXa0uJyt/EcjY+y9LWdyH2D5rdou/33g2q8uqYXTuqLYuhWzliDRxBvRslWxbsVUhj+noumsz3qALrnjwyoTxk6tyzikZu/snxkgydKi9OYGBf5ZqyDpdVr2Gu6XEKJckOtNQdvP1aZpO6jKA7T67nHtGRx9KTucWvHG9c5EW40ZcfThWC4p1MDsOKqGeE8OTFb6/QZrdvljuLPNBs1y6/56r3DCa7pC0LqysLCvfx8W+dTWRlCPHgc2xf562KE+t+5jGO1LJYN4clvGgr99iVyhfdzbHwp8uzSHovRTlVcB3GbvZNmpNmXmpNjIvcFGqjsodxK9RTfpJa0zTRmyRZ97ZVAtZrbj4XbxRhZmtL5q8/o93NnL5y+Y3yjSiRmhYlfbfBVKCTRgjDoXwp+SoM7sK3qxJD5W5AhnSq3JobzmMUxV+DBHpj/5ltRFePmxsWbzz0Q/SkXRO049wkyM8laXy3429ccsr1YkrfKgnJYUOA7pi1yULB/jtY/heRqqXcfty5ut+3p7cs+wsRBQOckDN8W9CBdQNhwGZ6xMcmkV+XMf7c+/025nF6ae4
*/