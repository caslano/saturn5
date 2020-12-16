
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
2jI67Yho666J0aNfOx8dPhfZqsLCv/9Mstz1qHEusovzvJXhuUg25xZD+4FdB9SFJHUniXQD/XMu5gbNpyptLhdLcZYRYJ6D8ZUuX2/Q9P5wtolpa0UHTqevW0eFvrn8hAri4eJh+HwNJmzp0e9Vk/eaTc8Aq6eyTd7H1tqGTqsC/cEWH/tITEiwqcPS7l0b3wET7OKDtQISbg90C5m0CaCGI6Fyzc9AhJU3SYF5YfdaxaV7t4+ve61Ffb9woLNX8tHTEuwNn8pvOXvEN6mNvPUL1gRYUi8VPMq9lyvkfVeBepp8RiGWQs7kmqrOpYgP5niHMi/rRQLj3NQta7nv3/C3ysVcMTd6vz5+YGMHh+15vUDGZe5+7mPsKoi2bls2Mh8bnhx+Pdz0pPGa+uITpmcWaKcyPxcmY1/mPXB8unvOypNGGtc9eWCxL/5O6VFfO6qtzXvqeQOuXDDo8AfV81D8jPDu9Xp1F84EGldCh5ZgEiuxIlkepP4HuwPG/QN7x8rrd/noNi4oi7amOozt+hy55Smpf5kjGzm3GNtHpM1rS7wldltNrdvOmfYNZq/2xr0RYN416Qclb39nkH0PB++nA/2dspt8tipgkTG5VtSs2rT6yD4iP4niZJ2tOzk5lBPSO7zm9Z/Qln35rpyAV+xQ8oa+Gtut3hYdZV+k3Ip1SiCMs+8dW4a9tl65gVk717/I1d/DW4blJmh5zkxVvt05fC5+CLSK8zaBGvSK71h4xbaRcE98Nz3oDe1Es1fVViJ1jb3YCHfYFjErktcwCdftXFNha7yj/+bW7oGLoXXvXeLWPk+LBcNzV2O7/J6wmKkL1Q9oDPdhH/H8IH20c4Gj+hrHZp4l3MxzGOYsqrHXeMPosk1kOm3Nk3c2oHC8N3QTyCvVJ3OAeKADRLaptphh+vGGtQ1o77jT4LxjTdIxwEy4a+DNtL9WwqU8hY6wNBI+um1ku/kZAgkfcf+dbBN3tLTjEe8jyDbjWunIcLxVgyNt79Cx+XkqYDIMxOb0MK2RfkNrbSPP7WWbeT4m4XJOpw4iYeZcR5IJfW6dZ8vD70vTPXdfl6G++5ygNMGkO4dhqE97R7IZ5tUeAzW3QdYMk/EehuE84Zgyw+WH1c1wwZv6XXljW6+YJrIkpKV17Tl6t8vpsUvujTD5hmfxruaOXu09WAAkTP9+7+Zu8bLR9Gb5UiYN1t+jsKs8TRG5ti3QJxvln0yAEhi+Rxt+0bNkQLQN9Haqd525iodf82sJ9VXQ2hoSCuoINRvbIBVqGWZj7SWd5hb2/6hfiPApUvfhFz9rqKIT7AaNMIM4JnwyqHwRlhGOjCH2zC+oM/cXZjUS7+jk5rp4SWNXb7/5lX/iBYF9oTu9amaWL5BT+n1t5vcJYiH5+mcDTD5ToIPJz/8r0vEMbdro4VZju9zcLb7Vb4T3Srcy4XeJpx15qaLS5+82t0ljhM+5ia4BzXBVbWa43MkVhklf1r24kzZDu/zBooNJzY7eJ7QeI7Gkmc160d5TaoAFfa0dhnOZAAyw8PsA5e/a4e/r7g7gw/rNdbwQ0Si9+v5vUk5HmyJ26zb7YEXCR3tRqGyTQ/YzwwnTGlklsi38Ck0NTVv0gw6rh5rXa/gyhRsH6QltR5HxZOgnn1kyhaB5JJlZTD0lnuFFoqPBRyWh4Z7cHuiWwmrDam/HCypDOtLJKu1rzBDmd7eaVb4vHOY95vegs84lI1Px9bUNyO3WBhxzGjTDw2nQ/K5KLTbkbyv963/5vohDXYIsZS5UIqfjGrzGXRE+rvdW2VdY9OceurCIWaf10tqKPTZvsdPrcZRWabAQeeYuhnMXgPC5kZYZHppXheGcOmo=
*/