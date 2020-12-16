/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_LIMITS_07212005_1104)
#define FUSION_MAP_LIMITS_07212005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>

#if !defined(FUSION_MAX_MAP_SIZE)
# define FUSION_MAX_MAP_SIZE FUSION_MAX_VECTOR_SIZE
#else
# if FUSION_MAX_MAP_SIZE < 3
#   undef FUSION_MAX_MAP_SIZE
#   if (FUSION_MAX_VECTOR_SIZE > 10)
#       define FUSION_MAX_MAP_SIZE 10
#   else
#       define FUSION_MAX_MAP_SIZE FUSION_MAX_VECTOR_SIZE
#   endif
# endif
#endif

#define FUSION_MAX_MAP_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_MAP_SIZE))

#endif

/* limits.hpp
d1569vJfnj338T2p195Rtmfk4Jp9HOWI7pe4jwp/3/ygfBWvwTaaQ+wMX9cc3SE4Bf4ZeuCbcD08DDfAt+EWzTXer7nG/ZprfEVzjX+GR+Db8MPAXGEj3Ufp/qoCifN/i8YsbTXH1h621Zx/F835j4excCrsDMtgF7gdxsEHNef/GOymubLu8C3YAx6HPeFXmvtvjs7+sDUcAGPhQNgTDobD4RCYBIfBcXA4vBKOhAvgKFgEE+FKmAQ3w7HwZ3AcfBKOhy/CZLiQNk+Fi+A06IOpcDWcDu+BaXAXnAGfgDODc/G6J4OPhM7Fy4dzlsVnswFmy3eTC8thsXxMV8nHtE4+pm3wB/BB+ENYCbfAgN7yrMh675Deu6R3m/RWSO+90rtdeu+T3vul9yfS+4D0Pii9ZVG6R4M7pNfQ45Pen2kcV2ru++fyYf0CjocPaa75ETgTPgrz4GPQCx/XuN4NN8Gn4V3wl/BeWGWxIzM7sh3PyI69suNZ2fGc7Pi17HheduyXHS/IjpdkxwHZ8Yrs+J3seFV2lEbpng3eJzuawXzZ8Yns+FTH9Wc6ro/puP4LnCSfxmXyaXjg59L/BSyHX8Kt8B+wAv5T+lOidL8GvdLfFCYFfKA6fufANvAKOFJz15fATDgPZsk3M1fjehdSoXrZhnr93/XYqXq/Vh6Ib9Suf8NesJHqbwxT5DuZK5+UDzaD18Gz4BbYXL6ns+WriYEvy2d1GJ4je86F1Gn6rFrC82Ef2FLngVZwDmyt9aHu5egz2R/r12+WwdovQ2T/UI2P4fLlXgSnwRHaLyPhXDgKLoaJcDscDR+Bl8DH4Bj4NEzSeXYs/BCOh3+DE+HXcBLshC2TYTc4BQ6EU2ESTIUpcDpMhTPgIngZvAXOhJvh5XAHnAWfhBnwd3AufBNmw8+gBx6HOZZxo/tJ2hY+brrq/NFNPqYesBPsqf7pBYfA3nAY7Kt6OT51v4gt6vfz+ffDqjdP/b5Q/Z4PDf2L4FjohZfCxTAHFsFSWAzLoE/9vkTnp2XwCbgcvgZXwCNwJWyK/tXwfHiV+rlMeWyuhhPhNXAGvBbOgmvgu6eyfxfhS0Gs+Uzi+HfSnGg3r4mb18TNa/Id5TXJf6ZxnXOblHG8bkV2IQeRL5HWBYwlJA3xIhuQnciBAtc34Ba3uMUtbnGLW9ziFufSGFnwnfj/557wu//Ge4gX8fCeZ/r25R7KKPbx4mhUZ71z6NV7iDhfeF/J+KOPvOx5rOL3/T9m8f2na74kXj7CTlHyk6VYfYTzinJyan+/xel94eEBf7DDdwJGGP7nlFB/bLb5Ss28guJa/YI15ebnkTzsmwgXo68yXJ+vKL/+ebel05ZH/mEHnSPReSBUp14ZakgucvSG9e1Q+dr7Iy2R3kgieo+F6c0pNd8ursP7Y9qXAX3y9wd9vZ5SaG175anObU+4NDyeoWB+cV6w6XXw/4a03ebjbic/ewvpjUFGozclXG9+Vm7DxlRA13rpai5dZxkbocsbpov4kga2KzB+v2rs3J/lYbrozgbkjXdqX16TEJ1qX2WoTjOJyIm170XpCjylN0V8/OVAqC6dvkzUQac1rmio/OyHta9eV8zLYZuOgpyldfBzO8S72I7B3Q55/5PQFTXdlve/Qec3a8yJscGLZn+addj6dELT8O80jDOOQbsNDT7nhX5r4MemHf66okLOBwcdbJmALZl2W07oXBhqz43qF9Vn2z9eDbQRSFtkCDLJOJ7s9jToHIkdEc+Ret9VOR6yinJt/UQ53bmfDtvtOqHzpnM/Beqzxy2VWew5XfYcY/2YNJs99T6fhoxh9ZFZh0W/OoFypd7FvhwZRn8khumf76k=
*/