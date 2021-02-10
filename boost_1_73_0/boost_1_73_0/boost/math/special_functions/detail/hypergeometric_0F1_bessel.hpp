///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_0F1_BESSEL_HPP
#define BOOST_MATH_HYPERGEOMETRIC_0F1_BESSEL_HPP

#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/gamma.hpp>

  namespace boost { namespace math { namespace detail {

  template <class T, class Policy>
  inline T hypergeometric_0F1_bessel(const T& b, const T& z, const Policy& pol)
  {
    BOOST_MATH_STD_USING

    const bool is_z_nonpositive = z <= 0;

    const T sqrt_z = is_z_nonpositive ? T(sqrt(-z)) : T(sqrt(z));
    const T bessel_mult = is_z_nonpositive ?
      boost::math::cyl_bessel_j(b - 1, 2 * sqrt_z, pol) :
      boost::math::cyl_bessel_i(b - 1, 2 * sqrt_z, pol) ;

    if (b > boost::math::max_factorial<T>::value)
    {
       const T lsqrt_z = log(sqrt_z);
       const T lsqrt_z_pow_b = (b - 1) * lsqrt_z;
       T lg = (boost::math::lgamma(b, pol) - lsqrt_z_pow_b);
       lg = exp(lg);
       return lg * bessel_mult;
    }
    else
    {
       const T sqrt_z_pow_b = pow(sqrt_z, b - 1);
       return (boost::math::tgamma(b, pol) / sqrt_z_pow_b) * bessel_mult;
    }
  }

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_0F1_BESSEL_HPP

/* hypergeometric_0F1_bessel.hpp
6fnztx8f77aRP795eHt6/paP/vnt03t9im+2Eby//nF5+PC0PD0sH0+Hq+X8uqvl/cPN8d359zYV2x8/fHxzdzzdXs2hbBe6v3n+8LicDnd3m9T2tuPhtA/5sLzUzFydX7V82EZ7fDr/Oj3cn85X+v724f3PXrhN4Sby7uPj/XaZbQq219w8bBN8tXy8vzk8Xl57+dBcQbN5mdr/5SuZY71ZHu63kSy/evFy+fLlr5Y316fj6Wr585ev/v3r/3y1/PnFn/704qtX3yxf/9vy4qtvNq3/+PKr323f93G70uNy+OHD4+G0XflxOb7/cHc83Fwu+Pf7ebZd8fJFb3P8dB75Vjb3H7epP769vtsuu03As1e/f/nqixcvf/9y+edtIk5Pdnn0y2O+PJbLY708tsvjennsl8cBHc8u7067yK5iu4ztOrYL2a5ku5TtWraL2Qgl35Vc49mVfFfyXcl3Jd+VfFfyXcmnUt6V8q6U9dF2pbwr5V0p70p5V8q7Up5KZVcqu1LZlYpmaVcqu1LZlcquVHalMpXqrlR3pbor1V2pasJ3pbor1V2p7kp1KrVdqe1KbVdqu1LblZq+u12p7UptV2pTad2V1l1p3ZXWXWndldZdaVUZ7ErrrrROpb4r9V2p70p9V+q7Ut+V
*/