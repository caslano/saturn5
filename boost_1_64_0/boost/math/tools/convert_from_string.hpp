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
sPb5hvw+32dtrFBjmlHOcvta8HLIEe7IfgWHD8vqPdjxxv77gILDIMmLE1zcC2HOp6YGKMVZfQDngTbV2oruAm4cQjq1j6TtexDSKM9yPhg7zGkw1ctLKOjf4qWH7jye8FDEaDeKBNwLONSLBZzY42hvwssPh++WTx87JvBPLZwdO/fyI2xMmy3tKx9p40xb2uXbdQzZwNJe79yjCEN3fu3vz1+3sO3vync9GnDW/aBdH0cfY+NQluwXB44CxnhBVe94PmPQKRnqO0eP6RiocvJHoNFk8pJ+13GNjtVH6b/3sUA37ycNW+w3jiDG9psj68wfbcdgemRXf0LirLvH65LWfvd47aRCR8m7m7vkMU7jPZvyXd/Bv+HdsvbSSmnueZyBwbEl7+BUOl4W4mpFPlRPSYycV2ipIllHXBVHZ1bVv+tlX8Wg4hfNKV21X+wLFayYd5UY1gnS5FkJ5kwQ0hPrI71vHrpbtSlyI79w3SpmEb6hyk2l9C+l4t2C+V7CIwEWkmOUz5GwO12akQ+QXSmG0q1VOXdUYRklhV8w6SwOOUal3qGWzzQABier2VPxXbVJYFTGoEG8jEET5W4WFAlTvce8EF5XiVvm7ZKWVpk4YR2W0qOOLMuK9IOn4n2XZU6aFmXF9cNgqViCLdyLgU+cf6yIIGrdXrvbOBs6flBFGetB1Xb7Zii4SYdjxMJcr9dIBZmqnD/fbdjblVEdFgm8p87Clpq/7nOW842E2SnY+wuSCBqixIL5tp6f2ksCJ4qzvpyJcefUGOcUB06MdKEdPFWfVWdVWX7IXDfmQSD9vqwVeSARYu1TCVNt6t+iyQpYHbp+UNaVJUsOG/V8Q+e066qcENotLgovC7B8sL+d41XOT+F8IK8siF6DCaj1/YTv6PlxvSJzvCjV8iOUVUUOzsPHWWFLPsPPPKQP8FJVTsXCJPO9KEnYOL5F8lwoPtbOy3dwla9gWRKFeRZy10kw+C024nu7ylez3HX9MHBiBm/YnGt6fnVG9HfkPN+Mj/erfGO+n7he6MWYTflYSu/0H9fT8cICTuVJycBqCvrvBagRuKKc6cp0ZByl7+jn+dQLiszzXFkh8CAMV6HLolnojXa+eX++ofIfi+oqCCPuxfOkANLb9sS3tLftzAu8KPZqHr5nGbZ6ELhspsnbotQnMcrkhknsVgwf8bHSKU+jje7Fh88OEd9xP/OyJCl9ptrUL0mfYHq+/CjMYAiGzPBCLTMn9WR1vqIKg9CNU1bjqKoSX8maEmPyu/o7ehjktef6GRvXLqNUXkfamyIvplmVCUyBaY7XUbB3X1hW+Zi0sVD5clYHuZdVQcIcPKERE+lgjKk8FfPrpMpSJ2QV3mTa/uAoNveMWjcnk7hMqsKDLs8vSpW0wqa9YjWtUT8N3DJzMwazlO1rttbLkqeVm+Qud5eM70pcH8Hoe89Wee6ACs89t/KARTxZIQfqYjRlmFd5Ttb/puxKg/TMpnB30lmMGBGDIMYgGHsn6R4ZBvfdt/sukkYwtE73l0nTm/6+EPvYB0HsQRB7qFQZxQ8/7Gvsa5W1LFV++KFKFFX8oMq59zvvPffc9+vIDPkm857nnLude+5+Tu2VTVDFikcfh5k6vtY6s3tGu55BV2VHF1fJl8k40J1zGoLRGnnHBOLArDggul+6BTBXcFZ/eivhumf1hLt1G+KCuopnn+rJp0T2coJ8am1XuEHfnOdR3gzm3J0Qg0vJ5bk149jN+Kr+OT8v9TOviqAR7+h+r31e+syxGXazUk/91ODPz0u7ODxOcc5Lu7h+V97U5lE4kndtm+4E4uAeJB27EX2whejWkZuhH9lKdOuojWKxbLPoxkU=
*/