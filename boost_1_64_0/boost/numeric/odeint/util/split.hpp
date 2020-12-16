/*
 [auto_generated]
 boost/numeric/odeint/util/split.hpp

 [begin_description]
 Split abstraction for parallel backends.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_SPLIT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_SPLIT_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

/*
 * No default implementation of the split operation
 */
template< class Container1, class Container2 , class Enabler = void >
struct split_impl
{
    static void split( const Container1 &from , Container2 &to );
};

template< class Container1 , class Container2 >
void split( const Container1 &from , Container2 &to )
{
    split_impl< Container1 , Container2 >::split( from , to );
}


/*
 * No default implementation of the unsplit operation
 */
template< class Container1, class Container2 , class Enabler = void >
struct unsplit_impl
{
    static void unsplit( const Container1 &from , Container2 &to );
};

template< class Container1 , class Container2 >
void unsplit( const Container1 &from , Container2 &to )
{
    unsplit_impl< Container1 , Container2 >::unsplit( from , to );
}


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_COPY_HPP_INCLUDED


/* split.hpp
jj6fKZyue/9knI40rNDBrPmnac/bjLGiLuLYo1CI1ReZ45CQyjiiw8uJfaU2c40Uf/km/Z3ddhtTPiE2J4T7KkSA08JkUfYtc1boh359kak2P03B02yxPPEou/YzlSfHRcdO84q1b1pi+3Zb/xdcllz/R97nodaMruMfurSL9otM5JzglmqhZpdxxL10sSE6tRhUM572qQIbqEv5QY4fYoij5YGrOati561qDhJJmX+65u5j1tH3WEduNcftKzHqyBSW6WcG05exJaJPqNEngzGBbK2/GcInvKhh/TaEgycKzKAqWqieZkuwv8S2lVtTNd34zPrH+ROKP07uN2vGZ5zuysjb7yrZD50kPvZASFxcLbN95IU8pvxbhiXYwyemzZa4k0/88tvS0M38UmlRu48qUTrR2H10Sf9166X2OAH4GkUAxsTdXeePrwdSBDKnsiOazBcz9fcO0BanmnjBOO1B1c+zimNjr7o5Rj3GkhnqRAo2g384wQxukpeXxcnLCeF2TEggL9dhzj+eMwlG/dotUBSw0WqC30DwDynwlQZ4ikGL1640sNdAhkE4abxauvC2JvWENkpyCHFmc9ezUP2G8BcYqO20mlUz3kwkNTGROahYsOWj86fqENkI1423MrbHyuTSENDXVDzVQovra6TfrJKpFZqpSdQ/iqepbrVhEhtQ85W8moPkETPcSsMkniohoWTTTBYkExV9wShZmOBw456Oy+x5OMuuF3kgjKScfMhYMff9hnRSsI+8SMYHTJYudmwNbJxNt31dVs4/PoyO+UnkB0gZNn6P2N+Pp9uR4+v2Gcb4ukLrbnwpfveDc3iejKxtv/gOugTPBkOoZfIs88alNM4n01gneSU45KwXyrorsYdRSfFqC7yhbr2LTOSEywUxlRUvp9SbJ8TuNhuKbKmAFEc2772LPkdBXKRaI9ecLPJWD+yeNfP4WNUmf0SzdssfgQJCxd74o2RvVD/xnLxAQcNP1WaODbVpEGqd+hJawyuUI/3JqSgNqElFoR/cN0rCPkymI6xsMzoYzgp4vrUTcFgBXDrSIZEVMYARwssnkh2xvFSxI+SfSZMsFksor4aBFnyAFmgJ18SDEKLBk3hFAeNmNnTQuqhnkyxlnNWo9m0aIPxUry5MMVyUDFacbZHgqAqoOBdMiEK1p8lyjdX0ai+Am5dth63SaQorUGmWU510o5xhAsN8okD2M86JA6HSe7ppOUGX43Ym2kjgT4XoFHeSxY7U5FjJI6nh8JWSABZwSmZqssMaISjh2fp7WXC+XClKsTCMj+6ds+reZ63ux/EuwhvGuwfvu3gP4V241ureiv8K/O/DuxbvO3gHo4cU4x0O86V4J8Ns6Zv0WNXPlmI6gDXSt+snva+jK+cePWPGXgnOzt7gqez8b3sS+R3kuJHfwX9j4nqlJuHqelLbuXAVpJgL10+5cOkKZXpyTPw+3o2kLlEkoygW9NGEoHWJQWdIqHnEITB/YUv1NUxZ4yXzTO74J8ZA7EwAMU6BQIczTwrweqXN4+CqdKDL6+dbt3e1PqnyKDaOpFWJAkCLkcSytCtSYkQGM71fF5jp/TPESD6/PdgSJr9ItUbS/rB4pMl3qvcw+yEgamypTHXESK4vZ2kvmqx9dXvsM2rp7xkryKyZ+BvraE50l09UyKHtoHClTxz2majHhQck5U1Kbw0RG8faWEkDtcJDVqluPByQUsinl0psV283wWb45Nqst+tN0ukL1Zex/s1S5XP6xJOXx+h5r9tI4Jviizlsg4PfYL74UBa9nR7RoJ2rlDGflQecPtw1foUsaevlYAD5xbCZsbtaz7fGjuQEzoo+R4M4pYIsHWnceaU=
*/