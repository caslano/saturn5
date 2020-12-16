/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion { namespace detail
{
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37 , typename T38 , typename T39 , typename T40 , typename T41 , typename T42 , typename T43 , typename T44 , typename T45 , typename T46 , typename T47 , typename T48 , typename T49>
    struct deque_initial_size
    {
        typedef mpl::vector<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41 , T42 , T43 , T44 , T45 , T46 , T47 , T48 , T49> args;
        typedef typename mpl::find<args, void_>::type first_void;
        typedef typename mpl::distance<typename mpl::begin<args>::type, first_void>::type type;
    };
}}}

/* deque_initial_size50.hpp
Gs6FE2AWnAKz4TKYA++AuXAXzIMHoA0ehPPh1zAffgcLYAgHSiFsBotgAlwAx8OF8ApYDK+Hi2AevAGWwhvhNrgY7oM3wUq4BDa8gDH4sAlcDi+Gt8EB8HaYBFfAK+EdsAiuhDfAVXAZvAuugqvh3bAU7oR3w/fgPfBjeC88CtfBE3ATrIabofYBnS0wGG6FPeGDcCHcBpfA7fA2uAOWwt1wE3wUPgAfg9tgOayAT8LjcA88C5+C1XAvbMh58wfYDD4DW8Nn4WD4HBwBn4eXwxfgFPgivAa+DK+Fr8AMjq8a+r0k/6h/cwP+13ONBr474HvO0ZBvmNvwTaC/JrAElv/F5by8//MSWh/v/9r4/3baONYbiTE5hpMVMni/KHe2jA3l39vz7xU3q/+eb00ryMtlA3v/wRSl/yBJyd/XUvL33dmOZ1vHM/Ll06alZOelZaTInvCl9jGW8i7HuAnzdzbjdwmzZ/r6e8cwflf0fzyT8buZ+bvT+/Z3m/seT196Sf5bG8NXfBT02e1TeUhzxAGlvqUdQhp4xgHLZZzCk7Av3APj4FNwLNwLJ8KnYR90N7cNDtqHmOVU5znnJ5n/+HOa+3iY+gksgSWwBJbAElgCS2AJLIElsPz/Lefl/T/Dasuvp/z/k5T5/RXy/t4N9oAdYVtt7vBBw/i/T/NcN7ztGTdPMoiRJ9tjZEqMXPlOeIQjRp6WnZ2eNnueY/1cmbPH+vQUx7Q9/bwsiad7x9jj1Li96PVxjzsIxI7rIXZcX/O8fqrYccgEbX1e40e27Nrw+uqDx17bdHTj1VvrN3ZcESTnlZxv1Uh7yQ0eJOPfe8Ae8GJogYNgTzgCRsArYSScCfvCItgProf94U74C/gIHAB/A6Pg8zAGfgQHwc9gLDwFB8NqGAcb4tOlsAUcCsPhMNgRDodJdYyVBb7H998THzufsbGgdoF+tMASWAJLYAksgSWw/Pct5+X9f3a+rbCe3v8v4/1fcmmRE0ByPcjcXIvkjyp5zfX+z0t77TF7yb1jmCdumdhIERszkRbYKFdsZGfl2j/an5eZWasto/kFqr3+kgNvs+ShWY+EYi/qdQN7ub7kgwlu/eLrap+GeU4d/Vh+6Z+QXF6e34haI34OlXoZLHUf9IbLT488Qx1rqX+LUv9qvq5sGVM8Sdp3HPJqNGMF3Ha0D5PQxUMvk/2wq71OpA5c+Xisue46aBxmX5efl+P+HpPF8Z2lvCDRTdbVn/T9yP5saRla68i8jzVvSO4GXe6zhMbG5Sr3Lpc192dYrq9MytU12LhcYQfc5SriCJ7tbC4fchqdz3LNOGBcrq9MymXTl4vm+jmWa49ZuSQH37KGXG/gLTCMbSoPqDm7imyuq46Ua24t15ywtzyvOTYDX4td1xxmN3HZqWleUSI8yjq5Fulyxlnt822qaaOTlGcj6y97025fl0suVyu7Rz7G5CaGOQipAHf5s26w1npd199D1Dles0IkRx077AlbwtbYiHfYcMyQK3QdP8U2H3MyjjzoqmPXHKSjMgcpVI6Po0puv1TXb8e8qbne9Sx1KvUs6/oYzNeyGMzNitLNw3L3TfvfB11fucbqq+/455ZTzN++Zn9zh/2nc4QNs/dZt5j6zcIz7zR+xbZ47dE3558uq3suMHnm41mQ7XQ5SNpKLpF20ALbQ+fYw3LRSxE9dezhUNEbBiPgcDgIjoBj4Ug4E14m+ysOkuc0uFn21wJmO09cycEyBvaAl8MBcCyMg4lwOhwP0+EEmAEnwYVwMrwTXgHvhUlwvee3geT5C98N6mGwlGcIHAwvUfSSRG+SgV5fqbd+cBzsr+iVm+pB0btQ9HqrOZIOmOtFiV4=
*/