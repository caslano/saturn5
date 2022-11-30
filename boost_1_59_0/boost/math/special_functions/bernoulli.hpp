
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
OutputIterator bernoulli_number_imp(OutputIterator out, std::size_t start, std::size_t n, const Policy& pol, const std::integral_constant<int, N>& tag)
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
OutputIterator bernoulli_number_imp(OutputIterator out, std::size_t start, std::size_t n, const Policy& pol, const std::integral_constant<int, 0>& tag)
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
   typedef std::integral_constant<int, detail::bernoulli_imp_variant<T>::value> tag_type;
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
   typedef std::integral_constant<int, detail::bernoulli_imp_variant<T>::value> tag_type;
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
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
*/