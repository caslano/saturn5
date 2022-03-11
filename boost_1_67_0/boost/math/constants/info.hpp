//  Copyright John Maddock 2010.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef _MSC_VER
#  pragma once
#endif

#ifndef BOOST_MATH_CONSTANTS_INFO_INCLUDED
#define BOOST_MATH_CONSTANTS_INFO_INCLUDED

#include <boost/math/constants/constants.hpp>
#include <iostream>
#include <iomanip>
#include <typeinfo>

namespace boost{ namespace math{ namespace constants{

   namespace detail{

      template <class T>
      const char* nameof(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
      {
         return typeid(T).name();
      }
      template <>
      const char* nameof<float>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(float))
      {
         return "float";
      }
      template <>
      const char* nameof<double>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(double))
      {
         return "double";
      }
      template <>
      const char* nameof<long double>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(long double))
      {
         return "long double";
      }

   }

template <class T, class Policy>
void print_info_on_type(std::ostream& os = std::cout BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T) BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(Policy))
{
   using detail::nameof;
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4127)
#endif
   os <<
      "Information on the Implementation and Handling of \n"
      "Mathematical Constants for Type " << nameof<T>() <<
      "\n\n"
      "Checking for std::numeric_limits<" << nameof<T>() << "> specialisation: " <<
      (std::numeric_limits<T>::is_specialized ? "yes" : "no") << std::endl;
   if(std::numeric_limits<T>::is_specialized)
   {
      os <<
         "std::numeric_limits<" << nameof<T>() << ">::digits reports that the radix is " << std::numeric_limits<T>::radix << ".\n";
      if (std::numeric_limits<T>::radix == 2)
      {
      os <<
         "std::numeric_limits<" << nameof<T>() << ">::digits reports that the precision is \n" << std::numeric_limits<T>::digits << " binary digits.\n";
      }
      else if (std::numeric_limits<T>::radix == 10)
      {
         os <<
         "std::numeric_limits<" << nameof<T>() << ">::digits reports that the precision is \n" << std::numeric_limits<T>::digits10 << " decimal digits.\n";
         os <<
         "std::numeric_limits<" << nameof<T>() << ">::digits reports that the precision is \n"
         << std::numeric_limits<T>::digits * 1000L /301L << " binary digits.\n";  // divide by log2(10) - about 3 bits per decimal digit.
      }
      else
      {
        os << "Unknown radix = " << std::numeric_limits<T>::radix << "\n";
      }
   }
   typedef typename boost::math::policies::precision<T, Policy>::type precision_type;
   if(precision_type::value)
   {
      if (std::numeric_limits<T>::radix == 2)
      {
       os <<
       "boost::math::policies::precision<" << nameof<T>() << ", " << nameof<Policy>() << " reports that the compile time precision is \n" << precision_type::value << " binary digits.\n";
      }
      else if (std::numeric_limits<T>::radix == 10)
      {
         os <<
         "boost::math::policies::precision<" << nameof<T>() << ", " << nameof<Policy>() << " reports that the compile time precision is \n" << precision_type::value << " binary digits.\n";
      }
      else
      {
        os << "Unknown radix = " << std::numeric_limits<T>::radix <<  "\n";
      }
   }
   else
   {
      os <<
         "boost::math::policies::precision<" << nameof<T>() << ", Policy> \n"
         "reports that there is no compile type precision available.\n"
         "boost::math::tools::digits<" << nameof<T>() << ">() \n"
         "reports that the current runtime precision is \n" <<
         boost::math::tools::digits<T>() << " binary digits.\n";
   }

   typedef typename construction_traits<T, Policy>::type construction_type;

   switch(construction_type::value)
   {
   case 0:
      os <<
         "No compile time precision is available, the construction method \n"
         "will be decided at runtime and results will not be cached \n"
         "- this may lead to poor runtime performance.\n"
         "Current runtime precision indicates that\n";
      if(boost::math::tools::digits<T>() > max_string_digits)
      {
         os << "the constant will be recalculated on each call.\n";
      }
      else
      {
         os << "the constant will be constructed from a string on each call.\n";
      }
      break;
   case 1:
      os <<
         "The constant will be constructed from a float.\n";
      break;
   case 2:
      os <<
         "The constant will be constructed from a double.\n";
      break;
   case 3:
      os <<
         "The constant will be constructed from a long double.\n";
      break;
   case 4:
      os <<
         "The constant will be constructed from a string (and the result cached).\n";
      break;
   default:
      os <<
         "The constant will be calculated (and the result cached).\n";
      break;
   }
   os << std::endl;
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

template <class T>
void print_info_on_type(std::ostream& os = std::cout BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(T))
{
   print_info_on_type<T, boost::math::policies::policy<> >(os);
}

}}} // namespaces

#endif // BOOST_MATH_CONSTANTS_INFO_INCLUDED

/* info.hpp
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
*/