//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SQRT1PM1
#define BOOST_MATH_SQRT1PM1

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>

//
// This algorithm computes sqrt(1+x)-1 for small x:
//

namespace boost{ namespace math{

template <class T, class Policy>
inline typename tools::promote_args<T>::type sqrt1pm1(const T& val, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   BOOST_MATH_STD_USING

   if(fabs(result_type(val)) > 0.75)
      return sqrt(1 + result_type(val)) - 1;
   return boost::math::expm1(boost::math::log1p(val, pol) / 2, pol);
}

template <class T>
inline typename tools::promote_args<T>::type sqrt1pm1(const T& val)
{
   return sqrt1pm1(val, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SQRT1PM1






/* sqrt1pm1.hpp
toB8wO52Axbwb1oKdNvWJPA4S7jNqpf3sPJponxUlMG6RFSMD4jfVsj7aZ2BZg+jObYsvicSlF1hsPm3M/vNJPKcismPb9zli3vZQBvmLDVFieYF+twPfddTJNtGnRfUMrtMbRvVzsdZQZxrxr5cnG8cEn94DXyCHE3Q9wThc56pbLCTf4cNlpWNOLVP1zJ+yKeCpav9uJbRKZ+lLF3tuyqNtN+ydLW/1rJ5j3zs2cn7HO6Ww9kwnHGFbYjzkuOKjQhb1E+4kO4Vv1PxBWPvdPkyfA6+7JoGX2LpwpiA8484K7wzAR1Dcfgbbd7d2dxnCPwT6e1sxY6Nl4HktOyPwRVlwPvdJTqO0G11JLbPbtH6LPw3i8Vd78foP3Wl+pqDvVT6RKmci7vaJxKMUWpbOSmBZlpol5gjjRhoPcpolTo7lMNtzq3l+oWWo3I+l8rPYqUQPl86Pit+zqf6XZDnlJI/S5v/JZ4Xjhj4epTxVeK19f8hXjaDbHqYbErpHMmJr/tseXzdU/XrvTmJ+y3OmuFMB+6DxH2a/bN1GYKvem0Kt3+xfr3d0P4HWfvL9aOKc/Buv4LvkfJz807SB3hFs+J5N1Vfqs3h9gfO5YJeSTfOPeL+TEJ0P24yX+4pTlj9aSH/o2R6Y3AOizP6ectYnNG/O5/FGf26S1mc0R//MRZn9MPXsbhMQ1yLMvYn8snDzMLdo7jHFGebcaYU
*/