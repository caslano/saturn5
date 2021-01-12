//  Copyright John Maddock 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Tools for operator on complex as well as scalar types.
//

#ifndef BOOST_MATH_TOOLS_COMPLEX_HPP
#define BOOST_MATH_TOOLS_COMPLEX_HPP

#include <boost/type_traits/is_complex.hpp>

namespace boost {
   namespace math {
      namespace tools {

         //
         // Specialize this trait for user-defined complex types (ie Boost.Multiprecision):
         //
         template <class T>
         struct is_complex_type : public boost::is_complex<T> {};
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
YjC+63w9QKYv7+J6wJdyPaAQy+I5p+kKfmO6SzLdDZmudClHfotkuk76/Mo91V5YFYOwOrZCP8f08tvK/11Mf49M31imvw+bY3Pne4Fl+jgX13nayPQPyPShOAw74Tjs5pSPgga3X259ZD4DJf1wbIvDHNPz+3T76cfK9FHYCqNl+njH9PzG3L4ek2X6VClHOrbCGU7Tr/6N9OfI9I9hc1wk6S9xLn/D2y+HbJn+GUn/WWyO
*/