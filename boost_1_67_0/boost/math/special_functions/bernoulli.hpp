
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
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
*/