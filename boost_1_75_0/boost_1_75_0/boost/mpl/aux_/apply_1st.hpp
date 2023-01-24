
#ifndef BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED
#define BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

struct apply_1st
{
    template< typename Pair, typename T > struct apply
        : apply2<
              typename Pair::first
            , typename Pair::second
            , T
            >
    {
    };
};

}}}

#endif // BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

/* apply_1st.hpp
CUwuFYrM+1ij/tSA73V+Q2PKWY+ii/URWRkljaVjS14rF9yTApxszOj/S4z7tTqGV/KzW9u3LkshgNWGD1haTJVTrRn4oXO10RbS7eIyUUcD4UQ/vtdc1pY9Iy4xDja5NMZj8vxEo9GsSywumhKJ+DzDtuImTXtDZtrCcMIKfqg9sTPa1z8i755ctqSxjbUfhyZPXx9UW6llIjrmSdYmcnc2XG+om151kLO4n+sM2lbJb9ca78OslwUcVJHgT7mc7151/kLtuXtpErAhHOQPG64GsucxKd4g2q0/rXItrtfu5DIsni7kdZLEy30/msq7SEi2uX11ZhjNrrJ9bVpr8570e/Ae/pVTbkfxXDe6DYE4g4kf9SaNuDLheSdCGZIY4hrBMK1a4kZ8JVonIh9czR0xZAEib/oRXiC5ALoASTmyfXDLP/YNqoI9elEHoY6FUna1Q+3sSAvIoDcgJPLgOPGywqtKP7GueG8HiWbcpTcOqB3BTvkycQdZC3eCbvCfaXGvxhYxQdZTS/jn39FwVHqp33o5H11wr22ZNvPvctLkWOVDsMIkanJgx7iRHW+6GkfePpCWzgfdCDthueuJitFOrVu06KeRLpG2xP5+Z5Ewb/VYU27rvmbjSWr1fu4MKwxmhdAO4vi+7PfS/4H2i0dz5vq0sSaKWqlPgE7pMWa6dBmA70V4w+7W+dpAFL+Pa+ATk12k7/ESRoQY
*/