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
+QnHbfw+V4lw0vns3hsAOQbcdJs3LpiQbBVuFyZTe2LNHy3llOdJf+9MZOkDY3bUmh/uB4tBN2DQzOFlNJfie2dxj64yLFENK1o0IRLZf48F78hI4ZCpv2Q4L1uwwIoeqpfs/4MMA1GvdbGPL5rm9tsPM+FAuXssWFcMoZ79ABqLrpGFonV8Noh0ky4vOjqLPm+QMo7bvRuSWJwcSnk4pllY16AMRRubVf5UoMh0HBcx3U8Wi0Fv4tDYd5sar9/fgNIdrnXjJf7E2hmAVFY9/5dv81x0NqygP5H5c8OWY4DPkBePLooWezPBpptTssbOlV/VJxXUHRrC84p/ji2J+RfJRniN0zWAQKf3gI+vqhRa70TP54C5PWBlHvj2wdhIETB55Jm7Z7k4ctx2lAfSkvcTP7D1o2q1UoHxWuql/fQixWxuI0WU9P/dU7WpktxyTRzy5aZk69U88RRv6vg81YcvStu+CiTCWsXbzptr0khjqRPFqXyONlaNShbHomcS0Qx+802ikpn9f2Gy6ZEViNVaSDhNvhoNovvttwwFfaE+MzW0UlVUIqc8dg==
*/