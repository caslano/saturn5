//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_ASINH_INCLUDED
#define BOOST_MATH_COMPLEX_ASINH_INCLUDED

#ifndef BOOST_MATH_COMPLEX_DETAILS_INCLUDED
#  include <boost/math/complex/details.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_ASIN_INCLUDED
#  include <boost/math/complex/asin.hpp>
#endif

namespace boost{ namespace math{

template<class T> 
inline std::complex<T> asinh(const std::complex<T>& x)
{
   //
   // We use asinh(z) = i asin(-i z);
   // Note that C99 defines this the other way around (which is
   // to say asin is specified in terms of asinh), this is consistent
   // with C99 though:
   //
   return ::boost::math::detail::mult_i(::boost::math::asin(::boost::math::detail::mult_minus_i(x)));
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ASINH_INCLUDED

/* asinh.hpp
uQgn0T3JRli09iQxDGpSLH3snNEuUu2Fqf4IJB9jljJYTUTkAwUVhmxOINARs01ws/NnitbTxuB/luZFbwFGkxjoDhcwXXRhw510CaymywkdP1gN5/PhbLmG7BKGs3VM9n06u6DSSyKzgPe1RUfkFmRVK4lFy/l2Le30pM5VKBC63hjFHPpQD0T37/W9lR5N8PFTZ2ckbS3YVVzMgo/3yNHl9GoMfdo68iqWVDsPNAt0qp/BO26p9nUt9db9+Jl0Xj1TLYYKx7zl2pXkRJ9mCcQbLDckKX4jZ4Lyx59aNXdU5UbOgrzX21fV5IL4+1JHUA81/dsg7f/nepwA+fMLUEsDBAoAAAAIAC1nSlIV9IC4DAYAAA8PAAAcAAkAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfeGF0dHIuY1VUBQABtkgkYK1WbW/bNhD+7l9xTYHOTlUrKdBiTdKunuOswTInsJS1wVoIskRZXCVSI6m8LM1/3x0pyU7cLB1WGrYlkvf+3EP6m99v9GATHhyR/UY48N9KnCj5J0vM13dH0RdwH5T6iP8PGfFhKfIlGsDDIl+gb0WixsoePUfRQ4Y+km/045Pkx4gecQbFSHIsqyvFF7mB/ngA269e/QjP4PnW8y0P9mPBWQGBYWLO1MKD
*/