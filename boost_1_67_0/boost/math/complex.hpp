//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_INCLUDED
#define BOOST_MATH_COMPLEX_INCLUDED

#ifndef BOOST_MATH_COMPLEX_ASIN_INCLUDED
#  include <boost/math/complex/asin.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_ASINH_INCLUDED
#  include <boost/math/complex/asinh.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_ACOS_INCLUDED
#  include <boost/math/complex/acos.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_ACOSH_INCLUDED
#  include <boost/math/complex/acosh.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_ATAN_INCLUDED
#  include <boost/math/complex/atan.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_ATANH_INCLUDED
#  include <boost/math/complex/atanh.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_FABS_INCLUDED
#  include <boost/math/complex/fabs.hpp>
#endif


#endif // BOOST_MATH_COMPLEX_INCLUDED

/* complex.hpp
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
*/