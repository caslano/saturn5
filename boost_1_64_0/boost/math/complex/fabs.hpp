//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_FABS_INCLUDED
#define BOOST_MATH_COMPLEX_FABS_INCLUDED

#ifndef BOOST_MATH_HYPOT_INCLUDED
#  include <boost/math/special_functions/hypot.hpp>
#endif

namespace boost{ namespace math{

template<class T> 
inline T fabs(const std::complex<T>& z)
{
   return ::boost::math::hypot(z.real(), z.imag());
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_FABS_INCLUDED

/* fabs.hpp
d0sPdoax9lPtDIrZC3y09nULIvWkRC5oGeUTJroK9PaxbDd8LVgtcE8T26zhrBi8P03z+FdN34+kje24vaR+BcWjiXssUAwS/i0p6xLoH4/dEP0s5FYVogfEqdPAZzEGqsBgAb1bNFvElRmM8gu78X31FK9C4dBB30izWeXRboqtjg3ebpncVRxw6xOBsAulrnbY0KLzvXfxs8pV3FeF1Ft/Ao4WYTQRGIkT8GG410eockz1dJMY1FwccHwDq6pt00PaR9YMg7LefbesaT9C+nDtn3qSehmC3EQ8EC/8wsf9a8ertO05GIEjKwo6MCvGmGbcwW1UH6KuJJaa3rYamCVWCo6Cwc+bt1rsIh2TuLQLqO38lUAMNVcDsa5FzD6L2Q2cEVty/v+QcQbD2HFkxJK1mxN0CWOBFKQm7aZiLqv6W8EUQ1s49snzHRiI2o7gejgQY+kcXqFkg8GTEzIHSboUkgp4HbREuY663ZO6PtlB5kLGbzfIddkxbZ9s5UBjDk9PgFXfNboZtvt53SpM64vqfDaXOX0zuaVYY5+qV6tqPVpgkJfbaIkxrA==
*/