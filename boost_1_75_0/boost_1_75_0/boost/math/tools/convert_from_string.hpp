//  Copyright John Maddock 2016.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_CONVERT_FROM_STRING_INCLUDED
#define BOOST_MATH_TOOLS_CONVERT_FROM_STRING_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/type_traits/is_constructible.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/lexical_cast.hpp>

namespace boost{ namespace math{ namespace tools{

   template <class T>
   struct convert_from_string_result
   {
      typedef typename boost::conditional<boost::is_constructible<T, const char*>::value, const char*, T>::type type;
   };

   template <class Real>
   Real convert_from_string(const char* p, const boost::false_type&)
   {
#ifdef BOOST_MATH_NO_LEXICAL_CAST
      // This function should not compile, we don't have the necessary functionality to support it:
      BOOST_STATIC_ASSERT(sizeof(Real) == 0);
#else
      return boost::lexical_cast<Real>(p);
#endif
   }
   template <class Real>
   BOOST_CONSTEXPR const char* convert_from_string(const char* p, const boost::true_type&) BOOST_NOEXCEPT
   {
      return p;
   }
   template <class Real>
   BOOST_CONSTEXPR typename convert_from_string_result<Real>::type convert_from_string(const char* p) BOOST_NOEXCEPT_IF((boost::is_constructible<Real, const char*>::value))
   {
      return convert_from_string<Real>(p, boost::is_constructible<Real, const char*>());
   }

} // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_CONVERT_FROM_STRING_INCLUDED


/* convert_from_string.hpp
lcu7cdXsTDZBfevUnu5vqlaDMCUIKr3gqGoupb5C5T03NfI4ZOdKOJakslhoUCTLnQ2LF93sJaBfsSt1lruzNUB3q3nLvB8HF7N+cVKZKczblrjKx90I++S9Ap7JymYcKEU/9G2IkwOmZS3/4ss8fZQZQF6lByh+CbOgHq6QwSU9XufsKGTxQRy1y0UyMWXOY59EUvtQ12tGrXaVvRDrPxc0LamTxxbIdR4pfupwH35cbipZOEK8sxtzEeAlzTsZYfQsB7XU1qQvPt4T0DLrZ7Dc383mei6LfV3nryEh+sEWsCErvr8fDKx1Pmgw7cG5RUyssBMeqW3o9Mr6kjLiJTTa7PGrs0CqAbzDEw8tIuOQcaX8LTYqklm/vuEvRrd6dTaU2+ClAEsPUyjm0Zuivr+qdX0P1bjMFMDKegVrj+EyIr+qoO93EWdaRi0qiV/orpbvN7mmBQb8/NC08vsoXAQbEPWFfH9/uZ6QfH855brqiviIvj9+ZHhFwP18QqQQyNRbtuPAOrH4kMsANtiQZNceGTV2I1u+VL0fWPpFMBCMU1QjbNRBTTBxe0ylZ0Qimqyx8Q07vmQhnK+Qmv6+1OmJr5ugJ27QDatTxgv9ZOhGXM6lDZgj42ypczJ/gyysEx3OnS+2Q1iV+UZ/iFXlxxSWZ9MINOkw6djpU7dr5HDwULgLrhGMj9A10S1NqFaPYcDvwOkKU1npgI1H
*/