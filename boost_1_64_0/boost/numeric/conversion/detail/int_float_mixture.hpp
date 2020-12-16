//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP

#include "boost/config.hpp"
#include "boost/limits.hpp"

#include "boost/numeric/conversion/int_float_mixture_enum.hpp"
#include "boost/numeric/conversion/detail/meta.hpp"

#include "boost/mpl/integral_c.hpp"

namespace boost { namespace numeric { namespace convdetail
{
  // Integral Constants for 'IntFloatMixture'
  typedef mpl::integral_c<int_float_mixture_enum, integral_to_integral> int2int_c ;
  typedef mpl::integral_c<int_float_mixture_enum, integral_to_float>    int2float_c ;
  typedef mpl::integral_c<int_float_mixture_enum, float_to_integral>    float2int_c ;
  typedef mpl::integral_c<int_float_mixture_enum, float_to_float>       float2float_c ;

  // Metafunction:
  //
  //   get_int_float_mixture<T,S>::type
  //
  // Selects the appropriate Int-Float Mixture Integral Constant for the combination T,S.
  //
  template<class T,class S>
  struct get_int_float_mixture
  {
    typedef mpl::bool_< ::std::numeric_limits<S>::is_integer > S_int ;
    typedef mpl::bool_< ::std::numeric_limits<T>::is_integer > T_int ;

    typedef typename
      for_both<S_int, T_int, int2int_c, int2float_c, float2int_c, float2float_c>::type
        type ;
  } ;

  // Metafunction:
  //
  //   for_int_float_mixture<Mixture,int_int,int_float,float_int,float_float>::type
  //
  // {Mixture} is one of the Integral Constants for Mixture, declared above.
  // {int_int,int_float,float_int,float_float} are aribtrary types. (not metafunctions)
  //
  // According to the value of 'IntFloatMixture', selects the corresponding type.
  //
  template<class IntFloatMixture, class Int2Int, class Int2Float, class Float2Int, class Float2Float>
  struct for_int_float_mixture
  {
    typedef typename
      ct_switch4<IntFloatMixture
                 ,int2int_c, int2float_c, float2int_c  // default
                 ,Int2Int  , Int2Float  , Float2Int  , Float2Float
                >::type
        type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* int_float_mixture.hpp
ASbjMLpbJPv+FCZjG7T88XPOI1iAMO+nMzku/jNz1oJ6I7OKcjxhfsLy3nyyj+smTMYoPSWlDcdFsU0eV7XfW4LJ/lUu/LYm8xpmISwm4uxvrg/KdRvyP0rl+gDzEGb81Ef73WOYl7BuIV97cH2AOQtbOaHULdaXWcgRYSv2v5zBPS0st7Dj98N4XatZSp41zVrPcYHJfInLO60z8wUm+1e3vucl1muYm7Bq9/freOaCyb4H13m5knMa5iLMpWxvrrcPlesqbrPmWVQ3O2dOBL27qH3/DpP37O164TPXP5ibvKflnHncT8BkfjZYVP01x0x53sDuRay5xin3/HklvAX3kTAZv17+FVZxDwbzEbY3MrABxwXmLu/5c4U75xHMRlj7rnk4Ll9gQQYz+rMffDj6JOvSHO29m+5PW8q12sz90hxtj/nbCP9fn27r2Yc5HJdsa/syaAlzHlZI2KqYGZzvV2DWwjombGHtyVTseGlzHddb0ZZfsJkL7Stz3ZzL9eivdfVrwnUTFiQsdYufE/s3l3+/Ndtsjaa3Zz2DuYjrBt0uVJz7Api/sJjtPRtyfUDm+Alrs2LUSrYFVkBYbqc2zVnLYU7CalX4x43zT7lu0qHt9TnWsAaiDzXbBbKG6ObrdJXEdQPGzdEzr2E+wg7fLleJz4PphWX1jXvGOgiT/btzf2QwcxcWKGx36KThjDushLBLXaK8uG/FClNBWGKl2aM5LjB5z+VBEZXYFpi/sPBpC+txPwGTca83974r8wzmJSzuXZKOY7Ywp60+VJbzwR8m4+DUaTvrfCPYf/n5E9bjXhEz1siFrJHZ1nCBb1XWSFghYa+c9nGunBT3/AELevsrkHN6IWMEwz1vFtvBd0+LMK+Fme/S9ihVYDbC+g8JWsY+KFb5tNlBzpVFWlu+w2bGxjC2SYvYlmzruOsi69kqcd03WJB1SgfmxCKuK9lWxHPKV9Z5WCFhpay9jVnLF+t0JsKmng8bxFoAMxXWacGAa4wfzFLY4RpPzVkHlXsOa9WR9aUYzFjY4+jHQ7imKtc1r2rGehaqXFf89bDY/6yCYn29rXwZI8XyWp1mnQhT7N3+JnW514dZCduS74cP3+/CGhni8AW29euKZO5DFrOWZ1vXAFttXwdzFXYmT727nEewIGGv823hd6YuS7S4f4Z9DA/ezj4I+wS78s7zAtfNJdxLZdvSQxnOnEcwneHvm37EfwOqdcrF9xNL+fe2s61nYIt5rLvLcF9hJ1v7zGTfl7H2ZFupr+VOsRYs1+nSDD//8gFWZ9zZglxvl/N52ZbhGl6ANWsFnies7a+HhZnXK/i8bLtp2m8cc3Alcs0wLu9hjz6u78vztLB3f2zQ9kecYyu1uvQWNuX6Ea5HGbBGhra8ga3aed6C+bmKa062vZi/9wlrAcxe2D1L4zTWglVa3F/D5o6rXoR7YZi/3d8xewUbVubXeo7Ldq2dL2F5rPJqv+MOszT/e91z2MSbYTbMwX3adVmwhb7TOFc+7NPy5RksucU4nrl+wNyFrTqwO4s1ZL9O5yls+PPlvzguMDdhhTbn/cZ5BNML+53odZwxgjkLaxXsvJy5C7MWNr/zGq4BkxXb51xrBcdTeV67+r9Z5zfCbISV3OMSxDOzYoNXF2fNOgOzE3bJ980X7m1gcjzveK64xtyF2QqLqtO/JuOgXDdIvywv46CMy4jlH7xYJw7kbMtbT6/qfId7QIlDsT2sPVVgrsJmdA8bwX05TLaz3ZLvXKd7wPTC9rebOpwxUixm9OxIrtMwdzlmJzy4h06FeQsrV28/x/qCcs93Jb3LcDxhjrLvIdc9uL7DrIV9Db3N2mN6MOd1uvY=
*/