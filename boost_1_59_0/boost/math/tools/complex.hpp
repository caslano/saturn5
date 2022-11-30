//  Copyright John Maddock 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Tools for operator on complex as well as scalar types.
//

#ifndef BOOST_MATH_TOOLS_COMPLEX_HPP
#define BOOST_MATH_TOOLS_COMPLEX_HPP

#include <utility>
#include <boost/math/tools/is_detected.hpp>

namespace boost {
   namespace math {
      namespace tools {

         namespace detail {
         template <typename T, typename = void>
         struct is_complex_type_impl
         {
            static constexpr bool value = false;
         };

         template <typename T>
         struct is_complex_type_impl<T, void_t<decltype(std::declval<T>().real()), 
                                               decltype(std::declval<T>().imag())>>
         {
            static constexpr bool value = true;
         };
         } // Namespace detail

         template <typename T>
         struct is_complex_type : public detail::is_complex_type_impl<T> {};
         
         //
         // Use this trait to typecast integer literals to something
         // that will interoperate with T:
         //
         template <class T, bool = is_complex_type<T>::value>
         struct integer_scalar_type
         {
            typedef int type;
         };
         template <class T>
         struct integer_scalar_type<T, true>
         {
            typedef typename T::value_type type;
         };
         template <class T, bool = is_complex_type<T>::value>
         struct unsigned_scalar_type
         {
            typedef unsigned type;
         };
         template <class T>
         struct unsigned_scalar_type<T, true>
         {
            typedef typename T::value_type type;
         };
         template <class T, bool = is_complex_type<T>::value>
         struct scalar_type
         {
            typedef T type;
         };
         template <class T>
         struct scalar_type<T, true>
         {
            typedef typename T::value_type type;
         };


} } }

#endif // BOOST_MATH_TOOLS_COMPLEX_HPP

/* complex.hpp
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
*/