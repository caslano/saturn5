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
nvXyfvskp29D59ex/X24XO+sUNfW/6SPrf8X6ffz1j5XcV2WYwzhSYwhRirXAe+5ZTlGKA80lORZhuFKmSyRiSZrXfG+OJ6zCDxG/VlLypWTWFYoKYMvfx/F+OEBSr8phaue0ckJZut0Yxje+2hpptPmRLmeMlCup3iUknVP1kX9uyUephrvxScxBLNxAK7AEbgSp+Iq3Iw5uBNX4ye4Fr/GdVhG3rlTH5/HLliID+N3OA2/
*/