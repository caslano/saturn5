// Copyright 2008 John Maddock
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_DETAIL_HG_QUANTILE_HPP
#define BOOST_MATH_DISTRIBUTIONS_DETAIL_HG_QUANTILE_HPP

#include <boost/math/policies/error_handling.hpp>
#include <boost/math/distributions/detail/hypergeometric_pdf.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T>
inline unsigned round_x_from_p(unsigned x, T p, T cum, T fudge_factor, unsigned lbound, unsigned /*ubound*/, const policies::discrete_quantile<policies::integer_round_down>&)
{
   if((p < cum * fudge_factor) && (x != lbound))
   {
      BOOST_MATH_INSTRUMENT_VARIABLE(x-1);
      return --x;
   }
   return x;
}

template <class T>
inline unsigned round_x_from_p(unsigned x, T p, T cum, T fudge_factor, unsigned /*lbound*/, unsigned ubound, const policies::discrete_quantile<policies::integer_round_up>&)
{
   if((cum < p * fudge_factor) && (x != ubound))
   {
      BOOST_MATH_INSTRUMENT_VARIABLE(x+1);
      return ++x;
   }
   return x;
}

template <class T>
inline unsigned round_x_from_p(unsigned x, T p, T cum, T fudge_factor, unsigned lbound, unsigned ubound, const policies::discrete_quantile<policies::integer_round_inwards>&)
{
   if(p >= 0.5)
      return round_x_from_p(x, p, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_down>());
   return round_x_from_p(x, p, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_up>());
}

template <class T>
inline unsigned round_x_from_p(unsigned x, T p, T cum, T fudge_factor, unsigned lbound, unsigned ubound, const policies::discrete_quantile<policies::integer_round_outwards>&)
{
   if(p >= 0.5)
      return round_x_from_p(x, p, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_up>());
   return round_x_from_p(x, p, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_down>());
}

template <class T>
inline unsigned round_x_from_p(unsigned x, T /*p*/, T /*cum*/, T /*fudge_factor*/, unsigned /*lbound*/, unsigned /*ubound*/, const policies::discrete_quantile<policies::integer_round_nearest>&)
{
   return x;
}

template <class T>
inline unsigned round_x_from_q(unsigned x, T q, T cum, T fudge_factor, unsigned lbound, unsigned /*ubound*/, const policies::discrete_quantile<policies::integer_round_down>&)
{
   if((q * fudge_factor > cum) && (x != lbound))
   {
      BOOST_MATH_INSTRUMENT_VARIABLE(x-1);
      return --x;
   }
   return x;
}

template <class T>
inline unsigned round_x_from_q(unsigned x, T q, T cum, T fudge_factor, unsigned /*lbound*/, unsigned ubound, const policies::discrete_quantile<policies::integer_round_up>&)
{
   if((q < cum * fudge_factor) && (x != ubound))
   {
      BOOST_MATH_INSTRUMENT_VARIABLE(x+1);
      return ++x;
   }
   return x;
}

template <class T>
inline unsigned round_x_from_q(unsigned x, T q, T cum, T fudge_factor, unsigned lbound, unsigned ubound, const policies::discrete_quantile<policies::integer_round_inwards>&)
{
   if(q < 0.5)
      return round_x_from_q(x, q, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_down>());
   return round_x_from_q(x, q, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_up>());
}

template <class T>
inline unsigned round_x_from_q(unsigned x, T q, T cum, T fudge_factor, unsigned lbound, unsigned ubound, const policies::discrete_quantile<policies::integer_round_outwards>&)
{
   if(q >= 0.5)
      return round_x_from_q(x, q, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_down>());
   return round_x_from_q(x, q, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_up>());
}

template <class T>
inline unsigned round_x_from_q(unsigned x, T /*q*/, T /*cum*/, T /*fudge_factor*/, unsigned /*lbound*/, unsigned /*ubound*/, const policies::discrete_quantile<policies::integer_round_nearest>&)
{
   return x;
}

template <class T, class Policy>
unsigned hypergeometric_quantile_imp(T p, T q, unsigned r, unsigned n, unsigned N, const Policy& pol)
{
#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable:4267)
#endif
   typedef typename Policy::discrete_quantile_type discrete_quantile_type;
   BOOST_MATH_STD_USING
   BOOST_FPU_EXCEPTION_GUARD
   T result;
   T fudge_factor = 1 + tools::epsilon<T>() * ((N <= boost::math::prime(boost::math::max_prime - 1)) ? 50 : 2 * N);
   unsigned base = static_cast<unsigned>((std::max)(0, (int)(n + r) - (int)(N)));
   unsigned lim = (std::min)(r, n);

   BOOST_MATH_INSTRUMENT_VARIABLE(p);
   BOOST_MATH_INSTRUMENT_VARIABLE(q);
   BOOST_MATH_INSTRUMENT_VARIABLE(r);
   BOOST_MATH_INSTRUMENT_VARIABLE(n);
   BOOST_MATH_INSTRUMENT_VARIABLE(N);
   BOOST_MATH_INSTRUMENT_VARIABLE(fudge_factor);
   BOOST_MATH_INSTRUMENT_VARIABLE(base);
   BOOST_MATH_INSTRUMENT_VARIABLE(lim);

   if(p <= 0.5)
   {
      unsigned x = base;
      result = hypergeometric_pdf<T>(x, r, n, N, pol);
      T diff = result;
      if (diff == 0)
      {
         ++x;
         // We want to skip through x values as fast as we can until we start getting non-zero values,
         // otherwise we're just making lots of expensive PDF calls:
         T log_pdf = boost::math::lgamma(static_cast<T>(n + 1), pol)
            + boost::math::lgamma(static_cast<T>(r + 1), pol)
            + boost::math::lgamma(static_cast<T>(N - n + 1), pol)
            + boost::math::lgamma(static_cast<T>(N - r + 1), pol)
            - boost::math::lgamma(static_cast<T>(N + 1), pol)
            - boost::math::lgamma(static_cast<T>(x + 1), pol)
            - boost::math::lgamma(static_cast<T>(n - x + 1), pol)
            - boost::math::lgamma(static_cast<T>(r - x + 1), pol)
            - boost::math::lgamma(static_cast<T>(N - n - r + x + 1), pol);
         while (log_pdf < tools::log_min_value<T>())
         {
            log_pdf += -log(static_cast<T>(x + 1)) + log(static_cast<T>(n - x)) + log(static_cast<T>(r - x)) - log(static_cast<T>(N - n - r + x + 1));
            ++x;
         }
         // By the time we get here, log_pdf may be fairly inaccurate due to
         // roundoff errors, get a fresh PDF calculation before proceeding:
         diff = hypergeometric_pdf<T>(x, r, n, N, pol);
      }
      while(result < p)
      {
         diff = (diff > tools::min_value<T>() * 8) 
            ? T(n - x) * T(r - x) * diff / (T(x + 1) * T(N + x + 1 - n - r))
            : hypergeometric_pdf<T>(x + 1, r, n, N, pol);
         if(result + diff / 2 > p)
            break;
         ++x;
         result += diff;
#ifdef BOOST_MATH_INSTRUMENT
         if(diff != 0)
         {
            BOOST_MATH_INSTRUMENT_VARIABLE(x);
            BOOST_MATH_INSTRUMENT_VARIABLE(diff);
            BOOST_MATH_INSTRUMENT_VARIABLE(result);
         }
#endif
      }
      return round_x_from_p(x, p, result, fudge_factor, base, lim, discrete_quantile_type());
   }
   else
   {
      unsigned x = lim;
      result = 0;
      T diff = hypergeometric_pdf<T>(x, r, n, N, pol);
      if (diff == 0)
      {
         // We want to skip through x values as fast as we can until we start getting non-zero values,
         // otherwise we're just making lots of expensive PDF calls:
         --x;
         T log_pdf = boost::math::lgamma(static_cast<T>(n + 1), pol)
            + boost::math::lgamma(static_cast<T>(r + 1), pol)
            + boost::math::lgamma(static_cast<T>(N - n + 1), pol)
            + boost::math::lgamma(static_cast<T>(N - r + 1), pol)
            - boost::math::lgamma(static_cast<T>(N + 1), pol)
            - boost::math::lgamma(static_cast<T>(x + 1), pol)
            - boost::math::lgamma(static_cast<T>(n - x + 1), pol)
            - boost::math::lgamma(static_cast<T>(r - x + 1), pol)
            - boost::math::lgamma(static_cast<T>(N - n - r + x + 1), pol);
         while (log_pdf < tools::log_min_value<T>())
         {
            log_pdf += log(static_cast<T>(x)) - log(static_cast<T>(n - x + 1)) - log(static_cast<T>(r - x + 1)) + log(static_cast<T>(N - n - r + x));
            --x;
         }
         // By the time we get here, log_pdf may be fairly inaccurate due to
         // roundoff errors, get a fresh PDF calculation before proceeding:
         diff = hypergeometric_pdf<T>(x, r, n, N, pol);
      }
      while(result + diff / 2 < q)
      {
         result += diff;
         diff = (diff > tools::min_value<T>() * 8)
            ? x * T(N + x - n - r) * diff / (T(1 + n - x) * T(1 + r - x))
            : hypergeometric_pdf<T>(x - 1, r, n, N, pol);
         --x;
#ifdef BOOST_MATH_INSTRUMENT
         if(diff != 0)
         {
            BOOST_MATH_INSTRUMENT_VARIABLE(x);
            BOOST_MATH_INSTRUMENT_VARIABLE(diff);
            BOOST_MATH_INSTRUMENT_VARIABLE(result);
         }
#endif
      }
      return round_x_from_q(x, q, result, fudge_factor, base, lim, discrete_quantile_type());
   }
#ifdef _MSC_VER
#  pragma warning(pop)
#endif
}

template <class T, class Policy>
inline unsigned hypergeometric_quantile(T p, T q, unsigned r, unsigned n, unsigned N, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::assert_undefined<> >::type forwarding_policy;

   return detail::hypergeometric_quantile_imp<value_type>(p, q, r, n, N, forwarding_policy());
}

}}} // namespaces

#endif


/* hypergeometric_quantile.hpp
AL5lD7F0W4+eRCzcbAw35+eFxUDkA4cCFY13uRCHplD/XBVF5EX7B5xoPel71TB0U69o9CmctpblJip9kSTTzluazwNzimZr1PtV2gWNEDfA6kCDDUNaigwhfGeV+vKM0LL8st9LyVUzZYKdgd47AgocjIWal7G2tbABdGmz0wWqKTchWNl4/QqGzsLoycIIWfo9C352QWg03WMNgpcnapj9UKavAGRUU1WgcFZEuErF8oVrye5fy9siYT5X48CnTgklmbVhPTC5lVirarQTgbq48U6b3PALaMsZqd6gSOMw/261USNHaZORKTgdPK2LB0w5sU/rBdzkIwSb/JSeDpQ/s/EBsqnhdxRMgb4lLA/rmPcSb9pz2l5FSsgppKq+92vtPIPrGVPJeGK6Ki82dqUKkk5oY71cZnBB3d20TFV42GSmqqx3fdTUcpNw4hpx9dPCKPCi53jTZ7KegbNoX3D9b3ETpq+2UFPs2os/Qk35IsjCkokF+Vuh9uhm83Wu/jkwT+GFq+ku/YRN5wfLYAoaDaBUkuv23VY9effRUeJGSDV1pOCnReaKqEVH71q3CmLGR1GQfPhCOmp3t9CaYfGa69GC5YPyt9JxbayCtaDOdv/w7Pmg0bbEgXmcvQONBYIfOTYsJjvNTebtBqOZsN/lkKQW/LrJBYfgMYqKKlIKLIFXijUMtnGBN9I41ZJ2Gmb6GrEFhZ88iPFEMgd30oIp7YbM1wWHHoP+6BgTEeZp8+O40shVNVOvnfjbPR3CjFD/UexOX+qS9I+xgiiCXNBTV0VnRTEhZSU8LAYy0qoYcmexCpkEWTFKwMzNtYW1G7FgwtYgsLaXo5TcnXD4gIK93YoJeOChj09YM4TOceRxq9V6AFYM7TSINc4ZhoWlvqnxVtZxbe9MOXO9QQobXWbcVPnFLc5whALb2799GdRda46/oHxBA1zXDgVfUgjOKPNvyUo4gYxCxGh2FRLxIwDR0HhbN6rlhQfsrBsIUnC98J61AIUm9nJDw2badkoQcsjKD31MycxNeo7EXCa32vjiWyzHGhInCfvqTAjpSVPRHrglE3nyj3MuBBI1krYYO1o9G7qpJtevUlbBAzzVKeGaPxn0JQprxvNV4zmIBhqdPOn6e9YzBhX5o3OvUEM7RJVtHJOV2v1pYj5uXlMB3y0jKARUUnDsYPJaU8UFQ5xFQ5248MQEUIteGMhaQPY6/LYV/1QDdDyZojTlKX0+Y30J8XjrykGE5Pjh8HTXgsItt2EilexBOtj2nG/tP+A8S/KbOfB/wp3Y2okZ09/naMMyF68aze5bi4dx0vfef/4i6B1RugRpc1tLVrMZHjPkCWTH8uGr7Nwev1ndvhM7epEF6EwiL+cbV0GUISqE445mGOtrJevNzVFuRQQG9PuzIYlrHaXRUxn/gjfwE7k3E78ARl3YvyvEM3DCx922GWY+lLJzzwi4QUfZiuld9cPAFA4SzecrgNqonEm6x/M+41kohcF2NPidjX6V30orY/s1d39EGCdMxtFnCfqWt7Rma3vZUuxe06FSEu36InArgmaYAX0WitadHRa+c+qe/f2X+atrnNb0M6Y1vN9yfjlJ0HnN+YaQFpjBxlOczCewc6/PyEy+2o4CVl2VqZdnDPll/9AcLGKFXnzdz8nuXHIgdjsZszjB62iF+NWUez+ScSVGXADmnOTX59/krzNqjP3NnDFblGGU4EX3ioil/kVeDP3V1kOXh9P2fjute8etIgYtXXLjjHIxMXmkhl/61VjTnLZMFAZGuwmd8S9Sg834ICcJ6vj0D8tIWcvX5ZZzQp6jkUe46Fbhhf6Pxwlcntgbj9UlH+8dzjGYPrmX4HPJn7rTQIY87sPUUneyyeI5gsabr9zzXVTZHP2CySGPKLLCvy4caHHclCfQkYqCHqMk+vvnUHGSzb7JG7tVLzwkr3MuE2FoeEwWIvwqNvOXXfsGx9frMUSG7PH8abqzgvSPMD4IdIwVO18P9ooK08cP4od4IrZfS1MZduk6nxR5N2P9UCOPtkQxrz4MIBuy88nD6XiXx5soBXtOGF2i4F63nK00bsPakO9Hul4RPqZYSglPO208UQ2OjFaoWF/N8sNu5ixhDkv3MEWhV+AKBjGEW9xUid+g5xnSVG7CQAT9PEIHhP1J2uMiLcCDgn7eqe+JcTBAusX93UTy6LtGO5DAIIIwOK4dgslx/KVEwCgH5ssqKqc6BAgltZAgCF174X6Eqi2OFoM3/c2dibCxm6j8zVF3Z1gsczgzTt7rHPLNQhS0Z/cpw42fFDmT5wa2FU0Ivfcyit2WK/eCsSsqm1z5g1o984TwUOvRv9/uLaiy3j+FHAkWXtB5+SF83D5bf/l3PUAaDPveGVQN94IzlsozQKzl87btesFFGmyod1zEbeYapkhIptijWeC9uP+aAbXKAAQs+9N7USFS7RdIFuo5HZEeq3o/wIJuU8wvd9xjEdVFWchVDvDf3g9cHQEqRJGnp6IYa1x+d/haw9/hG8LFhHRNJa0LZxhKPmnnpii/up4GfvCQemuaWiwCY9th2/lz8NV3gmdq6+AbmDbHddSHeaZW1Y9y/bcTU6ic/ByHuA30XjV1cXQ+gkjPUSa4eoN3ziCP+Zsaq46fn12WZKVld51sk+iPgMmyp5fG4i3Q2qhrIz58PePOLyn7Zu85aGmlzG8+0GnRP+DhnMPY8jTJONtAuAusIMJw/MezDUyQYoUYbC8ICLWVNT6I55xT1ZGsPnD9l52ozpDKuKbbLQ9YWiOROAQ/cJw6PdDjLeSFQurzjD6hlpwwLdJ5qrvKeZfXBwL/zq5gSRSnhsmOIRNG49Y8njsngwY7cUXwVqHD4tc/hAJBGo20hZr7lM1pi97Iqv6M7aKvtI9cEhiirRyS4lWKw3cnQ0BxNSbtcBgNbbEp3uhUnpbUqHl370rgqsbo0E2Z4b1ftJF/05FFYGEY6vPWbt3cOmPALPN0l912x5LU88K7bHPqVfZSelFoD9F5fV63LsVY9xXbJVSEXIqrcYmbqE9urHVxYuqyBXunJpJEmydHzwdpua/90tNozr3Z6AfvIGNuOJMQp8EXJALVe+n49GAP03ug4JxsHO8IYF0XRxNt/WJSQK0d2ggvMQytLpkBNf/9fbAuKlejzLfC/OSrNKmoFwxHoJp+1N/xPP2ZPoaYups2a7WY8DdUbtZNm0IGtbfFn72+9wu4xSTErxBS8jRe+IN9gprXzjesdTIeTTgxSIHodz25YAvcDYJwKHSaMBP2/Ad22p/9ELFY4gg9sVok9Xv3MhWcXsubQYNfDUy/Ta/6JjH7uhdUaYO5vC80OZ8Q+7w+zPyS4PS28lBlaWwEXMIqiPoR/y5YbBeB+OTNwHpZjeC02PcNsJ5ZRDLbd7IExIIfDOf1HaTn1pbnvSby6Ei/SYRBQ4PCkuH6TTBzkB3DwU/AHkAHyGDEq9V1fG/44L+mty3qpuP5N2/AHZfMWCwsVXHubBi5O9/D9Ws0f3KPTzFWQeU52h2BgicVfsQ9Y0YYSBU8HQbNX0FypIrCv7I3Nk30uP3qHG8nq7Dre6sVVCoTxU4R74+bZ1znh+6JQETSRoMRjSGZE0FLDEj5kniykeHNgYK5+fZieSL+seKBeyAhjMAObS/wgcDXc+Kh5tfLJaGPpesfUH565VUGh9UQSBJrQMLZm39jjiZhu1MHen09FsJuRiDni18hulrqvyMWDFl4T3995iIeRgmq3i94R6lAiQAuYdKUtQIJeUwFk8Pr3Etcj2JmpEfGmuZplZXvV3NA3rOBZRA1d8ujLVtcb0jcLaP1X9O92+1R1CAJz6kStHUHqiPS3L34W3NMjpqGd2zylJpE9yXWkTKYih2Xb43Xe7kS0hkVkZQ+r+QuKMcSG2CSV0cQTwoXWLiQ7tQagk9NvWexLTjmcMryQVSuwKsFi/g8ipR6bQTW5SUT8Uwy2TLYArNMfqJkjcz4Nx9GNVAtdqUD2VW1M/EvSD/qzEKLoYJW6md1sZ0LctWmLu8NlJuOJSfudp7Sj2zosu2MItpH0vohFosvjtTWKRD9Fbu3pHKRCjYKeDT3NUsccCvtKuk/ofRQkVN8JdxVmNT7/Jp9fuvcrB6fONijdd+zfels/0Cu6dpOAW6gJ3vpHLPJFjxEVM8Tuj9ysA9mRZnGY8qc44Y+Z4UtuiMKVHUFAqEx21JFNDrQqtRcgnXuUGl1DNqNiAqlbDwiaOmAR6uvFd/hUBA0fG6mBOEc5SuehOHHzA2tUwRfUVuq4DKZfAIRTh2EK0W4iiu2RepBR8ZCqb5sSaosEIOTdYlZWHKMNmnZM/j0KQHdy35WtYpR1ri4W65jOmINwolYvigVPOjgavi3NfOSSUTLHUQo6cRbBlgOoequOxQECFGfDA6RV7xDN4yEV6RXqATqoX84UnW9Bem0pCZXxJNz9tI/5r4NY86J+Ekgh6ck/QpIscH5J9/qCI2DWncWtiJVu6NAI6blP+wdfIoDgigbLxh9btWqu9VuC/Gd9reNTuDU3H5IH+3xoy8TQjBrqMJd1Lz0x6gKvm/KFKcoTeQ92hGxBvaPr9Aa/XgjXB6EJxEHxQFqYszQFBhHahepC6tEy1WyYwc1RGfl8yG8G+XxhLdGSKNEb5mSKdKDYKtJCCgQyaoekGVYKaYCSr3uGuiWQwz6cQnijhaPeXdXQx0X/kRSnf9PC+W105zJNx5Xg47xlTbHpoN3m9ElFpkNweUrx4UjCenU/7+XseISjcoIu/MJl7pfHq3TjjwacDs8wIp/fOmwZQ8s2AtVSaaYzRl35Cxbu6oPMX2Cr6JZCNmdYiB+7LM6vA5fITvbK2RA776Fq+tvqsPGPzZUibSLqVXo5WCd7yx7+KDRdQJ5X6+4+iY0dElYhb7A5+hLL36NKY/fDURdYZfBX0LHsaAOqR0tjV4pgjNSUBFKITLu25bztHB3WgivL/kZGi3rN3nlgtTfqL8PEv/TCsXFUqGy/uPNjJhxT/3F+ddVKOwX8IcFCgJM+0C1SS1LvRvadMQMMp87cw72Q6l8m6XGVrZNVlxkXtcAqWr51x5pNSMQmeIKLrxg1TPMETwzrU1Ef6vboqkPOPvBYh7Ixe8drtNxwI0fs68fnmLHpGJqsVX7PkFm5yTQyPgTqMk9MZUCNEyJImsrUmf2EagbSuajptbWzN1ci4emvDgkQBL0aCoxyNtsfA1ueaBlHfdkSAIw+8nw9GxYhaKSr4dyb0zMecFQE5qzvX9h/mBgqkXH2q3NTsRnhSxTNeYmu4UW9/yucGlcK2mKC5g7lP1KLUrf4eFTE8P+VmrAySUxL+/cVrwSLc5Pxnka8OM0Pp/84nbgjR2Fn5CnmPodc8GnTH9Z/hZD6bfb1nQWWxW1ilORpz2+B/NMTU/9lQrft8WCPYuYgH1mE6fFTaYFChFRf23IHO290qEnVHRBTHhXfL3+6u/GF11ViEYfknCZfY0NxzqJSb4VhoiIKY5HnRAL/PvKStExmbFDmYE2Z/KQjgPzPKdc+0HVq61J7A6IjKHEW4oUuMWjSZi69JgCd/FPA1Rwo6ujN7qf+4KSihUZwibfryAItvE7kXDZ7P4rWnj7PAxRuCbDgjSwYWsiJL9+m5V8D9YGF0QcuWxbKjO9Y+EMpLRyR4hF/3umY6T7NyU8zAaQIP/K6nDKK/7C56wRx9bBWfzIfR6kL4UkTJ24oSXgXRpdnQqWo37dUH+9ZGGwqOgV4EGkiYWbjxVGVXgU9AvYUDYrdNvy6+fu5WlswsoZe3UiRzBhkQPjTINkqOtAgRTwOjsl/LgCdnIg5X9eSpseprUTy5RpgXcNMMDty2+YSm8lDd2PyERHbRikhNTQDKfVle/IE54pSJ/WbtSWkoddaWZA+lmPGFBsecY5jSMf4OvVmZbXGV+TH1nNeV4FW18Lxn2poxy0Wp2XnW59e6AOJ9qGGfA+06VbG1GnCiab+d8G3LGLPZ9KzlaYAeJGzkV6zvokCsmjIr89F9TTA3qSnXTz+i9CplezwiJyn+k0KN/Dh0xme6keff4ohXuZ+2i6f8JtLVSAjalQfLkT0gvyj0AVPZFxoTmPJKWbRuYl/h5CXlOXtQIeuMu8z4uZh3PXuQaLORFRqlV2QhFV20e4a7dvI4FH0cDAr1e2wKmn+aJBjdSCHOXlxXzbPuJPTjNw1LXOV0u741RL5thvqIfw+ldZddIqcu7VrcNt8DojN2NCA+olCHm4tM54zp5R8y9psfbQodmr33ToR1UWYsGn1xCrO9mjWUpt7xqeGs/p0EXVv9vttVuvq41lT17Ojk+ZLcbZbiWltfrmud2s8N7IO5V99vL3lCun1DuIYUznQMSJ0a5E486GN84gF5Pz0MnIqqBh5VSQyeS/Wvpf003pBJMk9Fymlw05riS4mqaYio9vXSzknvr/VHjhiUfAZGHYRsc6YY5HsV2ZFqmVYp299q4d6e4qU1XtAqzo2d9I9M7JLyHZo07iMDb1F8QPnm5HzqCQ2xhXITkjO7tlOIcVRfPO9L12GB23WdZ055MUEDBhc//Wx7a6m6NVUaZKpSO6u1cQRE6LvFJ0WfbhPNkzEP2pEZt2nQxhMC3jaV8SnkoB6zekNGBlujI1Y8xLlx2DXRMp0StxxNoH18etEmF3ES+Xt4Xs6yP827vHGR0Sa4clAc3Jb8/+piDrZNt1GJBSFtRUDGRX9isn1IUz9OlDtlAwH4kFVTCCk+Dr60qrtWepEip5KHdYIbQtFN0n9Nfa+KHzZAnbQYA3JIEWTit1yNE0+x9gmYK2/LWl0Dbyf1Jybxdyw8PmpGjaT8Bfrfv+Vj5uoMcCIem6rmpcSBiyH+AaUOBKRWx4TMmTfwkbHZhSZ8Veajxm5gpMzxeIPc5OypieX60P07jCqcsv9hiBKHZGqftSXIkfOIhVGNxEKe/cmgNRGlz4krWLWefHeFHluIERZyaN6wYStoIH9/tbyU+FiKi9bcAiT07CiMJ9X8HnEzNP4Ss8ycV/LI4r1TLzclcEfDWMOpAQrZu8L5TQppT7ke16JD6h8rwS7TB/w06cnH+DSxysBGDfl09Gyw8QIXdJvf4goT57oHH8OpPba6uCd3mRJLIiSYQdR/ubDMetfwUvBUdr8LcZqmlUbYuPhvyX0Q+lE9NS3TN1cuuKO9C/5Fgl2CY2OWQuRohBVGQQ8GqLp7YIeGGm5xvrmNw+844NnT3T+6kRIoT3p7kQvJtGA7/tch07BGyOqIdBWUZaGIMqDN9tuF49J6YKbCYGGH7QPInY/HxTSe7HwodFyGAMTQ8W4r+b155gZWExnF6O9ZQ3RI2q7GONuCU6wM5COIQBkNTAzxXhtNqLrKE0csZsQnPh6YXlBH8D41J0ebEgdh9wrXCONKf6ZbE/1LBce00I2HYgC/+MZW+Ap2BLV8hWG2Aviwz9bJU5ySsdc4M0AoOyi3k/oLf3sz5rBk96eM9zaVjJLFsQ0sep3Cw1ezm4sqS7Svc69ynvnWHzDFGV9hHqw9djw0ssqNeLr2lffyC5vXcEKfBa0tPP1pBdMzBVMjESisbI7zUSE1S+8ZSC+a9ShzxH1ECCIAoPRCq3+/vk0gKJ3PEP2JNaFWKL1Qvk
*/