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
0siP4euUn0jahRrpMWiu7leL8VtxfbO8W82v7u9uVrdjOQE1X5Ysg682QrFVgi8XcMbYCBYY2Q+bqm2L0OnA5h38/rWAMLioXyEb/MGxssoJtH4tQ6w4idPZ2XcO9NMMnO7uRPNZPyDZeoBKRw26jphjhnTDoNEB/iHndRQaH4+Ees5clkAiT8ZXfIAzFvxUKrknycM1fQdQSwMECgAAAAgALWdKUjZ5LVOMAQAAhQIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMDI3VVQFAAG2SCRgTVLBTtwwFLz7K6YsEtlqU2+5IIGJVPVQIVEORaBKpQfXedlYZO3I9rJE6sf32ZvCXuK88bzxeJ5VopiMjtQIZV3neXmmae9DGxtR1z0No1DyHVLywBILscA9hRcKdbQtCRVoHKZMmH8K4+tgyaWZYUrBlFj6GuG8Y1j+L6Gc3rIRswsD5rOh5AGEMn671a49svWGZCs6mB6dD0g9RULae0Q+zjoaMPA3wrq8h9wMv0vjLl3BdhmboANx8861KxZjxMH02hnuyjsb79vSmwXDLGFjhgJ9Emr0HGJP5rkRI2XzhDM/kqtu7lanX358e/y1/r28wnbCabFyveGQKlk9RL2hS5QLL/9Wdc05ROvd
*/