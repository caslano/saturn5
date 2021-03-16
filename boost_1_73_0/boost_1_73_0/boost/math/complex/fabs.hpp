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
a0yRRmPo6he6rlHfu/YZm2tekUZj6NosdF1o89WKa02RRmPo2iJ0XSP+OLXL5tpcpNEYurYKZx/OsUe5SKMxdJ0qdF3Tbr70cpvrZ0UajZiZsLlOI67DJV3lMQugOV757rkim8ZrcJ1OXMWSbs6nvUttrrEH2TSMq5EYQZjmg/QvmKhrXhuOyCSfvE7E27q6emOU6ktyqRrm+Pr74M56Tvd1tW1IUrLJ/EZUf3NztK8/FY0nEr0JfhePb3K+7Wo=
*/