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
a6W04TPh6mwHHbfEOcjt4Mxx2/ppVNpaZHWK3Zh+XAVKXCoPrd9akq/tN9S+C9U/XeLpGunM4H4I7fMs0vQvJ93tFJcmhzS1RUumazBd9XXkNN4cMEvCFUYG8u0tmBfdCGfT0bB+m5H5myXpPEblqfzvPoPeS5V7C8yGIfSPFtAtpW/8BOPdC3Gx4iXgMtUx8/wvxVRn+qh9KQE9gOy9Yn3p83b1Zfyr2tXXKzs15mZk94+KufXz+9zexm1/oXk3X+xnlJ9RPmdOv7pwj9S5oRgZc3sq6Kbx7wyG3Y25KSsoK6Rt1+u3gyVtnIGq7tj52IO6Y2+G7Kn58faN+Xbdss3NQveb6nxQs5dNt0wmhYTmBMLb+rfRmXpM/PfDHqFvRW3jPnFYdJICugBPiX+RkxqYRz4St6RvHJsTrQ+v7P6yl33M3JyhZabnuaCMmZkFtrKTITNcdqY8/ixhTnTyyPkAx6pnTrz2Mu2tY2Zb8R/kpvJvb8wIzALMYuK8ghHvKeLNcpNtZU3c9nGzh6avi/jv7eYQR2/GlZPpoVXMkz+F+/8MJ9nvOEXWMVbjDeuGmTr8VPz3dVoROqbbhGpTUH9PaDqaOm4n9oimNaaDVagympPEf7vcY9CJdJaRxrucIiOz2ba955/bYLsqqssraWprvnm8uGUa+e05FMq1mdR52/pjV1IDY9dw77sBey/s/lh2b0F93debYm5GD+mKgvpj2dkFgbFsN9p2Q2PNfgWmvYt9rNr7hNr/Oy3Mu3kGe0Gzpn19OebdWU8S3iYrbOpnrfjn0L5SLW1Zwwf2Dpd9x71DQD5TyuOB9nb5yQr9wu81HU9gelMetfXLQ4eDxMqjtoHy6KTz8gvi/4hzCP9OwszD3IK5R8KwFvHjCMhPq1vceOIE1u054Dbxv9vpTy5HY0oxKzA3YkL6JWbdNK+wrq8m84XWmIDssOTPT89rEvcDsXi0/XXy9VTEfx32VuQryTkGXAZe4aQHZYhPJ1LTLo6Vb/d2Cqj5Qtb+22mf61vVrf0zUgemRDJS0lKSMlrhFGgbKjOs9LV4Xu7RJ1dX+zQfUK/B9X819sVdElmzJLdeIWlyymbNLE+4jcXfnaLlRrt7pX38Wr5DoW+P1y/YkllfNrbYa4eFFtlY2iGyvDNmQGPym4Acqy+futptSH509+X8GpIXPO0jF/fumeNu33RfqzGfHX/EQadcPH7r7stf2uU+G5YTtctr7r6cpV2ecs/JuTYkf/mJyOTJT84ZJousXl373gwu130x7tCqDKV/9qJnP5MbuU86K3Cf9HD/3EPPUiZruxsQeJu2ud6vnK33LReofd/AW7PVmLEaz2KNpwWmSuO5Rb+/Tu9r/oXKwm0Ee6p7f/B34ADwPpWNuxMcDq4HjwDvAo8GHwBPBGvAMg1HOtBq0P2h7oUna17Wu7H7qqNgbzBdZUlzVOYzDxyqsnXD9P7o4Xp/9KFgicqUHgpeBh6psnNHqQzisUo3SenmqMxplcp4nqMynktUxvNy8HhwJXgKeB04CbwDnAyuB08Fa8Ap4CawHHwenAp+qOn4TNPxOTgDdL0NDJgBzgSzwQqwPXgm2AWcD/YHz1JZvbPBw8AF4NHgQrAcXATOAM9XWb0LwCXgYvAqdb8VXAI+Al4LPgVeD24F16hs3s3gu+AV4E7wSjCD+lkFZoE3a/1N8/cPureZrOd7E7UdHayyT4eCrcDDwBzwcLAAHAN2VBmkvVWGqRg8HuyrskxDxa4yPq6udXUfMBnsiSnT9hJVGZ80sBnYDMwADwRbgOkqg9VCv98S7KyyNPuqLE1/pfdlaob6MjXqfiiYC44G88CjwXxwPLgX+GOwPXg=
*/