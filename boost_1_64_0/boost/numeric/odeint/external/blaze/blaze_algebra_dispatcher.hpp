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
4WM5vBp9bJufeDzm2LY2y5/gbxr+P1f6OdbYdtpQiHXMv8oGY9uYQ5D5HeOMbbsO4R4fUY03tm3Ivq/xx7YH2fyuCca2bUj61U84tj031G956yz/482kY9sOpH23mnxsm3qCf46/GHvqv/qXs6W5R9vh/fN/8+H/x5Mjx7bl2POBT8/WP4LPytZvPQrXR45fwFn/SFSOTft3+uPGpv076fFj8/V74Kx/pzgRzxcf36Z/8/Wn/Cv98x4c+9f+zx0c11/B6frb8KtZ/eehsXn5Bs7Onz48tp04lHv9gLbl568f5/evhbP71z05ti0/g9mFf/M3pvhrfII3mv/r/NqXXPNT4XT852jwIUj5e3Sf3r9sdH5+bwzfLhna3T7aB/z86cDn7x/8STK+qhnXt5Hwl5WG+st/nNxsHPwNbt60vh1O8pcGvjjZPy+b3rdX4KFr/YDYt2FI/u3NxO9vDP91/wbH/S1n4c+3hp9nZP7jrL7tzcZvzuZbxvaXhw/Y9wmfjVx/Oodv67D2JXiL+Fkc4weiufnvT+APD4V45/5HeD5kf/R0Ad9eRXwz5v/n//GieH8Q/9wI/+/R4j5dH6mAT/pr/P+Pb+iX8O1aNj54SXx/bPz7Ur5tx9rHlvYtZ+NT4AFbPwa+H1sfbBnfxhgC/98I///8u2XxfZH6UbKcbzuw/dnhdPx6yt+PKOXxSSrSPzgdPyeOX4rrq0V8K66vF9dny/PjR3D6fYn4DM6ur4DT+bfi+LW4vlZ4D7+YpG/tCr6tNSQZv7Iy0gcyPyRezbfNSf5ua/h2GJu/BV+JeLSmb3eS8WnRWjz/TIRn8HnY/YdPPwSpn63j8/2h4HuT6+/ho9H543i+rH0fHhPP4Rux8Qlwun9y5ttcrH0CPjcbXwifiqVf6/m2KPEMTtdPhE9DvIHPxfpX1vfp+HbbwLcJ2P2HT8v6r+EjsfETcLo/D3wi9v3Dp2a/b0N83yT/K+F0/BF8Wzb/ZCOftn/lcHb8UngNH4+tDwun6wMIt425e/D12P4iIr4SXsPZ+JZWeA8fk13/Jjw+Fp7C2fFzEV8Kr+F0fLg4fwefcgj3/o/ZZvz8hfAKTtcnEPGdcNucHz+Cs/hEeAan5Tdx/lIcvxbeivN34vy2BT9+JDyBs+NnIr4QXsHp9y3O38Lp+g5bco+FZ8JL4c2vTsqXwqOt+PFTOIsvhNfi+J2I97bmnsDZ8XPhlTh+K9y24eWzWHgmvBTeCO/h4xD3cu5xLq5fxBfCK3H8VsT3wr1t+fET4TmcHb8UXsPfZvW77Xybn32f2/tWkPpJAx+W5K/ejrx9poFfPARZf31n345g+1/sguOT8nmyq2+bkfaVFs7W36t3Q/2W7T+OzpE1yfWXe/owkn4K7+EzkuPne/u2Cbn+Hn4y8brw7QzixT6+nU76V9N9+fUXcFp/gdP+DeGdOL7tx+Mj4Qmcjo8X8bnwEr6f4c+u8SP7+zY7ixfewdn43+QAvN9kfejsQLTfsPYB+FrmXl8mP8i3lVn7JXxqsj9Ldgh+3xCk/+5QPB/2/A/z+fhJOBvfV8HZ+NYWPj9bP/VwtP+w9ws+DStfwtn6tY04fgdn1+8dwT0RnsNp/R0esf014XR8rfBOeC/cjkT5m3gEn5W138C3Jm5HcS+FR6Vov4TT9XXgWxHv4Wz9l+YY9J8M6fb2eJ7+9nB2fd4J3GP4/cxP9G0vlr/DxyPjd5KTfduNpU9wNj7MTsH9Zc8XztZfSU/17TpWPz2Nv7+p8AzO+rd6+FZs/MsZuL9s/Z0zfRuf5U/wDUm8V/H+tVh4Cl+fld/hYxLv4TMSj89C+zTpv6jP9m05tj/3Ofz6E/h5JP8=
*/