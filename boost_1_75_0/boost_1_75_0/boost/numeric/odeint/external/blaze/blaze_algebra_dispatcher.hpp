/*
  [auto_generated]
  boost/numeric/odeint/external/blaze/blaze_algebra_dispatcher.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <blaze/math/dense/StaticVector.h>
#include <blaze/math/dense/DynamicVector.h>






namespace boost {
namespace numeric {
namespace odeint {

template< typename T , size_t N , bool TF >
struct algebra_dispatcher< blaze::StaticVector< T , N , TF >  >
{
    typedef vector_space_algebra algebra_type;
};

template< typename T , bool TF >
struct algebra_dispatcher< blaze::DynamicVector< T , TF > >
{
    typedef vector_space_algebra algebra_type;
};





}
}
}


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_ALGEBRA_DISPATCHER_HPP_INCLUDED

/* blaze_algebra_dispatcher.hpp
uYFbi0LyJhUROd9Ps4rfC3nTOeznxMEuACfGBcyJvYBrs2wfMCnamyU+p0hXGSilcpT8s86A0vJlMSgZkVjI4DxzibmVlQvehqlnCU99FpN1PCcdFpzE0RSLcJIiPNoc58t8Z4dz3087wZmVITvagJjDSnYTwjr+gWRkhfoItJvWlKU0Bt6ZZxiDpcr/2zFgZc/yO4UdR2NURIzGpWrsaBxjcaORPrL9aFBtsnCQ1yYzl2kdfUaJW85GrzifkV4x4eH2esXrSzvxGa06ZCJHWm6MXuFj8XrF/Td2oleoMye1acu3i6DJe6qiQZO64Aa5484avPGGXlxrKDHxlGgiVnVqBQV24yrqbkIjpS9CokdRtnlNPIpSlzu6EipSobZtNpTQDoaJ0CHPWUIsbvQMYnEr+GSvUF8C5PROYYLXcf3CsyjsCcHPOdDiE8ZKTu4l5vSRJqHkC93xT0s4Z+Lao88reDV3kjeb9P1yQ7+6IY30K2dTO71rKL+f2RS1V0gf+BI3HjmmNgPTPrAQ5mB4aNFD6/uTLjN5UVmjL+x5MlzENl6dRkwBRPxzwBB84aJ1PAujfx2qCNAZFgTJgGZWw7yTtvASaQtP2FL9T/jCkzfZLvfU2FI9K2yX+/f8CjdX/2pL8x+Duz9q9sdUhMXfB7G9TebY7ufU0BCrHyDsTVHYx1bqsCcz/0N0zHvyHNC4AHBWubE/12hsnp3M
*/