/*!
@file
Defines macros for tracking the version of the library.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_VERSION_HPP
#define BOOST_HANA_VERSION_HPP

//! @internal
//! Transforms a (version, revision, patchlevel) triple into a number of the
//! form 0xVVRRPPPP to allow comparing versions in a normalized way.
//!
//! See http://sourceforge.net/p/predef/wiki/VersionNormalization.
#define BOOST_HANA_CONFIG_VERSION(version, revision, patch) \
    (((version) << 24) + ((revision) << 16) + (patch))

//! @ingroup group-config
//! Macro expanding to the major version of the library, i.e. the `x` in `x.y.z`.
#define BOOST_HANA_MAJOR_VERSION 1

//! @ingroup group-config
//! Macro expanding to the minor version of the library, i.e. the `y` in `x.y.z`.
#define BOOST_HANA_MINOR_VERSION 6

//! @ingroup group-config
//! Macro expanding to the patch level of the library, i.e. the `z` in `x.y.z`.
#define BOOST_HANA_PATCH_VERSION 0

//! @ingroup group-config
//! Macro expanding to the full version of the library, in hexadecimal
//! representation.
//!
//! Specifically, `BOOST_HANA_VERSION` expands to an hexadecimal number of the
//! form 0xVVRRPPPP, where `VV` is the major version of the library, `RR` is
//! the minor version and `PPPP` is the patch level. This allows the version
//! of the library to be compared:
//! @snippet example/version.cpp main
//!
//!
//! @note
//! The major, minor and patch versions of the library are also available
//! individually with the `BOOST_HANA_{MAJOR,MINOR,PATCH}_VERSION` macros.
#define BOOST_HANA_VERSION                                                  \
    BOOST_HANA_CONFIG_VERSION(BOOST_HANA_MAJOR_VERSION,                     \
                              BOOST_HANA_MINOR_VERSION,                     \
                              BOOST_HANA_PATCH_VERSION)                     \
/**/

#endif // !BOOST_HANA_VERSION_HPP

/* version.hpp
3LDOUeHXsmD3cHSbvrdiluYyHGfsMNb4QU0bnhOiTbibx4RRjwuKNj1mHDa1hrKDOP3UotCvG0EcT7AOfBEmQhgY4MBrXyIu1YV8OnMez6tFaR2MCSeLNW5nvBLoLO7wEvGtDmVEiO+hQu3W+3PIfJAX89EinypClx0IYSk3j4jVnA3xg3GCq1eEX89DISxN5AhoJn4Wc+4xO+Ktfpo7OBaPPUY+iMsVq+U3yif5UI/SDnh2yRRzf1r2m4038wTz9K67f1lcXj6zUmIJ02871eHnFMaaWIo+YhjCOOM32Mf9gNu/fLPJNdzEudLGhF8vFLr3fCLe3ifdEnoEd9J6fwBb54EAZkChYUJ3pB7yMWIPEceHh3jJPYR89yKMdW3BWbzXnYA/xR7wKz2SDwt/OxG/WR8IPOz6Ez5e63D4gOYDPF1fxik5Nv4Loj3YtgNjI2zh8boVqJdtBxe2kiBP2+aLM1wiNtyf9xLx4f68HOgH48+J2OcQT2mTZQUZxKytyXzrB32MtWeW7yAfCGOnefN+odWU7yC754x0tVouzK9U9a5Bv6OXRbzAeDx0HuqSjOdlQuY1uDflYhdPL5dZ+hrwLwE/ibFtsTefFsTwyMAXSvSnfoWUPdeVvzORhxjjMK4xFPuJvNwjuS+aivuCOR+niosqJnA3Drs4NXp4YnWIvZlfN9KSCot2YJxLD4WwZgcMfBb23jBvkiQbj7v9Z8T4N+QL5cXS8vIipa7EGvHYmG69sCjucickBq9virs30X/W66NiHZwTPIKvYQof/3wYi1coJXY2jMXLlxJbCmPxcqXEng9i14P13Qhjg/U9F8YG69sLY636Yt5IrP/iZh93XhLnv7oJ3D6B819kTfWPGPmyxt6ey9OSh/uKquAxaeN4GwM/GkHzX2qN6/tA1CP0Ci3yLghc6EVb2acpWbb7aq2Izf2D4Bl6SfeYWU8FP/Ei7RD+d4KuXzdkYZO+OvcFRr6gCL+W/S6d6qIyZ8v9o4fRp1ydpg4+HB7OHt+UoIdebMRZ+bjAVfSNgTbZmqAdnJ3GYelXfbTN4rwzFs8j1UF9g1gEhdQh+0EcTIF1nIFDOBMdoycUzgwJ2ApM4zE2b2HpP9Vo524yK3bF/rj0zCDWrF1t7CdsXKWarq5UGKoHgbZoA7HPn0vEc2cNsMaGcagC9ocCp31PzcQbdi9w6r4R5qiPFXlzejS1hf+Aj41uVgdRnKm8573mY0XjIzjaf9zDyv5vI3+Uz9PKnXQzQF936of9RRhrOqgL+6KPQx4AxO/4GD050YeYc3d9LGaQ7BvE7Y3B8yNNfbOTTsXnwfA3Vt6E22GMaVsHtvMADrOO7nvprOGN/aw7nq+nbrVnbeyjYPN3rdE1+BsGceZKgkOu4jjvMLbT7TRU25rYS3g4pDqD8oO9zMNCmdAgvz3OU+fjpCqJfVSmJA5W6yHWHo9uz/Ftu5ylymkVXlQuFKumDfF49MZjKbFUN46pS8Ry/eqw+SXi7HresmSBQ/m0zqgjLyfG2MdKOWdrOmKMw1h7Tsi348bj+d4Mdpcw1iSPbcDWG8bFXpHSZpKApcTBLb0XSiF2OQFLBwGuKIm7ubuL/YbD30QdIda7Kz7OXMibe03cnW8kYKOQNfrkYltNqPbLjE718WbHz9cX9IChmtSqTuRsJt4LCX9nkl73sf74OJMjcNSvU81FTHApgBWZtC/hjODj9JpRx8sBsPkI37NKuaS9Zt/R1EpziFiBKRsnXQbXi+KMa+GwZvDy26YjB2xiRy2cvg7iN4+IH/JL1nDP5NTz7Hy6om32wEyHMHz9LuzRIQxfHdP+lVsfx2rdl9ilwlJOR6Zy/Ibwr+g=
*/