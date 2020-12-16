
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2013 Nikhar Agrawal
//  Copyright 2013 Christopher Kormanyos
//  Copyright 2013 John Maddock
//  Copyright 2013 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef _BOOST_BERNOULLI_B2N_2013_05_30_HPP_
#define _BOOST_BERNOULLI_B2N_2013_05_30_HPP_

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/detail/unchecked_bernoulli.hpp>
#include <boost/math/special_functions/detail/bernoulli_details.hpp>

namespace boost { namespace math { 
   
namespace detail {

template <class T, class OutputIterator, class Policy, int N>
OutputIterator bernoulli_number_imp(OutputIterator out, std::size_t start, std::size_t n, const Policy& pol, const boost::integral_constant<int, N>& tag)
{
   for(std::size_t i = start; (i <= max_bernoulli_b2n<T>::value) && (i < start + n); ++i)
   {
      *out = unchecked_bernoulli_imp<T>(i, tag);
      ++out;
   }
   
   for(std::size_t i = (std::max)(static_cast<std::size_t>(max_bernoulli_b2n<T>::value + 1), start); i < start + n; ++i)
   {
      // We must overflow:
      *out = (i & 1 ? 1 : -1) * policies::raise_overflow_error<T>("boost::math::bernoulli_b2n<%1%>(n)", 0, T(i), pol);
      ++out;
   }
   return out;
}

template <class T, class OutputIterator, class Policy>
OutputIterator bernoulli_number_imp(OutputIterator out, std::size_t start, std::size_t n, const Policy& pol, const boost::integral_constant<int, 0>& tag)
{
   for(std::size_t i = start; (i <= max_bernoulli_b2n<T>::value) && (i < start + n); ++i)
   {
      *out = unchecked_bernoulli_imp<T>(i, tag);
      ++out;
   }
   //
   // Short circuit return so we don't grab the mutex below unless we have to:
   //
   if(start + n <= max_bernoulli_b2n<T>::value)
      return out;

   return get_bernoulli_numbers_cache<T, Policy>().copy_bernoulli_numbers(out, start, n, pol);
}

} // namespace detail

template <class T, class Policy>
inline T bernoulli_b2n(const int i, const Policy &pol)
{
   typedef boost::integral_constant<int, detail::bernoulli_imp_variant<T>::value> tag_type;
   if(i < 0)
      return policies::raise_domain_error<T>("boost::math::bernoulli_b2n<%1%>", "Index should be >= 0 but got %1%", T(i), pol);

   T result = static_cast<T>(0); // The = 0 is just to silence compiler warnings :-(
   boost::math::detail::bernoulli_number_imp<T>(&result, static_cast<std::size_t>(i), 1u, pol, tag_type());
   return result;
}

template <class T>
inline T bernoulli_b2n(const int i)
{
   return boost::math::bernoulli_b2n<T>(i, policies::policy<>());
}

template <class T, class OutputIterator, class Policy>
inline OutputIterator bernoulli_b2n(const int start_index,
                                    const unsigned number_of_bernoullis_b2n,
                                    OutputIterator out_it,
                                    const Policy& pol)
{
   typedef boost::integral_constant<int, detail::bernoulli_imp_variant<T>::value> tag_type;
   if(start_index < 0)
   {
      *out_it = policies::raise_domain_error<T>("boost::math::bernoulli_b2n<%1%>", "Index should be >= 0 but got %1%", T(start_index), pol);
      return ++out_it;
   }

   return boost::math::detail::bernoulli_number_imp<T>(out_it, start_index, number_of_bernoullis_b2n, pol, tag_type());
}

template <class T, class OutputIterator>
inline OutputIterator bernoulli_b2n(const int start_index,
                                    const unsigned number_of_bernoullis_b2n,
                                    OutputIterator out_it)
{
   return boost::math::bernoulli_b2n<T, OutputIterator>(start_index, number_of_bernoullis_b2n, out_it, policies::policy<>());
}

template <class T, class Policy>
inline T tangent_t2n(const int i, const Policy &pol)
{
   if(i < 0)
      return policies::raise_domain_error<T>("boost::math::tangent_t2n<%1%>", "Index should be >= 0 but got %1%", T(i), pol);

   T result;
   boost::math::detail::get_bernoulli_numbers_cache<T, Policy>().copy_tangent_numbers(&result, i, 1, pol);
   return result;
}

template <class T>
inline T tangent_t2n(const int i)
{
   return boost::math::tangent_t2n<T>(i, policies::policy<>());
}

template <class T, class OutputIterator, class Policy>
inline OutputIterator tangent_t2n(const int start_index,
                                    const unsigned number_of_tangent_t2n,
                                    OutputIterator out_it,
                                    const Policy& pol)
{
   if(start_index < 0)
   {
      *out_it = policies::raise_domain_error<T>("boost::math::tangent_t2n<%1%>", "Index should be >= 0 but got %1%", T(start_index), pol);
      return ++out_it;
   }

   return boost::math::detail::get_bernoulli_numbers_cache<T, Policy>().copy_tangent_numbers(out_it, start_index, number_of_tangent_t2n, pol);
}

template <class T, class OutputIterator>
inline OutputIterator tangent_t2n(const int start_index,
                                    const unsigned number_of_tangent_t2n,
                                    OutputIterator out_it)
{
   return boost::math::tangent_t2n<T, OutputIterator>(start_index, number_of_tangent_t2n, out_it, policies::policy<>());
}

} } // namespace boost::math

#endif // _BOOST_BERNOULLI_B2N_2013_05_30_HPP_

/* bernoulli.hpp
RnPObPo1iOr/oLsoqv8D1iikMZ+x0d75Wez7Wyjbi/hL5GuL6LcxjK3Xsfn2kL/lwCI53mLslij/By9RjcO7+GSzkOfN6OrVjAC2FX+JfuP6U2CtQ91/hX2/CeXdiY9Hd/B/hOeZIS+7GXtq6GupQvFycNgvR7C8qE71AMFS0ZrhQMFKzgt1UBN8i0MadQQb2z8ce5hgiyN5jxRsVn50/1ew+TNDXR0vWOml0f1faEQ6bQqNydHvfwiWf38YM80ZG30rzkEHV4aw1sjbMdRLIfxF586dwJdfLoBdBL5LQ3l7AKsW2u0yaKRCf+krWNUTo/u/6OrBUN6rkS3ylxGC9TwgjOnR0O0TynYDNK4IYbciR9TvDsF2ROuXSYxtHP3+h2CFUd3mvfBcKdT9LPzlxDBW54DvrRDfo/S7Ivr9D3QV7RufgW60P3oBf4n+/clX0FXl0O9fw5ZXhfZ9E131Dceupl9U4/+2YMVRzm0jsGgu/oCxkV99hE4PDf3lE+TtGurvS/QS0dgBjcNCeX9AB/nh2F3Anghj5jfGPh/SzW4vm68IaVQAFtWwVAEW1bzXEGxHbshLbcFG/jW026GCzYpyWkcIln9kqNM/ClYYnecdByyK/UbQjf7NxybgywphfxasanEoR0F74jLUQUvBijuHsXoePO+Jfv9XsFTPsF9H+l0eytZVsMX3hLJdAo3od9d7g+/jrADWB/4+DnUwEFikqyGClX4WynYNdKO8z18FKzkltNv18LIkuv9Lv2gPNh79tawcwIrhJTrLnypYwYIo/ydYz+hu7kx01Te6/wssOsOYi16iM4wn6Lcouv8Lz5H//QPfiGo5F8Lz4nDsq9DoFNX/CTa/X8jzKmDLQxutBV/5KP+HrgaHsr2PjUaVD2CljG0S+sF2fDeK8y+gG/2b/d+A740o/4derg3p/gKNd6L8HzaPzmeyOghfw1BXuYIVRXuhyoLlRd+A6oLlDwjHHixYz+i+VT3BCiPZ6gu2I5pP/yBYyaKo/o+xEc/50D08hDUGX/Rbzn+C5yhPeCbyzgv94GzBFm+M8n/QiPZWbQWbdXNI4wL4mxjd/wVf9NuP3QU7MPpthEvhpWWU/0P3h4VjB6CXw8IYHCxYQZ2Q5+Hguywcey066BnCxsLf5tCHbkZ/80K/vx3ZpoRjJ0Ijyi3dBey1MBamC1Z1T6i/+4G1DPE9CC8rQ7qPoPuZYbzNw69Sof6eAl/0m/zPgy8a+zJ2Oz0jgC1B3jtDH1/G2OjcaiU0aoc+VIK8W1IBbD326BHd/xWseEsI+xAa0fpgGzZvEPL8uWBjo7PyfwKL9nTfMfb10B4/C5aKcqV78IPojD7zAn5DOrRHecGKjwxhlQTLrxHyUk2wvOh8q5ZgYyNe6gpWNYqZPGD9QthR4Nsdwo4RbFZ05+xEwUraRfk/wXaMi37/Q7DCwaH/nQF/mSHsLOhG68RzBUsdH9qjDbxEvtFBsMXjQ3wXQiO6y9ONfleEuu8l2AnReeMV6PnxUH/9gWVG+T9sFM3Fw+gX1YuOQi89Ql7G0G9ByPNN4MsOdToOHUQ1rndit9yQ7hTscWg4dhr9eoby3gcsqhd9QLCekR88jN3uC/l7HDmi9eQC7NEu5O858EV3X19C9/VD2GJ4eTrK/wlWtCy6/4tsUY5sjWClvUPZ1gGLaoTfE6wg+g5ugZcoP/4x9tgY6vQzfLJBdP8XWH7I87fQiPzqJ+x2SEYA+xW9RL/1ltGRuptQf+UEmxXtPyoKVhDlGaoKVjI7qv8TbP5xUf2fYMVTo/o/YGtDORoIVhTVDjYULHVaKMcJ9Bse5f8Ey/8u1P2p8JwT1f8hW2nopy0EK70=
*/