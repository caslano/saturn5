/* boost random/traits.hpp header file
 *
 * Copyright John Maddock 2015
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * These traits classes serve two purposes: they are designed to mostly
 * work out of the box for multiprecision types (ie number types that are
 * C++ class types and not integers or floats from type-traits point of view),
 * they are also a potential point of specialization for user-defined
 * number types.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_TRAITS_HPP
#define BOOST_RANDOM_TRAITS_HPP

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <limits>

namespace boost {
namespace random {
namespace traits {
   // \cond show_private
   template <class T, bool intrinsic>
   struct make_unsigned_imp
   {
      typedef typename boost::make_unsigned<T>::type type;
   };
   template <class T>
   struct make_unsigned_imp<T, false>
   {
      BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_specialized);
      BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_signed == false);
      BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_integer == true);
      typedef T type;
   };
   // \endcond
   /** \brief Converts the argument type T to an unsigned type.
   *
   * This trait has a single member `type` which is the unsigned type corresponding to T.
   * Note that
   * if T is signed, then member `type` *should define a type with one more bit precision than T*.  For built-in
   * types this trait defaults to `boost::make_unsigned<T>::type`.  For user defined types it simply asserts that
   * the argument type T is an unsigned integer (using std::numeric_limits).
   * User defined specializations may be provided for other cases.
   */
   template <class T>
   struct make_unsigned
   // \cond show_private
      : public make_unsigned_imp < T, boost::is_integral<T>::value > 
      // \endcond
   {};
   // \cond show_private
   template <class T, bool intrinsic>
   struct make_unsigned_or_unbounded_imp
   {
      typedef typename boost::make_unsigned<T>::type type;
   };
   template <class T>
   struct make_unsigned_or_unbounded_imp<T, false>
   {
      BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_specialized);
      BOOST_STATIC_ASSERT((std::numeric_limits<T>::is_signed == false) || (std::numeric_limits<T>::is_bounded == false));
      BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_integer == true);
      typedef T type;
   };
   // \endcond
   /** \brief Converts the argument type T to either an unsigned type or an unbounded integer type.
   *
   * This trait has a single member `type` which is either the unsigned type corresponding to T or an unbounded
   * integer type.  This trait is used to generate types suitable for the calculation of a range: as a result
   * if T is signed, then member `type` *should define a type with one more bit precision than T*.  For built-in
   * types this trait defaults to `boost::make_unsigned<T>::type`.  For user defined types it simply asserts that
   * the argument type T is either an unbounded integer, or an unsigned one (using std::numeric_limits).
   * User defined specializations may be provided for other cases.
   */
   template <class T>
   struct make_unsigned_or_unbounded
      // \cond show_private
      : public make_unsigned_or_unbounded_imp < T, boost::is_integral<T>::value > 
      // \endcond
   {};
   /** \brief Traits class that indicates whether type T is an integer
   */
   template <class T>
   struct is_integral
      : public integral_constant<bool, boost::is_integral<T>::value || (std::numeric_limits<T>::is_integer)>
   {};
   /** \brief Traits class that indicates whether type T is a signed integer
   */
   template <class T> struct is_signed
      : public integral_constant<bool, boost::is_signed<T>::value || (std::numeric_limits<T>::is_specialized && std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed)>
   {};

}
}
}

#endif

/* traits.hpp
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
*/