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
CQy/ZNq7XdmGfIeteagfN37mo3mXtXLUMzNT8LZqailYX/rLvW5ezX5a6V3hdfnMzPbaGjpopHx+m/fPzzV8YYqaFoUYA5okvOXHtImOpwK5mHuJ8CSG0RtJYLaxQoZwMxsezm53ZVGfdlJ3GeiH/UNG672jGjLk5GycncfVrIzExGykpHTc3a2835Z/QAKBmL/9zb4Nb/ero3Tn0SMEhvYthYxlJifK8K/WIoj9ZSKHkLw2F7k6xucZHyjXTXFUBIRSJ4RhWTzyUOrGtfA1ktVmMWVWf7jGF+aN1TwOTmYywtYdZO96MpokpGqk36kvtMoTuWHSc7vGw8LSh7xOFGZFBAc5L10gRiH2D0Zyp4PPhazG/vLm1E1iAk5C/i8avez9jPfIea7zaMwP8qamKTkv+9M5nsLZchWVat/+ATsOATbesf4sWhOV0GX+41Zcz0lO8f0N0O2UTntIhvOBDX5qUsm8qSaAumejo7LyDyR6Nur2BxIV/w2JBmNK8Mf8XWBVDIXjRRrjdTLL9dvuxcZw/Rj2dQx6vs+RpC7Khm7VYtbYEGruPyDRsna+UMRpg3LkJN1uV8zCBPLfLmJxWhSP03A11Qx2e5E/SOQ5OUPi4mrgpov+h8yGdr4fdy6MLnmxtBp2Ct89XqanqR7K2n93oSZ+GoR/ULKvq4Nnck/B4J+EPZ3e/1Kqbkf5oYbr9tLF/mtD9sPo4p9s
*/