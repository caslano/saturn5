/*
 [auto_generated]
 boost/numeric/odeint/util/detail/less_with_sign.hpp

 [begin_description]
 Helper function to compare times taking into account the sign of dt
 [end_description]

 Copyright 2012-2015 Mario Mulansky
 Copyright 2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_LESS_WITH_SIGN_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_LESS_WITH_SIGN_HPP_INCLUDED

#include <limits>

#include <boost/numeric/odeint/util/unit_helper.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

/**
 * return t1 < t2 if dt > 0 and t1 > t2 if dt < 0 with epsilon accuracy
 */
template< typename T >
bool less_with_sign( T t1 , T t2 , T dt )
{
    if( get_unit_value(dt) > 0 )
        //return t1 < t2;
        return t2-t1 > std::numeric_limits<T>::epsilon();
    else
        //return t1 > t2;
        return t1-t2 > std::numeric_limits<T>::epsilon();
}

/**
 * return t1 <= t2 if dt > 0 and t1 => t2 if dt < 0 with epsilon accuracy
 */
template< typename T >
bool less_eq_with_sign( T t1 , T t2 , T dt )
{
    if( get_unit_value(dt) > 0 )
        return t1-t2 <= std::numeric_limits<T>::epsilon();
    else
        return t2-t1 <= std::numeric_limits<T>::epsilon();
}

template< typename T >
T min_abs( T t1 , T t2 )
{
    BOOST_USING_STD_MIN();
    BOOST_USING_STD_MAX();
    if( get_unit_value(t1)>0 )
        return min BOOST_PREVENT_MACRO_SUBSTITUTION ( t1 , t2 );
    else
        return max BOOST_PREVENT_MACRO_SUBSTITUTION ( t1 , t2 );
}

template< typename T >
T max_abs( T t1 , T t2 )
{
    BOOST_USING_STD_MIN();
    BOOST_USING_STD_MAX();
    if( get_unit_value(t1)>0 )
        return max BOOST_PREVENT_MACRO_SUBSTITUTION ( t1 , t2 );
    else
        return min BOOST_PREVENT_MACRO_SUBSTITUTION ( t1 , t2 );
}
} } } }

#endif

/* less_with_sign.hpp
2K07asZ/5d7hqDiCoSBwrLH1V/6kN9jjE/vekxsQH2w2aixVNbaBRDqAE+xofXA/bZ2Rlq6s17PRPbQ48iboMRujgnIw4mP4umQfRW2KifJw1FZEoRlT0ZXJ1J+8JhiKIc+0SWRPxcFpDgYrhSf4ROrlS3yw8P8438vX30dbaXYTH3y6euLgbTQHHorAuTJFAuIHb8rFxa/83oDfSoLfkcrvjIAqCkhVfm0ELKcAh/ILI4DIyXqRv5atT6NiByiLI8CvJyiWdWaGlS1R3U8Vz+zDiDxlBFEnNlFQfZugByhoqx7kE3fAXyAego0zmB9PBJO6BToRQf3UMd6XRn2nM+w/+zPOL38zRcZ1p6b/Y1/M+UWKL3f7RueXu9+NPr8MiNprn5G1Pbo39vwi6/uyq8RDr3uzMzuu3E/XA1skfI/nCzhh34jG974wRfbRZ2XdF8m6vWLjG+3iey8jWMf3vjSyW/TsRyiasi+Ao4Pzy1nh9SQRbCB269PgI9xu8zsdnWKqERM5xXQ9Cet7/FOJ9eXsM7C+L16PxvriI1uw3tTJsqmUdufr/zKsD78Y/C+lcK4OXbtkS55+Peowc9Ne7TAzoFDRTjJ6urtejz7JnL9fO8mM3R91kukJj09k7Y09yUgIqrNLCEree/onmXbPLxvfjsYbXzNFYPk52ea/NcfijUtbJd6ovN0ZKI6F5/eOafB87l6C5y7N0fC8Lgqed8v6b5D1e8X7r7ULz7bmCDxvjMCznv1cPfvvX+vc+eWNtyTGmEaQPq0jSN/1VvQpZrspFp6nH5HwPPEtA54HRTdA2Wo0dbHe1MWUQMLz0Vf/rfCcrMNzo0nSP19t5zBDOPOYz47rh5mUwgESBdAzPflqm5MMg2vI1qmTjHGeicDl8H0GXKKBU3WgbJJ1TXk1Fih3fyaB8srmTgNl1H3NvfEdnmcyjx5ve575WTPB7ZRX9PMMTfThOtDukO17BLF0mPljm8PMtQiVoNofNHEJp3qOpa+c4iQzZp+EyzMJLkdLuMRhRgdJn/hjc+Q807VwvHaY6ecFiejTyGEmuXCsBnZ6zXGvGCcZ52u09ix++bs+ycgfYZZE43Q1XSY117Etd23/jUBCE8GOdgP33euDfEzwS0vR1Y7arOA/LMTOuPXvdutRCnM7audbZKAVqqG2/s1u/cT96cI09zF/d2vj0FcDjRrJM3QZlZ42O5TBxw0ifyIGN/kzG2CdtsyU5A+k4xiRKSXDmVT8kl9A9yfBExbHshrmwT/TUQtpovfs1ma6sEL38tTSdSYi+qtr91Hm5cQ+Bgq8w7HJ7G72nzc+uDXF/UrRJ4W4jx1kcbJA4aE0izOf8bp+n9AHpHJGBj+yoJ6i8xy1V1vgRj0SS3fvXtg72GSzHh36iaOiCBx/M6dLPkX8pXk8u3M8Ox3/dH6Dcw4fD9fY0kjTsY522w0Po0eWQ4xdEzsBrYdRJpHjP8dr6uoOWkaOYvGkAWoyXUCvAm8lXAxXczshbSydp8UUwOwz/u4EZrLAGP7pfPp+wIqbAeV0qY1XBiC2NUZHLJREcj0lJ8WhF/QFBneiYODb0nI8rHH4LUpSxht56FTUAm1k1sDF+aKMV4Ya2JSQuHsnGQkviSr8dr1wUulUY6utGcWCYDw3rF+oufRY0DRceI5FSWLNC3R9nSx6yoWNNKj3Jn8PruzQa1zZWnPgXASCAgq/rLwvJfrkRfLaIFNHFQgPl+UKNkIq7iWa6lNelgyAl4QCJikD+S/UMiVf7aLb8X/wegRmhDMLSyLjiD1R8j/vMXaffBoTJ/g4fTUpPEY1S1zWY2oCHYCX8eVWN7lTosNnK5Um4wynl5WulUVXvdg=
*/