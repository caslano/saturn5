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
A73fiN0YQz+j6w42RH/opByg22f842IL/kGNQwfl2gF0uXnWFfeTplkQih92xndDXkZrX4zy3DjZKMHs6fFpOTvxA2IOQKHnkN5HsNPBYzCsZAravkjkBJ/U879HRG50FVsRwe8LalMlAg1QV9d990DU1R8ogkAFO3moW4BH8eQnZMLwNODk0e989deFaJDPd9XofBAk7Y4ugweBO4IQDp9FYfwF9MHAgGfAv4Ce+/8EveDrtwL/FfQK0Qx/4H4n/OKq9Q/cvT/YMQZ0KgIjWPdeNsgO4Ch2z5gPeKWZXZ+afVP77J2VwCa4YCExpC4IMWK3npkYyEx9c+C7MpDsucbivMIW+NY+s7FJZ0aJRqQumc1t2/fxcUKyY4WCS0H7UUki+eq3z2Qb7Fpywmfidr3hcb6GO3C3QMSgS+XPojd+5wort7fUyvnAoUOfH/6I9P7b6HcKROsA9o7wqNm0qgBXtMaPtRbPkLASnRdjAYMKMw3t7AMiWicwox1QBDj1zN5CC/fE0yZoU7fWif9KPWu28+rYrznxdnF+9C+klxwMDABpr14jBsZ+fl09cz+SeF7MkoP7Iunm5Wc3Srrl+qGX+LtLBHCRZH33vfEwmA96V6bJTRhkleLA5eKE4Lf53pauauZGYF+AVTOcEau6WAJR3eV6J44pEnJV/Gen+6CL41/6eMXiFAQrEQEFpgSI6edkgqQE92R7gsF+
*/