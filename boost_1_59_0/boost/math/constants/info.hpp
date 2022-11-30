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
#ifdef _MSC_VER
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
#ifdef _MSC_VER
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